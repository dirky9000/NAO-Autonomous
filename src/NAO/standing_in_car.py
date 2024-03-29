# This is the code that the NAO will be in default for driving, it is standing in front 
# of the chair with its arms ready to hit buttons

import os
import sys
import time
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')
import naoqi
from naoqi import ALProxy

# NAO_IP = "192.168.1.126"  # Replace here with your NaoQi's IP address. (This is bender)
# NAO_IP = "192.168.1.107"  # Replace here with your NaoQi's IP address. (This is peanut)
NAO_IP = "192.168.1.135"  # Replace here with your NaoQi's IP address. (This is petrie)
PORT = 9559

names = list()
times = list()
keys = list()

names.append("LElbowRoll")
times.append([0.8])
keys.append([[-0.819114, [3, -0.266667, 0], [3, 0, 0]]])

names.append("LElbowYaw")
times.append([0.8])
keys.append([[-1.42359, [3, -0.266667, 0], [3, 0, 0]]])

names.append("LShoulderPitch")
times.append([0.8])
keys.append([[1.05535, [3, -0.266667, 0], [3, 0, 0]]])

names.append("LShoulderRoll")
times.append([0.8])
keys.append([[0.156426, [3, -0.266667, 0], [3, 0, 0]]])

names.append("LWristYaw")
times.append([0.8])
keys.append([[-0.196394, [3, -0.266667, 0], [3, 0, 0]]])

names.append("RElbowRoll")
times.append([0.8])
keys.append([[0.888228, [3, -0.266667, 0], [3, 0, 0]]])

names.append("RElbowYaw")
times.append([0.8])
keys.append([[1.65514, [3, -0.266667, 0], [3, 0, 0]]])

names.append("RHand")
times.append([0.8])
keys.append([[0.0108, [3, -0.266667, 0], [3, 0, 0]]])

names.append("RShoulderPitch")
times.append([0.8])
keys.append([[1.12753, [3, -0.266667, 0], [3, 0, 0]]])

names.append("RShoulderRoll")
times.append([0.8])
keys.append([[0.030638, [3, -0.266667, 0], [3, 0, 0]]])

names.append("RWristYaw")
times.append([0.8])
keys.append([[-0.047596, [3, -0.266667, 0], [3, 0, 0]]])

try:
  motion = ALProxy("ALMotion", NAO_IP, PORT)
  motion.angleInterpolationBezier(names, times, keys)
except BaseException as err:
  print(err)