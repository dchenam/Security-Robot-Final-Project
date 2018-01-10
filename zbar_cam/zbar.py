#!/usr/bin/env python
import os
import rospy
import Image
import zbar
import cv2
import numpy as np
from std_msgs.msg import String

p=os.popen('zbarcam','r')

if __name__=="__main__":
    rospy.init_node('zbar_cam')

       
    while True:
        code = p.readline()
	pub = rospy.Publisher('/barcode', String, queue_size = 1)
        pub.publish("code")
        print 'Got barcode:', code
        
