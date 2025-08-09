// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from smart_can_msgs:msg/Feedbacksensor.idl
// generated code does not contain a copyright notice

#ifndef SMART_CAN_MSGS__MSG__DETAIL__FEEDBACKSENSOR__STRUCT_H_
#define SMART_CAN_MSGS__MSG__DETAIL__FEEDBACKSENSOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Feedbacksensor in the package smart_can_msgs.
typedef struct smart_can_msgs__msg__Feedbacksensor
{
  uint8_t steeringanglesensorhamdata;
  uint8_t brakepedalsensorhamdata;
  uint8_t handbrakesensor;
  uint8_t handbrakesensor_hamdata;
  uint8_t indir;
  uint8_t kaldir;
  uint8_t butonindir;
  uint8_t butonkaldir;
} smart_can_msgs__msg__Feedbacksensor;

// Struct for a sequence of smart_can_msgs__msg__Feedbacksensor.
typedef struct smart_can_msgs__msg__Feedbacksensor__Sequence
{
  smart_can_msgs__msg__Feedbacksensor * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} smart_can_msgs__msg__Feedbacksensor__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SMART_CAN_MSGS__MSG__DETAIL__FEEDBACKSENSOR__STRUCT_H_
