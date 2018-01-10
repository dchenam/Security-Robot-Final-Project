#!/usr/bin/env python
import os
import rospy

p=os.popen('/usr/bin/zbarcam','r')

if __name__=="__main__":
    rospy.init_node('zbar_cam')
    while True:
        code = p.readline()
        print 'Got barcode:', code
