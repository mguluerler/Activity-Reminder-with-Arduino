import serial
from datetime import datetime
import time

#Blinking degrees are set up.
def degreeSetter():
    remaining_minutes = 60 - int(datetime.today().strftime("%M"))  # [0-59]
    if remaining_minutes >= 20:
        degree = 1
    elif remaining_minutes < 20 and remaining_minutes >= 10:
        degree = 2
    elif remaining_minutes < 10 and remaining_minutes >= 7:
        degree = 3
    elif remaining_minutes < 7 and remaining_minutes >= 4:
        degree = 4
    elif remaining_minutes < 4 and remaining_minutes >= 2:
        degree = 5
    else:
        degree = 6
    return degree

#Activities are set up.
#Input Type: activityx = [dayofweek, hourofday, which activity on arduino code]
def activities():
    activity1 = [5, 16, 1]
    activity2 = [2, 10, 2]
    activity3 = [2, 14, 3]
    activity4 = [5, 22, 4]
    activity5 = [5, 17, 5]
    activity6 = [5, 15, 6]
    activity7 = [5, 8, 7]
    activity8 = [5, 8, 8]
    sortlist = [activity1, activity2, activity3, activity4, activity5, activity6, activity7, activity8]
    sortlist.sort(key=lambda i: i[1])
    return sortlist

# degrees = [1,2,3,4,5,6] => blink periods[1min, 30s, 15s, 10s, 5s, 2s] => How much time remains for activity[20min, 10min, 7min, 4min, 2min, 0min]

failed_connection = False #This variable is used for stopping continuous warnings for failed connections.
arduino_port = "COM5"
arduino = serial.Serial(arduino_port, baudrate=9600, timeout=1)
activitiesinlist = activities()

while True:
    day = int(datetime.today().strftime("%w"))  # [0-6]
    hour = int(datetime.today().strftime("%H"))  # [0-23]
    time_now = [day, hour]
    #Is LCD going to blinking?
    isblink = False
    output_ard = ""
    for act in activitiesinlist:
        #Same day?
        if act[0] == time_now[0]:
            #Is activity finished?
            if act[1] < time_now[1]:
                continue
            #Is 1 hour stayed for activity?
            elif act[1] == time_now[1] + 1:
                isblink = True
            output_ard = output_ard + str(act[2])

    if isblink:
        output_ard = str(degreeSetter()) + output_ard
    else:
        output_ard = "1" + output_ard

    try:
        #If connection broke already and expected program previous loop, try to reestahblish arduino.
        if failed_connection:
            arduino_port = "COM5"
            arduino = serial.Serial(arduino_port, baudrate=9600, timeout=1)
        arduino.write(output_ard.encode("ascii"))    # 112 [Degree of blink][1. oncoming activity][2. oncoming activity]
        #If the connection estahblished successfully prints for notifying user.
        if failed_connection:
            print("Connection is estahblished again!")
        failed_connection = 0
    except:
        #If first time connection failed print a warning to notifies user:
        if not failed_connection:
            print("No connection with Arduino!")
        failed_connection = True
    time.sleep(1)