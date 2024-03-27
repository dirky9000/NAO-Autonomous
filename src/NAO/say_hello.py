import sys
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')

import naoqi
from naoqi import ALProxy

tts = ALProxy("ALTextToSpeech", "192.168.1.107", 9559)

tts.say("Hello World")