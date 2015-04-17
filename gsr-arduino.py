#!/usr/bin/python
# -*- coding: utf-8 -*-

from PyQt5.Qt import *
import PyQt5.QtCore
import sys
from pyfirmata import ArduinoMega, util
import threading, time

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
	
     def run(self):
         while ( not self.stopNow) :
			v1 = self.board.analog[0].read()
			v2 = self.board.analog[1].read()
			#print v1,v2
			valueLabel1.setText(str(v1))
			valueLabel2.setText(str(v2))
			time.sleep(0.1)    
     
     def stop(self):
		 self.stopNow = True
		 self.board.exit()


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