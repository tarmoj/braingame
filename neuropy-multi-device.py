#!/usr/bin/python
# -*- coding: utf-8 -*-

from NeuroPy import NeuroPy
from time import sleep
import sys
from PyQt5.Qt import *
import PyQt5.QtCore
import socket


#; may need to: sudo rfcomm bind 0 74:E5:43:BE:36:A3 1 if /dev/rfcomm0 isn't there
# for releasing: sudo rfcomm release 0

# mindvave 2: rfcomm bind 1 20:68:9D:4C:12:25 1
# mindwave 3: rfcomm bind 2 20:68:9D:88:C2:D0 1


class BrainWindow(QWidget):
	def __init__(self, parent=None, sensorNUmber=0): #sensorNUmber - rfcomm port number - 0 for rfcomm0 etc
		super(BrainWindow, self).__init__(parent)
		
		self.sensorNUmber = sensorNUmber
		self.setWindowTitle(u"Mindwave "+str(self.sensorNUmber+1))
		
		layout = QGridLayout()
		layout.addWidget(QLabel("Value"),0,1)
		layout.addWidget(QLabel("Min"),0,2)
		layout.addWidget(QLabel("Max"),0,3)
		layout.addWidget(QLabel("Relative"),0,4)
		
		layout.addWidget(QLabel("Attention:"),1,0)
		layout.addWidget(QLabel("Poor signal:"),1,2)
		layout.addWidget(QLabel("Low beta"),2,0)
		layout.addWidget(QLabel("High beta"),3,0)
		layout.addWidget(QLabel("Low gamma"),4,0)
		layout.addWidget(QLabel("Mid gamma"),5,0)
		layout.addWidget(QLabel("Raw data:"),6,0)
		
		self.attentionLabel = QLabel()
		layout.addWidget(self.attentionLabel,1,1)
		
		self.poorSignalLabel = QLabel()
		layout.addWidget(self.poorSignalLabel,1,3)
		
		self.lBetaLabel = QLabel()
		self.lBetaMinLabel = QLabel()
		self.lBetaMaxLabel = QLabel()
		self.lBetaRelLabel = QLabel()
		layout.addWidget(self.lBetaLabel,2,1)
		layout.addWidget(self.lBetaMinLabel,2,2)
		layout.addWidget(self.lBetaMaxLabel,2,3)
		layout.addWidget(self.lBetaRelLabel,2,4)
		
		self.hBetaLabel = QLabel()
		self.hBetaMinLabel = QLabel()
		self.hBetaMaxLabel = QLabel()
		self.hBetaRelLabel = QLabel()
		layout.addWidget(self.hBetaLabel,3,1)
		layout.addWidget(self.hBetaMinLabel,3,2)
		layout.addWidget(self.hBetaMaxLabel,3,3)
		layout.addWidget(self.hBetaRelLabel,3,4)
		
		self.lGammaLabel = QLabel()
		self.lGammaMinLabel = QLabel()
		self.lGammaMaxLabel = QLabel()
		self.lGammaRelLabel = QLabel()
		layout.addWidget(self.lGammaLabel,4,1)
		layout.addWidget(self.lGammaMinLabel,4,2)
		layout.addWidget(self.lGammaMaxLabel,4,3)
		layout.addWidget(self.lGammaRelLabel,4,4)
		
		self.mGammaLabel = QLabel()
		self.mGammaMinLabel = QLabel()
		self.mGammaMaxLabel = QLabel()
		self.mGammaRelLabel = QLabel()
		layout.addWidget(self.mGammaLabel,5,1)
		layout.addWidget(self.mGammaMinLabel,5,2)
		layout.addWidget(self.mGammaMaxLabel,5,3)
		layout.addWidget(self.mGammaRelLabel,5,4)
		
		
		
		
		#stop
		stopButton = QPushButton("Stop")
		stopButton.clicked.connect(self.stop)
		layout.addWidget(stopButton,7,0)
		
		self.setLayout(layout)
		
		
		self.headSet = NeuroPy("/dev/rfcomm"+str(sensorNUmber),57600)
		self.headSet.setCallBack("attention",self.attention_callback)
		self.headSet.setCallBack("lowBeta",self.lowBeta_callback)
		self.headSet.setCallBack("highBeta",self.highBeta_callback)
		self.headSet.setCallBack("lowGamma",self.lowGamma_callback)
		self.headSet.setCallBack("midGamma",self.midGamma_callback)
		self.headSet.setCallBack("rawValue",self.rawValue_callback)
		self.headSet.setCallBack("poorSignal",self.poorSignal_callback)
		self.headSet.start()
		
		self.highLimit = 100000 # ignore occasional  higher values from EEG data
		self.lowLimit = 100
		
		self.lBetamin = 10000
		self.lBetamax = 0.1
		self.lBetarelative = 0
		self.hBetamin = 10000
		self.hBetamax = 0.1
		self.hBetarelative = 0
		self.lGammamin = 10000
		self.lGammamax = 0.1
		self.lGammarelative = 0
		self.mGammamin = 10000
		self.mGammamax = 0.1
		self.mGammarelative = 0
		
		
		
	def __del__(self):
		self.stop()
	
	def stop(self):
		self.headSet.stop()
		#self.perf.Stop()
		#self.perf.Join()
		#self.cs.Stop()
	
	#TEMPORARY -delete later
	
		
	
	def lowBeta_callback(self, value):
		#print "Low beta: ", value
		if (value>self.highLimit or value<self.lowLimit): # don't handle occasional high values
			return
		self.lBetaLabel.setText(str(value))
		if (value<self.lBetamin and value!=0):
			self.lBetamin = value
			self.lBetaMinLabel.setText(str(value))
		if (value>self.lBetamax):
			self.lBetamax = value
			self.lBetaMaxLabel.setText(str(value))
		self.lBetarelative = float(value-self.lBetamin)/(self.lBetamax-self.lBetamin+1)
		self.lBetaRelLabel.setText(str(self.lBetarelative))
		sendUdpMessage("sensor,lb"+str(self.sensorNUmber+1)+","+str(self.lBetarelative))

		#self.cs.SetChannel("lowBetaRelative",self.lBetarelative)		
		return None
	
	def highBeta_callback(self, value):
		#print "high beta: ", value
		if (value>self.highLimit or value<self.lowLimit): # don't handle occasional high values
			return
		self.hBetaLabel.setText(str(value))
		if (value<self.hBetamin and value!=0):
			self.hBetamin = value
			self.hBetaMinLabel.setText(str(value))
		if (value>self.hBetamax):
			self.hBetamax = value
			self.hBetaMaxLabel.setText(str(value))
		self.hBetarelative = float(value-self.hBetamin)/(self.hBetamax-self.hBetamin+1)
		self.hBetaRelLabel.setText(str(self.hBetarelative))
		sendUdpMessage("sensor,hb"+str(self.sensorNUmber+1)+","+str(self.hBetarelative))
		#self.cs.SetChannel("highBetaRelative",self.hBetarelative)		
		return None
	
	def lowGamma_callback(self, value):
		#print "Low gamma: ", value
		if (value>self.highLimit or value<self.lowLimit): # don't handle occasional high values
			return
		self.lGammaLabel.setText(str(value))
		if (value<self.lGammamin and value!=0):
			self.lGammamin = value
			self.lGammaMinLabel.setText(str(value))
		if (value>self.lGammamax):
			self.lGammamax = value
			self.lGammaMaxLabel.setText(str(value))
		self.lGammarelative = float(value-self.lGammamin)/(self.lGammamax-self.lGammamin+1)
		self.lGammaRelLabel.setText(str(self.lGammarelative))
		#self.cs.SetChannel("lowBetaRelative",self.lGammarelative)		
		return None
	
	def midGamma_callback(self, value):
		#print "mid gamma: ", value
		if (value>self.highLimit or value<self.lowLimit): # don't handle occasional high values
			return
		self.mGammaLabel.setText(str(value))
		if (value<self.mGammamin and value!=0):
			self.mGammamin = value
			self.mGammaMinLabel.setText(str(value))
		if (value>self.mGammamax):
			self.mGammamax = value
			self.mGammaMaxLabel.setText(str(value))
		self.mGammarelative = float(value-self.mGammamin)/(self.mGammamax-self.mGammamin+1)
		self.mGammaRelLabel.setText(str(self.mGammarelative))
		#self.cs.SetChannel("midmGammaRelative",self.mGammarelative)		
		return None
	
	def attention_callback(self, value):
		#print "Attention: ",value
		self.attentionLabel.setText(str(value))
		sendUdpMessage("sensor,attention"+str(self.sensorNUmber+1)+","+str(float(value)/100))
		#self.cs.SetChannel("attention",value)
		return None
	
	def rawValue_callback(self, value):
		#this is very fast don't print this 
		#print "rawValue: ", value
		#self.cs.SetChannel("rawValue",value)
		if (abs(value)<1000):
			sendUdpMessage("sensor,raw"+str(self.sensorNUmber+1)+","+str(value))
		return None
	
	def poorSignal_callback(self,value):
		print "headset: ",self.sensorNUmber,"poor signal: ",value
		self.poorSignalLabel.setText(str(value))

def sendUdpMessage(message):
	#print message
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.sendto(message, ("127.0.0.1", 7077))

if __name__ == "__main__":
	print "Hello"
	app = QApplication(sys.argv)
	
	if (len(sys.argv)<2):
		sensor = 0
	else:
		sensor = sys.argv[1]
	#print "sensor: ",sensor
	b = BrainWindow( sensorNUmber=int(sensor))
	b.show()
	
	#sleep(1)
	#b2 = BrainWindow( sensorNUmber=2)
	#b2.show()
	
	sys.exit(app.exec_())
	
	#headSet = NeuroPy("/dev/rfcomm0",115200)
	#headSet.setCallBack("attention",attention_callback)
	#headSet.start()
	
	#cs = csnd6.Csound()
	#cs.Compile("neuropy-proov.csd")
	#perf = csnd6.CsoundPerformanceThread(cs)
	#perf.Play()
	#counter = 0
	#oldvalue = 0
	#while (counter<4000):
		#counter+=1
		#value = headSet.rawValue +200+ headSet.attention*10 
		#if (oldvalue!=value):
			#print "new value: ", value
			#cs.SetChannel("freq",float(value))
			#oldvalue = value
		##print headSet.highBeta
		#sleep(0.01)
	#headSet.stop()
		