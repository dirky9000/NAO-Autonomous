import sys
import os
import time 
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')

import naoqi
from naoqi import ALProxy

# Replace this with your robot's IP address
IP = "192.168.1.107"
PORT = 9559

# Create a proxy to ALPhotoCapture
try:
  photoCaptureProxy = ALProxy("ALPhotoCapture", IP, PORT)
except Exception, e:
  print("Error when creating ALPhotoCapture proxy:")
  print(str(e))
  exit(1)

# Take 3 pictures in VGA and store them in /home/nao/recordings/cameras/

photoCaptureProxy.setResolution(2)
photoCaptureProxy.setPictureFormat("jpg")
photoCaptureProxy.takePictures(3, "/home/nao/recordings/cameras/", "image")

# Run this command to save picture onto computer
# C:\Users\dirky>scp nao@192.168.1.107:/home/nao/recordings/cameras/image*.jpg C:\whatever\location\you\want\to\save\to