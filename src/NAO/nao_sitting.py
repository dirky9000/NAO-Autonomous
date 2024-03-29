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

names.append("HeadPitch")
times.append([0.64])
keys.append([[-0.019984, [3, -0.226667, 0], [3, 0, 0]]])

names.append("HeadYaw")
times.append([0.64])
keys.append([[-0.07214, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LAnklePitch")
times.append([0.64])
keys.append([[-0.144238, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LAnkleRoll")
times.append([0.64])
keys.append([[0.0307219, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LElbowRoll")
times.append([0.64])
keys.append([[-0.685656, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LElbowYaw")
times.append([0.64])
keys.append([[-1.3607, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LHand")
times.append([0.64])
keys.append([[0.268, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LHipPitch")
times.append([0.64])
keys.append([[-0.720938, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LHipRoll")
times.append([0.64])
keys.append([[-0.0659201, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LHipYawPitch")
times.append([0.64])
keys.append([[-0.210116, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LKneePitch")
times.append([0.64])
keys.append([[1.09677, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LShoulderPitch")
times.append([0.64])
keys.append([[1.00626, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LShoulderRoll")
times.append([0.64])
keys.append([[0.168698, [3, -0.226667, 0], [3, 0, 0]]])

names.append("LWristYaw")
times.append([0.64])
keys.append([[-1.85158, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RAnklePitch")
times.append([0.64])
keys.append([[-0.138018, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RAnkleRoll")
times.append([0.64])
keys.append([[-0.076658, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RElbowRoll")
times.append([0.64])
keys.append([[0.93885, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RElbowYaw")
times.append([0.64])
keys.append([[1.21642, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RHand")
times.append([0.64])
keys.append([[0.1856, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RHipPitch")
times.append([0.64])
keys.append([[-0.773178, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RHipRoll")
times.append([0.64])
keys.append([[0.0813439, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RHipYawPitch")
times.append([0.64])
keys.append([[-0.210116, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RKneePitch")
times.append([0.64])
keys.append([[1.12293, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RShoulderPitch")
times.append([0.64])
keys.append([[1.11066, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RShoulderRoll")
times.append([0.64])
keys.append([[-0.11049, [3, -0.226667, 0], [3, 0, 0]]])

names.append("RWristYaw")
times.append([0.64])
keys.append([[1.6214, [3, -0.226667, 0], [3, 0, 0]]])

try:
  motion = ALProxy("ALMotion", NAO_IP, PORT)
  motion.angleInterpolationBezier(names, times, keys)
except BaseException as err:
  print(err)
