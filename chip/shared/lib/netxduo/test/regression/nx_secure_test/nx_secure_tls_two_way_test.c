/* 14.19 TCP MUST include an SWS avoidance algorithm in the receiver when effective send MSS < (1/ 2)*RCV_BUFF.  */

/*  Procedure
    1.Connection successfully  
    2.First Client sends 40 data to Server, then check if the last_sent changed
    3.Then Client sends more 20 data to Server, also check if the last_sent changed
    4.If the last_sent changed, the SWS avoidance algorithm has not been used.  */

#include   "tx_api.h"
#include   "nx_api.h"
#include   "nx_tcp.h"
#include   "nx_secure_tls_api.h"
#include   "tls_test_utility.h"

extern void    test_control_return(UINT status);

#if !defined(NX_SECURE_TLS_CLIENT_DISABLED) && !defined(NX_SECURE_TLS_SERVER_DISABLED)
#define __LINUX__

/* Define the number of times to (re)establish a TLS connection. */
#define TLS_CONNECT_TIMES (6)

#define LARGE_SEND_SIZE   3000

#define MSG "----------abcdefgh20----------ABCDEFGH40----------klmnopqr60----------KLMNOPQR80--------------------"

/* Define the ThreadX and NetX object control blocks...  */

static TX_THREAD               ntest_0;
static TX_THREAD               ntest_1;

static NX_PACKET_POOL          pool_0;
static NX_PACKET_POOL          pool_1;
static NX_PACKET_POOL          pool_2;
static NX_IP                   ip_0;
static NX_IP                   ip_1;
static NX_TCP_SOCKET           client_socket;
static NX_TCP_SOCKET           server_socket;
static NX_SECURE_TLS_SESSION   client_tls_session;
static NX_SECURE_TLS_SESSION   server_tls_session;

static NX_SECURE_X509_CERT certificate;
static NX_SECURE_X509_CERT server_certificate;
static NX_SECURE_X509_CERT duplicate_server_certificate;
static NX_SECURE_X509_CERT ica_certificate;
static NX_SECURE_X509_CERT client_certificate;
static NX_SECURE_X509_CERT trusted_certificate;

/* Combined certificate buffers for new API. */
UCHAR remote_client_certs_buffer[(sizeof(NX_SECURE_X509_CERT) + 2000) * 2];
UCHAR remote_server_certs_buffer[(sizeof(NX_SECURE_X509_CERT) + 2000) * 2];

UCHAR server_packet_buffer[4000];
UCHAR client_packet_buffer[4000];

CHAR server_crypto_metadata[16000]; 
CHAR client_crypto_metadata[16000]; 

static UCHAR large_app_data[LARGE_SEND_SIZE];
static UCHAR server_recv_buffer[LARGE_SEND_SIZE];
static UCHAR client_recv_buffer[LARGE_SEND_SIZE];

/* Test PKI (3-level). */
#include "test_ca_cert.c"
#include "tls_two_test_certs.c"
#define ca_cert_der test_ca_cert_der
#define ca_cert_der_len test_ca_cert_der_len

/*  Cryptographic routines. */
extern const NX_SECURE_TLS_CRYPTO nx_crypto_tls_ciphers;

/* Server certificate. */
#if 0
static unsigned char test_device_cert_der[] = {
  0x30, 0x82, 0x03, 0xd2, 0x30, 0x82, 0x02, 0xba, 0xa0, 0x03, 0x02, 0x01,
  0x02, 0x02, 0x01, 0x01, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
  0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x30, 0x7a, 0x31, 0x0b, 0x30,
  0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x0b,
  0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x08, 0x0c, 0x02, 0x43, 0x41, 0x31,
  0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04, 0x07, 0x0c, 0x09, 0x53, 0x61,
  0x6e, 0x20, 0x44, 0x69, 0x65, 0x67, 0x6f, 0x31, 0x16, 0x30, 0x14, 0x06,
  0x03, 0x55, 0x04, 0x0a, 0x0c, 0x0d, 0x45, 0x78, 0x70, 0x72, 0x65, 0x73,
  0x73, 0x20, 0x4c, 0x6f, 0x67, 0x69, 0x63, 0x31, 0x14, 0x30, 0x12, 0x06,
  0x03, 0x55, 0x04, 0x0b, 0x0c, 0x0b, 0x4e, 0x65, 0x74, 0x58, 0x20, 0x53,
  0x65, 0x63, 0x75, 0x72, 0x65, 0x31, 0x1c, 0x30, 0x1a, 0x06, 0x03, 0x55,
  0x04, 0x03, 0x0c, 0x13, 0x4e, 0x65, 0x74, 0x58, 0x20, 0x53, 0x65, 0x63,
  0x75, 0x72, 0x65, 0x20, 0x54, 0x65, 0x73, 0x74, 0x20, 0x43, 0x41, 0x30,
  0x1e, 0x17, 0x0d, 0x31, 0x36, 0x31, 0x31, 0x31, 0x31, 0x31, 0x39, 0x35,
  0x31, 0x30, 0x30, 0x5a, 0x17, 0x0d, 0x32, 0x36, 0x31, 0x31, 0x30, 0x39,
  0x31, 0x39, 0x35, 0x31, 0x30, 0x30, 0x5a, 0x30, 0x62, 0x31, 0x0b, 0x30,
  0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x0b,
  0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x08, 0x0c, 0x02, 0x43, 0x41, 0x31,
  0x16, 0x30, 0x14, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x0c, 0x0d, 0x45, 0x78,
  0x70, 0x72, 0x65, 0x73, 0x73, 0x20, 0x4c, 0x6f, 0x67, 0x69, 0x63, 0x31,
  0x14, 0x30, 0x12, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x0c, 0x0b, 0x4e, 0x65,
  0x74, 0x58, 0x20, 0x53, 0x65, 0x63, 0x75, 0x72, 0x65, 0x31, 0x18, 0x30,
  0x16, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0c, 0x0f, 0x77, 0x77, 0x77, 0x2e,
  0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x30,
  0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,
  0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30,
  0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00, 0xae, 0x03, 0x2c, 0xec,
  0xa2, 0x79, 0xd1, 0x15, 0x20, 0x88, 0x4d, 0xcd, 0xa2, 0x1b, 0x05, 0xe3,
  0xbd, 0x55, 0xad, 0xc6, 0x1f, 0x64, 0xe8, 0xb5, 0xc5, 0x0d, 0x67, 0xfc,
  0x7e, 0xda, 0xfb, 0x70, 0xf6, 0xc9, 0x47, 0x87, 0x3a, 0xaa, 0x88, 0x00,
  0xf1, 0xa7, 0xf7, 0xe1, 0xf5, 0x2c, 0x54, 0x0e, 0x33, 0xda, 0xbe, 0x9c,
  0x66, 0x30, 0xd9, 0x40, 0xeb, 0x1d, 0xce, 0xe1, 0x55, 0x15, 0x2b, 0x11,
  0x47, 0x6c, 0x7e, 0x88, 0xc6, 0x24, 0xcf, 0x87, 0x1b, 0xb5, 0x1f, 0x47,
  0xb9, 0xef, 0xad, 0x29, 0xd3, 0x2e, 0x43, 0xee, 0x39, 0xdd, 0x09, 0x54,
  0xba, 0xfc, 0xed, 0xbc, 0x2e, 0x0e, 0x53, 0x15, 0x37, 0xcb, 0xc5, 0xf5,
  0xee, 0x70, 0x2a, 0xe8, 0x01, 0x6d, 0xb1, 0x39, 0x94, 0x5a, 0xc2, 0x8a,
  0x00, 0x04, 0xa9, 0xff, 0xea, 0x56, 0xf7, 0xd7, 0xa8, 0x1b, 0xa4, 0x26,
  0xcd, 0x28, 0xaf, 0xfa, 0x52, 0x85, 0x1c, 0x26, 0x3e, 0x5e, 0x01, 0xf7,
  0xe1, 0x66, 0xff, 0xac, 0xad, 0x9c, 0x98, 0x2f, 0xe0, 0x7e, 0x9f, 0xf1,
  0x33, 0x31, 0xc3, 0x7f, 0xe6, 0x58, 0x5d, 0xd8, 0x5f, 0x7d, 0x2b, 0x5a,
  0x55, 0xcf, 0xb1, 0x91, 0x53, 0x41, 0x04, 0xac, 0x86, 0x5e, 0x01, 0x35,
  0x2b, 0x74, 0x8d, 0x46, 0x4d, 0x48, 0xc0, 0x5f, 0x83, 0x67, 0xb5, 0x6d,
  0x52, 0x3f, 0x3e, 0xe6, 0xec, 0xf8, 0x2e, 0x10, 0x28, 0xdb, 0x69, 0xa6,
  0x9d, 0x4b, 0xde, 0x19, 0x2e, 0xd2, 0x5f, 0xc8, 0xa9, 0x3b, 0x52, 0xe9,
  0xb2, 0xcd, 0x6e, 0x19, 0x22, 0xf9, 0x99, 0xa6, 0xcc, 0xf5, 0xd3, 0xec,
  0xff, 0x0c, 0x77, 0x6f, 0x25, 0x92, 0x07, 0x4c, 0x64, 0x7d, 0x34, 0x49,
  0x6f, 0xff, 0x0a, 0xa8, 0x15, 0x64, 0x72, 0x2d, 0x4f, 0x42, 0x05, 0xe8,
  0x2b, 0x01, 0xf1, 0xe3, 0x65, 0x94, 0x23, 0xd9, 0xdf, 0x5e, 0x3b, 0xb5,
  0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x7b, 0x30, 0x79, 0x30, 0x09, 0x06,
  0x03, 0x55, 0x1d, 0x13, 0x04, 0x02, 0x30, 0x00, 0x30, 0x2c, 0x06, 0x09,
  0x60, 0x86, 0x48, 0x01, 0x86, 0xf8, 0x42, 0x01, 0x0d, 0x04, 0x1f, 0x16,
  0x1d, 0x4f, 0x70, 0x65, 0x6e, 0x53, 0x53, 0x4c, 0x20, 0x47, 0x65, 0x6e,
  0x65, 0x72, 0x61, 0x74, 0x65, 0x64, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69,
  0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d,
  0x0e, 0x04, 0x16, 0x04, 0x14, 0x8d, 0xb0, 0xee, 0x8f, 0x6b, 0x43, 0x52,
  0x29, 0xf4, 0x25, 0xff, 0x3c, 0xda, 0x5f, 0xb3, 0xce, 0x9b, 0x7b, 0x75,
  0xe1, 0x30, 0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x18, 0x30, 0x16,
  0x80, 0x14, 0x1b, 0x8d, 0x06, 0xd9, 0x6b, 0xad, 0xee, 0x82, 0x24, 0x26,
  0x55, 0x9a, 0x1b, 0x03, 0x44, 0x92, 0x0a, 0x06, 0x92, 0x48, 0x30, 0x0d,
  0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05,
  0x00, 0x03, 0x82, 0x01, 0x01, 0x00, 0x75, 0x83, 0x89, 0xab, 0x84, 0x52,
  0x5f, 0xa4, 0x9e, 0x98, 0xca, 0xa3, 0xf9, 0xab, 0xd4, 0x04, 0x32, 0xa4,
  0x8c, 0x96, 0x90, 0x39, 0x88, 0x92, 0xc3, 0xcd, 0x51, 0xc3, 0x01, 0x35,
  0x03, 0x78, 0xfa, 0x0d, 0x1e, 0x7b, 0x79, 0xe9, 0x7d, 0xd8, 0x68, 0x7a,
  0x65, 0xc6, 0x00, 0x7c, 0xa1, 0x7a, 0x52, 0xc9, 0xa3, 0xf4, 0x0b, 0xbd,
  0x76, 0x24, 0xdf, 0xde, 0x22, 0x2d, 0x95, 0xc5, 0xb6, 0x54, 0xb1, 0xac,
  0xb6, 0x9a, 0xe4, 0x68, 0x0f, 0x97, 0x4a, 0x44, 0xa2, 0x87, 0x01, 0x82,
  0xd4, 0x25, 0xbd, 0x01, 0xbc, 0x35, 0x8a, 0x6d, 0xb7, 0x7c, 0x48, 0xaa,
  0x92, 0xd7, 0x57, 0x76, 0x6a, 0xb0, 0xc9, 0x46, 0xa6, 0xbe, 0xbf, 0x0f,
  0xf0, 0xea, 0x62, 0x57, 0x71, 0x42, 0xf6, 0x67, 0xa7, 0xa1, 0x50, 0x87,
  0x14, 0x8e, 0x32, 0xd0, 0x5e, 0xc9, 0x7b, 0x79, 0x7e, 0xfa, 0x17, 0xc7,
  0xad, 0xbd, 0xc3, 0x98, 0x79, 0x45, 0xfb, 0x7f, 0xf7, 0xe6, 0x9f, 0x77,
  0xb3, 0x44, 0xc3, 0xaf, 0x6b, 0x61, 0x6a, 0x04, 0x68, 0x24, 0x2d, 0x31,
  0xf1, 0x28, 0x2c, 0xf4, 0xf0, 0x07, 0xfe, 0xfd, 0x66, 0x98, 0x77, 0x37,
  0x7b, 0x80, 0x1f, 0xb2, 0x49, 0xe4, 0xa6, 0x24, 0x72, 0x42, 0xf4, 0xca,
  0x91, 0x80, 0xa1, 0xb2, 0x0a, 0xc9, 0xc0, 0x93, 0xa7, 0x22, 0x0b, 0x13,
  0x8a, 0xb2, 0x75, 0x4b, 0x66, 0xf9, 0x87, 0x3a, 0x51, 0x97, 0xc7, 0x1e,
  0x2b, 0x61, 0x81, 0x5c, 0xf0, 0xf8, 0x4c, 0xdb, 0x36, 0xc7, 0xba, 0x49,
  0xd9, 0x04, 0x6a, 0x95, 0xb0, 0x7f, 0xfc, 0xce, 0xca, 0x23, 0xad, 0xf9,
  0xaf, 0x8a, 0x72, 0x8e, 0xab, 0xb8, 0x8b, 0x7e, 0xf7, 0x39, 0xa6, 0x22,
  0x56, 0x03, 0x72, 0x06, 0xc3, 0x57, 0x1f, 0x32, 0xaa, 0xb5, 0xa6, 0x00,
  0x67, 0x88, 0x4b, 0x40, 0xe9, 0x5e, 0x4a, 0x6f, 0x76, 0xe8
};
static unsigned int test_device_cert_der_len = 982;

static unsigned char test_device_cert_key_der[] = {
  0x30, 0x82, 0x04, 0xa4, 0x02, 0x01, 0x00, 0x02, 0x82, 0x01, 0x01, 0x00,
  0xae, 0x03, 0x2c, 0xec, 0xa2, 0x79, 0xd1, 0x15, 0x20, 0x88, 0x4d, 0xcd,
  0xa2, 0x1b, 0x05, 0xe3, 0xbd, 0x55, 0xad, 0xc6, 0x1f, 0x64, 0xe8, 0xb5,
  0xc5, 0x0d, 0x67, 0xfc, 0x7e, 0xda, 0xfb, 0x70, 0xf6, 0xc9, 0x47, 0x87,
  0x3a, 0xaa, 0x88, 0x00, 0xf1, 0xa7, 0xf7, 0xe1, 0xf5, 0x2c, 0x54, 0x0e,
  0x33, 0xda, 0xbe, 0x9c, 0x66, 0x30, 0xd9, 0x40, 0xeb, 0x1d, 0xce, 0xe1,
  0x55, 0x15, 0x2b, 0x11, 0x47, 0x6c, 0x7e, 0x88, 0xc6, 0x24, 0xcf, 0x87,
  0x1b, 0xb5, 0x1f, 0x47, 0xb9, 0xef, 0xad, 0x29, 0xd3, 0x2e, 0x43, 0xee,
  0x39, 0xdd, 0x09, 0x54, 0xba, 0xfc, 0xed, 0xbc, 0x2e, 0x0e, 0x53, 0x15,
  0x37, 0xcb, 0xc5, 0xf5, 0xee, 0x70, 0x2a, 0xe8, 0x01, 0x6d, 0xb1, 0x39,
  0x94, 0x5a, 0xc2, 0x8a, 0x00, 0x04, 0xa9, 0xff, 0xea, 0x56, 0xf7, 0xd7,
  0xa8, 0x1b, 0xa4, 0x26, 0xcd, 0x28, 0xaf, 0xfa, 0x52, 0x85, 0x1c, 0x26,
  0x3e, 0x5e, 0x01, 0xf7, 0xe1, 0x66, 0xff, 0xac, 0xad, 0x9c, 0x98, 0x2f,
  0xe0, 0x7e, 0x9f, 0xf1, 0x33, 0x31, 0xc3, 0x7f, 0xe6, 0x58, 0x5d, 0xd8,
  0x5f, 0x7d, 0x2b, 0x5a, 0x55, 0xcf, 0xb1, 0x91, 0x53, 0x41, 0x04, 0xac,
  0x86, 0x5e, 0x01, 0x35, 0x2b, 0x74, 0x8d, 0x46, 0x4d, 0x48, 0xc0, 0x5f,
  0x83, 0x67, 0xb5, 0x6d, 0x52, 0x3f, 0x3e, 0xe6, 0xec, 0xf8, 0x2e, 0x10,
  0x28, 0xdb, 0x69, 0xa6, 0x9d, 0x4b, 0xde, 0x19, 0x2e, 0xd2, 0x5f, 0xc8,
  0xa9, 0x3b, 0x52, 0xe9, 0xb2, 0xcd, 0x6e, 0x19, 0x22, 0xf9, 0x99, 0xa6,
  0xcc, 0xf5, 0xd3, 0xec, 0xff, 0x0c, 0x77, 0x6f, 0x25, 0x92, 0x07, 0x4c,
  0x64, 0x7d, 0x34, 0x49, 0x6f, 0xff, 0x0a, 0xa8, 0x15, 0x64, 0x72, 0x2d,
  0x4f, 0x42, 0x05, 0xe8, 0x2b, 0x01, 0xf1, 0xe3, 0x65, 0x94, 0x23, 0xd9,
  0xdf, 0x5e, 0x3b, 0xb5, 0x02, 0x03, 0x01, 0x00, 0x01, 0x02, 0x82, 0x01,
  0x01, 0x00, 0xa5, 0x22, 0x2c, 0x52, 0xd0, 0x09, 0x4c, 0x4a, 0x81, 0x59,
  0xf8, 0x83, 0xa9, 0x4f, 0x7d, 0xb2, 0x56, 0xad, 0xe5, 0x3f, 0xfb, 0xf0,
  0xf6, 0x09, 0xf1, 0x5b, 0x3c, 0x90, 0x58, 0x0e, 0x15, 0xc9, 0x68, 0xd9,
  0x30, 0x40, 0xfb, 0x82, 0x73, 0x98, 0x79, 0xbb, 0xcd, 0xb8, 0x27, 0xc3,
  0x8e, 0x6c, 0xff, 0xf6, 0x99, 0x26, 0xb0, 0xaf, 0xb0, 0xac, 0x33, 0xb3,
  0x50, 0xed, 0x73, 0xa1, 0xa8, 0x02, 0x38, 0xc6, 0x93, 0xf9, 0xd6, 0x17,
  0x7e, 0xbd, 0x97, 0xa4, 0xb5, 0x6f, 0x8a, 0xdb, 0x11, 0x78, 0x7c, 0x89,
  0x0e, 0x3c, 0x17, 0xbb, 0x54, 0x2c, 0x8d, 0x5a, 0x93, 0x7d, 0x1e, 0x33,
  0xc7, 0xd2, 0x7d, 0xe5, 0xaa, 0x12, 0x2d, 0xd9, 0x52, 0x4e, 0x63, 0x74,
  0xa6, 0x57, 0x9f, 0x1a, 0xd6, 0x3c, 0xc1, 0xb1, 0xab, 0x66, 0x4a, 0x0b,
  0x88, 0x1d, 0xa6, 0xd1, 0xbc, 0x60, 0x7a, 0x17, 0x1f, 0x8f, 0x9b, 0x35,
  0x57, 0xf8, 0xd0, 0x1c, 0xd3, 0xa6, 0x56, 0xc8, 0x03, 0x9c, 0x08, 0x3b,
  0x1b, 0x5b, 0xc2, 0x03, 0x3b, 0x3a, 0xa4, 0xe8, 0xed, 0x75, 0x66, 0xb0,
  0x85, 0x56, 0x40, 0xfe, 0xae, 0x97, 0x7e, 0xc0, 0x79, 0x49, 0x13, 0x8b,
  0x01, 0x0c, 0xae, 0x4c, 0x3d, 0x54, 0x47, 0xc5, 0x51, 0x40, 0x3d, 0xcc,
  0x4d, 0x17, 0xb3, 0x4e, 0x1d, 0x85, 0x1c, 0x41, 0x07, 0x03, 0x5e, 0xf9,
  0xfa, 0x17, 0x81, 0x24, 0x34, 0xaa, 0xbf, 0x67, 0x73, 0xb6, 0x9c, 0x67,
  0x36, 0xd9, 0xee, 0xf7, 0x86, 0x4c, 0x4d, 0x79, 0xca, 0xd7, 0xfd, 0x72,
  0xf9, 0xb3, 0x73, 0xc3, 0x57, 0xe5, 0x39, 0x72, 0x93, 0x56, 0xc2, 0xec,
  0xf8, 0x25, 0xe4, 0x8f, 0xba, 0xd0, 0x6f, 0x23, 0x8c, 0x39, 0x9e, 0x05,
  0x1a, 0x4e, 0xdc, 0x5e, 0xcd, 0x17, 0x59, 0x94, 0x37, 0x22, 0xb7, 0x39,
  0x50, 0x65, 0xdc, 0x91, 0x3c, 0xe1, 0x02, 0x81, 0x81, 0x00, 0xe4, 0xc6,
  0x42, 0xe5, 0xea, 0xe5, 0x32, 0xf3, 0x51, 0x36, 0x7b, 0x8c, 0x5b, 0x72,
  0x24, 0x1a, 0x4a, 0x44, 0x4f, 0x64, 0xe5, 0xa7, 0x74, 0xd9, 0xb2, 0x29,
  0x8a, 0x08, 0xcf, 0x9b, 0xd2, 0x9d, 0xc4, 0x20, 0x4c, 0xd3, 0x60, 0x4d,
  0xf7, 0xb7, 0xac, 0x92, 0x6b, 0x2b, 0x95, 0x73, 0x6e, 0x57, 0x00, 0x20,
  0x9d, 0xb2, 0xf6, 0xbd, 0x0b, 0xbb, 0xaa, 0x7e, 0x7e, 0x3e, 0x53, 0xfb,
  0x79, 0x7e, 0x45, 0xd5, 0x2e, 0xab, 0x5e, 0xff, 0x5c, 0x0a, 0x45, 0x2d,
  0x27, 0x19, 0xb0, 0x59, 0x0a, 0x39, 0x89, 0xf6, 0xae, 0xc6, 0xe2, 0xd1,
  0x07, 0x58, 0xbe, 0x95, 0x27, 0xaf, 0xf7, 0xa6, 0x2f, 0xaa, 0x37, 0x25,
  0x7c, 0x7b, 0xd3, 0xda, 0x13, 0x76, 0x0a, 0xb6, 0x6c, 0x99, 0x53, 0x5d,
  0xa5, 0x75, 0xfa, 0x10, 0x9b, 0x7f, 0xfe, 0xd7, 0xb4, 0x18, 0x95, 0xa8,
  0x65, 0x85, 0x07, 0xc5, 0xc4, 0xad, 0x02, 0x81, 0x81, 0x00, 0xc2, 0xb8,
  0x8e, 0xed, 0x9d, 0x4a, 0x1f, 0x9c, 0xda, 0x73, 0xf0, 0x2c, 0x35, 0x91,
  0xe4, 0x40, 0x78, 0xe1, 0x12, 0xf3, 0x08, 0xef, 0xdf, 0x97, 0xa0, 0xb0,
  0xdd, 0xea, 0xc2, 0xb9, 0x5b, 0xf8, 0xa1, 0xac, 0x32, 0xfd, 0xb8, 0xe9,
  0x0f, 0xed, 0xfd, 0xe0, 0xdc, 0x38, 0x90, 0x5e, 0xf5, 0x4c, 0x02, 0xc3,
  0x1a, 0x72, 0x18, 0xf7, 0xfe, 0xb7, 0xb8, 0x2a, 0xf8, 0x72, 0xbb, 0x99,
  0x56, 0xec, 0x85, 0x58, 0x31, 0x7e, 0x64, 0xdf, 0x02, 0x05, 0xe3, 0xb2,
  0xbb, 0xe2, 0x1b, 0xd6, 0x43, 0x73, 0xf8, 0x0f, 0xaf, 0x89, 0x57, 0x44,
  0x5f, 0x30, 0x1c, 0xe5, 0x78, 0xbf, 0x0b, 0xe7, 0x4b, 0xbe, 0x80, 0x2f,
  0x3d, 0x35, 0x44, 0xfc, 0x9e, 0x0d, 0x85, 0x5d, 0x94, 0x6e, 0xe9, 0x6a,
  0x72, 0xa7, 0x46, 0xd8, 0x64, 0x6c, 0xe9, 0x61, 0x92, 0xa0, 0xb6, 0xd1,
  0xee, 0xa6, 0xa6, 0xf4, 0x2c, 0x29, 0x02, 0x81, 0x81, 0x00, 0xb4, 0xa7,
  0x7b, 0x1c, 0x64, 0x29, 0x29, 0xda, 0xca, 0x3e, 0xe3, 0xc1, 0x2a, 0x55,
  0x2f, 0xfd, 0x32, 0xb8, 0x4e, 0x99, 0xb6, 0x60, 0x4d, 0xfd, 0xba, 0x9a,
  0xe2, 0xcd, 0xa2, 0x63, 0xc2, 0x25, 0xa3, 0x42, 0x7e, 0x68, 0x4c, 0x9c,
  0x45, 0x09, 0x5d, 0xd5, 0x21, 0x9c, 0x01, 0x20, 0x6d, 0xf9, 0x75, 0xb8,
  0x4b, 0xcf, 0x8e, 0xd8, 0x29, 0xf3, 0xbf, 0xe6, 0xb3, 0x7a, 0x34, 0x87,
  0x58, 0xa1, 0x46, 0x33, 0xd9, 0xee, 0xa9, 0xcd, 0xac, 0xb8, 0xcf, 0x77,
  0xa0, 0x70, 0xc0, 0xb9, 0x0f, 0x41, 0xf0, 0x98, 0x43, 0xdb, 0xfa, 0x30,
  0x66, 0x44, 0xc5, 0xfa, 0xb2, 0xa4, 0x5a, 0x43, 0x79, 0x50, 0x48, 0xcb,
  0xe9, 0x49, 0x3f, 0x39, 0xee, 0x34, 0x40, 0xb1, 0x5d, 0x80, 0x96, 0x3c,
  0x54, 0xf4, 0x9c, 0xcb, 0x90, 0x7f, 0xba, 0x96, 0x4b, 0x39, 0x3e, 0xb5,
  0x03, 0xb5, 0xd1, 0x35, 0x72, 0xe1, 0x02, 0x81, 0x80, 0x60, 0x14, 0xd5,
  0x61, 0xe6, 0x24, 0xf7, 0x28, 0x5c, 0x9a, 0xac, 0xbe, 0x03, 0xc8, 0xf3,
  0x49, 0xe4, 0xdb, 0x9a, 0x90, 0x15, 0xae, 0xd7, 0x33, 0x68, 0x75, 0x1d,
  0x6b, 0x83, 0x9e, 0x17, 0x05, 0xbe, 0x30, 0xcc, 0x10, 0x6a, 0x37, 0x86,
  0x46, 0xb6, 0xe9, 0x47, 0x81, 0x19, 0xab, 0xe1, 0x7a, 0x1a, 0x3a, 0xcf,
  0x47, 0xd1, 0x8e, 0x3d, 0x3f, 0xc6, 0x3e, 0x5d, 0xcd, 0xaf, 0x47, 0xe0,
  0x9e, 0x60, 0xc5, 0xbd, 0xd6, 0x52, 0x4b, 0xc0, 0x21, 0xcb, 0xd3, 0x1b,
  0xe6, 0x5c, 0x3a, 0x03, 0x9a, 0xab, 0xa2, 0x81, 0xc9, 0x51, 0x28, 0x49,
  0x97, 0xe2, 0x0a, 0x50, 0xe4, 0x64, 0x29, 0x43, 0x34, 0xc2, 0xe7, 0x8c,
  0x5a, 0x46, 0xaa, 0x28, 0x0b, 0x1f, 0xed, 0xa7, 0x1a, 0x7b, 0x4e, 0xad,
  0x38, 0x61, 0x3a, 0xd1, 0x82, 0xf4, 0x3d, 0xd3, 0x2e, 0x3e, 0x47, 0xa4,
  0x6c, 0xd3, 0x20, 0xd4, 0xd1, 0x02, 0x81, 0x80, 0x68, 0x1a, 0x8d, 0x3c,
  0x18, 0x3f, 0x42, 0x5e, 0x38, 0x6d, 0x0a, 0x1e, 0x52, 0xd5, 0x8f, 0xd6,
  0x32, 0xff, 0x7c, 0x1c, 0xf3, 0x20, 0x8b, 0x92, 0xa5, 0x44, 0xff, 0x08,
  0x21, 0xa1, 0xce, 0x68, 0x8b, 0x03, 0xe0, 0x90, 0xeb, 0x01, 0x4e, 0x85,
  0xf9, 0xc5, 0xb7, 0x86, 0xee, 0xd0, 0x59, 0x10, 0x73, 0x98, 0x2a, 0xcb,
  0xf6, 0xfe, 0x0d, 0xba, 0x07, 0x91, 0x18, 0xf6, 0xbc, 0x93, 0x8a, 0x91,
  0xdd, 0x80, 0x16, 0x37, 0xdf, 0x75, 0x46, 0x87, 0x68, 0xee, 0xf4, 0x76,
  0x0c, 0xc5, 0x87, 0x38, 0xf5, 0xb6, 0xda, 0x8a, 0xee, 0x62, 0xc8, 0xc0,
  0xa2, 0x8d, 0xbf, 0xd5, 0xf8, 0xba, 0xb5, 0x74, 0xf0, 0x07, 0xa6, 0x1c,
  0xcf, 0x76, 0x61, 0xbe, 0xa4, 0x88, 0x4a, 0x95, 0xb0, 0xa3, 0x70, 0x73,
  0xa1, 0x6f, 0x73, 0xf0, 0xe8, 0x38, 0x8d, 0xe8, 0xd0, 0x7e, 0x2c, 0x0c,
  0xdc, 0x21, 0xfa, 0xc1
};

static unsigned int test_device_cert_key_der_len = 1192;
#endif

#ifdef NX_SECURE_ENABLE_PSK_CIPHERSUITES
static UCHAR tls_psk[] = {
    0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f, 0x70, 0x81, 0x92, 0xa3, 0xb4, 0xc5, 0xd6, 0xe7, 0xf8, 0x09,
    0x1f, 0x2e, 0x3d, 0x4c, 0x5b, 0x6a, 0x79, 0x88, 0x97, 0xa6, 0xb5, 0xc4, 0xd3, 0xe2, 0xf1, 0x00,
    0x90, 0x8f, 0x7e, 0x6d, 0x5c, 0x4b, 0x3a, 0x29, 0x18, 0x07, 0xf6, 0xe5, 0xd4, 0xc3, 0xb2, 0xa1,
    0xf1, 0xe2, 0xd3, 0xc4, 0xb5, 0xa6, 0x97, 0x88, 0x79, 0x6a, 0x5b, 0x4c, 0x3d, 0x2e, 0x1f, 0xff };
#endif


#define     DEMO_STACK_SIZE  4096 //  (3 * 1024 / sizeof(ULONG))

/* Define the IP thread's stack area.  */
#define IP_STACK_SIZE 4096 //(2 * 1024 / sizeof(ULONG))

/* Define packet pool for the demonstration.  */
#define NX_PACKET_POOL_BYTES  ((1536 + sizeof(NX_PACKET)) * 20)
#define NX_PACKET_POOL_SIZE (NX_PACKET_POOL_BYTES/sizeof(ULONG) + 64 / sizeof(ULONG))

/* Define the ARP cache area.  */
#define ARP_AREA_SIZE 1024 // (512 / sizeof(ULONG))

#define TOTAL_STACK_SPACE (2 * (DEMO_STACK_SIZE + IP_STACK_SIZE + NX_PACKET_POOL_SIZE + ARP_AREA_SIZE))

#ifndef __LINUX__
ULONG test_stack_area[TOTAL_STACK_SPACE + 2000];
#endif

static ULONG pool_area[3][NX_PACKET_POOL_SIZE];

/* Define the counters used in the demo application...  */
ULONG                   error_counter;


/* Define thread prototypes.  */

static void    ntest_0_entry(ULONG thread_input);
static void    ntest_1_entry(ULONG thread_input);
static void    ntest_0_connect_received(NX_TCP_SOCKET *server_socket, UINT port);
static void    ntest_0_disconnect_received(NX_TCP_SOCKET *server_socket);
extern void    _nx_ram_network_driver_1500(struct NX_IP_DRIVER_STRUCT *driver_req);

/* Define what the initial system looks like.  */
#ifndef __LINUX__
void    tx_application_define(void *first_unused_memory)
#else
#ifdef CTEST
void test_application_define(void *first_unused_memory);
void test_application_define(void *first_unused_memory)
#else
void           nx_secure_tls_two_way_test_application_define(void *first_unused_memory)
#endif
#endif
{
CHAR       *pointer;
UINT       status;

    /* Setup the working pointer.  */
#ifndef __LINUX__
    pointer = (CHAR*)test_stack_area;
#else
    pointer = (CHAR *) first_unused_memory;
#endif

    error_counter = 0;
    
    /* Create the main thread.  */
    tx_thread_create(&ntest_0, "thread 0", ntest_0_entry, 0,  
                     pointer, DEMO_STACK_SIZE, 
                     3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);

    pointer = pointer + DEMO_STACK_SIZE;

    /* Create the main thread.  */
    tx_thread_create(&ntest_1, "thread 1", ntest_1_entry, 0,  
                     pointer, DEMO_STACK_SIZE, 
                     4, 4, TX_NO_TIME_SLICE, TX_AUTO_START);

    pointer = pointer + DEMO_STACK_SIZE;

    /* Initialize the NetX system.  */
    nx_system_initialize();
      
    /* Create a packet pool.  */
    status = nx_packet_pool_create(&pool_0, "NetX Main Packet Pool", 1536, pool_area[0], sizeof(pool_area[0]));

    if(status)
    {
        printf("Error in function nx_packet_pool_create: 0x%x\n", status);
        error_counter++;
    }
      
    /* Create a packet pool.  */
    status = nx_packet_pool_create(&pool_1, "NetX Main Packet Pool", 1536, pool_area[1], sizeof(pool_area[1]));

    if(status)
    {
        printf("Error in function nx_packet_pool_create: 0x%x\n", status);
        error_counter++;
    }

    /* Create a packet pool.  */
    status = nx_packet_pool_create(&pool_2, "NetX TLS Packet Pool", 1536, pool_area[2], sizeof(pool_area[2]));

    if(status)
    {
        printf("Error in function nx_packet_pool_create: 0x%x\n", status);
        error_counter++;
    }

    /* Create an IP instance.  */
    status = nx_ip_create(&ip_0, "NetX IP Instance 0", IP_ADDRESS(1, 2, 3, 4), 0xFFFFFF00UL, &pool_0, _nx_ram_network_driver_1500,
                          pointer, IP_STACK_SIZE, 1);
    pointer = pointer + IP_STACK_SIZE;

    /* Create another IP instance.  */
    status += nx_ip_create(&ip_1, "NetX IP Instance 1", IP_ADDRESS(1, 2, 3, 5), 0xFFFFFF00UL, &pool_1, _nx_ram_network_driver_1500,
                           pointer, IP_STACK_SIZE, 1);
    pointer = pointer + IP_STACK_SIZE;

    if(status)
    {
        printf("Error in function nx_ip_create: 0x%x\n", status);
        error_counter++;
    }

    /* Enable ARP and supply ARP cache memory for IP Instance 0.  */
    status = nx_arp_enable(&ip_0, (void *) pointer, ARP_AREA_SIZE);
    pointer = pointer + ARP_AREA_SIZE;

    /* Enable ARP and supply ARP cache memory for IP Instance 1.  */
    status += nx_arp_enable(&ip_1, (void *) pointer, ARP_AREA_SIZE);
    pointer = pointer + ARP_AREA_SIZE;

    /* Check ARP enable status.  */
    if(status)
    {
        printf("Error in function nx_arp_enable: 0x%x\n", status);
        error_counter++;
    }

    /* Enable TCP processing for both IP instances.  */
    status = nx_tcp_enable(&ip_0);
    status += nx_tcp_enable(&ip_1);

    /* Check TCP enable status.  */
    if(status)
    {
        printf("Error in function tcp_enable: 0x%x\n", status);
        error_counter++;
    }
    
    nx_secure_tls_initialize();
}

/*  Define callbacks used by TLS.  */
/* Include CRL associated with Verisign root CA (for AWS) for demo purposes. */
#include "test_ca.crl.der.c"


/* Timestamp function - should return Unix time formatted 32-bit integer. */
ULONG tls_timestamp_function(void)
{
    // Return a fixed epoch - 1500939067 seconds = 07/24/2017 @ 11:31pm (UTC) 
    // 1541030400 = 0x5BDA4200L = 11/01/2018 @ 12:00AM (UTC)
    return(0x5BDA4200L); 
}

#ifndef NX_SECURE_DISABLE_X509
/* Callback invoked whenever TLS has to validate a certificate from a remote host. Additional checking
   of the certificate may be done by the application here. */
ULONG certificate_verification_callback(NX_SECURE_TLS_SESSION *session, NX_SECURE_X509_CERT* certificate)
{
const CHAR *dns_tld = "certificate_with_policies"; //"NX Secure Device Certificate";
UINT status;
NX_SECURE_X509_CERTIFICATE_STORE *store;
NX_SECURE_X509_CERT *issuer_certificate;
UINT                 issuer_location;
USHORT key_usage_bitfield;

    /* Check DNS entry string. */
    status = nx_secure_x509_common_name_dns_check(certificate, (UCHAR*)dns_tld, strlen(dns_tld));
  
    if(status != NX_SUCCESS)
    {
        printf("Error in certificate verification: DNS name did not match CN\n");
        return(status);
    }    
    
    /* Check CRL revocation status. */
    store = &session -> nx_secure_tls_credentials.nx_secure_tls_certificate_store;
    
#ifndef NX_SECURE_X509_DISABLE_CRL
    status = nx_secure_x509_crl_revocation_check(test_ca_crl_der, test_ca_crl_der_len, store, certificate);

    if(status != NX_SUCCESS)
    {
        return(status);
    }
#endif /* NX_SECURE_X509_DISABLE_CRL */

    /* Check key usage extension. */
    status = nx_secure_x509_key_usage_extension_parse(certificate, &key_usage_bitfield);

    if(status != NX_SUCCESS)
    {
        printf("Error in parsing key usage extension: 0x%x\n", status);
        return(status);
    }

    if((key_usage_bitfield & NX_SECURE_X509_KEY_USAGE_DIGITAL_SIGNATURE) == 0 ||
       (key_usage_bitfield & NX_SECURE_X509_KEY_USAGE_NON_REPUDIATION)   == 0 ||
       (key_usage_bitfield & NX_SECURE_X509_KEY_USAGE_KEY_ENCIPHERMENT)  == 0)
    {
        printf("Expected key usage bitfield bits not set!\n");
        return(NX_SECURE_X509_KEY_USAGE_ERROR);
    }

    /* Extended key usage - look for specific OIDs. */
    status = nx_secure_x509_extended_key_usage_extension_parse(certificate, NX_SECURE_TLS_X509_TYPE_PKIX_KP_TIME_STAMPING);

    if(status != NX_SUCCESS)
    {
        printf("Expected certificate extension not found!\n");
    }

    return(NX_SUCCESS);
}
#endif


/* Define the test threads.  */

/* -----===== SERVER =====----- */

/* Define a TLS name to test the Server Name Indication extension. */
#define TLS_SNI_SERVER_NAME "testing"

static CHAR *html_data =  "HTTP/1.1 200 OK\r\n" \
        "Date: Fri, 15 Sep 2016 23:59:59 GMT\r\n" \
        "Content-Type: text/html\r\n" \
        "Content-Length: 200\r\n\r\n" \
        "<html>\r\n"\
        "<body>\r\n"\
        "<b>Hello NetX Secure User!</b>\r\n"\
        "This is a simple webpage\r\n"\
        "served up using NetX Secure!\r\n"\
        "</body>\r\n"\
        "</html>\r\n";

#ifndef NX_SECURE_DISABLE_X509

/* Callback for ClientHello extensions processing. */
static ULONG tls_server_callback(NX_SECURE_TLS_SESSION *tls_session, NX_SECURE_TLS_HELLO_EXTENSION *extensions, UINT num_extensions)
{
NX_SECURE_X509_DNS_NAME dns_name;
INT compare_value;
UINT status;
NX_SECURE_X509_CERT *cert_ptr;

    /* Process clienthello extensions. */
    status = _nx_secure_tls_session_sni_extension_parse(tls_session, extensions, num_extensions, &dns_name);

#ifdef NX_SECURE_TLS_SNI_EXTENSION_DISABLED
    if(status != NX_SECURE_TLS_EXTENSION_NOT_FOUND)
    {
        printf("SNI extension should not exist\n");
        error_counter++;
    }
#else
    if(status != NX_SUCCESS)
    {
        printf("SNI extension parsing failed with status 0x%x\n", status);
        error_counter++;
    }

    /* NULL-terminate name string. */
    dns_name.nx_secure_x509_dns_name[dns_name.nx_secure_x509_dns_name_length] = 0;

    /* Make sure our SNI name matches. */
    compare_value = memcmp(dns_name.nx_secure_x509_dns_name, TLS_SNI_SERVER_NAME, strlen(TLS_SNI_SERVER_NAME));

    if(compare_value || dns_name.nx_secure_x509_dns_name_length != strlen(TLS_SNI_SERVER_NAME))
    {
        printf("Error in SNI processing. SNI name '%s' does not match '%s'\n", dns_name.nx_secure_x509_dns_name, TLS_SNI_SERVER_NAME);
        error_counter++;
    }
#endif

    /* Find a certificate based on it's unique ID. */
    _nx_secure_tls_server_certificate_find(tls_session, &cert_ptr, 1);

    /* Set the certificate we want to use. */
    nx_secure_tls_active_certificate_set(tls_session, cert_ptr);

    return(NX_SUCCESS);
}
#endif


static void    ntest_0_entry(ULONG thread_input)
{
UINT       status;
ULONG      actual_status;
NX_PACKET *send_packet;
NX_PACKET *receive_packet;
UCHAR receive_buffer[100];
ULONG bytes;
UINT connect_count;
UINT i;

    /* Print out test information banner.  */
    printf("NetX Secure Test:   TLS Two Way Client/Server Test.....................");

    /* Check for earlier error.  */
    if(error_counter)
    {
        printf("ERROR!\n");
        test_control_return(1);
    }

    /* Ensure the IP instance has been initialized.  */
    status = nx_ip_status_check(&ip_0, NX_IP_INITIALIZE_DONE, &actual_status, NX_IP_PERIODIC_RATE);

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_ip_status_check: 0x%x\n", status);
        error_counter++;
    }

    /* Create a socket.  */
    status = nx_tcp_socket_create(&ip_0, &server_socket, "Server Socket", 
                                  NX_IP_NORMAL, NX_FRAGMENT_OKAY, NX_IP_TIME_TO_LIVE * 100, 16*1024,
                                  NX_NULL, ntest_0_disconnect_received);

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_tcp_socket_create: 0x%x\n", status);
        error_counter++;
    }

    /* Create a TLS session for our socket.  */
    status =  nx_secure_tls_session_create(&server_tls_session,
                                           &nx_crypto_tls_ciphers,
                                           server_crypto_metadata,
                                           sizeof(server_crypto_metadata));

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_secure_tls_session_create: 0x%x\n", status);
        error_counter++;
    }

    /* Setup our packet reassembly buffer. */
    nx_secure_tls_session_packet_buffer_set(&server_tls_session, server_packet_buffer, sizeof(server_packet_buffer));

    /* Set a custom packet pool for TLS server. */
    nx_secure_tls_session_packet_pool_set(&server_tls_session, &pool_2);

#ifndef NX_SECURE_DISABLE_X509

    /* Enable Client Certificate Verification. */
    nx_secure_tls_session_x509_client_verify_configure(&server_tls_session, 2, remote_client_certs_buffer,
                                                       sizeof(remote_client_certs_buffer));

    /* Add a timestamp function for time checking and timestamps in the TLS handshake. */
    _nx_secure_tls_session_time_function_set(&server_tls_session, tls_timestamp_function);

    /* Setup the callback invoked when TLS has a certificate it wants to verify so we can
       do additional checks not done automatically by TLS. */
    _nx_secure_tls_session_certificate_callback_set(&server_tls_session, certificate_verification_callback);
    
    /* Set callback for server TLS extension handling. */
    _nx_secure_tls_session_server_callback_set(&server_tls_session, tls_server_callback);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Initialize our certificate
    status = nx_secure_x509_certificate_initialize(&certificate, test_device_cert_der, test_device_cert_der_len, NX_NULL, 0, test_device_cert_key_der, test_device_cert_key_der_len, NX_SECURE_X509_KEY_TYPE_RSA_PKCS1_DER);
    EXPECT_EQ(NX_SUCCESS, status);
    status = nx_secure_tls_server_certificate_add(&server_tls_session, &certificate, 1);
    EXPECT_EQ(NX_SUCCESS, status);

    status = nx_secure_x509_certificate_initialize(&server_certificate, test_server_cert_der, test_server_cert_der_len, NX_NULL, 0, test_server_cert_key_der, test_server_cert_key_der_len, NX_SECURE_X509_KEY_TYPE_RSA_PKCS1_DER);
    EXPECT_EQ(NX_SUCCESS, status);
    status = nx_secure_tls_server_certificate_add(&server_tls_session, &server_certificate, 2);
    EXPECT_EQ(NX_SUCCESS, status);

    /* Add a duplicate of the server certificate to make sure we handle duplicate certificates in the handshake. */
    status = nx_secure_x509_certificate_initialize(&duplicate_server_certificate, test_device_cert_der, test_device_cert_der_len, NX_NULL, 0, NULL, 0, NX_SECURE_X509_KEY_TYPE_NONE);
    EXPECT_EQ(NX_SUCCESS, status);
    status = nx_secure_tls_server_certificate_add(&server_tls_session, &duplicate_server_certificate, 2);
    EXPECT_EQ(NX_SECURE_TLS_CERT_ID_DUPLICATE, status);
    status = nx_secure_tls_server_certificate_add(&server_tls_session, &duplicate_server_certificate, 3);
    EXPECT_EQ(NX_SUCCESS, status);

    status = nx_secure_x509_certificate_initialize(&ica_certificate, ica_cert_der, ica_cert_der_len, NX_NULL, 0, NULL, 0, NX_SECURE_X509_KEY_TYPE_NONE);
    EXPECT_EQ(NX_SUCCESS, status);
    status = nx_secure_tls_local_certificate_add(&server_tls_session, &ica_certificate);
    EXPECT_EQ(NX_SUCCESS, status);

    /* Add a CA Certificate to our trusted store for verifying incoming client certificates. */
    status = nx_secure_x509_certificate_initialize(&trusted_certificate, ca_cert_der, ca_cert_der_len, NX_NULL, 0, NULL, 0, NX_SECURE_X509_KEY_TYPE_NONE);
    EXPECT_EQ(NX_SUCCESS, status);
    status = nx_secure_tls_trusted_certificate_add(&server_tls_session, &trusted_certificate);
    EXPECT_EQ(NX_SUCCESS, status);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

    /* Setup this thread to listen.  */
    status = nx_tcp_server_socket_listen(&ip_0, 12, &server_socket, 5, ntest_0_connect_received);

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_tcp_server_socket_listen: 0x%x\n", status);
        error_counter++;
    }

    /* Fill the large send buffer.  */
    for (i = 0; i < LARGE_SEND_SIZE; ++i)
    {
        large_app_data[i] = (UCHAR)(i & 0xFF);
    }

#ifdef NX_SECURE_ENABLE_PSK_CIPHERSUITES
    /* For PSK ciphersuites, add a PSK and identity hint.  */
    status = nx_secure_tls_psk_add(&server_tls_session, tls_psk, sizeof(tls_psk), "Client_identity", 15, "12345678", 8);
    if(status)
    {
        printf("Error in function nx_secure_tls_psk_add: 0x%x\n", status);
        error_counter++;
    }
#endif

    for(connect_count = 0; connect_count < TLS_CONNECT_TIMES; ++connect_count)
    {

        /* Accept a client socket connection.  */
        status = nx_tcp_server_socket_accept(&server_socket, NX_IP_PERIODIC_RATE);

        tx_thread_suspend(&ntest_0);


        /* Check for error.  */
        if(status)
        {
            printf("Error in function nx_tcp_server_socket_accept: 0x%x\n", status);
            error_counter++;
        }

        /* Start the TLS Session now that we have a connected socket. */
        status = nx_secure_tls_session_start(&server_tls_session, &server_socket, NX_WAIT_FOREVER);

        /* Check for error.  */
        if (status)
        {
            printf("TLS Server Session start failed, error: %x\n", status);
            error_counter++;
        }

        /* Receive the HTTP request, and print it out. */
        status = nx_secure_tls_session_receive(&server_tls_session, &receive_packet, NX_WAIT_FOREVER);
    
        /* Check for error.  */
        if (status)
        {
            printf("TLS Server receive failed, error: %x\n", status);
            error_counter++;
            return;
        }
        else
        {
            status = nx_packet_data_extract_offset(receive_packet, 0, receive_buffer, 100, &bytes);
            receive_buffer[bytes] = 0;

            if(bytes != 14)
            {
                printf("ERROR: data received by server does not match that sent by client.\n");
                error_counter++;
            }

            error_counter += strncmp((CHAR *)receive_buffer, "Hello there!\r\n", bytes);

            if(error_counter)
            {
                printf("Error in receiving data.\n");
            }

            //printf("Received data: %s\n", receive_buffer);

        }

        nx_packet_release(receive_packet);

        /* Allocate a return packet and send our HTML data back to the client. */

        nx_secure_tls_packet_allocate(&server_tls_session, &pool_0, &send_packet, NX_WAIT_FOREVER);
        nx_packet_data_append(send_packet, html_data, strlen(html_data), &pool_0, NX_WAIT_FOREVER);

        /* TLS send the HTML/HTTPS data back to the client. */
        status = nx_secure_tls_session_send(&server_tls_session, send_packet, NX_IP_PERIODIC_RATE);

        /* Check for error.  */
        if (status)
        {
              printf("Error in Server TLS send: %x\n", status);

              /* Release the packet.  */
              nx_packet_release(send_packet);
              error_counter++;
        }


        /* Receive the large application data. */
        status = nx_secure_tls_session_receive(&server_tls_session, &receive_packet, NX_WAIT_FOREVER);

        /* Check for error.  */
        if (status)
        {
            printf("TLS Server receive failed, error: %x\n", status);
            error_counter++;
        }
        else
        {
            memset(server_recv_buffer, 0, LARGE_SEND_SIZE);

            status = nx_packet_data_extract_offset(receive_packet, 0, server_recv_buffer, LARGE_SEND_SIZE, &bytes);

            if (bytes != LARGE_SEND_SIZE)
            {
                printf("ERROR: data received by server does not match that sent by client.\n");
                error_counter++;
            }

            /* Check the received buffer. */
            for (i = 0; i < LARGE_SEND_SIZE; ++i)
            {
                if (server_recv_buffer[i] != large_app_data[i])
                {
                    printf("ERROR: data received by server does not match that sent by client.\n");
                    error_counter++;
                    break;
                }
            }

        }

        nx_packet_release(receive_packet);


        /* Attempt a renegotiation after receiving. */
#ifndef NX_SECURE_TLS_DISABLE_SECURE_RENEGOTIATION
        status  = nx_secure_tls_session_renegotiate(&server_tls_session, NX_WAIT_FOREVER);

        if(status)
        {
            printf("TLS renegotiation request failed with error: 0x%x\n", status);
            error_counter++;
        }
#endif

        /* Allocate a return packet and send the large application data back to the client. */

        nx_secure_tls_packet_allocate(&server_tls_session, &pool_0, &send_packet, NX_WAIT_FOREVER);
        nx_packet_data_append(send_packet, large_app_data, LARGE_SEND_SIZE, &pool_0, NX_WAIT_FOREVER);

        /* TLS send the data back to the client. */
        status = nx_secure_tls_session_send(&server_tls_session, send_packet, NX_IP_PERIODIC_RATE);

        /* Check for error.  */
        if (status)
        {
            printf("Error in Server TLS send: %x\n", status);

            /* Release the packet.  */
            nx_packet_release(send_packet);
            error_counter++;
        }


        status = nx_secure_tls_session_receive(&server_tls_session, &receive_packet, NX_WAIT_FOREVER);

        /* Check for error.  */
        if (status)
        {
            printf("TLS Server receive failed, error: %x\n", status);
            error_counter++;
            return;
        }

        nx_packet_release(receive_packet);

        /* Attempt another renegotiation. */
#ifndef NX_SECURE_TLS_DISABLE_SECURE_RENEGOTIATION
        status  = nx_secure_tls_session_renegotiate(&server_tls_session, NX_WAIT_FOREVER);

        if(status)
        {
            printf("TLS renegotiation request failed with error: 0x%x\n", status);
            error_counter++;
        }
#endif

        nx_secure_tls_packet_allocate(&server_tls_session, &pool_0, &send_packet, NX_WAIT_FOREVER);
        nx_packet_data_append(send_packet, html_data, strlen(html_data), &pool_0, NX_WAIT_FOREVER);

        /* TLS send some data back to the client. */
        status = nx_secure_tls_session_send(&server_tls_session, send_packet, NX_IP_PERIODIC_RATE);

        /* Check for error.  */
        if (status)
        {
              printf("Error in Server TLS send: %x\n", status);

              /* Release the packet.  */
              nx_packet_release(send_packet);
              error_counter++;
        }

        tx_thread_sleep(10);

        /* End the TLS session. This is required to properly shut down the TLS connection. */
        status = nx_secure_tls_session_end(&server_tls_session, NX_WAIT_FOREVER);

        /* If the session did not shut down cleanly, this is a possible security issue. */
        if (status)
        {
              printf("Error in TLS Server session end: %x\n", status);
              error_counter++;
        }

        /* Disconnect the server socket.  */
        status = nx_tcp_socket_disconnect(&server_socket, NX_WAIT_FOREVER); // NX_IP_PERIODIC_RATE * 10);

        /* Check for error.  */
        if(status)
        {
            printf("Error in function nx_tcp_socket_disconnect: 0x%x\n", status);
            error_counter++;
        }

        /* Unaccept the server socket.  */
        status = nx_tcp_server_socket_unaccept(&server_socket);

        /* Check for error.  */
        if(status)
        {
            printf("Error in function nx_tcp_server_socket_unaccept: 0x%x\n", status);
            error_counter++;
        }

        /* Unlisten on the server port.  */
        status = nx_tcp_server_socket_relisten(&ip_0, 12, &server_socket);

        /* Check for error.  */
        if (status)
        {
            printf("Error in function nx_tcp_server_socket_relisten: 0x%x\n", status);
            error_counter++;
        }


    } /* End connect loop. */

    /* Unlisten on the server port.  */
    status = nx_tcp_server_socket_unlisten(&ip_0, 12);

    /* Check for error.  */
    if (status)
    {
        printf("Error in function nx_tcp_server_socket_unlisten: 0x%x\n", status);
        error_counter++;
    }

    /* Delete TLS session. */
    status = nx_secure_tls_session_delete(&server_tls_session);

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_secure_tls_session_delete: 0x%x\n", status);
        error_counter++;
    }

    /* Delete the socket.  */
    status = nx_tcp_socket_delete(&server_socket);

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_tcp_socket_delete: 0x%x\n", status);
        error_counter++;
    }
}



/* -----===== CLIENT =====----- */

static ULONG tls_client_callback(NX_SECURE_TLS_SESSION *tls_session, NX_SECURE_TLS_HELLO_EXTENSION *extensions, UINT num_extensions)
{
    /* Process serverhello extensions. */
    return(NX_SUCCESS);
}


static void    ntest_1_entry(ULONG thread_input)
{
UINT         status;
NX_PACKET *send_packet;
NX_PACKET *receive_packet;
UCHAR receive_buffer[400];
ULONG bytes;
UINT connect_count;
UINT i;
NX_SECURE_X509_DNS_NAME dns_name;

    /* Create a socket.  */
    status = nx_tcp_socket_create(&ip_1, &client_socket, "Client Socket", 
                                  NX_IP_NORMAL, NX_FRAGMENT_OKAY, NX_IP_TIME_TO_LIVE * 100, 1024*16,
                                  NX_NULL, NX_NULL);

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_tcp_socket_create: 0x%x\n", status);
        error_counter++;
    }


    /* Create a TLS session for our socket.  */
    status =  nx_secure_tls_session_create(&client_tls_session,
                                           &nx_crypto_tls_ciphers,
                                           client_crypto_metadata,
                                           sizeof(client_crypto_metadata));

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_secure_tls_session_create: 0x%x\n", status);
        error_counter++;
    }


    /* Setup our packet reassembly buffer. */
    nx_secure_tls_session_packet_buffer_set(&client_tls_session, client_packet_buffer, sizeof(client_packet_buffer));

#ifndef NX_SECURE_DISABLE_X509

    /* Make sure client certificate verification is disabled. */
    nx_secure_tls_session_client_verify_disable(&client_tls_session);

    /* Need to allocate space for the certificate coming in from the remote host. */
    nx_secure_tls_remote_certificate_buffer_allocate(&client_tls_session, 2, remote_server_certs_buffer, sizeof(remote_server_certs_buffer));

    //nx_secure_x509_certificate_initialize(&certificate, cert_der, cert_der_len, NX_NULL, 0, private_key_der, private_key_der_len, NX_SECURE_X509_KEY_TYPE_RSA_PKCS1_DER);
    nx_secure_x509_certificate_initialize(&client_certificate, test_device_cert_der, test_device_cert_der_len, NX_NULL, 0, test_device_cert_key_der, test_device_cert_key_der_len, NX_SECURE_X509_KEY_TYPE_RSA_PKCS1_DER);
    nx_secure_tls_local_certificate_add(&client_tls_session, &client_certificate);

    /* Add a CA Certificate to our trusted store for verifying incoming server certificates. */
    nx_secure_x509_certificate_initialize(&trusted_certificate, ca_cert_der, ca_cert_der_len, NX_NULL, 0, NULL, 0, NX_SECURE_X509_KEY_TYPE_NONE);
    nx_secure_tls_trusted_certificate_add(&client_tls_session, &trusted_certificate);


    /* Add a timestamp function for time checking and timestamps in the TLS handshake. */
    _nx_secure_tls_session_time_function_set(&client_tls_session, tls_timestamp_function);

    /* Setup the callback invoked when TLS has a certificate it wants to verify so we can
       do additional checks not done automatically by TLS. */
    _nx_secure_tls_session_certificate_callback_set(&client_tls_session, certificate_verification_callback);

    /* Set callback for server TLS extension handling. */
    _nx_secure_tls_session_client_callback_set(&client_tls_session, tls_client_callback);


    /* Set up a DNS name for the Server Name Indication extension. The server thread will compare
     * to make sure the name was sent and recieved appropriately. */
    nx_secure_x509_dns_name_initialize(&dns_name, TLS_SNI_SERVER_NAME, strlen(TLS_SNI_SERVER_NAME));
    nx_secure_tls_session_sni_extension_set(&client_tls_session, &dns_name);
#endif

#ifdef NX_SECURE_ENABLE_PSK_CIPHERSUITES
    /* For PSK ciphersuites, add a PSK and identity hint.  For the client, we need to add the identity
       and set it for the particular server with which we want to communicate.
       "Client_identity" is the identity hint used by default in the OpenSSL s_server application
       when uisng PSK ciphersuites. */
    status = nx_secure_tls_psk_add(&client_tls_session, tls_psk, sizeof(tls_psk), "Client_identity", 15, "12345678", 8);
    if(status)
    {
        printf("Error in function nx_secure_tls_psk_add: 0x%x\n", status);
        error_counter++;
    }

    /* Our target server will use this PSK entry. */
    status = nx_secure_tls_client_psk_set(&client_tls_session, tls_psk, sizeof(tls_psk), "Client_identity", 15, "12345678", 8);
    if(status)
    {
        printf("Error in function nx_secure_tls_client_psk_set: 0x%x\n", status);
        error_counter++;
    }

#endif

    /* Connect multiple times. */
    for(connect_count = 0; connect_count < TLS_CONNECT_TIMES; ++connect_count)
    {
        /* Bind the socket.  */
        status = nx_tcp_client_socket_bind(&client_socket, 12, NX_IP_PERIODIC_RATE);

        /* Check for error.  */
        if(status)
        {
            printf("Error in function nx_tcp_client_socket_bind: 0x%x\n", status);
            error_counter++;
        }

        status = nx_tcp_client_socket_connect(&client_socket, IP_ADDRESS(1, 2, 3, 4), 12, 5 * NX_IP_PERIODIC_RATE);

        if(status)
        {
            printf("Error in function nx_tcp_client_socket_connect: 0x%x\n", status);
            error_counter++;
        }

        tx_thread_resume(&ntest_0);

        status = nx_secure_tls_session_start(&client_tls_session, &client_socket, NX_WAIT_FOREVER);

        /* Check for error.  */
        if (status)
        {
            printf("Error in Client TLS handshake: 0x%02X\n", status);
            printf("ERROR!\n");
            test_control_return(1);
        }

        /* Send some data to be read by the server thread instance. */
        nx_secure_tls_packet_allocate(&client_tls_session, &pool_1, &send_packet, NX_WAIT_FOREVER);
        nx_packet_data_append(send_packet, "Hello there!\r\n", 14, &pool_1, NX_WAIT_FOREVER);
        status = nx_secure_tls_session_send(&client_tls_session, send_packet, NX_IP_PERIODIC_RATE);

        /* Check for error.  */
        if (status)
        {
              printf("Error in Client TLS send: %x\n", status);

              /* Release the packet.  */
              nx_packet_release(send_packet);
              error_counter++;
        }

        /* Receive the echoed and reversed data, and print it out. */
        status = nx_secure_tls_session_receive(&client_tls_session, &receive_packet, NX_WAIT_FOREVER);

        /* Check for error.  */
        if (status)
        {
            printf("TLS receive failed in Client, error: %x\n", status);
            error_counter++;
        }
        else
        {
            status = nx_packet_data_extract_offset(receive_packet, 0, receive_buffer, 400, &bytes);
            receive_buffer[bytes] = 0;
            if(strlen(html_data) != bytes)
            {
                printf("Error: received data on client does not match that sent by server. \n");
                error_counter++;
            }
            error_counter += strncmp((CHAR *)receive_buffer, html_data, strlen(html_data));
            
            if(error_counter)
            {
                printf("Error in received data from server\n");
            }
            //printf("Received data: %s\n", receive_buffer);
        }

        /* Attempt a renegotiation after receiving. */
#ifndef NX_SECURE_TLS_DISABLE_SECURE_RENEGOTIATION
#ifndef NX_SECURE_TLS_DISABLE_CLIENT_INITIATED_RENEGOTIATION
        status  = nx_secure_tls_session_renegotiate(&client_tls_session, NX_WAIT_FOREVER);

        if(status)
        {
            printf("TLS renegotiation request failed with error: 0x%x\n", status);
            error_counter++;
        }
#endif
#endif	

        nx_packet_release(receive_packet);

        /* Send a large data to the server. */
        nx_secure_tls_packet_allocate(&client_tls_session, &pool_1, &send_packet, NX_WAIT_FOREVER);
        nx_packet_data_append(send_packet, large_app_data, LARGE_SEND_SIZE, &pool_1, NX_WAIT_FOREVER);
        status = nx_secure_tls_session_send(&client_tls_session, send_packet, NX_IP_PERIODIC_RATE);

        /* Check for error.  */
        if (status)
        {
            printf("Error in Client TLS send: %x\n", status);

            /* Release the packet.  */
            nx_packet_release(send_packet);
            error_counter++;
        }

        /* Receive the large data. */
        status = nx_secure_tls_session_receive(&client_tls_session, &receive_packet, NX_WAIT_FOREVER);

        /* Check for error.  */
        if (status)
        {
            printf("TLS receive failed in Client, error: %x\n", status);
            error_counter++;
        }
        else
        {
            memset(client_recv_buffer, 0, LARGE_SEND_SIZE);
            status = nx_packet_data_extract_offset(receive_packet, 0, client_recv_buffer, LARGE_SEND_SIZE, &bytes);
            
            if (LARGE_SEND_SIZE != bytes)
            {
                printf("Error: received data on client does not match that sent by server. \n");
                error_counter++;
            }
            
            /* Check the received buffer. */
            for (i = 0; i < LARGE_SEND_SIZE; ++i)
            {
                if (client_recv_buffer[i] != large_app_data[i])
                {
                    printf("Error: received data on client does not match that sent by server. \n");
                    error_counter++;
                    break;
                }
            }
        }
        nx_packet_release(receive_packet);

        /* Send some data to be read by the server thread instance. */
        nx_secure_tls_packet_allocate(&client_tls_session, &pool_1, &send_packet, NX_WAIT_FOREVER);
        nx_packet_data_append(send_packet, "Hello there!\r\n", 14, &pool_1, NX_WAIT_FOREVER);
        status = nx_secure_tls_session_send(&client_tls_session, send_packet, NX_IP_PERIODIC_RATE);

        /* Check for error.  */
        if (status)
        {
              printf("Error in Client TLS send: %x\n", status);

              /* Release the packet.  */
              nx_packet_release(send_packet);
              error_counter++;
        }

        receive_packet = NX_NULL;

        /* Test receive in non blocking mode. */
        do
        {
            status = nx_secure_tls_session_receive(&client_tls_session, &receive_packet, NX_NO_WAIT);
        }while(status == NX_CONTINUE || status == NX_NO_PACKET);

        /* Check for error.  */
        if (status)
        {
            printf("TLS non-blocking receive failed in Client, error: %x\n", status);
            error_counter++;
        }
        else
        {
            status = nx_packet_data_extract_offset(receive_packet, 0, receive_buffer, 400, &bytes);
            receive_buffer[bytes] = 0;
            if(strlen(html_data) != bytes)
            {
                printf("Error: received data on client does not match that sent by server. \n");
                error_counter++;
            }
            error_counter += strncmp((CHAR *)receive_buffer, html_data, strlen(html_data));

            if(error_counter)
            {
                printf("Error in received data from server\n");
            }
            nx_packet_release(receive_packet);
        }

        /* Test nx_secure_tls_session_send for send_packet with insufficient header room. */
        nx_packet_allocate(&pool_1, &send_packet, 0, NX_WAIT_FOREVER);
        nx_packet_data_append(send_packet, "Hello there!\r\n", 14, &pool_1, NX_WAIT_FOREVER);
        status = nx_secure_tls_session_send(&client_tls_session, send_packet, NX_IP_PERIODIC_RATE);
        if (status != NX_SECURE_TLS_INVALID_PACKET)
        {
            printf("Expected NX_SECURE_TLS_INVALID_PACKET but got %x\n", status);
            error_counter++;
        }
        nx_packet_release(send_packet);

        tx_thread_sleep(10);

        /* End the TLS session. This is required to properly shut down the TLS connection. */
        status = nx_secure_tls_session_end(&client_tls_session, NX_WAIT_FOREVER);
    
        /* If the session did not shut down cleanly, this is a possible security issue. */
        if (status)
        {
            printf("Error in TLS Client session end: %x\n", status);
            error_counter++;
        }


        /* Disconnect this socket.  */
        status = nx_tcp_socket_disconnect(&client_socket, NX_WAIT_FOREVER); //NX_IP_PERIODIC_RATE * 10);

        /* Check for error.  */
        if(status)
        {
            printf("Error in function nx_tcp_socket_disconnect: 0x%x\n", status);
            error_counter++;
        }

        /* Bind the socket.  */
        status = nx_tcp_client_socket_unbind(&client_socket);

        /* Check for error.  */
        if(status)
        {
            printf("Error in function nx_tcp_client_socket_unbind: 0x%x\n", status);
            error_counter++;
        }

    } /* End connect loop. */

    /* Delete TLS session. */
    status = nx_secure_tls_session_delete(&client_tls_session);

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_secure_tls_session_delete: %x\n", status);
        error_counter++;
    }

    /* Delete the socket.  */
    status = nx_tcp_socket_delete(&client_socket);

    /* Check for error.  */
    if(status)
    {
        printf("Error in function nx_tcp_socket_delete: %x\n", status);
        error_counter++;
    }

    /* Shutdown the TLS services. */
    nx_secure_tls_shutdown();

    EXPECT_EQ(pool_0.nx_packet_pool_total, pool_0.nx_packet_pool_available);
    EXPECT_EQ(pool_1.nx_packet_pool_total, pool_1.nx_packet_pool_available);

    /* Determine if the test was successful.  */
    if(error_counter)
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

static void    ntest_0_connect_received(NX_TCP_SOCKET *socket_ptr, UINT port)
{

    /* Check for the proper socket and port.  */
    if((socket_ptr != &server_socket) || (port != 12))
        error_counter++;
}

static void    ntest_0_disconnect_received(NX_TCP_SOCKET *socket)
{

    /* Check for proper disconnected socket.  */
    if(socket != &server_socket)
        error_counter++;
}
#else
#ifdef CTEST
void test_application_define(void *first_unused_memory);
void test_application_define(void *first_unused_memory)
#else
VOID    nx_secure_tls_two_way_test_application_define(void *first_unused_memory)
#endif
{

    /* Print out test information banner.  */
    printf("NetX Secure Test:   TLS Two Way Client/Server Test.....................N/A\n");
    test_control_return(3);
}
#endif
