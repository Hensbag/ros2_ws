// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from smart_can_msgs:msg/Fbvehiclespeed.idl
// generated code does not contain a copyright notice
#include "smart_can_msgs/msg/detail/fbvehiclespeed__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
smart_can_msgs__msg__Fbvehiclespeed__init(smart_can_msgs__msg__Fbvehiclespeed * msg)
{
  if (!msg) {
    return false;
  }
  // fb_vehiclespeed_kmh
  // fb_reelvehiclespeed_kmh
  // fb_reelvehiclespeed_ms
  return true;
}

void
smart_can_msgs__msg__Fbvehiclespeed__fini(smart_can_msgs__msg__Fbvehiclespeed * msg)
{
  if (!msg) {
    return;
  }
  // fb_vehiclespeed_kmh
  // fb_reelvehiclespeed_kmh
  // fb_reelvehiclespeed_ms
}

bool
smart_can_msgs__msg__Fbvehiclespeed__are_equal(const smart_can_msgs__msg__Fbvehiclespeed * lhs, const smart_can_msgs__msg__Fbvehiclespeed * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // fb_vehiclespeed_kmh
  if (lhs->fb_vehiclespeed_kmh != rhs->fb_vehiclespeed_kmh) {
    return false;
  }
  // fb_reelvehiclespeed_kmh
  if (lhs->fb_reelvehiclespeed_kmh != rhs->fb_reelvehiclespeed_kmh) {
    return false;
  }
  // fb_reelvehiclespeed_ms
  if (lhs->fb_reelvehiclespeed_ms != rhs->fb_reelvehiclespeed_ms) {
    return false;
  }
  return true;
}

bool
smart_can_msgs__msg__Fbvehiclespeed__copy(
  const smart_can_msgs__msg__Fbvehiclespeed * input,
  smart_can_msgs__msg__Fbvehiclespeed * output)
{
  if (!input || !output) {
    return false;
  }
  // fb_vehiclespeed_kmh
  output->fb_vehiclespeed_kmh = input->fb_vehiclespeed_kmh;
  // fb_reelvehiclespeed_kmh
  output->fb_reelvehiclespeed_kmh = input->fb_reelvehiclespeed_kmh;
  // fb_reelvehiclespeed_ms
  output->fb_reelvehiclespeed_ms = input->fb_reelvehiclespeed_ms;
  return true;
}

smart_can_msgs__msg__Fbvehiclespeed *
smart_can_msgs__msg__Fbvehiclespeed__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  smart_can_msgs__msg__Fbvehiclespeed * msg = (smart_can_msgs__msg__Fbvehiclespeed *)allocator.allocate(sizeof(smart_can_msgs__msg__Fbvehiclespeed), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(smart_can_msgs__msg__Fbvehiclespeed));
  bool success = smart_can_msgs__msg__Fbvehiclespeed__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
smart_can_msgs__msg__Fbvehiclespeed__destroy(smart_can_msgs__msg__Fbvehiclespeed * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    smart_can_msgs__msg__Fbvehiclespeed__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
smart_can_msgs__msg__Fbvehiclespeed__Sequence__init(smart_can_msgs__msg__Fbvehiclespeed__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  smart_can_msgs__msg__Fbvehiclespeed * data = NULL;

  if (size) {
    data = (smart_can_msgs__msg__Fbvehiclespeed *)allocator.zero_allocate(size, sizeof(smart_can_msgs__msg__Fbvehiclespeed), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = smart_can_msgs__msg__Fbvehiclespeed__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        smart_can_msgs__msg__Fbvehiclespeed__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
smart_can_msgs__msg__Fbvehiclespeed__Sequence__fini(smart_can_msgs__msg__Fbvehiclespeed__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      smart_can_msgs__msg__Fbvehiclespeed__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

smart_can_msgs__msg__Fbvehiclespeed__Sequence *
smart_can_msgs__msg__Fbvehiclespeed__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  smart_can_msgs__msg__Fbvehiclespeed__Sequence * array = (smart_can_msgs__msg__Fbvehiclespeed__Sequence *)allocator.allocate(sizeof(smart_can_msgs__msg__Fbvehiclespeed__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = smart_can_msgs__msg__Fbvehiclespeed__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
smart_can_msgs__msg__Fbvehiclespeed__Sequence__destroy(smart_can_msgs__msg__Fbvehiclespeed__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    smart_can_msgs__msg__Fbvehiclespeed__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
smart_can_msgs__msg__Fbvehiclespeed__Sequence__are_equal(const smart_can_msgs__msg__Fbvehiclespeed__Sequence * lhs, const smart_can_msgs__msg__Fbvehiclespeed__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!smart_can_msgs__msg__Fbvehiclespeed__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
smart_can_msgs__msg__Fbvehiclespeed__Sequence__copy(
  const smart_can_msgs__msg__Fbvehiclespeed__Sequence * input,
  smart_can_msgs__msg__Fbvehiclespeed__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(smart_can_msgs__msg__Fbvehiclespeed);
    smart_can_msgs__msg__Fbvehiclespeed * data =
      (smart_can_msgs__msg__Fbvehiclespeed *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!smart_can_msgs__msg__Fbvehiclespeed__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          smart_can_msgs__msg__Fbvehiclespeed__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!smart_can_msgs__msg__Fbvehiclespeed__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
