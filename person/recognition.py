#!/usr/bin/env python
import rospy
from std_msgs.msgs import Int8
from actionlib_msgs import GoalID

class RecognitionNode(object):
    def __init__(self):
        rospy.init_node('recognition_node')
        rospy.Subscriber("/darknet_ros/found_object", Int8, self.person_callback, queue_size=10)
        self.stop_pub = rospy.Publisher("/move_base/cancel", GoalID, queue_size=10)
    def person_callback(self, msg):
        if msg.data == 2:
            stop_msg = GoalID()
            stop_msg.data = ''
            self.stop_pub.publish(stop_msg)

if __name__ == "__main__":
    recognition_node = RecognitionNode()
    rospy.spin()

