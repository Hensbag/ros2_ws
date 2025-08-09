#include "smart_can_stuff/ros2can.hpp"
#include <iostream>

namespace smart_can_stuff
{

CanHandler::CanHandler() : Node("can_handler")
{
    if (!readParameters())
    {
        RCLCPP_ERROR(this->get_logger(), "Could not read parameters.");
        rclcpp::shutdown();
    }

    // Initialize member variables
    unitto_omux_.rc_ignition = 0; // 0 = OFF, 1 = ON 
    unitto_omux_.rc_selectiongear = 0; // 0:N 1:D 2:R ** 2bit
    unitto_omux_.rc_highbeam = 0; // 0 = OFF, 1 = ON
    unitto_omux_.rc_lowbeam = 0; // 0 = OFF, 1 = ON
    unitto_omux_.rc_drl = 0; // 0 = OFF, 1 = ON
    unitto_omux_.rc_signalstatus = 0; // 0:off 1: sağ 2:sol 3:flashör ** 2bit
    unitto_omux_.autonomous_door_close = 0; // 0 = OFF, 1 = ON
    unitto_omux_.autonomous_door_open = 0; // 0 = OFF, 1 = ON
    unitto_omux_.rc_reverselight = 0; // 0 = OFF, 1 = ON
    unitto_omux_.rc_interiorlight = 0; // 0 = OFF, 1 = ON
    unitto_omux_.rc_windowresintance = 0; // 0 = OFF, 1 = ON
    unitto_omux_.rc_brakelight = 0; // 0 = OFF, 1 = ON
    unitto_omux_.autonomous_emergency = 0; // 0 = araç hareket eder, 1 = araç durur

    //rc_thrt_data
    rc_thrt_data_.rc_thrt_pedal_press = 1; // 0:pedala basıldı 1:basılmadı
    rc_thrt_data_.rc_thrt_pedal_position = 0; // data range: 50-250 offset:0 factor:1 //8bit 2.byte

    //autonomous_brake_pedal_control
    autonomous_brake_pedal_control_.autonomous_brakepedalmotor_en = 0; // 0:disable 1:enable/ 0-7.bit
    autonomous_brake_pedal_control_.autonomous_brakepedalmotor_acc = 0; // data range:5000- 65500 / 8-23.bit / pedala basılma hızı
    autonomous_brake_pedal_control_.autonomous_brakepedalmotor_per = 0; // data range: 0-100 / 24-31.bit / pedalın pozisyonu
    autonomous_brake_pedal_control_.autonomous_brakemotor_voltage = 0; //0:disable 1:enable / 32-39.bit /fren motor voltaj ac kapa

    //autonomous_steering_mot_control/ 0x701
    autonomous_steering_mot_control_.autonomous_steeringmot_pwm = 0; // data range: 0 - 255  / 0-7.bit /0-127: sola 128-255 sağa
    autonomous_steering_mot_control_.autonomous_steeringmot_en = 0; // 0:disable 1:enable/ 8-15.bit

    //autonomous_hb_motor_control/ 0x702
    autonomous_hb_motor_control_.autonomous_hb_moten = 0; // 0:disable 1:Enable  / 0-7.bit /motor voltajı
    autonomous_hb_motor_control_.autonomous_hb_motstate = 0; // 0:el frenini çek 1:el frenini indir / 8-15.bit
    autonomous_hb_motor_control_.autonomous_hb_motor_pwm = 0; //data range: 0-255  / 16-23.bit

    autonomous_brake_pedal_control_sub_ = this->create_subscription<smart_can_msgs::msg::Autonomousbrakepedalcontrol>(
        "/beemobs/AUTONOMOUS_BrakePedalControl", 10, std::bind(&CanHandler::autonomousBrakePedalControlCallback, this, std::placeholders::_1));

    autonomous_hb_motor_control_sub_ = this->create_subscription<smart_can_msgs::msg::Autonomoushbmotorcontrol>(
        "/beemobs/AUTONOMOUS_HB_MotorControl", 10, std::bind(&CanHandler::autonomousHbMotorControlCallback, this, std::placeholders::_1));

    autonomous_steering_mot_control_sub_ = this->create_subscription<smart_can_msgs::msg::Autonomoussteeringmotcontrol>(
        "/beemobs/AUTONOMOUS_SteeringMot_Control", 10, std::bind(&CanHandler::autonomousSteeringMotControlCallback, this, std::placeholders::_1));

    rc_thrt_data_sub_ = this->create_subscription<smart_can_msgs::msg::Rcthrtdata>(
        "/beemobs/RC_THRT_DATA", 10, std::bind(&CanHandler::rcThrtDataCallback, this, std::placeholders::_1));

    rc_unitto_omux_sub_ = this->create_subscription<smart_can_msgs::msg::Rcunittoomux>(
        "/beemobs/rc_unittoOmux", 10, std::bind(&CanHandler::rcUnittoOmuxCallback, this, std::placeholders::_1));

    ros2can_publisher_ = this->create_publisher<can_msgs::msg::Frame>("/to_can_bus", 10);

    // Start loop
    timer_ = this->create_wall_timer(
     std::chrono::milliseconds(10), std::bind(&CanHandler::loop, this));

    // rclcpp::TimerBase::SharedPtr timer_ = this->create_wall_timer(
    //     std::chrono::milliseconds(100), std::bind(&CanHandler::loop, this));
}

bool CanHandler::readParameters()
{
    // Implement parameter reading here
    // For now, return true to simulate successful parameter reading
    return true;
}

uint8_t CanHandler::setCanMsg(float phy_value, float resolution, int offset)
{
    // Implement CAN message setting logic here
    // For now, return a dummy value
    return phy_value * resolution + offset;
}

void CanHandler::autonomousBrakePedalControlCallback(const smart_can_msgs::msg::Autonomousbrakepedalcontrol::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "Received autonomous brake pedal control message");
    // Process brake pedal control message here
    autonomous_brake_pedal_control_.autonomous_brakepedalmotor_en = msg->autonomous_brakepedalmotor_en;
    autonomous_brake_pedal_control_.autonomous_brakepedalmotor_acc = msg->autonomous_brakepedalmotor_acc;
    autonomous_brake_pedal_control_.autonomous_brakepedalmotor_per = msg->autonomous_brakepedalmotor_per;
    autonomous_brake_pedal_control_.autonomous_brakemotor_voltage = msg->autonomous_brakemotor_voltage;
}

void CanHandler::autonomousHbMotorControlCallback(const smart_can_msgs::msg::Autonomoushbmotorcontrol::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "Received autonomous HB motor control message");
    // Process HB motor control message here
    autonomous_hb_motor_control_.autonomous_hb_moten = msg->autonomous_hb_moten;
    autonomous_hb_motor_control_.autonomous_hb_motstate = msg->autonomous_hb_motstate;
    autonomous_hb_motor_control_.autonomous_hb_motor_pwm = msg->autonomous_hb_motor_pwm;
}

void CanHandler::autonomousSteeringMotControlCallback(const smart_can_msgs::msg::Autonomoussteeringmotcontrol::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "Received autonomous steering motor control message");
    // Process steering motor control message here
    autonomous_steering_mot_control_.autonomous_steeringmot_pwm = msg->autonomous_steeringmot_pwm;
    autonomous_steering_mot_control_.autonomous_steeringmot_en = msg->autonomous_steeringmot_en;
}

void CanHandler::rcThrtDataCallback(const smart_can_msgs::msg::Rcthrtdata::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "Received RC throttle data message");
    // Process throttle data message here
    rc_thrt_data_.rc_thrt_pedal_press = msg->rc_thrt_pedal_press;
    rc_thrt_data_.rc_thrt_pedal_position = msg->rc_thrt_pedal_position;
}

void CanHandler::rcUnittoOmuxCallback(const smart_can_msgs::msg::Rcunittoomux::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "Received RC unit to Omux message");
    // Process RC unit to Omux message here
    unitto_omux_.rc_ignition = msg->rc_ignition;
    unitto_omux_.rc_selectiongear = msg->rc_selectiongear; // 0:n 1:d 2:r ** 2bit
    unitto_omux_.rc_highbeam = msg->rc_highbeam; // 0 = off, 1 = on
    unitto_omux_.rc_lowbeam = msg->rc_lowbeam; // 0 = off, 1 = on
    unitto_omux_.rc_drl = msg->rc_drl; // 0 = off, 1 = on
    unitto_omux_.rc_signalstatus = msg->rc_signalstatus; // 0 = off, 1 = on
    unitto_omux_.autonomous_door_close = msg->autonomous_door_close; // 0 = off, 1 = on
    unitto_omux_.autonomous_door_open = msg->autonomous_door_open; // 0 = off, 1 = on
    unitto_omux_.rc_reverselight = msg->rc_reverselight; // 0 = off, 1 = on
    unitto_omux_.rc_interiorlight = msg->rc_interiorlight; // 0 = off, 1 = on
    unitto_omux_.rc_windowresintance = msg->rc_windowresintance; // 0 = off, 1 = on
    unitto_omux_.rc_brakelight = msg->rc_brakelight; // 0 = off, 1 = on
    unitto_omux_.autonomous_emergency = msg->autonomous_emergency; // 0 = off, 1 = on

}

void CanHandler::loop()
{
    // Implement the periodic tasks to be executed here
    RCLCPP_INFO(this->get_logger(), "Executing loop");
    // unit to omux
    can_msgs::msg::Frame can_msg;
    can_msg.id = 0x0000800;
    can_msg.is_extended = true;
    can_msg.dlc = 8;
        
    can_msg.data[0] = (unitto_omux_.rc_ignition & 0x01) |

                          ((unitto_omux_.rc_selectiongear & 0x03) << 1) |
                          ((unitto_omux_.rc_highbeam & 0x01) << 3) |
                          ((unitto_omux_.rc_lowbeam & 0x01) << 4) |
                          ((unitto_omux_.rc_drl & 0x01) << 5) |
                          ((unitto_omux_.rc_signalstatus & 0x03) << 6);

    can_msg.data[1] = (unitto_omux_.autonomous_door_close & 0x01) |
                          ((unitto_omux_.autonomous_door_open & 0x01) << 1) |
                          ((unitto_omux_.rc_reverselight & 0x01) << 2) |
                          ((unitto_omux_.rc_interiorlight & 0x01) << 3) |
                          ((unitto_omux_.rc_windowresintance & 0x01) << 4)|
                          ((unitto_omux_.rc_brakelight & 0x01) << 5)|
                          ((unitto_omux_.autonomous_emergency & 0x01) << 6); 
    can_msg.data[2] = can_msg.data[3] = can_msg.data[4] = can_msg.data[5] = can_msg.data[6] = can_msg.data[7] = 0;        
    ros2can_publisher_->publish(can_msg);

    can_msgs::msg::Frame can_msg1;
    can_msg1.id = 0xCF00300;
    can_msg1.is_extended = true;
    can_msg1.dlc = 8;

    can_msg1.data[0] = (rc_thrt_data_.rc_thrt_pedal_press & 0x01);
    can_msg1.data[1] = (rc_thrt_data_.rc_thrt_pedal_position );
    can_msg1.data[2] = can_msg1.data[3] = can_msg1.data[4] = can_msg1.data[5] = can_msg1.data[6] = can_msg1.data[7] = 0;
    ros2can_publisher_->publish(can_msg1);

    can_msgs::msg::Frame can_msg2;
    can_msg2.id = 0x0000700;
    can_msg2.is_extended = true;
    can_msg2.dlc = 8;

    can_msg2.data[0] = (autonomous_brake_pedal_control_.autonomous_brakepedalmotor_en ) ;
    can_msg2.data[1] = (autonomous_brake_pedal_control_.autonomous_brakepedalmotor_acc & 0xFF);
    can_msg2.data[2] = (autonomous_brake_pedal_control_.autonomous_brakepedalmotor_acc >>8 ) & 0xFF;
    can_msg2.data[3] = (autonomous_brake_pedal_control_.autonomous_brakepedalmotor_per );
    can_msg2.data[4] = (autonomous_brake_pedal_control_.autonomous_brakemotor_voltage );
    can_msg2.data[5] = can_msg2.data[6] = can_msg2.data[7] = 0;

    ros2can_publisher_->publish(can_msg2);
        
    can_msgs::msg::Frame can_msg3;
    can_msg3.id = 0x0000701;
    can_msg3.is_extended = true;
    can_msg3.dlc = 8;

    can_msg3.data[0] = (autonomous_steering_mot_control_.autonomous_steeringmot_pwm ) ;
    can_msg3.data[1] = (autonomous_steering_mot_control_.autonomous_steeringmot_en );
    can_msg3.data[2] = can_msg3.data[3] = can_msg3.data[4] = can_msg3.data[5] = can_msg3.data[6] = can_msg3.data[7] = 0;
    ros2can_publisher_->publish(can_msg3);

    can_msgs::msg::Frame can_msg4;
    can_msg4.id = 0x0000702;
    can_msg4.is_extended = true;
    can_msg4.dlc = 8;

    can_msg4.data[0] = (autonomous_hb_motor_control_.autonomous_hb_moten);
    can_msg4.data[1] = (autonomous_hb_motor_control_.autonomous_hb_motstate);
    can_msg4.data[2] = (autonomous_hb_motor_control_.autonomous_hb_motor_pwm);
    can_msg4.data[3] = can_msg4.data[4] = can_msg4.data[5] = can_msg4.data[6] = can_msg4.data[7] = 0;
    ros2can_publisher_->publish(can_msg4);
    
}

}  // namespace smart_can_stuff

// #include "rclcpp_components/register_node_macro.hpp"

// RCLCPP_COMPONENTS_REGISTER_NODE(smart_can_stuff::CanHandler)
