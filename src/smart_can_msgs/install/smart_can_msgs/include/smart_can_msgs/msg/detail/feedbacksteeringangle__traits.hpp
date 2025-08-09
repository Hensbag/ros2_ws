// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from smart_can_msgs:msg/Feedbacksteeringangle.idl
// generated code does not contain a copyright notice

#ifndef SMART_CAN_MSGS__MSG__DETAIL__FEEDBACKSTEERINGANGLE__TRAITS_HPP_
#define SMART_CAN_MSGS__MSG__DETAIL__FEEDBACKSTEERINGANGLE__TRAITS_HPP_

#include "smart_can_msgs/msg/detail/feedbacksteeringangle__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<smart_can_msgs::msg::Feedbacksteeringangle>()
{
  return "smart_can_msgs::msg::Feedbacksteeringangle";
}

template<>
inline const char * name<smart_can_msgs::msg::Feedbacksteeringangle>()
{
  return "smart_can_msgs/msg/Feedbacksteeringangle";
}

template<>
struct has_fixed_size<smart_can_msgs::msg::Feedbacksteeringangle>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<smart_can_msgs::msg::Feedbacksteeringangle>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<smart_can_msgs::msg::Feedbacksteeringangle>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SMART_CAN_MSGS__MSG__DETAIL__FEEDBACKSTEERINGANGLE__TRAITS_HPP_
