#ifndef SMART_CAN_STUFF__ROS2CAN_HPP_
#define SMART_CAN_STUFF__ROS2CAN_HPP_

#include <rclcpp/rclcpp.hpp>

// ROS messages
#include <can_msgs/msg/frame.hpp>
#include <std_msgs/msg/bool.hpp>
#include <smart_can_msgs/msg/kinematicmessages.hpp>
#include <smart_can_stuff/can_id.h>
#include <smart_can_msgs/msg/autonomousbrakepedalcontrol.hpp>
#include <smart_can_msgs/msg/autonomoushbmotorcontrol.hpp>
#include <smart_can_msgs/msg/autonomoussteeringmotcontrol.hpp>
#include <smart_can_msgs/msg/fbmotordriver.hpp> // veh to auto
#include <smart_can_msgs/msg/fbomuxtoautonomous.hpp> //veh to auto
#include <smart_can_msgs/msg/fbvehiclespeed.hpp> // veh to auto
#include <smart_can_msgs/msg/rcthrtdata.hpp>
#include <smart_can_msgs/msg/rcunittoomux.hpp>
#include <smart_can_msgs/msg/sndrcunitbrakedata.hpp> //veh to auto
#include <smart_can_msgs/msg/sndrcunithandbrakedata.hpp> //veh to auto
#include <smart_can_msgs/msg/sndrcunitsteeringdata.hpp> //veh to auto
#include <smart_can_msgs/msg/autonomousheardbit.hpp> //veh to auto
#include <smart_can_msgs/msg/feedbacksteeringangle.hpp> //veh to auto
#include <smart_can_msgs/msg/feedbacksensor.hpp> //veh to auto

namespace smart_can_stuff
{
class CanHandler : public rclcpp::Node
{
public:
    /*!
    * Constructor
    */
    CanHandler();

private:
    /*!
    * Reads and verifies the ROS parameters.
    * @return true if successful.
    */
    bool readParameters();
    uint8_t setCanMsg(float phy_value, float resolution, int offset);

    //// Parameters from config file
    smart_can_msgs::msg::Rcunittoomux unitto_omux_;
    smart_can_msgs::msg::Rcthrtdata rc_thrt_data_;
    smart_can_msgs::msg::Autonomousbrakepedalcontrol autonomous_brake_pedal_control_;
    smart_can_msgs::msg::Autonomoussteeringmotcontrol autonomous_steering_mot_control_;
    smart_can_msgs::msg::Autonomoushbmotorcontrol autonomous_hb_motor_control_;
    
    // CAN topic
    std::string sender_can_topic_;

    rclcpp::TimerBase::SharedPtr timer_;

    // Subscribers and publishers
    rclcpp::Subscription<smart_can_msgs::msg::Autonomousbrakepedalcontrol>::SharedPtr autonomous_brake_pedal_control_sub_;
    rclcpp::Subscription<smart_can_msgs::msg::Autonomoushbmotorcontrol>::SharedPtr autonomous_hb_motor_control_sub_;
    rclcpp::Subscription<smart_can_msgs::msg::Autonomoussteeringmotcontrol>::SharedPtr autonomous_steering_mot_control_sub_;
    rclcpp::Subscription<smart_can_msgs::msg::Rcthrtdata>::SharedPtr rc_thrt_data_sub_;
    rclcpp::Subscription<smart_can_msgs::msg::Rcunittoomux>::SharedPtr rc_unitto_omux_sub_;
    rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr ros2can_publisher_;

    // Callback functions
    void autonomousBrakePedalControlCallback(const smart_can_msgs::msg::Autonomousbrakepedalcontrol::SharedPtr msg);
    void autonomousHbMotorControlCallback(const smart_can_msgs::msg::Autonomoushbmotorcontrol::SharedPtr msg);
    void autonomousSteeringMotControlCallback(const smart_can_msgs::msg::Autonomoussteeringmotcontrol::SharedPtr msg);
    void rcThrtDataCallback(const smart_can_msgs::msg::Rcthrtdata::SharedPtr msg);
    void rcUnittoOmuxCallback(const smart_can_msgs::msg::Rcunittoomux::SharedPtr msg);

    void loop();
};
}  // namespace smart_can_stuff

#endif // SMART_CAN_STUFF__ROS2CAN_HPP_
