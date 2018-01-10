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
        self.stop_pub = rospy.Publisher("/move_base/cancel", GoalID, queue_size=10)
        self.cmd_pub = rospy.Publisher("/command", String, queue_size=10)
        uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(uuid)
        self.launch = roslaunch.parent.ROSLaunchParent(uuid, ["/home/dchenam/catkin_ws/launch/tracking.launch"])
        self.launch.start()

    def person_callback(self, msg):
        if msg.boundingBoxes[0].Class == "person":
            stop_msg = GoalID()
            stop_msg.id = ''
            voice_stop = String()
            voice_stop.data = 'Please Provide Your Identification Card for Checking'
            self.cmd_pub.publish(voice_stop)
            self.stop_pub.publish(stop_msg)
            self.launch.shutdown()
            p=os.popen('zbarcam','r')
            code = p.readline()
            pub = rospy.Publisher('/barcode', String, queue_size = 1)
            pub.publish(code)
            print 'Got barcode:', code

if __name__ == "__main__":
    recognition_node = RecognitionNode()
    rospy.spin()

