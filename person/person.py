#!/usr/bin/env python
import rospy
import os
from darknet_ros_msgs.msg import BoundingBoxes
from std_msgs.msg import Int8, String
from actionlib_msgs.msg import GoalID
import roslaunch

class RecognitionNode(object):
    def __init__(self):
        rospy.init_node('recognition_node')
        rospy.Subscriber("/darknet_ros/bounding_boxes", BoundingBoxes, self.person_callback, queue_size=10)
        rospy.Subscriber("/barcode", String, self.id_callback, queue_size=10)
        rospy.Subscriber("/resume", String, self.resume_callback, queue_size=10)
        self.stop_pub = rospy.Publisher("/move_base/cancel", GoalID, queue_size=10)
        self.cmd_pub = rospy.Publisher("/command", String, queue_size=1)
        uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(uuid)
        self.launch = roslaunch.parent.ROSLaunchParent(uuid, ["/home/dchenam/catkin_ws/launch/tracking.launch"])
        self.launch.start()
        self.voice = True
        self.stop = False
        self.switch = True
    #
    # def zbar_callback(self, msg):
    #     print "zbar call"
    #     if self.enabled:
    #         print "enabled"
    #         code = self.p.readline()
    #         self.bar_pub.publish(code)
    #         print 'Got barcode:', code

    def person_callback(self, msg):
        if msg.boundingBoxes[0].Class == "person":
            if self.voice:
                voice_stop = String()
                voice_stop.data = 'Please Scan You ID card on the small laptop'
                self.cmd_pub.publish(voice_stop)
            if self.switch:
                self.switch = False
                self.stop = True
            print(self.stop)

    def timer_callback(self, msg):
        stop_msg = GoalID()
        stop_msg.id = ''
        if self.stop:
            self.stop_pub.publish(stop_msg)


    def id_callback(self, msg):
        self.voice = False
        id = msg.data
        lhs, rhs = id.split(":", 1)
        print(rhs)
        voice_greeting = String()
        voice_greeting.data = "Hello" + rhs
        self.cmd_pub.publish(voice_greeting)

    def resume_callback(self, msg):
        self.stop = False


if __name__ == "__main__":
    recognition_node = RecognitionNode()
    rospy.Timer(rospy.Duration(0, 1), recognition_node.timer_callback)
    rospy.spin()
