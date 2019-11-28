/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: sensordata.proto */

#ifndef PROTOBUF_C_sensordata_2eproto__INCLUDED
#define PROTOBUF_C_sensordata_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003002 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Ninux__Entry Ninux__Entry;
typedef struct _Ninux__Myset Ninux__Myset;
typedef struct _Ninux__Sensordata Ninux__Sensordata;


/* --- enums --- */


/* --- messages --- */

struct  _Ninux__Entry
{
  ProtobufCMessage base;
  char *key;
  int32_t value;
};
#define NINUX__ENTRY__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ninux__entry__descriptor) \
    , NULL, 0 }


struct  _Ninux__Myset
{
  ProtobufCMessage base;
  int32_t timestamp;
  size_t n_entries;
  Ninux__Entry **entries;
};
#define NINUX__MYSET__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ninux__myset__descriptor) \
    , 0, 0,NULL }


struct  _Ninux__Sensordata
{
  ProtobufCMessage base;
  size_t n_sets;
  Ninux__Myset **sets;
};
#define NINUX__SENSORDATA__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ninux__sensordata__descriptor) \
    , 0,NULL }


/* Ninux__Entry methods */
void   ninux__entry__init
                     (Ninux__Entry         *message);
size_t ninux__entry__get_packed_size
                     (const Ninux__Entry   *message);
size_t ninux__entry__pack
                     (const Ninux__Entry   *message,
                      uint8_t             *out);
size_t ninux__entry__pack_to_buffer
                     (const Ninux__Entry   *message,
                      ProtobufCBuffer     *buffer);
Ninux__Entry *
       ninux__entry__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ninux__entry__free_unpacked
                     (Ninux__Entry *message,
                      ProtobufCAllocator *allocator);
/* Ninux__Myset methods */
void   ninux__myset__init
                     (Ninux__Myset         *message);
size_t ninux__myset__get_packed_size
                     (const Ninux__Myset   *message);
size_t ninux__myset__pack
                     (const Ninux__Myset   *message,
                      uint8_t             *out);
size_t ninux__myset__pack_to_buffer
                     (const Ninux__Myset   *message,
                      ProtobufCBuffer     *buffer);
Ninux__Myset *
       ninux__myset__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ninux__myset__free_unpacked
                     (Ninux__Myset *message,
                      ProtobufCAllocator *allocator);
/* Ninux__Sensordata methods */
void   ninux__sensordata__init
                     (Ninux__Sensordata         *message);
size_t ninux__sensordata__get_packed_size
                     (const Ninux__Sensordata   *message);
size_t ninux__sensordata__pack
                     (const Ninux__Sensordata   *message,
                      uint8_t             *out);
size_t ninux__sensordata__pack_to_buffer
                     (const Ninux__Sensordata   *message,
                      ProtobufCBuffer     *buffer);
Ninux__Sensordata *
       ninux__sensordata__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ninux__sensordata__free_unpacked
                     (Ninux__Sensordata *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Ninux__Entry_Closure)
                 (const Ninux__Entry *message,
                  void *closure_data);
typedef void (*Ninux__Myset_Closure)
                 (const Ninux__Myset *message,
                  void *closure_data);
typedef void (*Ninux__Sensordata_Closure)
                 (const Ninux__Sensordata *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor ninux__entry__descriptor;
extern const ProtobufCMessageDescriptor ninux__myset__descriptor;
extern const ProtobufCMessageDescriptor ninux__sensordata__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_sensordata_2eproto__INCLUDED */
