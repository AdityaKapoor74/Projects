import serial
import time
from playsound import playsound


ser = serial.Serial('COM5', 9600, timeout=0)
 
while 1:
    serialValue = ser.readline().decode('utf-8')
    if serialValue == "C":
        print ("Input is C: Playing cymbal")
        playsound('cymbal.wav')
    elif serialValue == "D":
        print ("Input is D: Playing snare")
        playsound('snare.wav')
    elif serialValue == "E":
        print ("Input is E: Playing kick")
        playsound('kick.wav')
    elif serialValue == "F":
        print ("Input is F: Playing tom")
        playsound('tom.wav')
