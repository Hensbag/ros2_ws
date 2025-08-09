// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from smart_can_msgs:msg/Feedbacksteeringangle.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "smart_can_msgs/msg/detail/feedbacksteeringangle__rosidl_typesupport_introspection_c.h"
#include "smart_can_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "smart_can_msgs/msg/detail/feedbacksteeringangle__functions.h"
#include "smart_can_msgs/msg/detail/feedbacksteeringangle__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  smart_can_msgs__msg__Feedbacksteeringangle__init(message_memory);
}

void Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_fini_function(void * message_memory)
{
  smart_can_msgs__msg__Feedbacksteeringangle__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_message_member_array[2] = {
  {
    "feedbacksteeringangle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smart_can_msgs__msg__Feedbacksteeringangle, feedbacksteeringangle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedbackbrakepedalangle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(smart_can_msgs__msg__Feedbacksteeringangle, feedbackbrakepedalangle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_message_members = {
  "smart_can_msgs__msg",  // message namespace
  "Feedbacksteeringangle",  // message name
  2,  // number of fields
  sizeof(smart_can_msgs__msg__Feedbacksteeringangle),
  Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_message_member_array,  // message members
  Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_init_function,  // function to initialize message memory (memory has to be allocated)
  Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_message_type_support_handle = {
  0,
  &Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_smart_can_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, smart_can_msgs, msg, Feedbacksteeringangle)() {
  if (!Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_message_type_support_handle.typesupport_identifier) {
    Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &Feedbacksteeringangle__rosidl_typesupport_introspection_c__Feedbacksteeringangle_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
