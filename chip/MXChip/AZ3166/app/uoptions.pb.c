/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.4.9 */

#include "uoptions.pb.h"
#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

PB_BIND(uprotocol_UServiceTopic, uprotocol_UServiceTopic, AUTO)


/* Definition for extension field uprotocol_file_someip */
typedef struct _uprotocol_file_someip_extmsg {
    bool file_someip;
} uprotocol_file_someip_extmsg;
#define uprotocol_file_someip_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, BOOL,     file_someip,     51000)
#define uprotocol_file_someip_extmsg_CALLBACK NULL
#define uprotocol_file_someip_extmsg_DEFAULT NULL
pb_byte_t uprotocol_file_someip_extmsg_default[] = {0x00};
PB_BIND(uprotocol_file_someip_extmsg, uprotocol_file_someip_extmsg, 4)
const pb_extension_type_t uprotocol_file_someip = {
    NULL,
    NULL,
    &uprotocol_file_someip_extmsg_msg
};




/* Definition for extension field uprotocol_service_version_minor */
typedef struct _uprotocol_service_version_minor_extmsg {
    uint32_t service_version_minor;
} uprotocol_service_version_minor_extmsg;
#define uprotocol_service_version_minor_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, UINT32,   service_version_minor, 51103)
#define uprotocol_service_version_minor_extmsg_CALLBACK NULL
#define uprotocol_service_version_minor_extmsg_DEFAULT NULL
pb_byte_t uprotocol_service_version_minor_extmsg_default[] = {0x00};
PB_BIND(uprotocol_service_version_minor_extmsg, uprotocol_service_version_minor_extmsg, 4)
const pb_extension_type_t uprotocol_service_version_minor = {
    NULL,
    NULL,
    &uprotocol_service_version_minor_extmsg_msg
};

/* Definition for extension field uprotocol_service_permission_level */
typedef struct _uprotocol_service_permission_level_extmsg {
    uint32_t service_permission_level;
} uprotocol_service_permission_level_extmsg;
#define uprotocol_service_permission_level_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, UINT32,   service_permission_level, 51104)
#define uprotocol_service_permission_level_extmsg_CALLBACK NULL
#define uprotocol_service_permission_level_extmsg_DEFAULT NULL
pb_byte_t uprotocol_service_permission_level_extmsg_default[] = {0x00};
PB_BIND(uprotocol_service_permission_level_extmsg, uprotocol_service_permission_level_extmsg, 4)
const pb_extension_type_t uprotocol_service_permission_level = {
    NULL,
    NULL,
    &uprotocol_service_permission_level_extmsg_msg
};



/* Definition for extension field uprotocol_service_someip */
typedef struct _uprotocol_service_someip_extmsg {
    bool service_someip;
} uprotocol_service_someip_extmsg;
#define uprotocol_service_someip_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, BOOL,     service_someip,  51107)
#define uprotocol_service_someip_extmsg_CALLBACK NULL
#define uprotocol_service_someip_extmsg_DEFAULT NULL
pb_byte_t uprotocol_service_someip_extmsg_default[] = {0x00};
PB_BIND(uprotocol_service_someip_extmsg, uprotocol_service_someip_extmsg, 4)
const pb_extension_type_t uprotocol_service_someip = {
    NULL,
    NULL,
    &uprotocol_service_someip_extmsg_msg
};


/* Definition for extension field uprotocol_method_permission_level */
typedef struct _uprotocol_method_permission_level_extmsg {
    uint32_t method_permission_level;
} uprotocol_method_permission_level_extmsg;
#define uprotocol_method_permission_level_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, UINT32,   method_permission_level, 51201)
#define uprotocol_method_permission_level_extmsg_CALLBACK NULL
#define uprotocol_method_permission_level_extmsg_DEFAULT NULL
pb_byte_t uprotocol_method_permission_level_extmsg_default[] = {0x00};
PB_BIND(uprotocol_method_permission_level_extmsg, uprotocol_method_permission_level_extmsg, 4)
const pb_extension_type_t uprotocol_method_permission_level = {
    NULL,
    NULL,
    &uprotocol_method_permission_level_extmsg_msg
};

/* Definition for extension field uprotocol_message_someip */
typedef struct _uprotocol_message_someip_extmsg {
    bool message_someip;
} uprotocol_message_someip_extmsg;
#define uprotocol_message_someip_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, BOOL,     message_someip,  51300)
#define uprotocol_message_someip_extmsg_CALLBACK NULL
#define uprotocol_message_someip_extmsg_DEFAULT NULL
pb_byte_t uprotocol_message_someip_extmsg_default[] = {0x00};
PB_BIND(uprotocol_message_someip_extmsg, uprotocol_message_someip_extmsg, 4)
const pb_extension_type_t uprotocol_message_someip = {
    NULL,
    NULL,
    &uprotocol_message_someip_extmsg_msg
};

/* Definition for extension field uprotocol_message_size */
typedef struct _uprotocol_message_size_extmsg {
    uint32_t message_size;
} uprotocol_message_size_extmsg;
#define uprotocol_message_size_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, UINT32,   message_size,    51301)
#define uprotocol_message_size_extmsg_CALLBACK NULL
#define uprotocol_message_size_extmsg_DEFAULT NULL
pb_byte_t uprotocol_message_size_extmsg_default[] = {0x00};
PB_BIND(uprotocol_message_size_extmsg, uprotocol_message_size_extmsg, 4)
const pb_extension_type_t uprotocol_message_size = {
    NULL,
    NULL,
    &uprotocol_message_size_extmsg_msg
};

/* Definition for extension field uprotocol_field_size */
typedef struct _uprotocol_field_size_extmsg {
    uint32_t field_size;
} uprotocol_field_size_extmsg;
#define uprotocol_field_size_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, UINT32,   field_size,      51400)
#define uprotocol_field_size_extmsg_CALLBACK NULL
#define uprotocol_field_size_extmsg_DEFAULT NULL
pb_byte_t uprotocol_field_size_extmsg_default[] = {0x00};
PB_BIND(uprotocol_field_size_extmsg, uprotocol_field_size_extmsg, 4)
const pb_extension_type_t uprotocol_field_size = {
    NULL,
    NULL,
    &uprotocol_field_size_extmsg_msg
};

/* Definition for extension field uprotocol_field_key_size */
typedef struct _uprotocol_field_key_size_extmsg {
    uint32_t field_key_size;
} uprotocol_field_key_size_extmsg;
#define uprotocol_field_key_size_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, UINT32,   field_key_size,  51401)
#define uprotocol_field_key_size_extmsg_CALLBACK NULL
#define uprotocol_field_key_size_extmsg_DEFAULT NULL
pb_byte_t uprotocol_field_key_size_extmsg_default[] = {0x00};
PB_BIND(uprotocol_field_key_size_extmsg, uprotocol_field_key_size_extmsg, 4)
const pb_extension_type_t uprotocol_field_key_size = {
    NULL,
    NULL,
    &uprotocol_field_key_size_extmsg_msg
};

/* Definition for extension field uprotocol_field_count */
typedef struct _uprotocol_field_count_extmsg {
    uint32_t field_count;
} uprotocol_field_count_extmsg;
#define uprotocol_field_count_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, UINT32,   field_count,     51402)
#define uprotocol_field_count_extmsg_CALLBACK NULL
#define uprotocol_field_count_extmsg_DEFAULT NULL
pb_byte_t uprotocol_field_count_extmsg_default[] = {0x00};
PB_BIND(uprotocol_field_count_extmsg, uprotocol_field_count_extmsg, 4)
const pb_extension_type_t uprotocol_field_count = {
    NULL,
    NULL,
    &uprotocol_field_count_extmsg_msg
};

/* Definition for extension field uprotocol_enum_size */
typedef struct _uprotocol_enum_size_extmsg {
    uint32_t enum_size;
} uprotocol_enum_size_extmsg;
#define uprotocol_enum_size_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, UINT32,   enum_size,       51500)
#define uprotocol_enum_size_extmsg_CALLBACK NULL
#define uprotocol_enum_size_extmsg_DEFAULT NULL
pb_byte_t uprotocol_enum_size_extmsg_default[] = {0x00};
PB_BIND(uprotocol_enum_size_extmsg, uprotocol_enum_size_extmsg, 4)
const pb_extension_type_t uprotocol_enum_size = {
    NULL,
    NULL,
    &uprotocol_enum_size_extmsg_msg
};

/* Definition for extension field uprotocol_enum_someip */
typedef struct _uprotocol_enum_someip_extmsg {
    bool enum_someip;
} uprotocol_enum_someip_extmsg;
#define uprotocol_enum_someip_extmsg_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, BOOL,     enum_someip,     51501)
#define uprotocol_enum_someip_extmsg_CALLBACK NULL
#define uprotocol_enum_someip_extmsg_DEFAULT NULL
pb_byte_t uprotocol_enum_someip_extmsg_default[] = {0x00};
PB_BIND(uprotocol_enum_someip_extmsg, uprotocol_enum_someip_extmsg, 4)
const pb_extension_type_t uprotocol_enum_someip = {
    NULL,
    NULL,
    &uprotocol_enum_someip_extmsg_msg
};

/* Definition for extension field uprotocol_mime_type */
typedef struct _uprotocol_mime_type_extmsg {
    pb_callback_t mime_type;
} uprotocol_mime_type_extmsg;
#define uprotocol_mime_type_extmsg_FIELDLIST(X, a) \
X(a, CALLBACK, REQUIRED, STRING,   mime_type,       51600)
#define uprotocol_mime_type_extmsg_CALLBACK pb_default_field_callback
#define uprotocol_mime_type_extmsg_DEFAULT NULL
pb_byte_t uprotocol_mime_type_extmsg_default[] = {0x00};
PB_BIND(uprotocol_mime_type_extmsg, uprotocol_mime_type_extmsg, 4)
const pb_extension_type_t uprotocol_mime_type = {
    NULL,
    NULL,
    &uprotocol_mime_type_extmsg_msg
};

/* Definition for extension field uprotocol_ce_name */
typedef struct _uprotocol_ce_name_extmsg {
    pb_callback_t ce_name;
} uprotocol_ce_name_extmsg;
#define uprotocol_ce_name_extmsg_FIELDLIST(X, a) \
X(a, CALLBACK, REQUIRED, STRING,   ce_name,         51601)
#define uprotocol_ce_name_extmsg_CALLBACK pb_default_field_callback
#define uprotocol_ce_name_extmsg_DEFAULT NULL
pb_byte_t uprotocol_ce_name_extmsg_default[] = {0x00};
PB_BIND(uprotocol_ce_name_extmsg, uprotocol_ce_name_extmsg, 4)
const pb_extension_type_t uprotocol_ce_name = {
    NULL,
    NULL,
    &uprotocol_ce_name_extmsg_msg
};


