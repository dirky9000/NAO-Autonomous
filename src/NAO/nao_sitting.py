# this is when the NAO is sitting down in the chair and ready to press buttons
#######################################################################################
import os
import sys
import time
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')
import naoqi
from naoqi import ALProxy
from naoqi import ALModule
from naoqi import ALBroker

# NAO_IP = "192.168.1.126"  # Replace here with your NaoQi's IP address. (This is bender)
# NAO_IP = "192.168.1.107"  # Replace here with your NaoQi's IP address. (This is peanut)
NAO_IP = "192.168.1.135"  # Replace here with your NaoQi's IP address. (This is petrie)
PC_IP = "192.168.1.149"   # Replace here with your computer IP address
PORT = 9559

names = list()
times = list()
keys = list()

########################### keep everything above this line ###########################  

# default sitting down position
names.append("HeadPitch")
times.append([0.44])
keys.append([[-0.092082, [3, -0.146667, 0], [3, 0, 0]]])

names.append("HeadYaw")
times.append([0.44])
keys.append([[0.0413761, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LAnklePitch")
times.append([0.44])
keys.append([[-0.188724, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LAnkleRoll")
times.append([0.44])
keys.append([[0.124296, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LElbowRoll")
times.append([0.44])
keys.append([[-0.481634, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LElbowYaw")
times.append([0.44])
keys.append([[-1.93135, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LHand")
times.append([0.44])
keys.append([[0.0508, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LHipPitch")
times.append([0.44])
keys.append([[-0.74855, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LHipRoll")
times.append([0.44])
keys.append([[-0.108872, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LHipYawPitch")
times.append([0.44])
keys.append([[-0.243864, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LKneePitch")
times.append([0.44])
keys.append([[1.16426, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LShoulderPitch")
times.append([0.44])
keys.append([[0.43408, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LShoulderRoll")
times.append([0.44])
keys.append([[-0.0767419, [3, -0.146667, 0], [3, 0, 0]]])

names.append("LWristYaw")
times.append([0.44])
keys.append([[-1.17355, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RAnklePitch")
times.append([0.44])
keys.append([[-0.223922, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RAnkleRoll")
times.append([0.44])
keys.append([[-0.075124, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RElbowRoll")
times.append([0.44])
keys.append([[0.521602, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RElbowYaw")
times.append([0.44])
keys.append([[1.38669, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RHand")
times.append([0.44])
keys.append([[0.0412, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RHipPitch")
times.append([0.44])
keys.append([[-0.759372, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RHipRoll")
times.append([0.44])
keys.append([[0.0552659, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RHipYawPitch")
times.append([0.44])
keys.append([[-0.243864, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RKneePitch")
times.append([0.44])
keys.append([[1.20577, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RShoulderPitch")
times.append([0.44])
keys.append([[0.552282, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RShoulderRoll")
times.append([0.44])
keys.append([[-0.066004, [3, -0.146667, 0], [3, 0, 0]]])

names.append("RWristYaw")
times.append([0.44])
keys.append([[1.77173, [3, -0.146667, 0], [3, 0, 0]]])

# you need to put this everytime at end of a motion
try:
  motion = ALProxy("ALMotion", NAO_IP, PORT)
  motion.angleInterpolationBezier(names, times, keys)
except BaseException as err:
  print(err)