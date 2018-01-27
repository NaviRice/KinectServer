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
  serialized_pb=_b('\n\x14navirice_image.proto\x12\x08navirice\"4\n\x0fProtoImageCount\x12\r\n\x05\x63ount\x18\x01 \x01(\x04\x12\x12\n\nbyte_count\x18\x02 \x01(\x04\"y\n\x10ProtoAcknowledge\x12-\n\x05state\x18\x01 \x01(\x0e\x32\x1e.navirice.ProtoAcknowledge.ACK\x12\r\n\x05\x63ount\x18\x02 \x01(\x04\"\'\n\x03\x41\x43K\x12\x08\n\x04NONE\x10\x00\x12\x0c\n\x08\x43ONTINUE\x10\x01\x12\x08\n\x04STOP\x10\x02\"\xb2\x01\n\nProtoImage\x12\r\n\x05width\x18\x01 \x01(\r\x12\x0e\n\x06height\x18\x02 \x01(\r\x12\x10\n\x08\x63hannels\x18\x03 \x01(\r\x12\x30\n\tdata_type\x18\x04 \x01(\x0e\x32\x1d.navirice.ProtoImage.DataType\x12\x11\n\tdata_size\x18\x05 \x01(\r\x12\x0c\n\x04\x64\x61ta\x18\x06 \x01(\x0c\" \n\x08\x44\x61taType\x12\t\n\x05\x46LOAT\x10\x00\x12\t\n\x05UBYTE\x10\x01\"\x88\x01\n\rProtoImageSet\x12\r\n\x05\x63ount\x18\x01 \x01(\x04\x12!\n\x03RGB\x18\x02 \x01(\x0b\x32\x14.navirice.ProtoImage\x12#\n\x05\x44\x65pth\x18\x03 \x01(\x0b\x32\x14.navirice.ProtoImage\x12 \n\x02IR\x18\x04 \x01(\x0b\x32\x14.navirice.ProtoImage\"L\n\x13ProtoCaptureSetting\x12\x0b\n\x03RGB\x18\x01 \x01(\x08\x12\r\n\x05\x44\x65pth\x18\x02 \x01(\x08\x12\n\n\x02IR\x18\x03 \x01(\x08\x12\r\n\x05\x63ount\x18\x04 \x01(\x04\"\xb5\x01\n\x0cProtoRequest\x12-\n\x05state\x18\x01 \x01(\x0e\x32\x1e.navirice.ProtoRequest.ReqType\x12\r\n\x05\x63ount\x18\x02 \x01(\x04\x12<\n\x15\x63\x61pture_setting_value\x18\x03 \x01(\x0b\x32\x1d.navirice.ProtoCaptureSetting\")\n\x07ReqType\x12\t\n\x05IMAGE\x10\x00\x12\x13\n\x0f\x43\x41PTURE_SETTING\x10\x01\x62\x06proto3')
)



_PROTOACKNOWLEDGE_ACK = _descriptor.EnumDescriptor(
  name='ACK',
  full_name='navirice.ProtoAcknowledge.ACK',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NONE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CONTINUE', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='STOP', index=2, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=170,
  serialized_end=209,
)
_sym_db.RegisterEnumDescriptor(_PROTOACKNOWLEDGE_ACK)

_PROTOIMAGE_DATATYPE = _descriptor.EnumDescriptor(
  name='DataType',
  full_name='navirice.ProtoImage.DataType',
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
  serialized_start=358,
  serialized_end=390,
)
_sym_db.RegisterEnumDescriptor(_PROTOIMAGE_DATATYPE)

_PROTOREQUEST_REQTYPE = _descriptor.EnumDescriptor(
  name='ReqType',
  full_name='navirice.ProtoRequest.ReqType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='IMAGE', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CAPTURE_SETTING', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=750,
  serialized_end=791,
)
_sym_db.RegisterEnumDescriptor(_PROTOREQUEST_REQTYPE)


_PROTOIMAGECOUNT = _descriptor.Descriptor(
  name='ProtoImageCount',
  full_name='navirice.ProtoImageCount',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='count', full_name='navirice.ProtoImageCount.count', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='byte_count', full_name='navirice.ProtoImageCount.byte_count', index=1,
      number=2, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=34,
  serialized_end=86,
)


_PROTOACKNOWLEDGE = _descriptor.Descriptor(
  name='ProtoAcknowledge',
  full_name='navirice.ProtoAcknowledge',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='state', full_name='navirice.ProtoAcknowledge.state', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='count', full_name='navirice.ProtoAcknowledge.count', index=1,
      number=2, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PROTOACKNOWLEDGE_ACK,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=88,
  serialized_end=209,
)


_PROTOIMAGE = _descriptor.Descriptor(
  name='ProtoImage',
  full_name='navirice.ProtoImage',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='width', full_name='navirice.ProtoImage.width', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='height', full_name='navirice.ProtoImage.height', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='channels', full_name='navirice.ProtoImage.channels', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='data_type', full_name='navirice.ProtoImage.data_type', index=3,
      number=4, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='data_size', full_name='navirice.ProtoImage.data_size', index=4,
      number=5, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='data', full_name='navirice.ProtoImage.data', index=5,
      number=6, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PROTOIMAGE_DATATYPE,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=212,
  serialized_end=390,
)


_PROTOIMAGESET = _descriptor.Descriptor(
  name='ProtoImageSet',
  full_name='navirice.ProtoImageSet',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='count', full_name='navirice.ProtoImageSet.count', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='RGB', full_name='navirice.ProtoImageSet.RGB', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='Depth', full_name='navirice.ProtoImageSet.Depth', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='IR', full_name='navirice.ProtoImageSet.IR', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=393,
  serialized_end=529,
)


_PROTOCAPTURESETTING = _descriptor.Descriptor(
  name='ProtoCaptureSetting',
  full_name='navirice.ProtoCaptureSetting',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='RGB', full_name='navirice.ProtoCaptureSetting.RGB', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='Depth', full_name='navirice.ProtoCaptureSetting.Depth', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='IR', full_name='navirice.ProtoCaptureSetting.IR', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='count', full_name='navirice.ProtoCaptureSetting.count', index=3,
      number=4, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=531,
  serialized_end=607,
)


_PROTOREQUEST = _descriptor.Descriptor(
  name='ProtoRequest',
  full_name='navirice.ProtoRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='state', full_name='navirice.ProtoRequest.state', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='count', full_name='navirice.ProtoRequest.count', index=1,
      number=2, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='capture_setting_value', full_name='navirice.ProtoRequest.capture_setting_value', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _PROTOREQUEST_REQTYPE,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=610,
  serialized_end=791,
)

_PROTOACKNOWLEDGE.fields_by_name['state'].enum_type = _PROTOACKNOWLEDGE_ACK
_PROTOACKNOWLEDGE_ACK.containing_type = _PROTOACKNOWLEDGE
_PROTOIMAGE.fields_by_name['data_type'].enum_type = _PROTOIMAGE_DATATYPE
_PROTOIMAGE_DATATYPE.containing_type = _PROTOIMAGE
_PROTOIMAGESET.fields_by_name['RGB'].message_type = _PROTOIMAGE
_PROTOIMAGESET.fields_by_name['Depth'].message_type = _PROTOIMAGE
_PROTOIMAGESET.fields_by_name['IR'].message_type = _PROTOIMAGE
_PROTOREQUEST.fields_by_name['state'].enum_type = _PROTOREQUEST_REQTYPE
_PROTOREQUEST.fields_by_name['capture_setting_value'].message_type = _PROTOCAPTURESETTING
_PROTOREQUEST_REQTYPE.containing_type = _PROTOREQUEST
DESCRIPTOR.message_types_by_name['ProtoImageCount'] = _PROTOIMAGECOUNT
DESCRIPTOR.message_types_by_name['ProtoAcknowledge'] = _PROTOACKNOWLEDGE
DESCRIPTOR.message_types_by_name['ProtoImage'] = _PROTOIMAGE
DESCRIPTOR.message_types_by_name['ProtoImageSet'] = _PROTOIMAGESET
DESCRIPTOR.message_types_by_name['ProtoCaptureSetting'] = _PROTOCAPTURESETTING
DESCRIPTOR.message_types_by_name['ProtoRequest'] = _PROTOREQUEST
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

ProtoImageCount = _reflection.GeneratedProtocolMessageType('ProtoImageCount', (_message.Message,), dict(
  DESCRIPTOR = _PROTOIMAGECOUNT,
  __module__ = 'navirice_image_pb2'
  # @@protoc_insertion_point(class_scope:navirice.ProtoImageCount)
  ))
_sym_db.RegisterMessage(ProtoImageCount)

ProtoAcknowledge = _reflection.GeneratedProtocolMessageType('ProtoAcknowledge', (_message.Message,), dict(
  DESCRIPTOR = _PROTOACKNOWLEDGE,
  __module__ = 'navirice_image_pb2'
  # @@protoc_insertion_point(class_scope:navirice.ProtoAcknowledge)
  ))
_sym_db.RegisterMessage(ProtoAcknowledge)

ProtoImage = _reflection.GeneratedProtocolMessageType('ProtoImage', (_message.Message,), dict(
  DESCRIPTOR = _PROTOIMAGE,
  __module__ = 'navirice_image_pb2'
  # @@protoc_insertion_point(class_scope:navirice.ProtoImage)
  ))
_sym_db.RegisterMessage(ProtoImage)

ProtoImageSet = _reflection.GeneratedProtocolMessageType('ProtoImageSet', (_message.Message,), dict(
  DESCRIPTOR = _PROTOIMAGESET,
  __module__ = 'navirice_image_pb2'
  # @@protoc_insertion_point(class_scope:navirice.ProtoImageSet)
  ))
_sym_db.RegisterMessage(ProtoImageSet)

ProtoCaptureSetting = _reflection.GeneratedProtocolMessageType('ProtoCaptureSetting', (_message.Message,), dict(
  DESCRIPTOR = _PROTOCAPTURESETTING,
  __module__ = 'navirice_image_pb2'
  # @@protoc_insertion_point(class_scope:navirice.ProtoCaptureSetting)
  ))
_sym_db.RegisterMessage(ProtoCaptureSetting)

ProtoRequest = _reflection.GeneratedProtocolMessageType('ProtoRequest', (_message.Message,), dict(
  DESCRIPTOR = _PROTOREQUEST,
  __module__ = 'navirice_image_pb2'
  # @@protoc_insertion_point(class_scope:navirice.ProtoRequest)
  ))
_sym_db.RegisterMessage(ProtoRequest)


# @@protoc_insertion_point(module_scope)
