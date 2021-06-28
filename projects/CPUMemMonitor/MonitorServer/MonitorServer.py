#!/usr/bin/env python3
import serial
from serial.serialutil import SerialException
import psutil
import time

refreshRate = 0
# Baud rate
baud = 9600
# Port (Windows)
port = "COM9"
# Port (Mac OS X)
# port = "/dev/cu.usbmodemfa121"
# Port (Linux)
# port = "/dev/ttyUSB0"

# Create serial object
try:
    ser = serial.Serial(port, baud)
except SerialException:
    print('Warning: Port not found! The client is not connected.')
    exit()

def getCPUPercent():
    cpuPercent = psutil.cpu_percent(1)
    print('CPU: ' + str(int(cpuPercent)))
    return int(cpuPercent)

def getMemPercent():
    mem = psutil.virtual_memory()
    memPercent = mem.percent
    print('Mem: ' + str(int(memPercent)))
    return int(memPercent)

while True:
    sendString = str(getCPUPercent()) + ',' + str(getMemPercent()) + '\n'
    encodedString = sendString.encode('ascii')
    ser.write(encodedString)
    time.sleep(refreshRate)
