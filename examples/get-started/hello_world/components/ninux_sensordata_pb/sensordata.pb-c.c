/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: sensordata.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "sensordata.pb-c.h"
void   ninux__entry__init
                     (Ninux__Entry         *message)
{
  static const Ninux__Entry init_value = NINUX__ENTRY__INIT;
  *message = init_value;
}
size_t ninux__entry__get_packed_size
                     (const Ninux__Entry *message)
{
  assert(message->base.descriptor == &ninux__entry__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ninux__entry__pack
                     (const Ninux__Entry *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ninux__entry__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ninux__entry__pack_to_buffer
                     (const Ninux__Entry *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ninux__entry__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ninux__Entry *
       ninux__entry__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ninux__Entry *)
     protobuf_c_message_unpack (&ninux__entry__descriptor,
                                allocator, len, data);
}
void   ninux__entry__free_unpacked
                     (Ninux__Entry *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ninux__entry__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ninux__myset__init
                     (Ninux__Myset         *message)
{
  static const Ninux__Myset init_value = NINUX__MYSET__INIT;
  *message = init_value;
}
size_t ninux__myset__get_packed_size
                     (const Ninux__Myset *message)
{
  assert(message->base.descriptor == &ninux__myset__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ninux__myset__pack
                     (const Ninux__Myset *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ninux__myset__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ninux__myset__pack_to_buffer
                     (const Ninux__Myset *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ninux__myset__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ninux__Myset *
       ninux__myset__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ninux__Myset *)
     protobuf_c_message_unpack (&ninux__myset__descriptor,
                                allocator, len, data);
}
void   ninux__myset__free_unpacked
                     (Ninux__Myset *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ninux__myset__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ninux__sensordata__init
                     (Ninux__Sensordata         *message)
{
  static const Ninux__Sensordata init_value = NINUX__SENSORDATA__INIT;
  *message = init_value;
}
size_t ninux__sensordata__get_packed_size
                     (const Ninux__Sensordata *message)
{
  assert(message->base.descriptor == &ninux__sensordata__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ninux__sensordata__pack
                     (const Ninux__Sensordata *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ninux__sensordata__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ninux__sensordata__pack_to_buffer
                     (const Ninux__Sensordata *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ninux__sensordata__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ninux__Sensordata *
       ninux__sensordata__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ninux__Sensordata *)
     protobuf_c_message_unpack (&ninux__sensordata__descriptor,
                                allocator, len, data);
}
void   ninux__sensordata__free_unpacked
                     (Ninux__Sensordata *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ninux__sensordata__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor ninux__entry__field_descriptors[2] =
{
  {
    "key",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ninux__Entry, key),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "value",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ninux__Entry, value),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ninux__entry__field_indices_by_name[] = {
  0,   /* field[0] = key */
  1,   /* field[1] = value */
};
static const ProtobufCIntRange ninux__entry__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ninux__entry__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ninux.entry",
  "Entry",
  "Ninux__Entry",
  "ninux",
  sizeof(Ninux__Entry),
  2,
  ninux__entry__field_descriptors,
  ninux__entry__field_indices_by_name,
  1,  ninux__entry__number_ranges,
  (ProtobufCMessageInit) ninux__entry__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ninux__myset__field_descriptors[2] =
{
  {
    "timestamp",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ninux__Myset, timestamp),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "entries",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Ninux__Myset, n_entries),
    offsetof(Ninux__Myset, entries),
    &ninux__entry__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ninux__myset__field_indices_by_name[] = {
  1,   /* field[1] = entries */
  0,   /* field[0] = timestamp */
};
static const ProtobufCIntRange ninux__myset__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ninux__myset__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ninux.myset",
  "Myset",
  "Ninux__Myset",
  "ninux",
  sizeof(Ninux__Myset),
  2,
  ninux__myset__field_descriptors,
  ninux__myset__field_indices_by_name,
  1,  ninux__myset__number_ranges,
  (ProtobufCMessageInit) ninux__myset__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ninux__sensordata__field_descriptors[1] =
{
  {
    "sets",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Ninux__Sensordata, n_sets),
    offsetof(Ninux__Sensordata, sets),
    &ninux__myset__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ninux__sensordata__field_indices_by_name[] = {
  0,   /* field[0] = sets */
};
static const ProtobufCIntRange ninux__sensordata__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor ninux__sensordata__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ninux.sensordata",
  "Sensordata",
  "Ninux__Sensordata",
  "ninux",
  sizeof(Ninux__Sensordata),
  1,
  ninux__sensordata__field_descriptors,
  ninux__sensordata__field_indices_by_name,
  1,  ninux__sensordata__number_ranges,
  (ProtobufCMessageInit) ninux__sensordata__init,
  NULL,NULL,NULL    /* reserved[123] */
};
