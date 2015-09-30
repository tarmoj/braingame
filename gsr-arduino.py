#!/usr/bin/python
# -*- coding: utf-8 -*-

# kui /dev/ttyACM0 ei kao lsof | grep /dev/ttyACM ja kill vastavaed protsessid
# vt. ka ls /var/lock


from PyQt5.Qt import *
import PyQt5.QtCore
import sys
from pyfirmata import ArduinoMega, util
import threading, time, socket

class FirmataThread(threading.Thread):
     def __init__(self,widget):
         super(FirmataThread, self).__init__()
         self.board = ArduinoMega('/dev/ttyACM0')
         self.it = util.Iterator(self.board)
         self.it.start()
         self.board.analog[0].enable_reporting()
         self.board.analog[1].enable_reporting()
         self.stopNow = False
         self.widget = widget
         print "ArduinoMEGA ready to operate"
         #self.max1 = 0.2
         #self.min1 = 0.1
         #self.max2 = 0.2
         #self.min2 = 0.1
	
     def run(self):
         while ( not self.stopNow) :
			v1 = self.board.analog[0].read()
			v2 = self.board.analog[1].read()
			#if (v1>self.max1 and v1<1): # find relative value between max and min of the session bit interesting
				#self.max1 = v1
			#if (v1<self.min1 and v1>0):
				#self.min1 = v1
			
			#if (v2>self.max2 and v2<1):
				#self.max2 = v2
			#if (v1<self.min2 and v2>0):
				#self.min2 = v2
			max = 0.6
			min = 0.2
			if (v1<min):
				v1 = min
			if (v1>max):
				v1 = max
			if (v2<min):
				v2 = min
			if (v2>max):
				v2 = max	
			rel1 = (v1-min) / (max-min)
			rel2 = (v2-min) / (max-min)
			#print rel1,rel2
			valueLabel1.setText(str(rel1))
			valueLabel2.setText(str(rel2))
			sendUdpMessage("sensor,skin1,"+str(rel1))
			sendUdpMessage("sensor,skin2,"+str(rel2))
			time.sleep(0.25)   
     
     def stop(self):
		 self.stopNow = True
		 self.board.exit()


def sendUdpMessage(message):
	#print message
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	try:
		sock.sendto(message, ("192.168.1.67", 7077)) #111.1.1.161
	except Exception as e:
		print(e)
	#sock.sendto(message, ("192.168.1.202", 7077)) #111.1.1.161

#main



app = QApplication(sys.argv)


window = QWidget() # window as main widget
layout = QGridLayout(window) # use gridLayout - the most flexible one - to place the widgets in a table-like structure
window.setLayout(layout) 
window.setWindowTitle("GSR from arduino")

arduino = FirmataThread(window)


layout.addWidget(QLabel("GSR 1: "),0,0) # first row, first column
layout.addWidget(QLabel("GSR 2: "),1,0) # second row, first column
valueLabel1 = QLabel("?")
valueLabel2 = QLabel("?")
layout.addWidget(valueLabel1,0,1)
layout.addWidget(valueLabel2,1,1)

stopButton = QPushButton("Stop")
stopButton.clicked.connect(arduino.stop)
layout.addWidget(stopButton,2,1)

window.show()
arduino.start()
#arduino.join()

sys.exit(app.exec_())