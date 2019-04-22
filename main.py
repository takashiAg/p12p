import serial
import serial.tools.list_ports
import sys
import time

def connect_auto():
    print("If you need to exit. please Press Ctrl + C")
    print("Now connecting",end="",flush=True)
    try:
        while True:
            ser = serial.Serial()
            ser.baudrate = 9600
            devices = serial.tools.list_ports.comports()
            for device in devices:
                if device.usb_description()=='Arduino Uno':
                    ser.port=device[0]
            try:
                ser.open()
                break
            except:
                print(".",end="",flush=True)
                time.sleep(1)
                continue
    except KeyboardInterrupt:
        print()
        print("stopped")
        sys.exit(-1)
    print("")
    print("connected!!")
    return ser

def send(Left,Right,ser):
    b = bytes([int(Left), int(Right),255])
    ser.write(b)
    print("send\tLeft:",int(b[0]),"\tRight:",int(b[1]))

def input_num(message):
    while True:
        NUM=input(message)
        if NUM.isdecimal() and int(NUM)<101:
            return NUM
        print("please fill number (number < 100)")

def main():
    ser = connect_auto()
    while True:
        Left  = input_num("Left\t: ")
        Right = input_num("Right\t: ")

        send(Left,Right,ser)

        # time.sleep(0.2)
        # print(ser.read(ser.inWaiting()).decode('utf-8'))

if __name__ == '__main__':
    main()
