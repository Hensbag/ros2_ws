#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/bool.hpp>
#include <smart_can_msgs/msg/feedbacksteeringangle.hpp> //veh to auto
#include <smart_can_msgs/msg/fbvehiclespeed.hpp> // veh to auto
#include <smart_can_msgs/msg/autonomoussteeringmotcontrol.hpp>
#include <smart_can_msgs/msg/rcthrtdata.hpp>

namespace hmk_pid_control
{
class PIDController : public rclcpp::Node
{
public:
    PIDController(const rclcpp::NodeOptions & options);

private:
    void setValueCallback(const std_msgs::msg::Float64::SharedPtr t_set_value);
    void feedbackValueCallback(const smart_can_msgs::msg::Feedbacksteeringangle::SharedPtr t_feedback_value);
    void feedbackspeedValueCallback(const smart_can_msgs::msg::Fbvehiclespeed::SharedPtr t_feedback_speed_value);
    void controlLoop();
    void sendToTopic();
    bool readParameters();

    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr m_set_value_subscriber;
    rclcpp::Subscription<smart_can_msgs::msg::Feedbacksteeringangle>::SharedPtr m_feedback_value_subscriber;
    rclcpp::Subscription<smart_can_msgs::msg::Fbvehiclespeed>::SharedPtr m_feedback_speed_value_subscriber;
    rclcpp::Publisher<smart_can_msgs::msg::Rcthrtdata>::SharedPtr m_output_speed_publisher;
    rclcpp::Publisher<smart_can_msgs::msg::Autonomoussteeringmotcontrol>::SharedPtr m_output_publisher;

    double m_kp;
    double m_kd;
    double m_ki;
    double m_kff;
    double m_pid_error_limit;
    double m_integral_initial_value;
    double m_integral_min_value;
    double m_integral_max_value;
    double m_max_output;
    double m_min_output;

    double m_previous_error;
    double m_integral_error;
    double m_error;
    double m_derivative_error;
    double m_previous_pid_time;

    double m_set_value;
    double m_feedback_value;
    double m_previous_set_value;

    double m_output;
    int m_target_data_since_lastcb;
    int m_timeout_threshold;

    std::string m_feedback_value_topic;
    std::string m_set_value_topic;
    std::string m_output_topic;

};
} // namespace hmk_pid_control
