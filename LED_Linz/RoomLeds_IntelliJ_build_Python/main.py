# This is a python script that sends information of the intellij build process
# to an arduino via serial ports

import serial
import time
from datetime import datetime

arduino = serial.Serial('COM4', 9600)


def write_to_serial(x):
    if not arduino.is_open:
        arduino.open()
    print('writing to serial...')
    arduino.write(x.encode())
    time.sleep(3)


# read file data and check if any new data arrived
def read_file():
    f = open("C:\\Users\\haslh\\AppData\\Local\\JetBrains\\IntelliJIdea2020.2\\log\\idea.log", "r")
    print('reading file...')
    lines = f.readlines()

    # build information consists of 10 lines
    build_data = lines[-10:]

    logTime = datetime.strptime(build_data[0][0:19], '%Y-%m-%d %H:%M:%S')

    # check if compilation succeeded based on text in log file
    # write to serial if build entry is not older than 10 seconds
    if build_data[0].__contains__('COMPILATION FINISHED (BUILD PROCESS); Errors: 0') \
            and (datetime.now() - logTime).total_seconds() < 5:
        print('Build succeeded. Turning LEDs green...')
        try:
            write_to_serial('2')  # write '2' to serial as it stands for build succeeded
        except serial.SerialException:
            print('### could not send data to serial port ###')
    f.close()
    print('Finished reading file')


while True:
    read_file()
    time.sleep(3)
