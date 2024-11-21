/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.9 */

#ifndef PB_UPROTOCOL_UOPTIONS_PB_H_INCLUDED
#define PB_UPROTOCOL_UOPTIONS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
/* Service topic definition */
typedef struct _uprotocol_UServiceTopic {
    /* Topic id (0x8000 - 0xFFFF).
 The topic id **MUST** be unique within the containing service scope. */
    uint32_t id;
    /* Topic name.
 The topic name **MUST** be unique within the containing service scope. */
    pb_callback_t name;
    /* The topic message (defines the data passed in the topic).

 Both absolute and relative message names can be used, following the
 [Protobuf type name resolution rules](https://protobuf.dev/programming-guides/proto3/#name-resolution):

 1. **Relative name:** partially-qualified name, resolved starting from the
    innermost scope to the outermost scope.
 2. **Absolute name:** fully-qualified name with a leading `'.'`, resolved
    starting from the outermost scope instead.

 For example, with respect to a concrete service *foo.bar.Service*, the
 following topic message references are all equivalent:

 - *foo.bar.Topic*
 - *bar.Topic*
 - *Topic*
 <br>

 **_NOTE:_** If the topic message is defined in a separate proto file, then
 this proto file must be explicitly imported into the proto file in which
 it is referenced, otherwise the message reference will not be resolved. */
    pb_callback_t message;
    /* One or more enumerated resource values that can be used to generate 
 corresponding list of topics:
 <p>&emsp;&emsp;&emsp;[* resource_enum *] : [* resource_value *]</p>

 Both absolute and relative resource enum names can be used, following the
 [Protobuf type name resolution rules](https://protobuf.dev/programming-guides/proto3/#name-resolution).
 If the resource name is relative, it will be resolved relative to the
 topic message. The *resource_enum* part is optional, and if omitted will
 default to "Resources".

 For example, with respect to a concrete topic message *foo.bar.Topic*, the
 following topic resource references are all equivalent:

 - *foo.bar.Topic.Resources* : \*
 - *bar.Topic.Resources* : \*
 - *Topic.Resources* : \*
 - *Resources* : \*
 - \*
 <br>

 Topics can be defined automatically using the `"\*"` wildcard (e.g., 
 `"Resources:*"`). This will create a separate topic per each resource
 instance, using the resource code/value to generate the topic id/uri.

 Topics with multiple resources can be defined using an array (e.g., 
 `["front_left", "front_right"]`). The `"\*"` wildcard can also be used in
 this context (e.g., `["*"]`). This can be used to define a single topic
 that is triggered by a combination of multiple resources.

 **_NOTE:_** If a topic resource is defined in a separate proto file, then
 this proto file must be explicitly imported into the proto file in which
 it is referenced, otherwise the resource reference will not be resolved. */
    pb_callback_t resources;
    /* Code Access Permission (CAP) Level for the topic */
    bool has_permission_level;
    uint32_t permission_level;
} uprotocol_UServiceTopic;


/* Extensions */
extern const pb_extension_type_t uprotocol_file_someip; /* field type: bool file_someip; */
/* Extension field uprotocol_service_id was skipped because only "optional"
   type of extension fields is currently supported. */
/* Extension field uprotocol_service_name was skipped because only "optional"
   type of extension fields is currently supported. */
/* Extension field uprotocol_service_version_major was skipped because only "optional"
   type of extension fields is currently supported. */
extern const pb_extension_type_t uprotocol_service_version_minor; /* field type: uint32_t service_version_minor; */
extern const pb_extension_type_t uprotocol_service_permission_level; /* field type: uint32_t service_permission_level; */
/* Extension field uprotocol_publish_topic was skipped because only "optional"
   type of extension fields is currently supported. */
/* Extension field uprotocol_notification_topic was skipped because only "optional"
   type of extension fields is currently supported. */
extern const pb_extension_type_t uprotocol_service_someip; /* field type: bool service_someip; */
/* Extension field uprotocol_method_id was skipped because only "optional"
   type of extension fields is currently supported. */
extern const pb_extension_type_t uprotocol_method_permission_level; /* field type: uint32_t method_permission_level; */
extern const pb_extension_type_t uprotocol_message_someip; /* field type: bool message_someip; */
extern const pb_extension_type_t uprotocol_message_size; /* field type: uint32_t message_size; */
extern const pb_extension_type_t uprotocol_field_size; /* field type: uint32_t field_size; */
extern const pb_extension_type_t uprotocol_field_key_size; /* field type: uint32_t field_key_size; */
extern const pb_extension_type_t uprotocol_field_count; /* field type: uint32_t field_count; */
extern const pb_extension_type_t uprotocol_enum_size; /* field type: uint32_t enum_size; */
extern const pb_extension_type_t uprotocol_enum_someip; /* field type: bool enum_someip; */
extern const pb_extension_type_t uprotocol_mime_type; /* field type: pb_callback_t mime_type; */
extern const pb_extension_type_t uprotocol_ce_name; /* field type: pb_callback_t ce_name; */

#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define uprotocol_UServiceTopic_init_default     {0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, false, 0}
#define uprotocol_UServiceTopic_init_zero        {0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}, false, 0}

/* Field tags (for use in manual encoding/decoding) */
#define uprotocol_UServiceTopic_id_tag           1
#define uprotocol_UServiceTopic_name_tag         2
#define uprotocol_UServiceTopic_message_tag      3
#define uprotocol_UServiceTopic_resources_tag    4
#define uprotocol_UServiceTopic_permission_level_tag 5
#define uprotocol_file_someip_tag                51000
#define uprotocol_service_id_tag                 51100
#define uprotocol_service_name_tag               51101
#define uprotocol_service_version_major_tag      51102
#define uprotocol_service_version_minor_tag      51103
#define uprotocol_service_permission_level_tag   51104
#define uprotocol_publish_topic_tag              51105
#define uprotocol_notification_topic_tag         51106
#define uprotocol_service_someip_tag             51107
#define uprotocol_method_id_tag                  51200
#define uprotocol_method_permission_level_tag    51201
#define uprotocol_message_someip_tag             51300
#define uprotocol_message_size_tag               51301
#define uprotocol_field_size_tag                 51400
#define uprotocol_field_key_size_tag             51401
#define uprotocol_field_count_tag                51402
#define uprotocol_enum_size_tag                  51500
#define uprotocol_enum_someip_tag                51501
#define uprotocol_mime_type_tag                  51600
#define uprotocol_ce_name_tag                    51601

/* Struct field encoding specification for nanopb */
#define uprotocol_UServiceTopic_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   id,                1) \
X(a, CALLBACK, SINGULAR, STRING,   name,              2) \
X(a, CALLBACK, SINGULAR, STRING,   message,           3) \
X(a, CALLBACK, REPEATED, STRING,   resources,         4) \
X(a, STATIC,   OPTIONAL, UINT32,   permission_level,   5)
#define uprotocol_UServiceTopic_CALLBACK pb_default_field_callback
#define uprotocol_UServiceTopic_DEFAULT NULL

extern const pb_msgdesc_t uprotocol_UServiceTopic_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define uprotocol_UServiceTopic_fields &uprotocol_UServiceTopic_msg

/* Maximum encoded size of messages (where known) */
/* uprotocol_UServiceTopic_size depends on runtime parameters */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif