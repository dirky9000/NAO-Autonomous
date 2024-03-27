import os
import sys
import time
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')
import naoqi
from naoqi import ALProxy
from naoqi import ALModule
from naoqi import ALBroker

count = 1
period = 500
moduleName = "pythonModule"
NAO_IP = "192.168.1.126"  # Replace here with your NaoQi's IP address.
PC_IP = "192.168.1.149"   # Replace here with your computer IP address
PORT = 9559
memValue = "PictureDetected" # ALMemory variable where the ALVisionRecognition module outputs its results.

class myModule(ALModule):
  """python class myModule test auto documentation"""
  
  def __init__(self, name):
    ALModule.__init__(self, name)
    self.last_label = None

  def pictureChanged(self, strVarName, value, strMessage):
    """callback when data change"""
    print("\ndatachanged", strVarName, " ", value, " ", strMessage)
    global count
    count = count-1
    tts = ALProxy("ALTextToSpeech", NAO_IP, PORT)
    if value:  # Check if value is not empty
        label = value[1][0][0][0]
        if label != self.last_label:  # Check if label has changed
            tts.say("I see a " + label)
            self.last_label = label  # Update last_label

broker = ALBroker("pythonBroker", PC_IP,9999, NAO_IP,9559)
pythonModule = myModule(moduleName)

# Create a proxy to ALMemory
try:
  memoryProxy = ALProxy("ALMemory", NAO_IP, PORT)
except RuntimeError as e:
  print("Error when creating ALMemory proxy:")
  exit(1)

# Have the python module called back when picture recognition results change.
try:
  memoryProxy.subscribeToEvent(memValue, moduleName, "pictureChanged")
except RuntimeError as e:
  print("Error when subscribing to micro event")
  exit(1)

# Let the picture recognition run for a little while (will stop after 'count' calls of the callback).
# You can check the results using a browser connected on your Nao, then
# Advanced -> Memory -> type PictureDetected in the field
while count>0:
  time.sleep(1)


# unsubscribe modules
memoryProxy.unsubscribeToEvent(memValue, moduleName)
#recoProxy.unsubscribe(moduleName)

print('end of vision_recognition python script')