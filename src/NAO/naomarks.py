from naoqi import ALProxy
import time

rooms = {
    64: "Maker Space Room",
    85: "Transportation Lab Room",
    107: "Survey Storage Room",
    108: "Robotics Lab Room",
    112: "Room 126",
    114: "Room 128"
}

try:
    nao_ip = "192.168.1.135"  # change to your NAO's IP address
    nao_port = 9559
    landmark_proxy = ALProxy("ALLandMarkDetection", nao_ip, nao_port)  # used to detect landmarks
    memory_proxy = ALProxy("ALMemory", nao_ip, nao_port)  # used to access landmark data
    tts_proxy = ALProxy("ALTextToSpeech", nao_ip, nao_port)  # used to make the robot speak

    landmark_proxy.subscribe("LandmarkTest")  # subscribe to the landmark detection module

    print("\n...Starting continuous landmark detection...\n")
    try:
        while True:
            landmark_data = memory_proxy.getData("LandmarkDetected")
            if landmark_data and landmark_data[1]:
                for mark in landmark_data[1]:
                    mark_id = mark[1][0]
                    if mark_id in rooms:
                        tts_proxy.say(rooms[mark_id])  # make the robot say the room name
                        print("Detected Naomark with ID: {}".format(mark_id))
                        print("Announced room:           {}\n".format(rooms[mark_id]))
                    else:
                        continue
            time.sleep(2)
    except KeyboardInterrupt:
        print("...Stopping continuous detection...")

finally:
    landmark_proxy.unsubscribe("LandmarkTest") # unsubscribe from the landmark detection module