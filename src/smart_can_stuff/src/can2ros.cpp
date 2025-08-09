#include "smart_can_stuff/can2ros.hpp"
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <smart_can_msgs/msg/kinematicmessages.hpp>
#include <smart_can_stuff/can_id.h>

namespace smart_can_stuff
{

CanListener::CanListener(const rclcpp::NodeOptions & options,std::string dbw_dbc_file)
: Node("smart_can_stuff_node", options),dbw_dbc_file_{dbw_dbc_file}
{
    
    // subs
    sub_can_ = this->create_subscription<Frame>(
    "from_can_bus", 500, std::bind(&CanListener::recvCAN, this, std::placeholders::_1));

    // dis sensor mesajları
    m_FB_MotorDriver = this->create_publisher<smart_can_msgs::msg::Fbmotordriver>("/beemobs/FB_MotorDriver", 5);
    m_FB_OMUX_to_AUTONOMOUS = this->create_publisher<smart_can_msgs::msg::Fbomuxtoautonomous>("/beemobs/FB_OMUX_to_AUTONOMOUS", 5);
    m_FB_VehicleSpeed = this->create_publisher<smart_can_msgs::msg::Fbvehiclespeed>("/beemobs/FB_VehicleSpeed", 5);
    m_snd_RCUnit_BrakeData = this->create_publisher<smart_can_msgs::msg::Sndrcunitbrakedata>("/beemobs/snd_RCUnit_BrakeData", 5);
    m_snd_RCUnit_HandBrakeData = this->create_publisher<smart_can_msgs::msg::Sndrcunithandbrakedata>("/beemobs/snd_RCUnit_HandBrakeData", 5);
    m_snd_RCUnit_SteeringData = this->create_publisher<smart_can_msgs::msg::Sndrcunitsteeringdata>("/beemobs/snd_RCUnit_SteeringData", 5);
    m_AutonomousHeardBit = this->create_publisher<smart_can_msgs::msg::Autonomousheardbit>("/beemobs/AutonomousHeardBit", 5);
    m_FeedbackSteeringAngle = this->create_publisher<smart_can_msgs::msg::Feedbacksteeringangle>("/beemobs/FeedbackSteeringAngle", 5);
    m_Feedback_SENSOR = this->create_publisher<smart_can_msgs::msg::Feedbacksensor>("/beemobs/Feedback_SENSOR", 5);
    //pub
    pub_can_ = this->create_publisher<Frame>("to_can_bus", 20);

    dbwDbc_ = NewEagle::DbcBuilder().NewDbc(dbw_dbc_file);
    
}
        
        rclcpp::Node::SharedPtr m_node_handle;
        std::string dbw_dbc_file;
        
        bool m_debug;
        NewEagle::Dbc dbwDbc_;


        bool readParameters()
        {
            if (dbw_dbc_file.empty())
            {
                std::cout << "Dbc file is empty!" << std::endl;
                return false;
            }
            return true;
        }
        CanListener::~CanListener()
        {
        }

        void CanListener::recvCAN(const Frame::SharedPtr msg)
        {
            if (m_debug)
            {
                std::cout << "Callback Canlistener" << std::endl;
            }

            switch (msg->id)
            {
            // feedback
            case ID_FB_MotorDriver:
            {
                if (m_debug)
                {
                    std::cout << "ID_FB_MotorDriver : " << ID_FB_MotorDriver << std::endl;
                }

                NewEagle::DbcMessage * message = dbwDbc_.GetMessageById(ID_FB_MotorDriver);

                if (msg->dlc >= message->GetDlc())// if data length less than the dlc in dbc, not recognize the message
                {
                    message->SetFrame(msg);

                    uint8_t GEAR_STATUS_FROM_MOTOR = message->GetSignal("GEAR_STATUS_FROM_MOTOR")->GetResult();
                    uint16_t PlusTripDistance = message->GetSignal("PlusTripDistance")->GetResult();
                    uint16_t VehicleRPM = message->GetSignal("VehicleRPM")->GetResult();

                    if (m_debug)
                    {
                        std::cout << "VehicleRPM : " << VehicleRPM << std::endl;
                    }
                    
                    smart_can_msgs::msg::Fbmotordriver motordriver;

                    motordriver.gear_status_from_motor = GEAR_STATUS_FROM_MOTOR;
                    motordriver.plustripdistance = PlusTripDistance;
                    motordriver.vehiclerpm = VehicleRPM;

                    m_FB_MotorDriver->publish(motordriver);
                    if (m_debug)
                    {
                        std::cout<<"motordriver Message is published successfully"<<std::endl;
                    }
                }
            }
            break;

            case ID_FB_VehicleSpeed:
      {
        if(m_debug)
          std::cout << "ID_FB_VehicleSpeed : " << ID_FB_VehicleSpeed << std::endl;

        NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_FB_VehicleSpeed);

        if (msg->dlc >= message->GetDlc()) // if data length less than the dlc in dbc, not recognize the message
        {
          message->SetFrame(msg);

          uint8_t FB_VehicleSpeed_KMh = message->GetSignal("FB_VehicleSpeed_KMh")->GetResult();
          uint8_t FB_ReelVehicleSpeed_KMh = message->GetSignal("FB_ReelVehicleSpeed_KMh")->GetResult();
          uint8_t FB_ReelVehicleSpeed_Ms = message->GetSignal("FB_ReelVehicleSpeed_Ms")->GetResult();

          //for debug
          if(m_debug)
          {
            std::cout << "FB_VehicleSpeed_KMh : " << FB_VehicleSpeed_KMh << std::endl;
          }
        
          // message
          smart_can_msgs::msg::Fbvehiclespeed  vehiclespeed;


          vehiclespeed.fb_reelvehiclespeed_kmh = FB_ReelVehicleSpeed_KMh;
          vehiclespeed.fb_reelvehiclespeed_ms = FB_ReelVehicleSpeed_Ms;
          vehiclespeed.fb_vehiclespeed_kmh = FB_VehicleSpeed_KMh;

          
          // publish
          m_FB_VehicleSpeed->publish(vehiclespeed);
          if (m_debug)
            std::cout<<"vehiclespeed Message is published successfully"<<std::endl;
        }
      }
      break;

      case ID_FB_OMUX_to_AUTONOMOUS:
      {
        if(m_debug)
          std::cout << "ID_FB_OMUX_to_AUTONOMOUS : " << ID_FB_OMUX_to_AUTONOMOUS << std::endl;

        NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_FB_OMUX_to_AUTONOMOUS);

        if (msg->dlc >= message->GetDlc()) // if data length less than the dlc in dbc, not recognize the message
        {
          message->SetFrame(msg);

          uint8_t FB_EMERGENCY = message->GetSignal("FB_EMERGENCY")->GetResult();
          uint8_t FB_ReverseLight = message->GetSignal("FB_ReverseLight")->GetResult();
          uint8_t FB_RightSignal = message->GetSignal("FB_RightSignal")->GetResult();
          uint8_t FB_WindowResistance = message->GetSignal("FB_WindowResistance")->GetResult();
          uint8_t FB_LeftSignal = message->GetSignal("FB_LeftSignal")->GetResult();
          uint8_t FB_InteriorLight = message->GetSignal("FB_InteriorLight")->GetResult();
          uint8_t FB_DRL = message->GetSignal("FB_DRL")->GetResult();
          uint8_t FB_DoorKeyStatus = message->GetSignal("FB_DoorKeyStatus")->GetResult();
          uint8_t FB_BrakeLight = message->GetSignal("FB_BrakeLight")->GetResult();
          uint8_t FB_BatteryVoltage = message->GetSignal("FB_BatteryVoltage")->GetResult();
          uint8_t FB_ChargeInput = message->GetSignal("FB_ChargeInput")->GetResult();
          uint8_t FB_HighBeam = message->GetSignal("FB_HighBeam")->GetResult();
          uint8_t FB_LowBeam = message->GetSignal("FB_LowBeam")->GetResult();
          uint8_t FB_IGNITION = message->GetSignal("FB_IGNITION")->GetResult();
          uint8_t FB_HazardousLight = message->GetSignal("FB_HazardousLight")->GetResult();
          uint8_t FB_VehicleStatus = message->GetSignal("FB_VehicleStatus")->GetResult();
          uint8_t FB_LeftDoorStatus = message->GetSignal("FB_LeftDoorStatus")->GetResult();
          uint8_t FB_RightDoorStatus = message->GetSignal("FB_RightDoorStatus")->GetResult();
          uint8_t FB_BatterySOC = message->GetSignal("FB_BatterySOC")->GetResult();
          uint8_t FB_ErrorPowerTrain = message->GetSignal("FB_ErrorPowerTrain")->GetResult();
          uint8_t FB_ErrorBattery = message->GetSignal("FB_ErrorBattery")->GetResult();
          uint8_t FB_BrakePedal_Voltage_EN = message->GetSignal("FB_BrakePedal_Voltage_EN")->GetResult();
          

          //for debug
          if(m_debug)
          {
            std::cout << "FB_IGNITION : " << FB_IGNITION << std::endl;
          }
        
          // message
          smart_can_msgs::msg::Fbomuxtoautonomous  omux_to_auto;


          omux_to_auto.fb_emergency = FB_EMERGENCY;
          omux_to_auto.fb_reverselight = FB_ReverseLight;
          omux_to_auto.fb_rightsignal = FB_RightSignal;
          omux_to_auto.fb_windowresistance = FB_WindowResistance;
          omux_to_auto.fb_leftsignal = FB_LeftSignal;
          omux_to_auto.fb_interiorlight = FB_InteriorLight;
          omux_to_auto.fb_drl = FB_DRL;
          omux_to_auto.fb_doorkeystatus = FB_DoorKeyStatus;
          omux_to_auto.fb_brakelight = FB_BrakeLight;
          omux_to_auto.fb_batteryvoltage = FB_BatteryVoltage;
          omux_to_auto.fb_chargeinput = FB_ChargeInput;
          omux_to_auto.fb_highbeam = FB_HighBeam;
          omux_to_auto.fb_lowbeam = FB_LowBeam;
          omux_to_auto.fb_ignition = FB_IGNITION;
          omux_to_auto.fb_hazardouslight = FB_HazardousLight;
          omux_to_auto.fb_vehiclestatus = FB_VehicleStatus;
          omux_to_auto.fb_leftdoorstatus = FB_LeftDoorStatus;
          omux_to_auto.fb_rightdoorstatus = FB_RightDoorStatus;
          omux_to_auto.fb_batterysoc = FB_BatterySOC;
          omux_to_auto.fb_errorpowertrain = FB_ErrorPowerTrain;
          omux_to_auto.fb_errorbattery = FB_ErrorBattery;
          omux_to_auto.fb_brakepedal_voltage_en = FB_BrakePedal_Voltage_EN;


          
          // publish
          m_FB_OMUX_to_AUTONOMOUS->publish(omux_to_auto);
          if (m_debug){
            std::cout<<"omux_to_auto Message is published successfully"<<std::endl;
          }
        }
      }
      break;

      case ID_snd_RCUnit_SteeringData:
      {
        if(m_debug)
          std::cout << "ID_snd_RCUnit_SteeringData : " << ID_snd_RCUnit_SteeringData << std::endl;

        NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_snd_RCUnit_SteeringData);

        if (msg->dlc >= message->GetDlc()) // if data length less than the dlc in dbc, not recognize the message
        {
          message->SetFrame(msg);

          std::cout << "Steeringdata" << std::endl;


          uint8_t RC_Steering_RightLimit = message->GetSignal("RC_Steering_RightLimit")->GetResult();
          uint8_t RC_Steering_LeftLimit = message->GetSignal("RC_Steering_LeftLimit")->GetResult();
          uint16_t RC_SteeringPWM = message->GetSignal("RC_SteeringPWM")->GetResult();
          uint8_t RC_SteeringDirection = message->GetSignal("RC_SteeringDirection")->GetResult();

          //for debug
          if(m_debug)
          {
            std::cout << "RC_SteeringPWM : " << RC_SteeringPWM << std::endl;
          }
        
          // message
          smart_can_msgs::msg::Sndrcunitsteeringdata  steeringdata;

          steeringdata.rc_steering_rightlimit = RC_Steering_RightLimit;
          steeringdata.rc_steering_leftlimit = RC_Steering_LeftLimit;
          steeringdata.rc_steeringpwm = RC_SteeringPWM;
          steeringdata.rc_steeringdirection = RC_SteeringDirection; 


          // publish
          m_snd_RCUnit_SteeringData->publish(steeringdata);
          if (m_debug)
            std::cout<<"steeringdata Message is published successfully"<<std::endl;
        }
      }
      break;

      case ID_snd_RCUnit_BrakeData:
      {
        if(m_debug)
          std::cout << "ID_snd_RCUnit_BrakeData : " << ID_snd_RCUnit_BrakeData << std::endl;

        NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_snd_RCUnit_BrakeData);

        if (msg->dlc >= message->GetDlc()) // if data length less than the dlc in dbc, not recognize the message
        {
          message->SetFrame(msg);

          uint16_t RC_BrakePedal_Speed = message->GetSignal("RC_BrakePedal_Speed")->GetResult();
          uint16_t RC_BrakePedal_Acc = message->GetSignal("RC_BrakePedal_Acc")->GetResult();
          uint8_t RC_BrakePedal_Pos = message->GetSignal("RC_BrakePedal_Pos")->GetResult(); 

          //for debug
          if(m_debug)
          {
            std::cout << "RC_BrakePedal_Pos : " << RC_BrakePedal_Pos << std::endl;
          }
        
          // message
          smart_can_msgs::msg::Sndrcunitbrakedata brakedata;

          brakedata.rc_brakepedal_acc = RC_BrakePedal_Acc;
          brakedata.rc_brakepedal_speed = RC_BrakePedal_Speed;
          brakedata.rc_brakepedal_pos = RC_BrakePedal_Pos;


          
          // publish
          m_snd_RCUnit_BrakeData->publish(brakedata);
          if (m_debug)
            std::cout<<"brakedata Message is published successfully"<<std::endl;
        }
      }
      break;

      case ID_snd_RCUnit_HandBrakeData:
      {
        if(m_debug)
          std::cout << "ID_snd_RCUnit_HandBrakeData : " << ID_snd_RCUnit_HandBrakeData << std::endl;

        NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_snd_RCUnit_HandBrakeData);

        if (msg->dlc >= message->GetDlc()) // if data length less than the dlc in dbc, not recognize the message
        {
          message->SetFrame(msg);

          uint16_t RC_HB_PwmValue = message->GetSignal("RC_HB_PwmValue")->GetResult();
          uint8_t RC_HandBrake_PRESS = message->GetSignal("RC_HandBrake_PRESS")->GetResult();
          uint8_t RC_HandBrake_FREE = message->GetSignal("RC_HandBrake_FREE")->GetResult();
          uint8_t RC_HandBrakeData = message->GetSignal("RC_HandBrakeData")->GetResult();

          //for debug
          if(m_debug)
          {
            std::cout << "RC_HandBrakeData : " << RC_HandBrakeData << std::endl;
          }
        
          // message
          smart_can_msgs::msg::Sndrcunithandbrakedata handbrakedata;

          handbrakedata.rc_hb_pwmvalue = RC_HandBrake_FREE;
          handbrakedata.rc_handbrake_press = RC_HandBrake_PRESS;
          handbrakedata.rc_handbrake_free = RC_HandBrake_FREE;
          handbrakedata.rc_handbrakedata = RC_HandBrakeData;


          
          // publish
          m_snd_RCUnit_HandBrakeData->publish(handbrakedata);
          if (m_debug)
            std::cout<<"handbrakedata Message is published successfully"<<std::endl;
        }
      }
      break;

      case ID_AutonomousHeardBit:
      {
        if(m_debug)
          std::cout << "ID_AutonomousHeardBit : " << ID_AutonomousHeardBit << std::endl;

        NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_AutonomousHeardBit);

        if (msg->dlc >= message->GetDlc()) // if data length less than the dlc in dbc, not recognize the message
        {
          message->SetFrame(msg);

          uint8_t AutonomousManuelSelect = message->GetSignal("AutonomousManuelSelect")->GetResult();

          //for debug
          if(m_debug)
          {
            std::cout << "AutonomousManuelSelect : " << AutonomousManuelSelect << std::endl;
          }
        
          // message
          smart_can_msgs::msg::Autonomousheardbit autonomousHeard;

          autonomousHeard.autonomousmanuelselect = AutonomousManuelSelect;

          // publish
          m_AutonomousHeardBit->publish(autonomousHeard);
          if (m_debug)
            std::cout<<"autonomousHeardbit Message is published successfully"<<std::endl;
        }
      }
      break;

      case ID_FeedbackSteeringAngle:
      {
        if(m_debug)
          std::cout << "ID_FeedbackSteeringAngle : " << ID_FeedbackSteeringAngle << std::endl;

        NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_FeedbackSteeringAngle);

        if (msg->dlc >= message->GetDlc()) // if data length less than the dlc in dbc, not recognize the message
        {
          message->SetFrame(msg);

          int8_t FeedBackSteeringAngle = message->GetSignal("FeedBackSteeringAngle")->GetResult();
          int8_t FeedBackBrakepedalAngle = message->GetSignal("FeedBackBrakepedalAngle")->GetResult();

          //for debug
          if(m_debug)
          {
            std::cout << "FeedBackSteeringAngle : " << FeedBackSteeringAngle << std::endl;
          }
        
          // message
          smart_can_msgs::msg::Feedbacksteeringangle feedbacksteeringangle_;

          feedbacksteeringangle_.feedbacksteeringangle = FeedBackSteeringAngle;
          feedbacksteeringangle_.feedbackbrakepedalangle = FeedBackBrakepedalAngle;
          
          // publish
          m_FeedbackSteeringAngle->publish(feedbacksteeringangle_);
          if (m_debug)
            std::cout<<"feedbacksteeringangle Message is published successfully"<<std::endl;
        }
      }
      break;

      case ID_Feedback_SENSOR:
      {
        if(m_debug)
          std::cout << "ID_Feedback_SENSOR : " << ID_Feedback_SENSOR << std::endl;

        NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_Feedback_SENSOR);

        if (msg->dlc >= message->GetDlc()) // if data length less than the dlc in dbc, not recognize the message
        {
          message->SetFrame(msg);

          uint8_t SteeringAngleSensorHamData = message->GetSignal("SteeringAngleSensorHamData")->GetResult();
          uint8_t BrakePedalSensorHamData = message->GetSignal("BrakePedalSensorHamData")->GetResult();
          uint8_t HandBrakeSensor = message->GetSignal("HandBrakeSensor")->GetResult();
          uint8_t HandBrakeSensor_HamData = message->GetSignal("HandBrakeSensor_HamData")->GetResult();
          uint8_t indir = message->GetSignal("indir")->GetResult();
          uint8_t kaldir = message->GetSignal("kaldir")->GetResult();
          uint8_t ButonIndir = message->GetSignal("ButonIndir")->GetResult();
          uint8_t ButonKaldir = message->GetSignal("ButonKaldir")->GetResult();

          //for debug
          if(m_debug)
          {
            std::cout << "SteeringAngleSensorHamData : " << SteeringAngleSensorHamData << std::endl;
          }
        
          // message
          smart_can_msgs::msg::Feedbacksensor feedback_sENSOR;

          feedback_sENSOR.steeringanglesensorhamdata = SteeringAngleSensorHamData;
          feedback_sENSOR.brakepedalsensorhamdata = BrakePedalSensorHamData;
          feedback_sENSOR.handbrakesensor = HandBrakeSensor;
          feedback_sENSOR.handbrakesensor_hamdata = HandBrakeSensor_HamData;
          feedback_sENSOR.indir = indir;
          feedback_sENSOR.kaldir = kaldir;
          feedback_sENSOR.butonindir = ButonIndir;
          feedback_sENSOR.butonkaldir = ButonKaldir;
          
          
          // publish
          m_Feedback_SENSOR->publish(feedback_sENSOR);
          if (m_debug)
            std::cout<<"feedback_sENSOR Message is published successfully"<<std::endl;
        }
      }
      break;
            // Diğer durumlar burada işlenir...

            default:
                if (m_debug)
                    {

                    }
                break;
            }

            if (m_debug)
                {

                }
        }
    

} // namespace smart_can_stuff