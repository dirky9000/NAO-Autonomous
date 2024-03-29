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

# Create a proxy to ALAutonomousLife
try:
  life_proxy = ALProxy("ALAutonomousLife", NAO_IP, PORT)
except RuntimeError as e:
  print("Error when creating ALAutonomousLife proxy:")
  exit(1)

# Create a proxy to ALMotion
try:
  motion_proxy = ALProxy("ALMotion", NAO_IP, PORT)
except RuntimeError as e:
  print("Error when creating ALMotion proxy:")
  exit(1)

# Wake up the robot
motion_proxy.wakeUp()

# Set the state of AutonomousLife to disabled
life_proxy.setState("disabled")

# Get the current state of the robot
state = life_proxy.getState()

# Print the current state of the robot
print("Current state:", state)