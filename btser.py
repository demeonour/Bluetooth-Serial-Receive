from datetime import datetime
import RPi.GPIO as IO
import serial
import time
IO.setmode(IO.BOARD)
IO.setwarnings(False)

IO.setup(36,IO.OUT) #Waiting LED
IO.setup(38,IO.OUT) #Recording LED
IO.setup(40,IO.OUT) #Writing LED

IO.setup(35, IO.IN)
IO.setup(37, IO.IN, pull_up_down=IO.PUD_UP)

IO.output(36,1)
IO.wait_for_edge(35,IO.RISING)
IO.output(36,0)



#Obtaining the time the program has started and turning it into a string
now = "{:%y-%m-%d:%H%M}".format(datetime.now())


#opens a serial port at /dev/rfcomm0 with baudrate at 9600bps
#sudo rfcomm bind 0 98:D3:31:FC:66:58
# 98:D3:31:FC:66:58 
btSer = serial.Serial("/dev/rfcomm0", baudrate=9600)
#Start the 'Go' Signal
btSer.write('G'.encode())

#buffer for the data to be stored in
data = []

#LED ON for RECORDING
IO.output(38,1)
while True: #i!=0:
	#recievce the serial data from the pi
	data.append(btSer.readline())
#Recording LED OFF
IO.output(38,0)


#After a reading is done, write to file, turn LED on for writing
IO.output(40,1)
f = open('test'+now+'.txt','w') 
for datum in data:
	f.write(datum.decode('UTF-8','ignore'))
f.close()
#After this, turn LED for writing OFF
GPIO.output(40,0)
