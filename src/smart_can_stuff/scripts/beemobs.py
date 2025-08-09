#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import inputs
import time
import threading
import numpy as np
from can_msgs.msg import Frame  
from smart_can_msgs.msg import Rcunittoomux, Rcthrtdata, Autonomousbrakepedalcontrol, Autonomoushbmotorcontrol, Autonomoussteeringmotcontrol
from sensor_msgs.msg import Joy
from std_msgs.msg import Bool


class Gamepad(Node):

    def __init__(self):
        super().__init__('cmd_gamepad_node')
        
        self.emergency_stop = True
        self.speed = 0.0
        self.joy_stick_standby_value = 128

        self.boom_angle = self.joy_stick_standby_value
        self.arm_angle = self.joy_stick_standby_value
        self.bucket_angle = self.joy_stick_standby_value
        self.swing_angle = self.joy_stick_standby_value
        self.boom2_angle = self.joy_stick_standby_value
        self.left_traveller = self.joy_stick_standby_value
        self.right_traveller = self.joy_stick_standby_value

        self.number_of_control_state = 7

        self.game_pad_max_value = 32767
        
        self.abs_ry_counter = 0  # Counter for ABS_RY button
        self.abs_ry_counter_old = 0

        self.monitor_thread = threading.Thread(target=self.monitor_gamepad, args=())
        self.monitor_thread.daemon = True
        self.monitor_thread.start()

        self.pad = inputs.devices.gamepads[0]
    
        self.can_pub = self.create_publisher(Frame, '/sent_messages', 10)
        self.cmd_publisher = self.create_publisher(Joy, '/gamepad_cmd', 10)
        self.msg_unittomux = Rcunittoomux()

        #beemobs pubs
        self.steering_pub = self.create_publisher(Autonomoussteeringmotcontrol, '/beemobs/AUTONOMOUS_SteeringMot_Control', 10)
        self.unittomux_pub = self.create_publisher(Rcunittoomux, '/beemobs/rc_unittoOmux', 10)
        self.thrt_pub = self.create_publisher(Rcthrtdata, '/beemobs/RC_THRT_DATA', 10)
        self.brake_pub = self.create_publisher(Autonomousbrakepedalcontrol, '/beemobs/AUTONOMOUS_BrakePedalControl', 10)
        self.hb_pub = self.create_publisher(Autonomoushbmotorcontrol, '/beemobs/AUTONOMOUS_HB_MotorControl', 10)

    def limit_gamepad_boom2_down(self, input): 
        if 0 == int(abs(round(((float(input) / float(255))) * self.joy_stick_standby_value ))):  
            return int(self.joy_stick_standby_value)
        else:
            return int(128 - (round(((float(input) / float(255))) * self.joy_stick_standby_value - 1 )))

    def limit_gamepad_boom2_up(self, input):
        if 0 == int(abs(round(((float(input) / float(255))) * self.joy_stick_standby_value ))):  
            return int(self.joy_stick_standby_value)
        else:
            return int(128 + (round(((float(input) / float(255))) * self.joy_stick_standby_value - 1 )))

    def limit_gamepad(self, input):
        if 120 < abs(round(((float(input) / float(self.game_pad_max_value)) + 1) * self.joy_stick_standby_value - 1 )) < 134:
            return int(self.joy_stick_standby_value)
        else:
            return int(abs(round(((float(input) / float(self.game_pad_max_value)) + 1) * self.joy_stick_standby_value - 1 )))

    def control_one_state(self): 
        if self.swing_angle != self.joy_stick_standby_value and self.arm_angle != self.joy_stick_standby_value:
            if abs(self.joy_stick_standby_value - self.swing_angle) > abs(self.joy_stick_standby_value - self.arm_angle):
                self.arm_angle = self.joy_stick_standby_value
            elif abs(self.joy_stick_standby_value - self.swing_angle) < abs(self.joy_stick_standby_value - self.arm_angle):
                self.swing_angle = self.joy_stick_standby_value
        if self.boom_angle != self.joy_stick_standby_value and self.bucket_angle != self.joy_stick_standby_value:
            if abs(self.joy_stick_standby_value - self.boom_angle) > abs(self.joy_stick_standby_value - self.bucket_angle):
                self.bucket_angle = self.joy_stick_standby_value
            elif abs(self.joy_stick_standby_value - self.boom_angle) < abs(self.joy_stick_standby_value - self.bucket_angle):
                self.boom_angle = self.joy_stick_standby_value

    def send_can_message(self, can_id, can_data):
        can_msg = Frame()
        can_msg.id = can_id
        can_msg.is_rtr = False
        can_msg.is_extended = True
        can_msg.is_error = False
        can_msg.dlc = 8
        can_msg.data = can_data

        self.can_pub.publish(can_msg)

    def monitor_gamepad(self):
        while True:
            try:
                events = inputs.get_gamepad()

                for event in events:
                    self.get_logger().info(f'{event.ev_type}, {event.code}, {event.state}')
                    if event.code == 'ABS_HAT0Y' and event.state == -1:
                        self.msg_unittomux.autonomous_emergency = 0
                        self.msg_unittomux.rc_windowresintance = 0
                        self.msg_unittomux.rc_interiorlight = 0
                        self.msg_unittomux.rc_reverselight = 0
                        self.msg_unittomux.rc_drl = 0
                        self.msg_unittomux.rc_brakelight = 0
                        self.msg_unittomux.autonomous_door_open = 0
                        self.msg_unittomux.autonomous_door_close = 0
                        self.msg_unittomux.rc_signalstatus = 0
                        self.msg_unittomux.rc_lowbeam = 0
                        self.msg_unittomux.rc_highbeam = 0
                        self.msg_unittomux.rc_selectiongear = 1
                        self.msg_unittomux.rc_ignition = 1

                    if event.code == 'ABS_HAT0Y' and event.state == 1:
                        can_id = 0x0000800
                        can_data = [3, 0, 0, 0, 0, 0, 0, 0]
                        self.send_can_message(can_id, can_data)
                        self.get_logger().info("beemobs thrt geri")

                    if event.code == 'BTN_START' and event.state:
                        self.msg_unittomux.autonomous_emergency = 0
                        self.msg_unittomux.rc_windowresintance = 0
                        self.msg_unittomux.rc_interiorlight = 0
                        self.msg_unittomux.rc_reverselight = 0
                        self.msg_unittomux.rc_drl = 0
                        self.msg_unittomux.rc_brakelight = 0
                        self.msg_unittomux.autonomous_door_open = 0
                        self.msg_unittomux.autonomous_door_close = 0
                        self.msg_unittomux.rc_signalstatus = 0
                        self.msg_unittomux.rc_lowbeam = 0
                        self.msg_unittomux.rc_highbeam = 0
                        self.msg_unittomux.rc_selectiongear = 0
                        self.msg_unittomux.rc_ignition = 1
                        self.unittomux_pub.publish(self.msg_unittomux)
                        self.get_logger().info("beemobs start")
                        #fren
                        # msg = Autonomousbrakepedalcontrol()

                        # msg.AUTONOMOUS_BrakeMotor_Voltage = 1
                        # msg.AUTONOMOUS_BrakePedalMotor_PER = 0
                        # msg.AUTONOMOUS_BrakePedalMotor_ACC = 0
                        # msg.AUTONOMOUS_BrakePedalMotor_EN = 1

                        # self.brake_pub.publish(msg)
                        #el freni
                        

                    if(event.code == 'BTN_SELECT' and event.state):
                        
                        msg_ = Rcthrtdata()
                        msg_.rc_thrt_pedal_position = 0
                        msg_.rc_thrt_pedal_press = 1
                        self.thrt_pub.publish(msg_)

                        msg = Autonomousbrakepedalcontrol()

                        msg.autonomous_brakemotor_voltage = 0
                        msg.autonomous_brakepedalmotor_per = 0
                        msg.autonomous_brakepedalmotor_acc = 0
                        msg.autonomous_brakepedalmotor_en = 0

                        self.brake_pub.publish(msg)

                        #el freni
                        # msghb = AUTONOMOUS_HB_MotorControl()

                        # msghb.AUTONOMOUS_HB_Motor_PWM = 200
                        # msghb.AUTONOMOUS_HB_MotState = 2
                        # msghb.AUTONOMOUS_HB_MotEN = 1

                        # self.hb_pub.publish(msghb)
                        # rospy.sleep(0.5)
                        # msghb.AUTONOMOUS_HB_MotEN = 0

                        # self.hb_pub.publish(msghb)

                        self.msg_unittomux = Rcunittoomux()
                        self.msg_unittomux.autonomous_emergency = 0
                        self.msg_unittomux.rc_windowresintance = 0
                        self.msg_unittomux.rc_interiorlight = 0
                        self.msg_unittomux.rc_reverselight = 0
                        self.msg_unittomux.rc_drl = 0
                        self.msg_unittomux.rc_brakelight = 0
                        self.msg_unittomux.autonomous_door_open = 0
                        self.msg_unittomux.autonomous_door_close = 0
                        self.msg_unittomux.rc_signalstatus = 0
                        self.msg_unittomux.rc_lowbeam = 0
                        self.msg_unittomux.rc_highbeam = 0
                        self.msg_unittomux.rc_selectiongear = 0
                        self.msg_unittomux.rc_ignition = 0

                        self.unittomux_pub.publish(self.msg_unittomux)
                        self.get_logger().info("beemobs stop")
                        
                    if(event.code == 'BTN_SOUTH' and event.state):
                        self.msg_unittomux.rc_selectiongear = 2
                        self.unittomux_pub.publish(self.msg_unittomux)

                        self.get_logger().info("beemobs vites geri")

                    if(event.code == 'BTN_NORTH' and event.state ==1):
                        msghb = Autonomoushbmotorcontrol()

                        msghb.autonomous_hb_motor_pwm = 200
                        msghb.autonomous_hb_motstate = 0
                        msghb.autonomous_hb_moten = 1

                        self.hb_pub.publish(msghb)

                        self.get_logger().info("el freni cek ")

                    if(event.code == 'BTN_WEST' and event.state):
                        self.msg_unittomux.rc_selectiongear = 1
                        self.unittomux_pub.publish(self.msg_unittomux)

                        self.get_logger().info("beemobs vites ileri")
                    
                    if(event.code == 'BTN_EAST' and event.state):
                        msghb = Autonomoushbmotorcontrol()

                        msghb.autonomous_hb_motor_pwm = 200
                        msghb.autonomous_hb_motstate = 1
                        msghb.autonomous_hb_moten = 1

                        self.hb_pub.publish(msghb)

                        self.get_logger().info("el freni indir ")

                    if event.code == 'ABS_X':
                        if event.state > 7500: #sag
                            self.get_logger().info("sag")
                            steering_msg = Autonomoussteeringmotcontrol()
                            steering_msg.autonomous_steeringmot_en = 1
                            steering_msg.autonomous_steeringmot_pwm = 200
                            self.steering_pub.publish(steering_msg)
                        elif event.state < -7500: # sol
                            steering_msg = Autonomoussteeringmotcontrol()
                            steering_msg.autonomous_steeringmot_en = 1
                            steering_msg.autonomous_steeringmot_pwm = 70
                            self.steering_pub.publish(steering_msg)
                        else :
                            steering_msg = Autonomoussteeringmotcontrol()
                            steering_msg.autonomous_steeringmot_en = 0
                            steering_msg.autonomous_steeringmot_pwm = 0
                            self.steering_pub.publish(steering_msg)

                    if event.code == 'ABS_RY':
                        
                        if event.state > 7000: #geri

                            self.msg_unittomux.rc_selectiongear = 0
                            self.unittomux_pub.publish(self.msg_unittomux)

                            msg = Autonomousbrakepedalcontrol()

                            msg.autonomous_brakemotor_voltage = 1
                            msg.autonomous_brakepedalmotor_per = 0
                            msg.autonomous_brakepedalmotor_acc = 10000
                            msg.autonomous_brakepedalmotor_en = 1
                            if event.state > 7100:
                                z = (100 - 30) * (event.state - 7100) / (34000 - 7100) + 30
                                msg.autonomous_brakepedalmotor_per = int(z)

                            self.brake_pub.publish(msg)
                            
                            self.get_logger().info("beemobs frene basildi")
                        if event.state < -400: # ileri

                            # msg = AUTONOMOUS_BrakePedalControl()

                            # msg.AUTONOMOUS_BrakeMotor_Voltage = 1
                            # msg.AUTONOMOUS_BrakePedalMotor_PER = 0
                            # msg.AUTONOMOUS_BrakePedalMotor_ACC = 0
                            # msg.AUTONOMOUS_BrakePedalMotor_EN = 1

                            # self.brake_pub.publish(msg)

                            msg_ = Rcthrtdata()
                            msg_.rc_thrt_pedal_position = 0
                            if event.state < -7500:
                                y = (120 - 50) * (event.state - -7500) / (-33000 - -7500) + 50
                                msg_.rc_thrt_pedal_position = int(y)

                            msg_.rc_thrt_pedal_press = 0
                            self.thrt_pub.publish(msg_)
            except Exception as e:
                self.get_logger().error(f'Exception in monitor_gamepad: {e}')
                continue

def main(args=None):
    rclpy.init(args=args)
    gamepad = Gamepad()
    gamepad.monitor_gamepad()
    # rclpy.spin(gamepad)
    # gamepad.destroy_node()
    # rclpy.shutdown()
    # time.sleep(0.05)

if __name__ == '__main__':
    main()
