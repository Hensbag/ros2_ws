cmake_minimum_required(VERSION 3.5)
project(smart_can_stuff)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(can_msgs REQUIRED)
find_package(can_dbc_parser REQUIRED)
find_package(smart_can_msgs REQUIRED)
find_package(ament_cmake_python REQUIRED)

# Add include directories
include_directories(include)

# Add executable
add_executable(can2ros_node
  src/can2ros_node.cpp
  src/can2ros.cpp
)

add_executable(ros2can_node
  src/ros2can_node.cpp
  src/ros2can.cpp
)

add_executable(steering_pid_node
  src/pid_controller_node.cpp
  src/pid_controller.cpp
)

add_executable(speed_pid_node
  src/pid_controller_node.cpp
  src/pid_controller_speed.cpp
)

ament_target_dependencies(can2ros_node
  rclcpp
  rclpy
  can_dbc_parser
  can_msgs
  smart_can_msgs
)

ament_target_dependencies(ros2can_node
  rclcpp
  rclpy
  can_dbc_parser
  can_msgs
  smart_can_msgs
)

ament_target_dependencies(steering_pid_node
  rclcpp
  rclpy
  can_msgs
  smart_can_msgs
)

ament_target_dependencies(speed_pid_node
  rclcpp
  rclpy
  can_msgs
  smart_can_msgs
)

install(TARGETS
  can2ros_node
    DESTINATION ${PROJECT_NAME}/src)

install(TARGETS
  can2ros_node
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS
  ros2can_node
    DESTINATION ${PROJECT_NAME}/src)
  
install(TARGETS
  ros2can_node
    DESTINATION lib/${PROJECT_NAME})

install(TARGETS
  steering_pid_node
    DESTINATION ${PROJECT_NAME}/src)

install(TARGETS
  steering_pid_node
    DESTINATION lib/${PROJECT_NAME})

install(TARGETS
  speed_pid_node
    DESTINATION ${PROJECT_NAME}/src)

install(TARGETS
  speed_pid_node
    DESTINATION lib/${PROJECT_NAME})
# Install Python modules
# ament_python_install_package(${PROJECT_NAME})

# Install Python executables
install(PROGRAMS
  scripts/beemobs.py
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)
install(
  PROGRAMS
  launch/can_launch.py
  DESTINATION lib/${PROJECT_NAME}
)
ament_package()

