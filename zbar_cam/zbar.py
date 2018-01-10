#!/usr/bin/env python
import os
import rospy
import Image
import zbar
import cv2
import numpy as np
from std_msgs.msg import String

p=os.popen('/usr/bin/zbarcam','r')

if __name__=="__main__":
    rospy.init_node('zbar_cam')
    img = np.zeros((512,512,3), np.uint8)
    
    title = "Dynamsoft Barcode Reader"
    # cv2.namedWindow(title, 1)
    cap = cv2.VideoCapture(0)
    if(False):
        pub = rospy.Publisher('/barcode', String, queue_size = 1)
        pub.publish("some string")
    while True:
        code = p.readline()
        print 'Got barcode:', code
        ret, img = cap.read()
        cv2.rectangle(img, (20, 45), (600, 430), (255,0,0), 2)
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(img,'SHOW YOUR ID',(300,430), font, 1, (200,255,155), 2, cv2.LINE_AA)
        cv2.imshow(title, img)
        key = cv2.waitKey(20)
        if key in [27, ord('Q'), ord('q')]: # exit on ESC
            break
        # img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # pil = Image.fromarray(img)
        # width, height = pil.size
        # raw = pil.tobytes()
        # wrap image data
        # image = zbar.Image(width, height, 'Y800', raw)
        # scanner = zbar.ImageScanner()
        # results = scanner.scan(image)
        # for result in results:
        #     print(result.type, result.data, result.quality, result.position)
