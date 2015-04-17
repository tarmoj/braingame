#!/usr/bin/python
# -*- coding: utf-8 -*-

from PyQt5.Qt import *
import PyQt5.QtCore
import sys, subprocess

#start and stop sensor programs

def start1():
	print "Starting Neuropy1"
	subprocess.call(["python", "neuropy-multi-device.py", "0"])
	
def start2():
	print "Starting Neuropy2"
	subprocess.call(["python", "neuropy-multi-device.py", "0"])
	
def start3():
	print "Starting Neuropy3"
	subprocess.call(["python", "neuropy-multi-device.py", "0"])
	
def startSkin():
	print "Starting Skin"
	subprocess.call(["python", "gsr-arduino.py"])

app = QApplication(sys.argv)


window = QWidget() # window as main widget
layout = QGridLayout(window) # use gridLayout - the most flexible one - to place the widgets in a table-like structure
window.setLayout(layout) 
window.setWindowTitle("Start sensor programs")


layout.addWidget(QLabel("Neuropy 1 Helena"),0,0)
layout.addWidget(QLabel("Neuropy 2 Taavi"),1,0)
layout.addWidget(QLabel("Neuropy 3 Vambola"),2,0)
layout.addWidget(QLabel("Arduino (skin)"),3,0)

startButton1 = QPushButton("Start")
startButton1.clicked.connect(start1)
layout.addWidget(startButton1,0,1)

startButton2 = QPushButton("Start")
startButton2.clicked.connect(start2)
layout.addWidget(startButton2,1,1)

startButton3 = QPushButton("Start")
startButton3.clicked.connect(start3)
layout.addWidget(startButton3,2,1)

startButton4 = QPushButton("Start")
startButton4.clicked.connect(startSkin)
layout.addWidget(startButton4,3,1)

window.show()

sys.exit(app.exec_())