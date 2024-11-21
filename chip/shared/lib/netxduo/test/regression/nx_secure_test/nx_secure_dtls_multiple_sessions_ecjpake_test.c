/* This test concentrates on DTLS connections.  */

#include   "nx_api.h"
#include   "nx_secure_dtls_api.h"
#include   "nx_crypto_ecjpake.h"

extern VOID    test_control_return(UINT status);


#if !defined(NX_SECURE_TLS_CLIENT_DISABLED) && !defined(NX_SECURE_TLS_SERVER_DISABLED) && defined(NX_SECURE_ENABLE_ECJPAKE_CIPHERSUITE) && defined(NX_SECURE_ENABLE_DTLS)
#define NUM_PACKETS                 24
#define PACKET_SIZE                 1536
#define PACKET_POOL_SIZE            (NUM_PACKETS * (PACKET_SIZE + sizeof(NX_PACKET)))
#define THREAD_STACK_SIZE           1024
#define ARP_CACHE_SIZE              1024
#define METADATA_SIZE               16000
#define CERT_BUFFER_SIZE            (2048 + sizeof(NX_SECURE_X509_CERT))
#define PSK                         "simple_psk"
#define PSK_IDENTITY                "psk_indentity"
#define PSK_HINT                    "psk_hint"
#define SERVER_PORT                 4433
#define CIPHERSUITE_INIT(p)         {p, sizeof(p) / sizeof(UINT)}

/* Number of DTLS sessions to apply to DTLS server. */
#define NUM_SERVER_SESSIONS         2


/* Define the ThreadX and NetX object control blocks...  */

static TX_THREAD                server_thread;
static NX_PACKET_POOL           server_pool;
static NX_IP                    server_ip;
static TX_THREAD                client_thread[2];
static NX_PACKET_POOL           client_pool[2];
static NX_IP                    client_ip[2];
static UINT                     error_counter;
static UINT                     ecjpake_init_counter;

static NX_UDP_SOCKET            client_socket[2];
static NX_SECURE_DTLS_SESSION   dtls_client_session[2];
static NX_SECURE_DTLS_SERVER    dtls_server;
extern const NX_SECURE_TLS_CRYPTO
                                nx_crypto_tls_ciphers;
static NX_SECURE_TLS_CRYPTO     tls_ciphers;

static ULONG                    server_pool_memory[PACKET_POOL_SIZE / sizeof(ULONG)];
static ULONG                    client_pool_memory[2][PACKET_POOL_SIZE / sizeof(ULONG)];
static ULONG                    server_thread_stack[THREAD_STACK_SIZE / sizeof(ULONG)];
static ULONG                    client_thread_stack[2][THREAD_STACK_SIZE / sizeof(ULONG)];
static ULONG                    server_ip_stack[THREAD_STACK_SIZE / sizeof(ULONG)];
static ULONG                    client_ip_stack[2][THREAD_STACK_SIZE / sizeof(ULONG)];
static ULONG                    server_arp_cache[ARP_CACHE_SIZE];
static ULONG                    client_arp_cache[2][ARP_CACHE_SIZE];
static UCHAR                    server_metadata[METADATA_SIZE * NUM_SERVER_SESSIONS];
static UCHAR                    client_metadata[2][METADATA_SIZE];
static UCHAR                    client_cert_buffer[2][CERT_BUFFER_SIZE];

static UCHAR                    server_tls_packet_buffer[4000 * NUM_SERVER_SESSIONS];
static UCHAR                    client_tls_packet_buffer[2][4000];

/* Session buffer for DTLS server. Must be equal to the size of NX_SECURE_DTLS_SESSION times the
   number of desired DTLS sessions. */
static UCHAR                    server_session_buffer[sizeof(NX_SECURE_DTLS_SESSION) * NUM_SERVER_SESSIONS];

/* Define thread prototypes.  */

static VOID    server_thread_entry(ULONG thread_input);
static VOID    client_thread_0_entry(ULONG thread_input);
static VOID    client_thread_1_entry(ULONG thread_input);
extern VOID    _nx_ram_network_driver_1500(struct NX_IP_DRIVER_STRUCT *driver_req);
static UINT    crypto_method_ecjpake_init(struct NX_CRYPTO_METHOD_STRUCT *method,
                                          UCHAR *key, NX_CRYPTO_KEY_SIZE key_size_in_bits,
                                          VOID **handle,
                                          VOID *crypto_metadata,
                                          ULONG crypto_metadata_size);

/* Declare a placeholder for ECJ-PAKE. */
static NX_CRYPTO_METHOD crypto_method_auth_ecjpake_mod =
{
    TLS_PUBLIC_AUTH_ECJPAKE,                  /* ECJ-PAKE placeholder                   */
    0,                                        /* Key size in bits                       */
    0,                                        /* IV size in bits                        */
    0,                                        /* ICV size in bits, not used.            */
    0,                                        /* Block size in bytes.                   */
    sizeof(NX_CRYPTO_ECJPAKE),                /* Metadata size in bytes                 */
    crypto_method_ecjpake_init,               /* Initialization routine.                */
    NX_NULL,                                  /* Cleanup routine, not used.             */
    _nx_crypto_method_ecjpake_operation,      /* Operation                              */
};

extern NX_CRYPTO_METHOD crypto_method_null;
extern NX_CRYPTO_METHOD crypto_method_aes_ccm_8;
extern NX_CRYPTO_METHOD crypto_method_tls_prf_sha256;
static NX_SECURE_TLS_CIPHERSUITE_INFO _nx_crypto_ciphersuite_ecjpake =
{TLS_ECJPAKE_WITH_AES_128_CCM_8,    &crypto_method_null, &crypto_method_auth_ecjpake_mod, &crypto_method_aes_ccm_8,  16,      16,        &crypto_method_null,      0,         &crypto_method_tls_prf_sha256};

static TX_SEMAPHORE            semaphore_connect;
static TX_SEMAPHORE            semaphore_server;
static TX_SEMAPHORE            semaphore_client;

/* Define what the initial system looks like.  */

#define ERROR_COUNTER() __ERROR_COUNTER(__FILE__, __LINE__)

static VOID    __ERROR_COUNTER(UCHAR *file, UINT line)
{
    printf("Error on line %d in %s", line, file);
    error_counter++;
}

#ifdef CTEST
void test_application_define(void *first_unused_memory);
void test_application_define(void *first_unused_memory)
#else
VOID    nx_secure_dtls_multiple_sessions_ecjpake_test_application_define(void *first_unused_memory)
#endif
{
UINT     status;
CHAR    *pointer;


    error_counter = 0;


    /* Setup the working pointer.  */
    pointer =  (CHAR *) first_unused_memory;

    /* Create the server thread.  */
    tx_thread_create(&server_thread, "server thread", server_thread_entry, 0,
                     server_thread_stack, sizeof(server_thread_stack),
                     7, 7, TX_NO_TIME_SLICE, TX_AUTO_START);

    /* Create the client thread.  */
    tx_thread_create(&client_thread[0], "client thread 0", client_thread_0_entry, 0,
                     client_thread_stack[0], sizeof(client_thread_stack[0]),
                     8, 8, TX_NO_TIME_SLICE, TX_AUTO_START);
    tx_thread_create(&client_thread[1], "client thread 1", client_thread_1_entry, 0,
                     client_thread_stack[1], sizeof(client_thread_stack[1]),
                     8, 8, TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_semaphore_create(&semaphore_connect, "semaphore connect", 0);
    tx_semaphore_create(&semaphore_client, "semaphore client", 0);
    tx_semaphore_create(&semaphore_server, "semaphore server", 0);

    /* Initialize the NetX system.  */
    nx_system_initialize();

    /* Create a packet pool.  */
    status =  nx_packet_pool_create(&server_pool, "Server Packet Pool", PACKET_SIZE,
                                    server_pool_memory, PACKET_POOL_SIZE);
    if (status)
    {
        ERROR_COUNTER();
    }
    status =  nx_packet_pool_create(&client_pool[0], "Client 0 Packet Pool", PACKET_SIZE,
                                    client_pool_memory[0], PACKET_POOL_SIZE);
    if (status)
    {
        ERROR_COUNTER();
    }
    status =  nx_packet_pool_create(&client_pool[1], "Client 1 Packet Pool", PACKET_SIZE,
                                    client_pool_memory[1], PACKET_POOL_SIZE);
    if (status)
    {
        ERROR_COUNTER();
    }

    /* Create an IP instance.  */
    status = nx_ip_create(&server_ip, "Server IP Instance", IP_ADDRESS(1, 2, 3, 4), 0xFFFFFF00UL,
                          &server_pool, _nx_ram_network_driver_1500,
                          server_ip_stack, sizeof(server_ip_stack), 1);
    if (status)
    {
        ERROR_COUNTER();
    }
    status = nx_ip_create(&client_ip[0], "Client 0 IP Instance", IP_ADDRESS(1, 2, 3, 5), 0xFFFFFF00UL,
                          &client_pool[0], _nx_ram_network_driver_1500,
                          client_ip_stack[0], sizeof(client_ip_stack[0]), 1);
    if (status)
    {
        ERROR_COUNTER();
    }
    status = nx_ip_create(&client_ip[1], "Client 1 IP Instance", IP_ADDRESS(1, 2, 3, 6), 0xFFFFFF00UL,
                          &client_pool[1], _nx_ram_network_driver_1500,
                          client_ip_stack[1], sizeof(client_ip_stack[1]), 1);
    if (status)
    {
        ERROR_COUNTER();
    }

    /* Enable ARP and supply ARP cache memory for IP Instance 0.  */
    status =  nx_arp_enable(&server_ip, (VOID *)server_arp_cache, sizeof(server_arp_cache));
    if (status)
    {
        ERROR_COUNTER();
    }
    status =  nx_arp_enable(&client_ip[0], (VOID *)client_arp_cache[0], sizeof(client_arp_cache[0]));
    if (status)
    {
        ERROR_COUNTER();
    }
    status =  nx_arp_enable(&client_ip[1], (VOID *)client_arp_cache[1], sizeof(client_arp_cache[1]));
    if (status)
    {
        ERROR_COUNTER();
    }

    /* Enable UDP traffic.  */
    status =  nx_udp_enable(&server_ip);
    if (status)
    {
        ERROR_COUNTER();
    }
    status =  nx_udp_enable(&client_ip[0]);
    if (status)
    {
        ERROR_COUNTER();
    }
    status =  nx_udp_enable(&client_ip[1]);
    if (status)
    {
        ERROR_COUNTER();
    }

    nx_secure_tls_initialize();
    nx_secure_dtls_initialize();
}

static UINT    crypto_method_ecjpake_init(struct NX_CRYPTO_METHOD_STRUCT *method,
                                          UCHAR *key, NX_CRYPTO_KEY_SIZE key_size_in_bits,
                                          VOID **handle,
                                          VOID *crypto_metadata,
                                          ULONG crypto_metadata_size)
{
    ecjpake_init_counter++;
    return(_nx_crypto_method_ecjpake_init(method, key, key_size_in_bits, handle,
                                          crypto_metadata, crypto_metadata_size));
}

static VOID ciphersuites_setup()
{

    /* Initialize ciphersuites. */
    memcpy(&tls_ciphers, &nx_crypto_tls_ciphers, sizeof(NX_SECURE_TLS_CRYPTO));
    tls_ciphers.nx_secure_tls_ciphersuite_lookup_table = &_nx_crypto_ciphersuite_ecjpake;
    tls_ciphers.nx_secure_tls_ciphersuite_lookup_table_size = 1;
}

static VOID client_dtls_setup(NX_SECURE_DTLS_SESSION *dtls_session_ptr, UINT index)
{
UINT status;

    status = nx_secure_dtls_session_create(dtls_session_ptr,
                                           &tls_ciphers,
                                           client_metadata[index],
                                           sizeof(client_metadata[index]),
                                           client_tls_packet_buffer[index], sizeof(client_tls_packet_buffer[index]),
                                           1, client_cert_buffer[index], sizeof(client_cert_buffer[index]));
    if (status)
    {
        ERROR_COUNTER();
    }

#if defined(NX_SECURE_ENABLE_PSK_CIPHERSUITES) || defined(NX_SECURE_ENABLE_ECJPAKE_CIPHERSUITE)
    /* For PSK ciphersuites, add a PSK and identity hint.  */
    nx_secure_dtls_psk_add(dtls_session_ptr, PSK, strlen(PSK),
                         PSK_IDENTITY, strlen(PSK_IDENTITY), PSK_HINT, strlen(PSK_HINT));
#endif
}


/* Notification flags for DTLS server connect/receive. */
static UINT server_connect_count = 0;
static UINT server_receive_count = 0;
static NX_SECURE_DTLS_SESSION *connect_session[8];

/* Connect notify callback for DTLS server - notifies the application thread that
   a DTLS connection is ready to kickoff a handshake. */
static UINT server_connect_notify(NX_SECURE_DTLS_SESSION *dtls_session, NXD_ADDRESS *ip_address, UINT port)
{
    connect_session[server_connect_count & 0x07] = dtls_session;
    server_connect_count++;
    tx_semaphore_put(&semaphore_connect);
    return(NX_SUCCESS);
}

/* Receive notify callback for DTLS server - notifies the application thread that
   we have received a DTLS record over an established DTLS session. */
static UINT server_receive_notify(NX_SECURE_DTLS_SESSION *dtls_session)
{
    server_receive_count++;
    return(NX_SUCCESS);
}


static VOID server_dtls_setup(NX_SECURE_DTLS_SERVER *dtls_server_ptr)
{
UINT status;
UINT i;

    status = nx_secure_dtls_server_create(dtls_server_ptr, &server_ip, SERVER_PORT, NX_IP_PERIODIC_RATE,
                                          server_session_buffer, sizeof(server_session_buffer),
                                          &tls_ciphers, server_metadata, sizeof(server_metadata),
                                          server_tls_packet_buffer, sizeof(server_tls_packet_buffer),
                                          server_connect_notify, server_receive_notify);
    if (status)
    {
        ERROR_COUNTER();
    }

#if defined(NX_SECURE_ENABLE_PSK_CIPHERSUITES) || defined(NX_SECURE_ENABLE_ECJPAKE_CIPHERSUITE)

    for (i = 0; i < dtls_server_ptr -> nx_dtls_server_sessions_count; i++)
    {

        /* For PSK ciphersuites, add a PSK and identity hint.  */
        nx_secure_dtls_psk_add(&dtls_server_ptr -> nx_dtls_server_sessions[i], PSK, strlen(PSK),
                               PSK_IDENTITY, strlen(PSK_IDENTITY), PSK_HINT, strlen(PSK_HINT));
    }

#endif
}

static void server_thread_entry(ULONG thread_input)
{
UINT status;
INT  i;

    /* Print out test information banner.  */
    printf("NetX Secure Test:   DTLS Multiple Sessions Ecjpake Test................");

    ciphersuites_setup();

    server_dtls_setup(&dtls_server);

    /* Start DTLS session. */
    status = nx_secure_dtls_server_start(&dtls_server);
    if (status)
    {
        printf("Error in starting DTLS server: 0x%02X\n", status);
        ERROR_COUNTER();
    }

    /* Wait for connection attempt. */
    tx_semaphore_get(&semaphore_connect, NX_IP_PERIODIC_RATE);

    status = nx_secure_dtls_server_session_start(connect_session[0], NX_WAIT_FOREVER);

    if (status)
    {
        printf("Error in establishing DTLS server session: 0x%02X\n", status);
        ERROR_COUNTER();
    }

    for (i = 1; i < 3; i++)
    {
        tx_semaphore_put(&semaphore_server);

        /* Wait for connection attempt. */
        tx_semaphore_get(&semaphore_connect, NX_IP_PERIODIC_RATE);

        status = nx_secure_dtls_server_session_start(connect_session[i], NX_WAIT_FOREVER);

        if (status)
        {
            printf("Error in establishing DTLS server session: 0x%02X\n", status);
            ERROR_COUNTER();
        }

        /* End the sessions.  */
        nx_secure_dtls_session_end(connect_session[i], NX_NO_WAIT);
    }

    /* End client 1.  */
    nx_secure_dtls_session_end(connect_session[0], NX_NO_WAIT);

    /* Wait clients end finished.  */
    tx_thread_suspend(&server_thread);

    /* Shutdown DTLS server. */
    nx_secure_dtls_server_stop(&dtls_server);

    /* Check packet leak.  */
    if (server_pool.nx_packet_pool_available != server_pool.nx_packet_pool_total)
    {
        ERROR_COUNTER();
    }

    if ((client_pool[0].nx_packet_pool_available != client_pool[0].nx_packet_pool_total) ||
        (client_pool[1].nx_packet_pool_available != client_pool[1].nx_packet_pool_total))
    {
        ERROR_COUNTER();
    }

    /* Delete server. */
    nx_secure_dtls_server_delete(&dtls_server);

    if (error_counter)
    {
        printf("ERROR!\n");
        test_control_return(1);
    }
    else
    {
        printf("SUCCESS!\n");
        test_control_return(0);
    }
}

static void client_thread_0_entry(ULONG thread_input)
{
UINT status;
NXD_ADDRESS server_address;

    server_address.nxd_ip_version = NX_IP_VERSION_V4;
    server_address.nxd_ip_address.v4 = IP_ADDRESS(1, 2, 3, 4);

    /* Create UDP socket. */
    status = nx_udp_socket_create(&client_ip[0], &client_socket[0], "Client socket 0", NX_IP_NORMAL,
                                  NX_DONT_FRAGMENT, 0x80, 5);
    if (status)
    {
        ERROR_COUNTER();
    }

    status = nx_udp_socket_bind(&client_socket[0], NX_ANY_PORT, NX_NO_WAIT);
    if (status)
    {
        ERROR_COUNTER();
    }

    client_dtls_setup(&dtls_client_session[0], 0);

    /* Start DTLS session. */
    status = nx_secure_dtls_client_session_start(&dtls_client_session[0], &client_socket[0], &server_address, SERVER_PORT, NX_WAIT_FOREVER);
    if (status)
    {
        ERROR_COUNTER();
    }

    nx_secure_dtls_session_end(&dtls_client_session[0], NX_NO_WAIT);

    nx_secure_dtls_session_delete(&dtls_client_session[0]);

    nx_udp_socket_unbind(&client_socket[0]);

    nx_udp_socket_delete(&client_socket[0]);
}

static void client_thread_1_entry(ULONG thread_input)
{
UINT status;
NXD_ADDRESS server_address;
UINT i;

    server_address.nxd_ip_version = NX_IP_VERSION_V4;
    server_address.nxd_ip_address.v4 = IP_ADDRESS(1, 2, 3, 4);

    /* Create UDP socket. */
    status = nx_udp_socket_create(&client_ip[1], &client_socket[1], "Client socket 1", NX_IP_NORMAL,
                                  NX_DONT_FRAGMENT, 0x80, 5);
    if (status)
    {
        ERROR_COUNTER();
    }

    status = nx_udp_socket_bind(&client_socket[1], NX_ANY_PORT, NX_NO_WAIT);
    if (status)
    {
        ERROR_COUNTER();
    }

    client_dtls_setup(&dtls_client_session[1], 1);

    for (i = 0; i < 2; i++)
    {
        tx_semaphore_get(&semaphore_server, NX_IP_PERIODIC_RATE);

        /* Start DTLS session. */
        status = nx_secure_dtls_client_session_start(&dtls_client_session[1], &client_socket[1], &server_address, SERVER_PORT, NX_WAIT_FOREVER);
        if (status)
        {
            ERROR_COUNTER();
        }

        nx_secure_dtls_session_end(&dtls_client_session[1], NX_NO_WAIT);
    }

    nx_secure_dtls_session_delete(&dtls_client_session[1]);

    nx_udp_socket_unbind(&client_socket[1]);

    nx_udp_socket_delete(&client_socket[1]);

    tx_thread_resume(&server_thread);
}
#else
#ifdef CTEST
void test_application_define(void *first_unused_memory);
void test_application_define(void *first_unused_memory)
#else
VOID    nx_secure_dtls_multiple_sessions_ecjpake_test_application_define(void *first_unused_memory)
#endif
{

    /* Print out test information banner.  */
    printf("NetX Secure Test:   DTLS Multiple Sessions Ecjpake Test................N/A\n");
    test_control_return(3);
}
#endif
