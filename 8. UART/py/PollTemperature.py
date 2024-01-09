'''
/*
 * @FILENAME:               PollTemperature.py
 *
 * @DESCRIPTION:            This script gets the CPU temperature using Open
 *                          Hardware Monitor and sends its value through
 *                          serial port.
 *                          It requires OpenHardwareMonitor to be running
 *
 * @AUTHOR:                 Hiram Montejano Gómez
 *
 * @STARTING DATE:          28/08/2021
 *
 * @ENDING DATE:            28/08/2021
 */
'''

import wmi
import serial
import time

w = wmi.WMI(namespace="root\\OpenHardwareMonitor")

'''
 * @BRIEF:       Gets CPU temperature from Open Hardware Monitor
 *
 * @RETURNS:     CPU Temperature
'''
def Get_Temperature():
    temperature_infos = w.Sensor() 
    for sensor in temperature_infos:
        if sensor.SensorType == u'Temperature':
            if sensor.Name == 'CPU Core': 
                return sensor.Value

'''
 * @BRIEF:       Sends CPU Temperature over serial port
 * 
 * @ARGUMENTS:   Temperature to send
'''
def Send_Temperature(temp):
    ser = serial.Serial('COM3', 115200)
    ser.write(temp.encode())
    
# main()

while True:
# Conversion to integer: remove decimal point
# Conversion to string: for later encoding and sending it through serial
# Division by 10: convert into 1 digit number
    CPU_Temperature = str(int(Get_Temperature() / 10))
    
    Send_Temperature(CPU_Temperature)
    time.sleep(2)
