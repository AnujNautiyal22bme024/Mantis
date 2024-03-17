#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int32

nodename='messagesubscriber'

topicnameLeftEncoder='left_encoder_pulses'
topicnameRightEncoder='right_encoder_pulses'

def callBackFunctionLeftEncoder(message1):
    print("Left encoder pulses: %s" %message1.data)

def callBackFunctionRightEncoder(message2):
    print("Right encoder pulses: %s" %message2.data)

rospy.init_node(nodename, anonymous=True)
rospy.Subscriber(topicnameLeftEncoder,Int32,callBackFunctionLeftEncoder)
rospy.Subscriber(topicnameRightEncoder,Int32,callBackFunctionRightEncoder)

rospy.spin 