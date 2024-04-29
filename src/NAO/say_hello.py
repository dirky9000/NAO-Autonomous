import naoqi
from naoqi import ALProxy

tts = ALProxy("ALTextToSpeech", "192.168.1.135", 9559)

tts.say("Hello World")