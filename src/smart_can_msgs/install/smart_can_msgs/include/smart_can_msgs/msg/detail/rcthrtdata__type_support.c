// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from smart_can_msgs:msg/Rcthrtdata.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "smart_can_msgs/msg/detail/rcthrtdata__rosidl_typesupport_introspection_c.h"
#include "smart_can_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "smart_can_msgs/msg/detail/rcthrtdata__functions.h"
#include "smart_can_msgs/msg/detail/rcthrtdata__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  smart_can_msgs__msg__Rcthrtdata__init(message_memory);
}

void Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_fini_function(void * message_memory)
{
  smart_can_msgs__msg__Rcthrtdata__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_message_member_array[2] = {
  {
    "rc_thrt_pedal_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smart_can_msgs__msg__Rcthrtdata, rc_thrt_pedal_position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rc_thrt_pedal_press",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smart_can_msgs__msg__Rcthrtdata, rc_thrt_pedal_press),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_message_members = {
  "smart_can_msgs__msg",  // message namespace
  "Rcthrtdata",  // message name
  2,  // number of fields
  sizeof(smart_can_msgs__msg__Rcthrtdata),
  Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_message_member_array,  // message members
  Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_init_function,  // function to initialize message memory (memory has to be allocated)
  Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_message_type_support_handle = {
  0,
  &Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_smart_can_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, smart_can_msgs, msg, Rcthrtdata)() {
  if (!Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_message_type_support_handle.typesupport_identifier) {
    Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &Rcthrtdata__rosidl_typesupport_introspection_c__Rcthrtdata_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
