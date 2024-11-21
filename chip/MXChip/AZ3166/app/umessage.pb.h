/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.9 */

#ifndef PB_UPROTOCOL_V1_UMESSAGE_PB_H_INCLUDED
#define PB_UPROTOCOL_V1_UMESSAGE_PB_H_INCLUDED
#include <pb.h>
#include "uattributes.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef PB_BYTES_ARRAY_T(128) uprotocol_v1_UMessage_payload_t;
/* UMessage is the top-level message type for the uProtocol.
 It contains a header (UAttributes), and payload and is a way of representing a
 message that would be sent between two uEs. */
typedef struct _uprotocol_v1_UMessage {
    /* uProtocol mandatory and optional attributes */
    bool has_attributes;
    uprotocol_v1_UAttributes attributes;
    /* Optional message payload */
    bool has_payload;
    uprotocol_v1_UMessage_payload_t payload;
} uprotocol_v1_UMessage;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define uprotocol_v1_UMessage_init_default       {false, uprotocol_v1_UAttributes_init_default, false, {0, {0}}}
#define uprotocol_v1_UMessage_init_zero          {false, uprotocol_v1_UAttributes_init_zero, false, {0, {0}}}

/* Field tags (for use in manual encoding/decoding) */
#define uprotocol_v1_UMessage_attributes_tag     1
#define uprotocol_v1_UMessage_payload_tag        2

/* Struct field encoding specification for nanopb */
#define uprotocol_v1_UMessage_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  attributes,        1) \
X(a, STATIC,   OPTIONAL, BYTES,    payload,           2)
#define uprotocol_v1_UMessage_CALLBACK NULL
#define uprotocol_v1_UMessage_DEFAULT NULL
#define uprotocol_v1_UMessage_attributes_MSGTYPE uprotocol_v1_UAttributes

extern const pb_msgdesc_t uprotocol_v1_UMessage_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define uprotocol_v1_UMessage_fields &uprotocol_v1_UMessage_msg

/* Maximum encoded size of messages (where known) */
#define UPROTOCOL_V1_UMESSAGE_PB_H_MAX_SIZE      uprotocol_v1_UMessage_size
#define uprotocol_v1_UMessage_size               756

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif