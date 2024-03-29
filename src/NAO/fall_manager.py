# This allows you to turn on and off the NAO's fall sequence 
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

# Create a proxy to ALMotion
motion_proxy = ALProxy("ALMotion", NAO_IP, PORT)

# Disable or Enable the fall manager by doing 'False' or 'True'
motion_proxy.setFallManagerEnabled(False)

# Check if the fall manager is enabled
is_enabled = motion_proxy.getFallManagerEnabled()
print("Is fall manager enabled:", is_enabled)