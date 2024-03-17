#!/usr/bin/env python3

import rospy
#we are gonna send Int32 message
from std_msgs.msg import Int32
nodename='messagepublisher'
topicnameLeftMotor='left_motor_velocity'
topicnameRightMotor='right_motor_velocity'

rospy.init_node(nodename,anonymous=True)

publisherLeftMotor=rospy.Publisher(topicnameLeftMotor, Int32, queue_size=10)
publisherRightMotor=rospy.Publisher(topicnameRightMotor, Int32, queue_size=10)
ratePublisher=rospy.Rate(1)

leftMotor=0
rightMotor=0

while not rospy.is_shutdown():
    rospy.loginfo(leftMotor)
    rospy.loginfo(rightMotor)

    leftMotor=int(input("Enter the left motor velocity :"))

    rightMotor=int(input("Enter the right motor velocity :"))

    publisherLeftMotor.publish(leftMotor)
    publisherRightMotor.publish(rightMotor)

    ratePublisher.sleep()
