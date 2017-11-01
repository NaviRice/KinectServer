# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: navirice_image.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='navirice_image.proto',
  package='navirice',
  syntax='proto3',
  serialized_pb=_b('\n\x14navirice_image.proto\x12\x08navirice\"\xc3\x02\n\x08ImageSet\x12\r\n\x05\x63ount\x18\x01 \x01(\x04\x12%\n\x03RGB\x18\x02 \x01(\x0b\x32\x18.navirice.ImageSet.Image\x12\'\n\x05\x44\x65pth\x18\x03 \x01(\x0b\x32\x18.navirice.ImageSet.Image\x12$\n\x02IR\x18\x04 \x01(\x0b\x32\x18.navirice.ImageSet.Image\x1a\xb1\x01\n\x05Image\x12\r\n\x05width\x18\x01 \x01(\r\x12\x0e\n\x06height\x18\x02 \x01(\r\x12\x10\n\x08\x63hannels\x18\x03 \x01(\r\x12\x34\n\tdata_type\x18\x04 \x01(\x0e\x32!.navirice.ImageSet.Image.DataType\x12\x11\n\tdata_size\x18\x05 \x01(\r\x12\x0c\n\x04\x64\x61ta\x18\x06 \x01(\x0c\" \n\x08\x44\x61taType\x12\t\n\x05\x46LOAT\x10\x00\x12\t\n\x05UBYTE\x10\x01\x62\x06proto3')
)



_IMAGESET_IMAGE_DATATYPE = _descriptor.EnumDescriptor(
  name='DataType',
  full_name='navirice.ImageSet.Image.DataType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='FLOAT', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='UBYTE', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=326,
  serialized_end=358,
)
_sym_db.RegisterEnumDescriptor(_IMAGESET_IMAGE_DATATYPE)


_IMAGESET_IMAGE = _descriptor.Descriptor(
  name='Image',
  full_name='navirice.ImageSet.Image',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='width', full_name='navirice.ImageSet.Image.width', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='height', full_name='navirice.ImageSet.Image.height', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='channels', full_name='navirice.ImageSet.Image.channels', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='data_type', full_name='navirice.ImageSet.Image.data_type', index=3,
      number=4, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='data_size', full_name='navirice.ImageSet.Image.data_size', index=4,
      number=5, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='data', full_name='navirice.ImageSet.Image.data', index=5,
      number=6, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _IMAGESET_IMAGE_DATATYPE,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=181,
  serialized_end=358,
)

_IMAGESET = _descriptor.Descriptor(
  name='ImageSet',
  full_name='navirice.ImageSet',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='count', full_name='navirice.ImageSet.count', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RGB', full_name='navirice.ImageSet.RGB', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Depth', full_name='navirice.ImageSet.Depth', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='IR', full_name='navirice.ImageSet.IR', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[_IMAGESET_IMAGE, ],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=35,
  serialized_end=358,
)

_IMAGESET_IMAGE.fields_by_name['data_type'].enum_type = _IMAGESET_IMAGE_DATATYPE
_IMAGESET_IMAGE.containing_type = _IMAGESET
_IMAGESET_IMAGE_DATATYPE.containing_type = _IMAGESET_IMAGE
_IMAGESET.fields_by_name['RGB'].message_type = _IMAGESET_IMAGE
_IMAGESET.fields_by_name['Depth'].message_type = _IMAGESET_IMAGE
_IMAGESET.fields_by_name['IR'].message_type = _IMAGESET_IMAGE
DESCRIPTOR.message_types_by_name['ImageSet'] = _IMAGESET
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

ImageSet = _reflection.GeneratedProtocolMessageType('ImageSet', (_message.Message,), dict(

  Image = _reflection.GeneratedProtocolMessageType('Image', (_message.Message,), dict(
    DESCRIPTOR = _IMAGESET_IMAGE,
    __module__ = 'navirice_image_pb2'
    # @@protoc_insertion_point(class_scope:navirice.ImageSet.Image)
    ))
  ,
  DESCRIPTOR = _IMAGESET,
  __module__ = 'navirice_image_pb2'
  # @@protoc_insertion_point(class_scope:navirice.ImageSet)
  ))
_sym_db.RegisterMessage(ImageSet)
_sym_db.RegisterMessage(ImageSet.Image)


# @@protoc_insertion_point(module_scope)