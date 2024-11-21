
#include "nx_api.h"

#ifdef __PRODUCT_NETXDUO__

#include "netx_mdns_test.h"
/* Frame (75 bytes) */
static const unsigned char pkt1[75] = {
0x01, 0x00, 0x5e, 0x00, 0x00, 0xfb, 0x00, 0x11, /* ..^..... */
0x22, 0x33, 0x44, 0x56, 0x08, 0x00, 0x45, 0x00, /* "3DV..E. */
0x00, 0x3d, 0x00, 0x07, 0x40, 0x00, 0xff, 0x11, /* .=..@... */
0xd9, 0xc2, 0xc0, 0xa8, 0x00, 0x42, 0xe0, 0x00, /* .....B.. */
0x00, 0xfb, 0x14, 0xe9, 0x14, 0xe9, 0x00, 0x29, /* .......) */
0xb3, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x5f, /* ......._ */
0x73, 0x6d, 0x62, 0x04, 0x5f, 0x74, 0x63, 0x70, /* smb._tcp */
0x05, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x00, 0x00, /* .local.. */
0x0c, 0x00, 0x01                                /* ... */
};

/* Frame (332 bytes) */
static const unsigned char pkt2[332] = {
0x01, 0x00, 0x5e, 0x00, 0x00, 0xfb, 0x18, 0x03, /* ..^..... */
0x73, 0x33, 0xc1, 0xbd, 0x08, 0x00, 0x45, 0x00, /* s3....E. */
0x01, 0x3e, 0x09, 0x17, 0x00, 0x00, 0xff, 0x11, /* .>...... */
0x0f, 0x8f, 0xc0, 0xa8, 0x00, 0x65, 0xe0, 0x00, /* .....e.. */
0x00, 0xfb, 0x14, 0xe9, 0x14, 0xe9, 0x01, 0x2a, /* .......* */
0x56, 0xdc, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, /* V....... */
0x00, 0x02, 0x00, 0x00, 0x00, 0x07, 0x04, 0x5f, /* ......._ */
0x73, 0x6d, 0x62, 0x04, 0x5f, 0x74, 0x63, 0x70, /* smb._tcp */
0x05, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x00, 0x00, /* .local.. */
0x0c, 0x00, 0x01, 0x00, 0x00, 0x11, 0x94, 0x00, /* ........ */
0x0c, 0x09, 0x43, 0x68, 0x65, 0x6e, 0x62, 0x6f, /* ..Chenbo */
0x2d, 0x50, 0x43, 0xc0, 0x0c, 0x09, 0x43, 0x68, /* -PC...Ch */
0x65, 0x6e, 0x62, 0x6f, 0x2d, 0x50, 0x43, 0x0c, /* enbo-PC. */
0x5f, 0x64, 0x65, 0x76, 0x69, 0x63, 0x65, 0x2d, /* _device- */
0x69, 0x6e, 0x66, 0x6f, 0xc0, 0x11, 0x00, 0x10, /* info.... */
0x00, 0x01, 0x00, 0x00, 0x11, 0x94, 0x00, 0x0e, /* ........ */
0x0d, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x3d, 0x57, /* .model=W */
0x69, 0x6e, 0x64, 0x6f, 0x77, 0x73, 0xc0, 0x27, /* indows.' */
0x00, 0x21, 0x80, 0x01, 0x00, 0x00, 0x00, 0x78, /* .!.....x */
0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x01, 0xbd, /* ........ */
0x09, 0x43, 0x68, 0x65, 0x6e, 0x62, 0x6f, 0x2d, /* .Chenbo- */
0x50, 0x43, 0xc0, 0x16, 0xc0, 0x27, 0x00, 0x10, /* PC...'.. */
0x80, 0x01, 0x00, 0x00, 0x11, 0x94, 0x00, 0x23, /* .......# */
0x11, 0x6e, 0x65, 0x74, 0x62, 0x69, 0x6f, 0x73, /* .netbios */
0x3d, 0x43, 0x48, 0x45, 0x4e, 0x42, 0x4f, 0x2d, /* =CHENBO- */
0x50, 0x43, 0x10, 0x64, 0x6f, 0x6d, 0x61, 0x69, /* PC.domai */
0x6e, 0x3d, 0x57, 0x4f, 0x52, 0x4b, 0x47, 0x52, /* n=WORKGR */
0x4f, 0x55, 0x50, 0xc0, 0x76, 0x00, 0x01, 0x80, /* OUP.v... */
0x01, 0x00, 0x00, 0x00, 0x78, 0x00, 0x04, 0xc0, /* ....x... */
0xa8, 0x00, 0x65, 0xc0, 0x76, 0x00, 0x1c, 0x80, /* ..e.v... */
0x01, 0x00, 0x00, 0x00, 0x78, 0x00, 0x10, 0x20, /* ....x..  */
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0xc0, /* ......1. */
0x76, 0x00, 0x1c, 0x80, 0x01, 0x00, 0x00, 0x00, /* v....... */
0x78, 0x00, 0x10, 0xfe, 0x80, 0x00, 0x00, 0x00, /* x....... */
0x00, 0x00, 0x00, 0x01, 0x59, 0x44, 0x79, 0xe1, /* ....YDy. */
0x0a, 0xd7, 0xf4, 0xc0, 0x27, 0x00, 0x2f, 0x80, /* ....'./. */
0x01, 0x00, 0x00, 0x00, 0x78, 0x00, 0x09, 0xc0, /* ....x... */
0x27, 0x00, 0x05, 0x00, 0x00, 0x80, 0x00, 0x40, /* '......@ */
0xc0, 0x76, 0x00, 0x2f, 0x80, 0x01, 0x00, 0x00, /* .v./.... */
0x00, 0x78, 0x00, 0x08, 0xc0, 0x76, 0x00, 0x04, /* .x...v.. */
0x40, 0x00, 0x00, 0x08                          /* @... */
};

/* Frame (129 bytes) */
static const unsigned char pkt3[129] = {
0x01, 0x00, 0x5e, 0x00, 0x00, 0xfb, 0x00, 0x11, /* ..^..... */
0x22, 0x33, 0x44, 0x56, 0x08, 0x00, 0x45, 0x00, /* "3DV..E. */
0x00, 0x73, 0x00, 0x08, 0x40, 0x00, 0xff, 0x11, /* .s..@... */
0xd9, 0x8b, 0xc0, 0xa8, 0x00, 0x42, 0xe0, 0x00, /* .....B.. */
0x00, 0xfb, 0x14, 0xe9, 0x14, 0xe9, 0x00, 0x5f, /* ......._ */
0x9d, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, /* ........ */
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x04, 0x5f, /* ......._ */
0x73, 0x6d, 0x62, 0x04, 0x5f, 0x74, 0x63, 0x70, /* smb._tcp */
0x05, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x00, 0x00, /* .local.. */
0x0c, 0x00, 0x01, 0x04, 0x5f, 0x73, 0x6d, 0x62, /* ...._smb */
0x04, 0x5f, 0x74, 0x63, 0x70, 0x05, 0x6c, 0x6f, /* ._tcp.lo */
0x63, 0x61, 0x6c, 0x00, 0x00, 0x0c, 0x00, 0x01, /* cal..... */
0x00, 0x00, 0x11, 0x93, 0x00, 0x1b, 0x09, 0x43, /* .......C */
0x68, 0x65, 0x6e, 0x62, 0x6f, 0x2d, 0x50, 0x43, /* henbo-PC */
0x04, 0x5f, 0x73, 0x6d, 0x62, 0x04, 0x5f, 0x74, /* ._smb._t */
0x63, 0x70, 0x05, 0x6c, 0x6f, 0x63, 0x61, 0x6c, /* cp.local */
0x00                                            /* . */
};

/* Frame (129 bytes) */
static const unsigned char pkt4[129] = {
0x01, 0x00, 0x5e, 0x00, 0x00, 0xfb, 0x00, 0x11, /* ..^..... */
0x22, 0x33, 0x44, 0x56, 0x08, 0x00, 0x45, 0x00, /* "3DV..E. */
0x00, 0x73, 0x00, 0x09, 0x40, 0x00, 0xff, 0x11, /* .s..@... */
0xd9, 0x8a, 0xc0, 0xa8, 0x00, 0x42, 0xe0, 0x00, /* .....B.. */
0x00, 0xfb, 0x14, 0xe9, 0x14, 0xe9, 0x00, 0x5f, /* ......._ */
0x9d, 0xeb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, /* ........ */
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x04, 0x5f, /* ......._ */
0x73, 0x6d, 0x62, 0x04, 0x5f, 0x74, 0x63, 0x70, /* smb._tcp */
0x05, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x00, 0x00, /* .local.. */
0x0c, 0x00, 0x01, 0x04, 0x5f, 0x73, 0x6d, 0x62, /* ...._smb */
0x04, 0x5f, 0x74, 0x63, 0x70, 0x05, 0x6c, 0x6f, /* ._tcp.lo */
0x63, 0x61, 0x6c, 0x00, 0x00, 0x0c, 0x00, 0x01, /* cal..... */
0x00, 0x00, 0x11, 0x91, 0x00, 0x1b, 0x09, 0x43, /* .......C */
0x68, 0x65, 0x6e, 0x62, 0x6f, 0x2d, 0x50, 0x43, /* henbo-PC */
0x04, 0x5f, 0x73, 0x6d, 0x62, 0x04, 0x5f, 0x74, /* ._smb._t */
0x63, 0x70, 0x05, 0x6c, 0x6f, 0x63, 0x61, 0x6c, /* cp.local */
0x00                                            /* . */
};

static MDNS_QUERY_INFO mdns_query = {NX_NULL, "_smb._tcp", NX_NULL};

MDNS_TEST_SEQ mdns_query_smb_tcp[] = {
    {TITLE, "Query _smb._tcp", 15, 0},
    
    {MDNS_QUERY, (char*)&mdns_query, 0, 0},
    {MDNS_CHECK_DATA_V4, (char*)&pkt1[0], sizeof(pkt1), 5},
    {INJECT, (char*)&pkt2[0], sizeof(pkt2), 0},
    {MDNS_CHECK_DATA_V4, (char*)&pkt3[0], sizeof(pkt3), 5},
};

int mdns_query_smb_tcp_size = sizeof(mdns_query_smb_tcp) / sizeof(MDNS_TEST_SEQ);

#endif /* __PRODUCT_NETXDUO__  */

