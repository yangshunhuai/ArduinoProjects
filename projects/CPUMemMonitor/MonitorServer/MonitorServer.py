#!/usr/bin/env python3
import serial

# Baud rate
baud = 9600
# Port (Windows)
port = "COM9"
# Port (Mac OS X)
# port = "/dev/cu.usbmodemfa121"
# Port (Linux)
# port = "/dev/ttyUSB0"

# Create serial object
ser = serial.Serial(port, baud)