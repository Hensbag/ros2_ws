#pragma once
#include <stdint.h>

namespace smart_can_stuff
{

enum {
  

  ID_snd_RCUnitToOmux           = 0x0000800,
  ID_RC_THRT_DATA               = 0xCF00300,
  ID_AUTONOMOUS_BrakePedalControl = 0x0000700,
  ID_AUTONOMOUS_SteeringMot_Control = 0x0000701,
  ID_AUTONOMOUS_HB_MotorControl = 0x0000702,
  ID_FB_MotorDriver             = 0x18316296,
  ID_FB_VehicleSpeed            = 0x18326239,
  ID_FB_OMUX_to_AUTONOMOUS      = 0x0000901,
  ID_snd_RCUnit_SteeringData    = 0x0000801,
  ID_snd_RCUnit_BrakeData       = 0x0000802,
  ID_snd_RCUnit_HandBrakeData   = 0x0000803,
  ID_AutonomousHeardBit         = 0x0000799,
  ID_FeedbackSteeringAngle      = 0x0000903,
  ID_Feedback_SENSOR            = 0x0000902,
};


} //raptor_dbw_can tılt_ıd=50 boom_ıd=90

