#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from std_msgs.msg import Int8
import socket, sys, threading, subprocess
import speech_recognition as sr

class GSpeech(object):
    """Speech Recogniser using Google Speech API"""
    def __init__(self):
        rospy.init_node('gspeech')
        # configure ROS settings
        self.pub_speech = rospy.Publisher('~speech', String, queue_size=10)
        self.r = sr.Recognizer()
        with sr.Microphone() as source:
            print("Please wait. Calibrating microphone...")
            # listen for 5 seconds and create the ambient noise energy level
            self.r.adjust_for_ambient_noise(source, duration=5)

    def do_recognition(self):
        """Do speech recognition"""
        while self.started:
            try:
                with sr.Microphone() as source:
                    print("Say something!")
                    self.audio = self.r.listen(source)
                message = self.r.recognize_google_cloud(self.audio)
                self.pub_speech.publish(message)
                print("Google thinks you said '" + message + "'")
                # print(self.r.recognize_wit(self.audio, key='IHS2FMOUQCRHT6TG64LPG3U4DPGRQQQB', show_all=True))
            except sr.UnknownValueError:
                print("Google Speech Recognition could not understand audio")
            except sr.RequestError as e:
                print("Could not request results from Google Speech Recognition service; {0}".format(e))

def is_connected():
    """Check if connected to Internet"""
    try:
    # check if DNS can resolve hostname
        remote_host = socket.gethostbyname("www.google.com")
    # check if host is reachable
        s = socket.create_connection(address=(remote_host, 80), timeout=5)
        return True
    except:
        pass
    return False

def main():
    if not is_connected():
        sys.exit("No Internet connection available")
    speech = GSpeech()
    while not rospy.is_shutdown():
        speech.do_recognition()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
    except KeyboardInterrupt:
        sys.exit(0)
