# This python script listens to events of EmptyEpsilon´s local http server
# it creates light effects with connected leds and sounds an alarm with a connected bluetooth device
from time import sleep

import requests
import serial

arduino = serial.Serial('COM4', 9600)


def write_to_serial(x):
    if not arduino.is_open:
        arduino.open()
    print('writing to serial...')
    arduino.write(x.encode())


while True:
    r = requests.get(url="http://localhost:8080/get.lua?alertLevel=getAlertLevel()")
    if "RED ALERT" in r.text:
        write_to_serial(2)
    if "YELLOW ALERT" in r.text:
        write_to_serial(3)

    sleep(10)
