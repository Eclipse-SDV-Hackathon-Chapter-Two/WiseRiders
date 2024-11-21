#include "nx_api.h"
#if defined(NX_TAHI_ENABLE) && defined(FEATURE_NX_IPV6)  

#include "netx_tahi.h"

static char pkt1[] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, 
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, 
0xdb, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

static char pkt2[] = {
0x33, 0x33, 0xff, 0x00, 0xa0, 0xa0, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xff, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xff, 0x00, 0xa0, 0xa0, 0x87, 0x00, 
0x6c, 0x27, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, 
0x00, 0x11, 0x22, 0x33, 0x44, 0x56 };

static char pkt3[] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, 
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x88, 0x00, 
0x4e, 0xa4, 0xe0, 0x00, 0x00, 0x00, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x02, 0x01, 
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0 };

static char pkt4[] = {
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x81, 0x00, 
0xda, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

#if 0
static char pkt5[] = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x16, 
0x17, 0xc9, 0xa1, 0xaf, 0x08, 0x00, 0x45, 0x00, 
0x00, 0xe7, 0x5a, 0x38, 0x00, 0x00, 0x40, 0x11, 
0x00, 0x00, 0x0a, 0x00, 0x00, 0x01, 0x0a, 0x00, 
0x00, 0xff, 0x00, 0x8a, 0x00, 0x8a, 0x00, 0xd3, 
0x15, 0xe4, 0x11, 0x0a, 0x72, 0xcc, 0x0a, 0x00, 
0x00, 0x01, 0x00, 0x8a, 0x00, 0xbd, 0x00, 0x00, 
0x20, 0x45, 0x45, 0x45, 0x49, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x41, 
0x41, 0x00, 0x20, 0x46, 0x48, 0x45, 0x50, 0x46, 
0x43, 0x45, 0x4c, 0x45, 0x48, 0x46, 0x43, 0x45, 
0x50, 0x46, 0x46, 0x46, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x42, 0x4f, 0x00, 0xff, 0x53, 0x4d, 0x42, 
0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x23, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x23, 0x00, 0x56, 0x00, 0x03, 
0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x34, 
0x00, 0x5c, 0x4d, 0x41, 0x49, 0x4c, 0x53, 0x4c, 
0x4f, 0x54, 0x5c, 0x42, 0x52, 0x4f, 0x57, 0x53, 
0x45, 0x00, 0x0f, 0x8e, 0x80, 0xfc, 0x0a, 0x00, 
0x44, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x09, 0x03, 0x9a, 0x84, 0x00, 0x0f, 0x01, 
0x55, 0xaa, 0x64, 0x68, 0x00 };

static char pkt6[] = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x16, 
0x17, 0xc9, 0xa1, 0xaf, 0x08, 0x00, 0x45, 0x00, 
0x00, 0xe7, 0x5a, 0x38, 0x00, 0x00, 0x40, 0x11, 
0x00, 0x00, 0x0a, 0x00, 0x00, 0x01, 0x0a, 0x00, 
0x00, 0xff, 0x00, 0x8a, 0x00, 0x8a, 0x00, 0xd3, 
0x15, 0xe4, 0x11, 0x0a, 0x72, 0xcc, 0x0a, 0x00, 
0x00, 0x01, 0x00, 0x8a, 0x00, 0xbd, 0x00, 0x00, 
0x20, 0x45, 0x45, 0x45, 0x49, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x41, 
0x41, 0x00, 0x20, 0x46, 0x48, 0x45, 0x50, 0x46, 
0x43, 0x45, 0x4c, 0x45, 0x48, 0x46, 0x43, 0x45, 
0x50, 0x46, 0x46, 0x46, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x42, 0x4f, 0x00, 0xff, 0x53, 0x4d, 0x42, 
0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x23, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x23, 0x00, 0x56, 0x00, 0x03, 
0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x34, 
0x00, 0x5c, 0x4d, 0x41, 0x49, 0x4c, 0x53, 0x4c, 
0x4f, 0x54, 0x5c, 0x42, 0x52, 0x4f, 0x57, 0x53, 
0x45, 0x00, 0x0f, 0x8e, 0x80, 0xfc, 0x0a, 0x00, 
0x44, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x09, 0x03, 0x9a, 0x84, 0x00, 0x0f, 0x01, 
0x55, 0xaa, 0x64, 0x68, 0x00 };

static char pkt7[] = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x16, 
0x17, 0xc9, 0xa1, 0xaf, 0x08, 0x00, 0x45, 0x00, 
0x00, 0xe7, 0x5a, 0x39, 0x00, 0x00, 0x40, 0x11, 
0x00, 0x00, 0x0a, 0x00, 0x00, 0x01, 0x0a, 0x00, 
0x00, 0xff, 0x00, 0x8a, 0x00, 0x8a, 0x00, 0xd3, 
0x15, 0xe4, 0x11, 0x0a, 0x72, 0xcd, 0x0a, 0x00, 
0x00, 0x01, 0x00, 0x8a, 0x00, 0xbd, 0x00, 0x00, 
0x20, 0x45, 0x45, 0x45, 0x49, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x41, 
0x41, 0x00, 0x20, 0x41, 0x42, 0x41, 0x43, 0x46, 
0x50, 0x46, 0x50, 0x45, 0x4e, 0x46, 0x44, 0x45, 
0x43, 0x46, 0x43, 0x45, 0x50, 0x46, 0x48, 0x46, 
0x44, 0x45, 0x46, 0x46, 0x50, 0x46, 0x50, 0x41, 
0x43, 0x41, 0x42, 0x00, 0xff, 0x53, 0x4d, 0x42, 
0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x23, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x23, 0x00, 0x56, 0x00, 0x03, 
0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x34, 
0x00, 0x5c, 0x4d, 0x41, 0x49, 0x4c, 0x53, 0x4c, 
0x4f, 0x54, 0x5c, 0x42, 0x52, 0x4f, 0x57, 0x53, 
0x45, 0x00, 0x0c, 0x8e, 0x80, 0xfc, 0x0a, 0x00, 
0x57, 0x4f, 0x52, 0x4b, 0x47, 0x52, 0x4f, 0x55, 
0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x09, 0x00, 0x10, 0x00, 0x80, 0x0f, 0x01, 
0x55, 0xaa, 0x44, 0x48, 0x00 };

static char pkt8[] = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x16, 
0x17, 0xc9, 0xa1, 0xaf, 0x08, 0x00, 0x45, 0x00, 
0x00, 0xe7, 0x5a, 0x39, 0x00, 0x00, 0x40, 0x11, 
0x00, 0x00, 0x0a, 0x00, 0x00, 0x01, 0x0a, 0x00, 
0x00, 0xff, 0x00, 0x8a, 0x00, 0x8a, 0x00, 0xd3, 
0x15, 0xe4, 0x11, 0x0a, 0x72, 0xcd, 0x0a, 0x00, 
0x00, 0x01, 0x00, 0x8a, 0x00, 0xbd, 0x00, 0x00, 
0x20, 0x45, 0x45, 0x45, 0x49, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 
0x41, 0x43, 0x41, 0x43, 0x41, 0x43, 0x41, 0x41, 
0x41, 0x00, 0x20, 0x41, 0x42, 0x41, 0x43, 0x46, 
0x50, 0x46, 0x50, 0x45, 0x4e, 0x46, 0x44, 0x45, 
0x43, 0x46, 0x43, 0x45, 0x50, 0x46, 0x48, 0x46, 
0x44, 0x45, 0x46, 0x46, 0x50, 0x46, 0x50, 0x41, 
0x43, 0x41, 0x42, 0x00, 0xff, 0x53, 0x4d, 0x42, 
0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x23, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x23, 0x00, 0x56, 0x00, 0x03, 
0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x34, 
0x00, 0x5c, 0x4d, 0x41, 0x49, 0x4c, 0x53, 0x4c, 
0x4f, 0x54, 0x5c, 0x42, 0x52, 0x4f, 0x57, 0x53, 
0x45, 0x00, 0x0c, 0x8e, 0x80, 0xfc, 0x0a, 0x00, 
0x57, 0x4f, 0x52, 0x4b, 0x47, 0x52, 0x4f, 0x55, 
0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x09, 0x00, 0x10, 0x00, 0x80, 0x0f, 0x01, 
0x55, 0xaa, 0x44, 0x48, 0x00 };
#endif

static char pkt9[] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, 
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, 
0xdb, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

static char pkt10[] = {
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x81, 0x00, 
0xda, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

static char pkt11[] = {
0x00, 0x00, 0x00, 0x00, 0xa0, 0xa0, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, 
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, 
0x00, 0x11, 0x22, 0x33, 0x44, 0x56 };

static char pkt12[] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
0x00, 0x00, 0xc0, 0xc0, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xff, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 
0xad, 0xcd, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x27, 0x10, 0x00, 0x00, 0x03, 0xe8, 0x01, 0x01, 
0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0 };

static char pkt13[] = {
0x00, 0x11, 0x22, 0x33, 0x44, 0x56, 0x00, 0x00, 
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0x80, 0x00, 
0xdb, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

static char pkt14[] = {
0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x3a, 0x40, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x81, 0x00, 
0xda, 0x52, 0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 
0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

static char pkt15[] = {
0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, 
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, 
0x00, 0x11, 0x22, 0x33, 0x44, 0x56 };

#if 0
static char pkt16[] = {
0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, 
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, 
0x00, 0x11, 0x22, 0x33, 0x44, 0x56 };

static char pkt17[] = {
0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x11, 
0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x20, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
0x22, 0xff, 0xfe, 0x33, 0x44, 0x56, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x87, 0x00, 
0x6a, 0xab, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0x01, 0x01, 
0x00, 0x11, 0x22, 0x33, 0x44, 0x56 };
#endif

static char pkt18[] = {
0x33, 0x33, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
0x00, 0x00, 0xa0, 0xa0, 0x86, 0xdd, 0x60, 0x00, 
0x00, 0x00, 0x00, 0x30, 0x3a, 0xff, 0xfe, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
0x00, 0xff, 0xfe, 0x00, 0xa0, 0xa0, 0xff, 0x02, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 
0x97, 0x93, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x75, 0x30, 0x00, 0x00, 0x03, 0xe8, 0x03, 0x04, 
0x40, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, 
0x05, 0x01, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

TAHI_TEST_SEQ tahi_02_157[] = {
    {TITLE, "02-157", 6, 0},
    {WAIT, NX_NULL, 0, 5},

    {INJECT, &pkt1[0], sizeof(pkt1), 0},  /* Echo request  */
    {CHECK, &pkt2[0], sizeof(pkt2), 2},   /* NS  */
    {INJECT, &pkt3[0], sizeof(pkt3), 0},  /* NA  */
    {CHECK, &pkt4[0], sizeof(pkt4), 2},   /* Echo reply  */
    {WAIT, NX_NULL, 0, 45},
    
    {INJECT, &pkt9[0], sizeof(pkt9), 0},  /* Echo request  */ 
    {CHECK, &pkt10[0], sizeof(pkt10), 2}, /* Echo reply  */
    {CHECK, &pkt11[0], sizeof(pkt11), 7}, /* NS  */
    {INJECT, &pkt12[0], sizeof(pkt12), 0},/* RA  */
    {INJECT, &pkt13[0], sizeof(pkt13), 0},/* Echo request  */
    {CHECK, &pkt14[0], sizeof(pkt14), 2}, /* Echo reply  */
    {CHECK, &pkt15[0], sizeof(pkt15), 7}, /* NS  */
    
    {WAIT, NX_NULL, 0, 4},
    {DUMP, NX_NULL, 0, 0},

    {INJECT, &pkt18[0], sizeof(pkt18), 0},/* RA  */
    
    {CLEANUP, NX_NULL, 0, 0},
    {DUMP, NX_NULL, 0, 0}
};

int tahi_02_157_size = sizeof(tahi_02_157) / sizeof(TAHI_TEST_SEQ);

#endif /* NX_TAHI_ENABLE */

