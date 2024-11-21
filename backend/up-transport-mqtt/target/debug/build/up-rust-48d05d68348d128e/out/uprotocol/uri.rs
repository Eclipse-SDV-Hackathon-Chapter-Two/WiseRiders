// This file is generated by rust-protobuf 3.6.0. Do not edit
// .proto file is parsed by protoc 28.2
// @generated

// https://github.com/rust-lang/rust-clippy/issues/702
#![allow(unknown_lints)]
#![allow(clippy::all)]

#![allow(unused_attributes)]
#![cfg_attr(rustfmt, rustfmt::skip)]

#![allow(dead_code)]
#![allow(missing_docs)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]
#![allow(trivial_casts)]
#![allow(unused_results)]
#![allow(unused_mut)]

//! Generated file from `uprotocol/v1/uri.proto`

/// Generated files are compatible only with the same version
/// of protobuf runtime.
const _PROTOBUF_VERSION_CHECK: () = ::protobuf::VERSION_3_6_0;

// @@protoc_insertion_point(message:uprotocol.v1.UUri)
#[derive(PartialEq,Clone,Default,Debug)]
pub struct UUri {
    // message fields
    // @@protoc_insertion_point(field:uprotocol.v1.UUri.authority_name)
    pub authority_name: ::std::string::String,
    // @@protoc_insertion_point(field:uprotocol.v1.UUri.ue_id)
    pub ue_id: u32,
    // @@protoc_insertion_point(field:uprotocol.v1.UUri.ue_version_major)
    pub ue_version_major: u32,
    // @@protoc_insertion_point(field:uprotocol.v1.UUri.resource_id)
    pub resource_id: u32,
    // special fields
    // @@protoc_insertion_point(special_field:uprotocol.v1.UUri.special_fields)
    pub special_fields: ::protobuf::SpecialFields,
}

impl<'a> ::std::default::Default for &'a UUri {
    fn default() -> &'a UUri {
        <UUri as ::protobuf::Message>::default_instance()
    }
}

impl UUri {
    pub fn new() -> UUri {
        ::std::default::Default::default()
    }

    fn generated_message_descriptor_data() -> ::protobuf::reflect::GeneratedMessageDescriptorData {
        let mut fields = ::std::vec::Vec::with_capacity(4);
        let mut oneofs = ::std::vec::Vec::with_capacity(0);
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "authority_name",
            |m: &UUri| { &m.authority_name },
            |m: &mut UUri| { &mut m.authority_name },
        ));
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "ue_id",
            |m: &UUri| { &m.ue_id },
            |m: &mut UUri| { &mut m.ue_id },
        ));
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "ue_version_major",
            |m: &UUri| { &m.ue_version_major },
            |m: &mut UUri| { &mut m.ue_version_major },
        ));
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "resource_id",
            |m: &UUri| { &m.resource_id },
            |m: &mut UUri| { &mut m.resource_id },
        ));
        ::protobuf::reflect::GeneratedMessageDescriptorData::new_2::<UUri>(
            "UUri",
            fields,
            oneofs,
        )
    }
}

impl ::protobuf::Message for UUri {
    const NAME: &'static str = "UUri";

    fn is_initialized(&self) -> bool {
        true
    }

    fn merge_from(&mut self, is: &mut ::protobuf::CodedInputStream<'_>) -> ::protobuf::Result<()> {
        while let Some(tag) = is.read_raw_tag_or_eof()? {
            match tag {
                10 => {
                    self.authority_name = is.read_string()?;
                },
                16 => {
                    self.ue_id = is.read_uint32()?;
                },
                24 => {
                    self.ue_version_major = is.read_uint32()?;
                },
                32 => {
                    self.resource_id = is.read_uint32()?;
                },
                tag => {
                    ::protobuf::rt::read_unknown_or_skip_group(tag, is, self.special_fields.mut_unknown_fields())?;
                },
            };
        }
        ::std::result::Result::Ok(())
    }

    // Compute sizes of nested messages
    #[allow(unused_variables)]
    fn compute_size(&self) -> u64 {
        let mut my_size = 0;
        if !self.authority_name.is_empty() {
            my_size += ::protobuf::rt::string_size(1, &self.authority_name);
        }
        if self.ue_id != 0 {
            my_size += ::protobuf::rt::uint32_size(2, self.ue_id);
        }
        if self.ue_version_major != 0 {
            my_size += ::protobuf::rt::uint32_size(3, self.ue_version_major);
        }
        if self.resource_id != 0 {
            my_size += ::protobuf::rt::uint32_size(4, self.resource_id);
        }
        my_size += ::protobuf::rt::unknown_fields_size(self.special_fields.unknown_fields());
        self.special_fields.cached_size().set(my_size as u32);
        my_size
    }

    fn write_to_with_cached_sizes(&self, os: &mut ::protobuf::CodedOutputStream<'_>) -> ::protobuf::Result<()> {
        if !self.authority_name.is_empty() {
            os.write_string(1, &self.authority_name)?;
        }
        if self.ue_id != 0 {
            os.write_uint32(2, self.ue_id)?;
        }
        if self.ue_version_major != 0 {
            os.write_uint32(3, self.ue_version_major)?;
        }
        if self.resource_id != 0 {
            os.write_uint32(4, self.resource_id)?;
        }
        os.write_unknown_fields(self.special_fields.unknown_fields())?;
        ::std::result::Result::Ok(())
    }

    fn special_fields(&self) -> &::protobuf::SpecialFields {
        &self.special_fields
    }

    fn mut_special_fields(&mut self) -> &mut ::protobuf::SpecialFields {
        &mut self.special_fields
    }

    fn new() -> UUri {
        UUri::new()
    }

    fn clear(&mut self) {
        self.authority_name.clear();
        self.ue_id = 0;
        self.ue_version_major = 0;
        self.resource_id = 0;
        self.special_fields.clear();
    }

    fn default_instance() -> &'static UUri {
        static instance: UUri = UUri {
            authority_name: ::std::string::String::new(),
            ue_id: 0,
            ue_version_major: 0,
            resource_id: 0,
            special_fields: ::protobuf::SpecialFields::new(),
        };
        &instance
    }
}

impl ::protobuf::MessageFull for UUri {
    fn descriptor() -> ::protobuf::reflect::MessageDescriptor {
        static descriptor: ::protobuf::rt::Lazy<::protobuf::reflect::MessageDescriptor> = ::protobuf::rt::Lazy::new();
        descriptor.get(|| file_descriptor().message_by_package_relative_name("UUri").unwrap()).clone()
    }
}

impl ::std::fmt::Display for UUri {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        ::protobuf::text_format::fmt(self, f)
    }
}

impl ::protobuf::reflect::ProtobufValue for UUri {
    type RuntimeType = ::protobuf::reflect::rt::RuntimeTypeMessage<Self>;
}

// @@protoc_insertion_point(message:uprotocol.v1.UUriBatch)
#[derive(PartialEq,Clone,Default,Debug)]
pub struct UUriBatch {
    // message fields
    // @@protoc_insertion_point(field:uprotocol.v1.UUriBatch.uris)
    pub uris: ::std::vec::Vec<UUri>,
    // special fields
    // @@protoc_insertion_point(special_field:uprotocol.v1.UUriBatch.special_fields)
    pub special_fields: ::protobuf::SpecialFields,
}

impl<'a> ::std::default::Default for &'a UUriBatch {
    fn default() -> &'a UUriBatch {
        <UUriBatch as ::protobuf::Message>::default_instance()
    }
}

impl UUriBatch {
    pub fn new() -> UUriBatch {
        ::std::default::Default::default()
    }

    fn generated_message_descriptor_data() -> ::protobuf::reflect::GeneratedMessageDescriptorData {
        let mut fields = ::std::vec::Vec::with_capacity(1);
        let mut oneofs = ::std::vec::Vec::with_capacity(0);
        fields.push(::protobuf::reflect::rt::v2::make_vec_simpler_accessor::<_, _>(
            "uris",
            |m: &UUriBatch| { &m.uris },
            |m: &mut UUriBatch| { &mut m.uris },
        ));
        ::protobuf::reflect::GeneratedMessageDescriptorData::new_2::<UUriBatch>(
            "UUriBatch",
            fields,
            oneofs,
        )
    }
}

impl ::protobuf::Message for UUriBatch {
    const NAME: &'static str = "UUriBatch";

    fn is_initialized(&self) -> bool {
        true
    }

    fn merge_from(&mut self, is: &mut ::protobuf::CodedInputStream<'_>) -> ::protobuf::Result<()> {
        while let Some(tag) = is.read_raw_tag_or_eof()? {
            match tag {
                10 => {
                    self.uris.push(is.read_message()?);
                },
                tag => {
                    ::protobuf::rt::read_unknown_or_skip_group(tag, is, self.special_fields.mut_unknown_fields())?;
                },
            };
        }
        ::std::result::Result::Ok(())
    }

    // Compute sizes of nested messages
    #[allow(unused_variables)]
    fn compute_size(&self) -> u64 {
        let mut my_size = 0;
        for value in &self.uris {
            let len = value.compute_size();
            my_size += 1 + ::protobuf::rt::compute_raw_varint64_size(len) + len;
        };
        my_size += ::protobuf::rt::unknown_fields_size(self.special_fields.unknown_fields());
        self.special_fields.cached_size().set(my_size as u32);
        my_size
    }

    fn write_to_with_cached_sizes(&self, os: &mut ::protobuf::CodedOutputStream<'_>) -> ::protobuf::Result<()> {
        for v in &self.uris {
            ::protobuf::rt::write_message_field_with_cached_size(1, v, os)?;
        };
        os.write_unknown_fields(self.special_fields.unknown_fields())?;
        ::std::result::Result::Ok(())
    }

    fn special_fields(&self) -> &::protobuf::SpecialFields {
        &self.special_fields
    }

    fn mut_special_fields(&mut self) -> &mut ::protobuf::SpecialFields {
        &mut self.special_fields
    }

    fn new() -> UUriBatch {
        UUriBatch::new()
    }

    fn clear(&mut self) {
        self.uris.clear();
        self.special_fields.clear();
    }

    fn default_instance() -> &'static UUriBatch {
        static instance: UUriBatch = UUriBatch {
            uris: ::std::vec::Vec::new(),
            special_fields: ::protobuf::SpecialFields::new(),
        };
        &instance
    }
}

impl ::protobuf::MessageFull for UUriBatch {
    fn descriptor() -> ::protobuf::reflect::MessageDescriptor {
        static descriptor: ::protobuf::rt::Lazy<::protobuf::reflect::MessageDescriptor> = ::protobuf::rt::Lazy::new();
        descriptor.get(|| file_descriptor().message_by_package_relative_name("UUriBatch").unwrap()).clone()
    }
}

impl ::std::fmt::Display for UUriBatch {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        ::protobuf::text_format::fmt(self, f)
    }
}

impl ::protobuf::reflect::ProtobufValue for UUriBatch {
    type RuntimeType = ::protobuf::reflect::rt::RuntimeTypeMessage<Self>;
}

static file_descriptor_proto_data: &'static [u8] = b"\
    \n\x16uprotocol/v1/uri.proto\x12\x0cuprotocol.v1\"\x8d\x01\n\x04UUri\x12\
    %\n\x0eauthority_name\x18\x01\x20\x01(\tR\rauthorityName\x12\x13\n\x05ue\
    _id\x18\x02\x20\x01(\rR\x04ueId\x12(\n\x10ue_version_major\x18\x03\x20\
    \x01(\rR\x0eueVersionMajor\x12\x1f\n\x0bresource_id\x18\x04\x20\x01(\rR\
    \nresourceId\"3\n\tUUriBatch\x12&\n\x04uris\x18\x01\x20\x03(\x0b2\x12.up\
    rotocol.v1.UUriR\x04urisB'\n\x18org.eclipse.uprotocol.v1B\tUUriProtoP\
    \x01b\x06proto3\
";

/// `FileDescriptorProto` object which was a source for this generated file
fn file_descriptor_proto() -> &'static ::protobuf::descriptor::FileDescriptorProto {
    static file_descriptor_proto_lazy: ::protobuf::rt::Lazy<::protobuf::descriptor::FileDescriptorProto> = ::protobuf::rt::Lazy::new();
    file_descriptor_proto_lazy.get(|| {
        ::protobuf::Message::parse_from_bytes(file_descriptor_proto_data).unwrap()
    })
}

/// `FileDescriptor` object which allows dynamic access to files
pub fn file_descriptor() -> &'static ::protobuf::reflect::FileDescriptor {
    static generated_file_descriptor_lazy: ::protobuf::rt::Lazy<::protobuf::reflect::GeneratedFileDescriptor> = ::protobuf::rt::Lazy::new();
    static file_descriptor: ::protobuf::rt::Lazy<::protobuf::reflect::FileDescriptor> = ::protobuf::rt::Lazy::new();
    file_descriptor.get(|| {
        let generated_file_descriptor = generated_file_descriptor_lazy.get(|| {
            let mut deps = ::std::vec::Vec::with_capacity(0);
            let mut messages = ::std::vec::Vec::with_capacity(2);
            messages.push(UUri::generated_message_descriptor_data());
            messages.push(UUriBatch::generated_message_descriptor_data());
            let mut enums = ::std::vec::Vec::with_capacity(0);
            ::protobuf::reflect::GeneratedFileDescriptor::new_generated(
                file_descriptor_proto(),
                deps,
                messages,
                enums,
            )
        });
        ::protobuf::reflect::FileDescriptor::new_generated_2(generated_file_descriptor)
    })
}
