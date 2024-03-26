import os
import sys
import time
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')
import naoqi
from naoqi import ALProxy

NAO_IP = "192.168.1.107"  # Replace here with your NaoQi's IP address.
PORT = 9559

# Create a proxy to ALMotion.
motion = ALProxy("ALMotion", NAO_IP, PORT)

# Get the current joint angles.
currentJointAngles = motion.getAngles("Body", True)

# Wake up the robot.
motion.wakeUp()

# Restore the joint angles.
motion.setAngles("Body", currentJointAngles, 0.1)

# Choregraphe bezier export in Python.
names = list()
times = list()
keys = list()

names.append("HeadPitch")
times.append([0.16])
keys.append([[0.116542, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("HeadYaw")
times.append([0.16])
keys.append([[0.0122299, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LAnklePitch")
times.append([0.16])
keys.append([[-0.131966, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LAnkleRoll")
times.append([0.16])
keys.append([[0.0598679, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LElbowRoll")
times.append([0.16])
keys.append([[-1.02314, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LElbowYaw")
times.append([0.16])
keys.append([[-1.56779, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LHand")
times.append([0.16])
keys.append([[0.2604, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LHipPitch")
times.append([0.16])
keys.append([[-0.751618, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LHipRoll")
times.append([0.16])
keys.append([[-0.0873961, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LHipYawPitch")
times.append([0.16])
keys.append([[-0.22699, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LKneePitch")
times.append([0.16])
keys.append([[1.0983, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LShoulderPitch")
times.append([0.16])
keys.append([[1.22716, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LShoulderRoll")
times.append([0.16])
keys.append([[0.079726, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("LWristYaw")
times.append([0.16])
keys.append([[-1.53251, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RAnklePitch")
times.append([0.16])
keys.append([[-0.162562, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RAnkleRoll")
times.append([0.16])
keys.append([[-0.0843279, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RElbowRoll")
times.append([0.16])
keys.append([[0.83147, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RElbowYaw")
times.append([0.16])
keys.append([[1.17193, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RHand")
times.append([0.16])
keys.append([[0.016, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RHipPitch")
times.append([0.16])
keys.append([[-0.796188, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RHipRoll")
times.append([0.16])
keys.append([[0.0844119, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RHipYawPitch")
times.append([0.16])
keys.append([[-0.22699, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RKneePitch")
times.append([0.16])
keys.append([[1.1398, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RShoulderPitch")
times.append([0.16])
keys.append([[1.0447, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RShoulderRoll")
times.append([0.16])
keys.append([[0.367591, [3, -0.0666667, 0], [3, 0, 0]]])

names.append("RWristYaw")
times.append([0.16])
keys.append([[1.84076, [3, -0.0666667, 0], [3, 0, 0]]])

try:
  motion = ALProxy("ALMotion", NAO_IP, PORT)
  motion.angleInterpolationBezier(names, times, keys)
except BaseException as err:
  print(err)

