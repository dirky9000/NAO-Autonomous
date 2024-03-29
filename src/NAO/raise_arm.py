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
times.append([1.04])
keys.append([[-0.397264, [3, -0.36, 0], [3, 0, 0]]])

names.append("LElbowYaw")
times.append([1.04])
keys.append([[-1.18122, [3, -0.36, 0], [3, 0, 0]]])

names.append("LHand")
times.append([1.04])
keys.append([[0.2952, [3, -0.36, 0], [3, 0, 0]]])

names.append("LShoulderPitch")
times.append([0.64, 1.04])
keys.append([[0.296122, [3, -0.226667, 0], [3, 0.133333, 0]], [0.368118, [3, -0.133333, 0], [3, 0, 0]]])

names.append("LShoulderRoll")
times.append([1.04])
keys.append([[0.187106, [3, -0.36, 0], [3, 0, 0]]])

names.append("LWristYaw")
times.append([1.04])
keys.append([[0.122678, [3, -0.36, 0], [3, 0, 0]]])

try:
  motion = ALProxy("ALMotion", NAO_IP, PORT)
  motion.angleInterpolationBezier(names, times, keys)
except BaseException as err:
  print(err)
