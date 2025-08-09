
#ifndef smart_can_stuff__smart_can_stuff_HPP_
#define smart_can_stuff__smart_can_stuff_HPP_

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

#include <can_dbc_parser/DbcMessage.hpp>
#include <can_dbc_parser/DbcSignal.hpp>
#include <can_dbc_parser/Dbc.hpp>
#include <can_dbc_parser/DbcBuilder.hpp>

#include <cmath>
#include <string>
#include <vector>

using can_msgs::msg::Frame;

// using raptor_dbw_msgs::msg::TwistCmd;
// using raptor_dbw_msgs::msg::WatchdogStatus;

namespace smart_can_stuff
{
/** \brief Class for converting Raptor DBW messages between CAN & ROS */
class CanListener : public rclcpp::Node
{
public:
/** \brief Default constructor.
 * \param[in] options The options for this node.
 * \param[in] dbw_dbc_file The name of the DBC file to use.
 */
  explicit CanListener(
    const rclcpp::NodeOptions & options,
    std::string dbw_dbc_file);
  ~CanListener();

  private:

  void recvCAN(const Frame::SharedPtr msg);

/** \brief Convert an Accel Pedal Report received over CAN into a ROS message.
 * \param[in] msg The message received over CAN.
 */

  // Parameters from launch
  std::string dbw_dbc_file_;


  // Subscribed topics
  rclcpp::Subscription<Frame>::SharedPtr sub_can_;


  // Published topics
  rclcpp::Publisher<Frame>::SharedPtr pub_can_;
  rclcpp::Publisher<smart_can_msgs::msg::Fbmotordriver>::SharedPtr m_FB_MotorDriver;
  rclcpp::Publisher<smart_can_msgs::msg::Fbomuxtoautonomous>::SharedPtr m_FB_OMUX_to_AUTONOMOUS;
  rclcpp::Publisher<smart_can_msgs::msg::Fbvehiclespeed>::SharedPtr m_FB_VehicleSpeed;
  rclcpp::Publisher<smart_can_msgs::msg::Sndrcunitbrakedata>::SharedPtr m_snd_RCUnit_BrakeData;
  rclcpp::Publisher<smart_can_msgs::msg::Sndrcunithandbrakedata>::SharedPtr m_snd_RCUnit_HandBrakeData;
  rclcpp::Publisher<smart_can_msgs::msg::Sndrcunitsteeringdata>::SharedPtr m_snd_RCUnit_SteeringData;
  rclcpp::Publisher<smart_can_msgs::msg::Autonomousheardbit>::SharedPtr m_AutonomousHeardBit;
  rclcpp::Publisher<smart_can_msgs::msg::Feedbacksteeringangle>::SharedPtr m_FeedbackSteeringAngle;
  rclcpp::Publisher<smart_can_msgs::msg::Feedbacksensor>::SharedPtr m_Feedback_SENSOR;

  NewEagle::Dbc dbwDbc_;

};

}  // namespace smart_can_stuff

#endif  // smart_can_stuff_smart_can_stuff_HPP
