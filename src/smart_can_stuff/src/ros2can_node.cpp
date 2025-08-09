#include "smart_can_stuff/ros2can.hpp"
#include <rclcpp/rclcpp.hpp>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<smart_can_stuff::CanHandler>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
