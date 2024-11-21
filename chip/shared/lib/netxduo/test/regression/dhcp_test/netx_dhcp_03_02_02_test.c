/* If the client's request is invalid, servers SHOULD respond with a DHCPNAK message to the client.
 * If 'giaddr' is 0x00 in the DHCPREQUEST message, the server MUST broacast the DHCPNAK message to the 0xffffffff broadcast address
 *
 * rfc 2131, page 19, 3.2 Client-server interaction - resuing a previously allocated network address
 */

#include   "tx_api.h"
#include   "nx_api.h"
#include   "netx_dhcp_clone_function.h"
#include   "nx_ipv4.h"
#include   "nxd_dhcp_client.h"
#include   "nxd_dhcp_server.h" 

extern void    test_control_return(UINT status);

#if !defined(NX_DISABLE_IPV4)

#define     DEMO_STACK_SIZE             4096
#define     NX_PACKET_SIZE              1536
#define     NX_PACKET_POOL_SIZE         NX_PACKET_SIZE * 8

#define     NX_DHCP_SERVER_IP_ADDRESS_0 IP_ADDRESS(10,0,0,1)   
#define     START_IP_ADDRESS_LIST_0     IP_ADDRESS(10,0,0,10)
#define     END_IP_ADDRESS_LIST_0       IP_ADDRESS(10,0,0,19)

#define     NX_DHCP_SUBNET_MASK_0       IP_ADDRESS(255,255,255,0)
#define     NX_DHCP_DEFAULT_GATEWAY_0   IP_ADDRESS(10,0,0,1)
#define     NX_DHCP_DNS_SERVER_0        IP_ADDRESS(10,0,0,1)

#define     CLIENT_IP_ADDRESS           IP_ADDRESS(100,0,0,10)

/* Define the ThreadX and NetX object control blocks...  */
static TX_THREAD               client_thread;
static NX_PACKET_POOL          client_pool;
static NX_IP                   client_ip;
static NX_DHCP                 dhcp_client;

static TX_THREAD               server_thread;
static NX_PACKET_POOL          server_pool;
static NX_IP                   server_ip;
static NX_DHCP_SERVER          dhcp_server;

/* Define the counters used in the demo application...  */

static ULONG                   error_counter;
static CHAR                    *pointer;

static UINT                    dhcp_nak_flag;
static UINT                    dhcp_request_count;

/* Define thread prototypes.  */

static void    server_thread_entry(ULONG thread_input);
static void    client_thread_entry(ULONG thread_input);

/******** Optionally substitute your Ethernet driver here. ***********/
extern void    _nx_ram_network_driver_1500(struct NX_IP_DRIVER_STRUCT *driver_req);
extern UINT    (*advanced_packet_process_callback)(NX_IP *ip_ptr, NX_PACKET *packet_ptr, UINT *operation_ptr, UINT *delay_ptr);
static UINT    my_packet_process(NX_IP *ip_ptr, NX_PACKET *packet_ptr, UINT *operation_ptr, UINT *delay_ptr);

/* Define what the initial system looks like.  */

#ifdef CTEST
VOID test_application_define(void *first_unused_memory)
#else
void    netx_dhcp_03_02_02_test_application_define(void *first_unused_memory)
#endif
{

UINT    status;

    /* Setup the working pointer.  */
    pointer =  (CHAR *) first_unused_memory;

    /* Create the client thread.  */
    tx_thread_create(&client_thread, "thread client", client_thread_entry, 0,  
            pointer, DEMO_STACK_SIZE, 
            4, 4, TX_NO_TIME_SLICE, TX_AUTO_START);
    pointer =  pointer + DEMO_STACK_SIZE;

    /* Create the server thread.  */
    tx_thread_create(&server_thread, "thread server", server_thread_entry, 0,  
            pointer, DEMO_STACK_SIZE, 
            3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
    pointer =  pointer + DEMO_STACK_SIZE;

    /* Initialize the NetX system.  */
    nx_system_initialize();

    /* Create the client packet pool.  */
    status =  nx_packet_pool_create(&client_pool, "NetX Main Packet Pool", 1024, pointer, NX_PACKET_POOL_SIZE);
    pointer = pointer + NX_PACKET_POOL_SIZE;

    /* Check for pool creation error.  */
    if (status)
        error_counter++;
    
    /* Create the server packet pool.  */
    status =  nx_packet_pool_create(&server_pool, "NetX Main Packet Pool", 1024, pointer, NX_PACKET_POOL_SIZE);
    pointer = pointer + NX_PACKET_POOL_SIZE;

    /* Check for pool creation error.  */
    if (status)
        error_counter++;

    /* Create an IP instance for the DHCP Client.  */
    status = nx_ip_create(&client_ip, "DHCP Client", IP_ADDRESS(0, 0, 0, 0), 0xFFFFFF00UL, &client_pool, _nx_ram_network_driver_1500, pointer, 2048, 1);

    pointer =  pointer + 2048;

    /* Check for IP create errors.  */
    if (status)
        error_counter++;
    
    /* Create an IP instance for the DHCP Server.  */
    status = nx_ip_create(&server_ip, "DHCP Server", NX_DHCP_SERVER_IP_ADDRESS_0, 0xFFFFFF00UL, &server_pool, _nx_ram_network_driver_1500, pointer, 2048, 1);

    pointer =  pointer + 2048;

    /* Check for IP create errors.  */
    if (status)
        error_counter++;

    /* Enable ARP and supply ARP cache memory for DHCP Client IP.  */
    status =  nx_arp_enable(&client_ip, (void *) pointer, 1024);
    pointer = pointer + 1024;

    /* Check for ARP enable errors.  */
    if (status)
        error_counter++;
    
    /* Enable ARP and supply ARP cache memory for DHCP Server IP.  */
    status =  nx_arp_enable(&server_ip, (void *) pointer, 1024);
    pointer = pointer + 1024;

    /* Check for ARP enable errors.  */
    if (status)
        error_counter++;

    /* Enable UDP traffic.  */
    status =  nx_udp_enable(&client_ip);

    /* Check for UDP enable errors.  */
    if (status)
        error_counter++;
    
    /* Enable UDP traffic.  */
    status =  nx_udp_enable(&server_ip);

    /* Check for UDP enable errors.  */
    if (status)
        error_counter++;

    /* Enable ICMP.  */
    status =  nx_icmp_enable(&client_ip);

    /* Check for errors.  */
    if (status)
        error_counter++;

    /* Enable ICMP.  */
    status =  nx_icmp_enable(&server_ip);

    /* Check for errors.  */
    if (status)
        error_counter++;

    return;
}

/* Define the test threads.  */

void    server_thread_entry(ULONG thread_input)
{

UINT        status;
UINT   	    iface_index;
UINT        addresses_added;

    printf("NetX Test:   DHCP 03_02_02 Test........................................");

    /* Create the DHCP Server.  */
    status =  nx_dhcp_server_create(&dhcp_server, &server_ip, pointer, DEMO_STACK_SIZE, 
                                   "DHCP Server", &server_pool);
    
    pointer = pointer + DEMO_STACK_SIZE;
    
    /* Check for errors creating the DHCP Server. */
    if (status)
        error_counter++;

    /* Load the assignable DHCP IP addresses for the first interface.  */
    iface_index = 0;

    status = nx_dhcp_create_server_ip_address_list(&dhcp_server, iface_index, START_IP_ADDRESS_LIST_0, 
                                                   END_IP_ADDRESS_LIST_0, &addresses_added);

    /* Check for errors creating the list. */
    if (status)
        error_counter++;

    /* Verify all the addresses were added to the list. */
    if (addresses_added != 10)
        error_counter++;

    status = nx_dhcp_set_interface_network_parameters(&dhcp_server, iface_index, NX_DHCP_SUBNET_MASK_0, 
                                                      NX_DHCP_DEFAULT_GATEWAY_0, NX_DHCP_DNS_SERVER_0);

    /* Check for errors setting network parameters. */
    if (status)
        error_counter++;

    /* Start DHCP Server task.  */
    status = nx_dhcp_server_start(&dhcp_server);

    /* Check for errors starting up the DHCP server.  */
    if (status)
        error_counter++;
    
    tx_thread_sleep(3 * NX_IP_PERIODIC_RATE);

    if((error_counter) || (dhcp_nak_flag == 0))
    {
        printf("ERROR!\n");
        test_control_return(1);
    }
    else
    {
        printf("SUCCESS!\n");
        test_control_return(0);
    }

    return;
}

/* Define the test threads.  */

void    client_thread_entry(ULONG thread_input)
{

UINT        status;
ULONG       requested_ip;
UINT        skip_discover_message = NX_TRUE;

    dhcp_nak_flag = 0;
    dhcp_request_count = 0;

    /* Create the DHCP instance.  */
    status =  nx_dhcp_create(&dhcp_client, &client_ip, "dhcp_client");
    if (status)
        error_counter++;

#ifdef NX_DHCP_CLIENT_USER_CREATE_PACKET_POOL
    status = nx_dhcp_packet_pool_set(&dhcp_client, &client_pool);
    if (status)
        error_counter++;
#endif /* NX_DHCP_CLIENT_USER_CREATE_PACKET_POOL  */

    /* Set the client IP if the host is configured to do so. */
    requested_ip = (ULONG)CLIENT_IP_ADDRESS;

    /* Request a specific IP address using the DHCP client address option. */
    status = nx_dhcp_request_client_ip(&dhcp_client, requested_ip, skip_discover_message);
    if (status)
        error_counter++;


    advanced_packet_process_callback   = my_packet_process;

    /* Start the DHCP Client.  */
    status =  nx_dhcp_start(&dhcp_client);
    if (status)
        error_counter++;

    /* Wait for DHCP to assign the IP address.  */
    do
    {
        /* Check for address resolution.  */
        status =  nx_ip_status_check(&client_ip, NX_IP_ADDRESS_RESOLVED, (ULONG *) &status, NX_IP_PERIODIC_RATE);

        /* Check status.  */
        if (status)
        {
            /* wait a bit. */
            tx_thread_sleep(NX_IP_PERIODIC_RATE);
        }

    } while (status != NX_SUCCESS);

    /* Stopping the DHCP client. */
    nx_dhcp_stop(&dhcp_client);

    /* All done. Return resources to NetX and ThreadX. */    
    nx_dhcp_delete(&dhcp_client);

    return;
}


static UINT my_packet_process(NX_IP *ip_ptr, NX_PACKET *packet_ptr, UINT *operation_ptr, UINT *delay_ptr)
{

UINT            status;
ULONG           message_type;
NX_UDP_HEADER  *udp_header;
ULONG           src_dst_port;
ULONG           gateway_ip;
#ifdef __PRODUCT_NETXDUO__
NX_IPV4_HEADER *ip_header;
#else
NX_IP_HEADER   *ip_header;
#endif
ULONG          dst_addr;

    udp_header = (NX_UDP_HEADER*)((packet_ptr -> nx_packet_prepend_ptr) + 20);
    src_dst_port = udp_header -> nx_udp_header_word_0; 
    NX_CHANGE_ULONG_ENDIAN(src_dst_port);

    /* client port 68(0x44), server port 67(0x43). packet sent to server from client*/
    if(src_dst_port == 0x00440043)
    {
        /* Get the dhcp message type. */
        status = dhcp_get_option_value((packet_ptr -> nx_packet_prepend_ptr + 20 + 8), NX_DHCP_SERVER_OPTION_DHCP_TYPE, 
                &message_type, (packet_ptr -> nx_packet_length - 20 - 8));
        if(status)
            error_counter++;

        /* Check if the message is a DHCPREQUEST. */
        if(message_type == NX_DHCP_TYPE_DHCPREQUEST)
        {
            dhcp_request_count++;

            /* Get secs giaddr value. */
            gateway_ip = dhcp_get_data((packet_ptr -> nx_packet_prepend_ptr + 20 + 8 + NX_BOOTP_OFFSET_GATEWAY_IP), 4);

            if(gateway_ip != 0)
                error_counter++;

        }
    }
    /* sent from server to client. */
    else if((src_dst_port == 0x00430044) && (dhcp_request_count == 1))
    {

        /* Get the dhcp message type. */
        status = dhcp_get_option_value((packet_ptr -> nx_packet_prepend_ptr + 20 + 8), NX_DHCP_SERVER_OPTION_DHCP_TYPE, 
                                                &message_type, (packet_ptr -> nx_packet_length - 20 - 8));
        if(status)
            error_counter++;

        /* Check if the message is a DHCPNACK. */
        if(message_type == NX_DHCP_TYPE_DHCPNACK)
        {
            dhcp_nak_flag++;

#ifdef __PRODUCT_NETXDUO__
            ip_header = (NX_IPV4_HEADER*)packet_ptr -> nx_packet_prepend_ptr;
#else
            ip_header = (NX_IP_HEADER *)packet_ptr -> nx_packet_prepend_ptr;
#endif
            /* Get the  destination ip address. */
            dst_addr = ip_header -> nx_ip_header_destination_ip;

            if(dst_addr != 0xffffffff)
                error_counter++;
        }

        /* restore the callback to NULL. */
        advanced_packet_process_callback = NX_NULL;
    }
   
    return NX_TRUE;

}
#else

#ifdef CTEST
VOID test_application_define(void *first_unused_memory)
#else
void    netx_dhcp_03_02_02_test_application_define(void *first_unused_memory)
#endif
{

    /* Print out test information banner.  */
    printf("NetX Test:   NetX DHCP 03_02_02 Test...................................N/A\n"); 

    test_control_return(3);  
}      
#endif
