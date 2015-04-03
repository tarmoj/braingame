
<CsoundSynthesizer>
<CsOptions>
<CsOptions>
-odac:system:playback_ -+rtaudio=jack -d
</CsOptions>
<CsInstruments>

sr = 44100
nchnls = 2
0dbfs = 1
ksmps = 32

;CHANNELS:

; the challels are: 1)  brainsensors (values scaled to 0..1, updated in every second - USE PORT): attention1, attention2, attention3; HighBt ta - hb1 , hb2, hb3; low beta - lb1,lb2,lb3 ; - everything scaled to 0..1
;raw data (around -1000...1000, sent 512 times per second), must check, rhough; USE LIMIT!
; skin conductance: (scaled to 0..1) - skin1, skin2 - not TESTED YET!


;schedule  "emulate",0, -1 ; mimics the sensors. comment out for performance! 
instr emulate 
	katn1 = 0.5 + jspline:k(0.5,0.1,5)
	khb1 = 0.5 + jspline:k(0.5,0.1,5)
	klb1 = 0.5 + jspline:k(0.5,0.1,5)
	kraw1 jspline 1000,1,50 ; may change pretty quickly
	chnset kraw1, "raw1"
	
	katn2 = 0.5 + jspline:k(0.5,0.1,5)
	khb2 = 0.5 + jspline:k(0.5,0.1,5)
	klb2 = 0.5 + jspline:k(0.5,0.1,5)
	kraw2 jspline 1000,1,50 ; may change pretty quickly
	chnset kraw2, "raw2"
	
	katn3 = 0.5 + jspline:k(0.5,0.1,5)
	khb3 = 0.5 + jspline:k(0.5,0.1,5)
	klb3 = 0.5 ;+ jspline:k(0.5,0.1,5)
	kraw3 jspline 1000,1,50 ; may change pretty quickly
	chnset kraw3, "raw3"

	chnset 0.5 + jspline:k(0.4,0.1,1),"skin1"
	chnset 0.5 + jspline:k(0.4,0.1,1),"skin2"
	
	
	if (metro(1)==1) then ; the sensors send these values in every second
		chnset katn1, "attention1"
		chnset khb1, "hb1"
		chnset klb1, "lb1"
		chnset katn2, "attention2"
		chnset khb2, "hb2"
		chnset klb2, "lb2"
		chnset katn3, "attention3"
		chnset khb3, "hb3"
		chnset klb3, "lb3"
	endif
endin

; demo instrument:
gkLevelTarmo init 1 ; re-evaluate thes constants to change sound! 
gkPanTarmo init 0.5
gkBaseFreq init 100
; schedule "tarmo",0,-1 ; turn on
; schedule -nstrnum("tarmo"),0,0 ; turn off
instr tarmo ; FM
	kattention chnget "attention2" ; 0..1
	krawValue chnget "raw2" ; anything, between -60000 and 60000

	if (abs(krawValue)<1000) then ; ignore big changes. or limit(kRawValue,-1000,1000)
		 kmod = (krawValue+1000)/1000 + 1 ; to tremble around 2.0
	endif
	kmod limit kmod, 0, 5
	
	klowBeta chnget "lb2" ; 0..1
	kmod += klowBeta
	kmod port kmod,0.1
	kindex = 1+klowBeta*10
	kindex port kindex,0.2
	
	kskin port chnget:k("skin1"),0.1
	aenv2 lfo 1-kskin, 1+10*(1-kskin),1 ; to give some pulsation
	
	kfreq = gkBaseFreq +kattention*200
	kfreq += kmod*8
	kfreq port kfreq,0.25

	aenv linenr 0.01,0.1,3,0.001 ; all envelopes should be with release (madsr, linenr etc)!
	asig foscil aenv, kfreq, 1,kmod, kindex, -1 
	apulse = asig*aenv2
	asig = 0.8*(asig+apulse)*port(gkLevelTarmo,0.05)
	aL, aR pan2 asig, gkPanTarmo
	outs aL, aR

endin

gkLevelTarmo2 init 1 ; use one global variable for level
gkratio init 1.25 ; use some gk-variables that are easy to change (send gkratio 1.234 for example)
; schedule "Tarmo2",0,-1 ; compile it to turn on
; schedule -nstrnum("Tarmo2"),0,0 ; turn off
instr Tarmo2
	aenv linenr 0.01,0.1,3,0.001 ; use and envelope with release
	kattention chnget "attention1" ; 0..1
	kamp port kattention, 0.25 ; make amplitude dependent of attention
	kfreq = 200 * (1+chnget:k("skin1"))

	a1 poscil aenv*kamp, kfreq
	a2 poscil aenv*kamp, kfreq*gkratio
	aout = (a1+a2)/2*gkLevelTarmo
	outs aout, aout
endin

;schedule "Frankenstein",0,-1 ; compile it to turn on
; schedule -nstrnum("Frankenstein"),0,0 ; turn off
gkStraight init 0
gkrvbAmount init 0.01
gkLevelFrank init  0.5
gkEmulate init 0
instr Frankenstein ; text
	setksmps 1
	kattention chnget "attention2" ; 0..100
	
	klowBetaRelative chnget "lb2"
	khighBetaRelative chnget "hb2"
	kskin chnget "skin1"
	
	
	if (gkStraight==1) then
	kindex = 1 ; speed of reading from the soundfile
	else
		if (kattention<0.6) then
			kindex = 0.05+(0.25*kattention)	; very slow reading
		else
			kindex = 0.5+(0.75*kattention) ; closer to normal	
		endif
		kindex port kindex,0.1
	endif		
	
	
	adisk diskin2 "Dec-Francis-E_rant1_Frankenstein_Earphone_radio.ogg", kindex, 0, 1
	adisk = adisk*0.5
	ktime = 1.5 + port(klowBetaRelative,0.5)*5
	
	khdif port kskin,0.05
	arev reverb2 adisk*port(gkrvbAmount,0.1), ktime, khdif 
	aenv linenr 1,0.1,3,0.001
	asig = (adisk + arev)*port(gkLevelFrank,0.05)*aenv
	outs asig, asig
	
endin

; victor

instr raw
kraw chnget "raw2"
araw interp kraw
araw /=200
aenv linenr 0.5,0.1,0.1,0.01
aout = araw* aenv
;chnmix araw*aenv, "raw_audio"

outs aout, aout
fout "raw_wave_interp.wav",4,aout
endin


instr 1
S1 sprintf "raw%d",int(p4)
;prints S1
kraw chnget S1
araw upsamp kraw
araw /=100
kenv linenr 0.5,1,0.1,0.01
chnmix araw*kenv, "raw_audio"
endin

schedule 100,0,-1
instr 100 ; central control & mix



khb1 chnget "hb1"
khb2 chnget "hb2"
khb3 chnget "hb3"
khb port (khb1+khb2+khb3)/3,0.1

araw chnget "raw_audio"
araw *= khb

      outs araw, araw

katt1 chnget "attention1"
kskin1 chnget "skin1"
if trigger(katt1,0.7,0)==1 then
event "i", 1,0,rnd(3),1,kskin1
endif

katt2 chnget "attention2"

schedkwhen trigger(katt2,0.7,2), 0, 0, "raw", 0, 10

kskin2 chnget "skin2"
;if  trigger(katt2,0.7,0)==1  then
;event "i", 1,0,rnd(3),1,kskin2
;endif

katt3 chnget "attention3"
if trigger(katt3,0.7,0)==1 then
event "i", 1,0,rnd(3),1,kskin2
endif

chnclear "raw_audio"
endin

</CsInstruments>
<CsScore>

</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>0</x>
 <y>0</y>
 <width>0</width>
 <height>0</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
