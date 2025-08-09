#include <rclcpp/rclcpp.hpp>
#include "smart_can_stuff/pid_controller.hpp"

int main(int argc, char ** argv)
{
    // ROS 2 ortamını başlat
    rclcpp::init(argc, argv);

    // PIDController düğümünü oluştur
    auto node = std::make_shared<hmk_pid_control::PIDController>(rclcpp::NodeOptions());

    // ROS 2 döngüsünü başlat
    rclcpp::spin(node);

    // ROS 2 ortamını kapat
    rclcpp::shutdown();

    return 0;
}
