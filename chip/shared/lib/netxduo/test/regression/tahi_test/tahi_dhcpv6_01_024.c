#include "nx_api.h"
#if defined(NX_TAHI_ENABLE) && defined(FEATURE_NX_IPV6)  
#include "netx_tahi.h"

#if 0
/* Frame (110 bytes) */
static char pkt1[110] = {
    0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, /* 33...... */
    0x00, 0x00, 0xa6, 0xa6, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
    0x00, 0x00, 0x00, 0x38, 0x3a, 0xff, 0xfe, 0x80, /* ...8:... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
    0x00, 0xff, 0xfe, 0x00, 0xa6, 0xa6, 0xff, 0x02, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, /* ........ */
    0x42, 0x9e, 0x00, 0x80, 0x0b, 0xb8, 0x00, 0x00, /* B....... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0xa6, 0xa6, 0x03, 0x04, /* ........ */
    0x40, 0x80, 0x00, 0x00, 0x38, 0x40, 0x00, 0x00, /* @...8@.. */
    0x1c, 0x20, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, /* . ....?. */
    0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00              /* ...... */
};

/* Frame (70 bytes) */
static char pkt2[70] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
    0x00, 0x00, 0xa1, 0xa1, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
    0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0x3f, 0xfe, /* ....:@?. */
    0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x00, /* ........ */
    0x00, 0xff, 0xfe, 0x00, 0xa1, 0xa1, 0x3f, 0xfe, /* ......?. */
    0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, /* "..3DV.. */
    0xe9, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* .z...... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00              /* ...... */
};
#endif

/* Frame (118 bytes) */
static char pkt3[118] = {
    0x33, 0x33, 0x00, 0x01, 0x00, 0x02, 0x00, 0x11, /* 33...... */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x40, 0x11, 0xff, 0xfe, 0x80, /* ...@.... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x02, 0x22, /* ......." */
    0x02, 0x23, 0x00, 0x40, 0x6d, 0x29, 0x01, 0x3e, /* .#.@m).> */
    0xf0, 0x12, 0x00, 0x01, 0x00, 0x0e, 0x00, 0x01, /* ........ */
    0x00, 0x01, 0xac, 0x7d, 0x87, 0x3a, 0x00, 0x11, /* ...}.:.. */
    0x22, 0x33, 0x44, 0x56, 0x00, 0x03, 0x00, 0x0c, /* "3DV.... */
    0xc0, 0xde, 0xdb, 0xad, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x02, /* ........ */
    0x00, 0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x17, /* ........ */
    0x00, 0x1f, 0x00, 0x29, 0x00, 0x18              /* ...).. */
    };

/* Frame (146 bytes) */
static char pkt4[146] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, /* .."3DV.. */
    0x00, 0x00, 0xa1, 0xa1, 0x86, 0xdd, 0x60, 0x00, /* ......`. */
    0x00, 0x00, 0x00, 0x5c, 0x11, 0x40, 0xfe, 0x80, /* ...\.@.. */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, /* ........ */
    0x00, 0xff, 0xfe, 0x00, 0xa1, 0xa1, 0xfe, 0x80, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x02, 0x22, /* "..3DV." */
    0x02, 0x22, 0x00, 0x5c, 0x1a, 0x77, 0x02, 0x3e, /* .".\.w.> */
    0xf0, 0x12, 0x00, 0x01, 0x00, 0x0e, 0x00, 0x01, /* ........ */
    0x00, 0x01, 0xac, 0x7d, 0x87, 0x3a, 0x00, 0x11, /* ...}.:.. */
    0x22, 0x33, 0x44, 0x56, 0x00, 0x02, 0x00, 0x0e, /* "3DV.... */
    0x00, 0x01, 0x00, 0x01, 0x00, 0x06, 0x1a, 0x80, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0xa1, 0xa1, 0x00, 0x03, /* ........ */
    0x00, 0x28, 0xc0, 0xde, 0xdb, 0xad, 0x00, 0x00, /* .(...... */
    0x00, 0x32, 0x00, 0x00, 0x00, 0x50, 0x00, 0x05, /* .2...P.. */
    0x00, 0x18, 0x3f, 0xfe, 0x05, 0x01, 0xff, 0xff, /* ..?..... */
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0xab, 0xcd, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, /* .....d.. */
    0x00, 0xc8                                      /* .. */
    };

/* Frame (164 bytes) */
static char pkt5[164] = {
    0x33, 0x33, 0x00, 0x01, 0x00, 0x02, 0x00, 0x11, /* 33...... */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x6e, 0x11, 0xff, 0xfe, 0x80, /* ...n.... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x02, 0x22, /* ......." */
    0x02, 0x23, 0x00, 0x6e, 0x9c, 0x98, 0x03, 0x08, /* .#.n.... */
    0x0e, 0x90, 0x00, 0x01, 0x00, 0x0e, 0x00, 0x01, /* ........ */
    0x00, 0x01, 0xac, 0x7d, 0x87, 0x3a, 0x00, 0x11, /* ...}.:.. */
    0x22, 0x33, 0x44, 0x56, 0x00, 0x08, 0x00, 0x02, /* "3DV.... */
    0x00, 0x00, 0x00, 0x02, 0x00, 0x0e, 0x00, 0x01, /* ........ */
    0x00, 0x01, 0x00, 0x06, 0x1a, 0x80, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0xa1, 0xa1, 0x00, 0x03, 0x00, 0x28, /* .......( */
    0xc0, 0xde, 0xdb, 0xad, 0x00, 0x00, 0x00, 0x32, /* .......2 */
    0x00, 0x00, 0x00, 0x50, 0x00, 0x05, 0x00, 0x18, /* ...P.... */
    0x3f, 0xfe, 0x05, 0x01, 0xff, 0xff, 0x01, 0x00, /* ?....... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0xcd, /* ........ */
    0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0xc8, /* ...d.... */
    0x00, 0x06, 0x00, 0x08, 0x00, 0x17, 0x00, 0x1f, /* ........ */
    0x00, 0x29, 0x00, 0x18                          /* .).. */
    };

#if 0
/* Frame (164 bytes) */
static char pkt6[164] = {
    0x33, 0x33, 0x00, 0x01, 0x00, 0x02, 0x00, 0x11, /* 33...... */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x6e, 0x11, 0xff, 0xfe, 0x80, /* ...n.... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x02, 0x22, /* ......." */
    0x02, 0x23, 0x00, 0x6e, 0x9c, 0x34, 0x03, 0x08, /* .#.n.4.. */
    0x0e, 0x90, 0x00, 0x01, 0x00, 0x0e, 0x00, 0x01, /* ........ */
    0x00, 0x01, 0xac, 0x7d, 0x87, 0x3a, 0x00, 0x11, /* ...}.:.. */
    0x22, 0x33, 0x44, 0x56, 0x00, 0x08, 0x00, 0x02, /* "3DV.... */
    0x00, 0x64, 0x00, 0x02, 0x00, 0x0e, 0x00, 0x01, /* .d...... */
    0x00, 0x01, 0x00, 0x06, 0x1a, 0x80, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0xa1, 0xa1, 0x00, 0x03, 0x00, 0x28, /* .......( */
    0xc0, 0xde, 0xdb, 0xad, 0x00, 0x00, 0x00, 0x32, /* .......2 */
    0x00, 0x00, 0x00, 0x50, 0x00, 0x05, 0x00, 0x18, /* ...P.... */
    0x3f, 0xfe, 0x05, 0x01, 0xff, 0xff, 0x01, 0x00, /* ?....... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0xcd, /* ........ */
    0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0xc8, /* ...d.... */
    0x00, 0x06, 0x00, 0x08, 0x00, 0x17, 0x00, 0x1f, /* ........ */
    0x00, 0x29, 0x00, 0x18                          /* .).. */
    };

/* Frame (164 bytes) */
static char pkt7[164] = {
    0x33, 0x33, 0x00, 0x01, 0x00, 0x02, 0x00, 0x11, /* 33...... */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x6e, 0x11, 0xff, 0xfe, 0x80, /* ...n.... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x02, 0x22, /* ......." */
    0x02, 0x23, 0x00, 0x6e, 0x9b, 0x6c, 0x03, 0x08, /* .#.n.l.. */
    0x0e, 0x90, 0x00, 0x01, 0x00, 0x0e, 0x00, 0x01, /* ........ */
    0x00, 0x01, 0xac, 0x7d, 0x87, 0x3a, 0x00, 0x11, /* ...}.:.. */
    0x22, 0x33, 0x44, 0x56, 0x00, 0x08, 0x00, 0x02, /* "3DV.... */
    0x01, 0x2c, 0x00, 0x02, 0x00, 0x0e, 0x00, 0x01, /* .,...... */
    0x00, 0x01, 0x00, 0x06, 0x1a, 0x80, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0xa1, 0xa1, 0x00, 0x03, 0x00, 0x28, /* .......( */
    0xc0, 0xde, 0xdb, 0xad, 0x00, 0x00, 0x00, 0x32, /* .......2 */
    0x00, 0x00, 0x00, 0x50, 0x00, 0x05, 0x00, 0x18, /* ...P.... */
    0x3f, 0xfe, 0x05, 0x01, 0xff, 0xff, 0x01, 0x00, /* ?....... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xab, 0xcd, /* ........ */
    0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0xc8, /* ...d.... */
    0x00, 0x06, 0x00, 0x08, 0x00, 0x17, 0x00, 0x1f, /* ........ */
    0x00, 0x29, 0x00, 0x18                          /* .).. */
    };

/* Frame (78 bytes) */
static char pkt8[78] = {
    0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x11, /* 33.3DV.. */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, /* ....:... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, /* ...3DV.. */
    0xd0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56              /* "..3DV */
};

/* Frame (78 bytes) */
static char pkt9[78] = {
    0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x11, /* 33.3DV.. */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, /* ....:... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, /* ...3DV.. */
    0xd0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56              /* "..3DV */
};

/* Frame (78 bytes) */
static char pkt10[78] = {
    0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x11, /* 33.3DV.. */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, /* ....:... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, /* ...3DV.. */
    0xd0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56              /* "..3DV */
};

/* Frame (70 bytes) */
static char pkt11[70] = {
    0x33, 0x33, 0x00, 0x00, 0x00, 0x02, 0x00, 0x11, /* 33...... */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x10, 0x3a, 0xff, 0xfe, 0x80, /* ....:... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x85, 0x00, /* ........ */
    0xad, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, /* ........ */
    0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (70 bytes) */
static char pkt12[70] = {
    0x33, 0x33, 0x00, 0x00, 0x00, 0x02, 0x00, 0x11, /* 33...... */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x10, 0x3a, 0xff, 0xfe, 0x80, /* ....:... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x85, 0x00, /* ........ */
    0xad, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, /* ........ */
    0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

/* Frame (70 bytes) */
static char pkt13[70] = {
    0x33, 0x33, 0x00, 0x00, 0x00, 0x02, 0x00, 0x11, /* 33...... */
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, /* "3DV..`. */
    0x00, 0x00, 0x00, 0x10, 0x3a, 0xff, 0xfe, 0x80, /* ....:... */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, /* ........ */
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, /* "..3DV.. */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x85, 0x00, /* ........ */
    0xad, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, /* ........ */
    0x00, 0x11, 0x22, 0x33, 0x44, 0x56              /* .."3DV */
};

#endif





TAHI_TEST_SEQ tahi_dhcpv6_01_024[] = {
    {TITLE, "dhcpv6 01-024", 13, 0},

    {CHECK,  &pkt3[0], sizeof(pkt3), 30},
    {INJECT, &pkt4[0], sizeof(pkt4), 5},
    {CHECK,  &pkt5[0], sizeof(pkt5), 5},

    {CLEANUP, NX_NULL, 0, 0},
    {DUMP, NX_NULL, 0, 0}
};

int  tahi_dhcpv6_01_024_size = sizeof(tahi_dhcpv6_01_024) / sizeof(TAHI_TEST_SEQ);



#endif
