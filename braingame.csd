
<CsoundSynthesizer>
<CsOptions>
-odac
-d
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


schedule  "emulate",0, -1 ; comment out for performance! 
instr emulate 
	katn1 = 0.5 + jspline:k(0.5,0.1,5)
	khb1 = 0.5 + jspline:k(0.5,0.1,5)
	klb1 = 0.5 ;+ jspline:k(0.5,0.1,5)
	kraw1 jspline 1000,1,50 ; may change pretty quickly
	chnset kraw1, "raw1"
	chnset 0.5 + jspline:k(0.4,0.1,1),"skin1"
	
	if (metro(1)==1) then ; the sensors send these values in every second
		chnset katn1, "attention1"
		chnset khb1, "hb1"
		chnset klb1, "lb1"
	endif
endin

gkLevelTarmo init 1 ; re-evaluate thes constants to change sound! 
gkPanTarmo init 0.5
; schedule "tarmo",0,-1 ; turn on
; schedule -nstrnum("tarmo"),0,0 ; turn off
instr tarmo ; FM
	kattention chnget "attention1" ; 0..1
	krawValue chnget "raw1" ; anything, between -60000 and 60000
	kfreq init 400
	if (abs(krawValue)<1000) then ; ignore big changes. or limit(kRawValue,-1000,1000)
		 kmod = (krawValue+1000)/1000 + 1 ; to tremble around 2.0
	endif
	kmod limit kmod, 0, 5
	
	klowBeta chnget "lb1" ; 0..1
	kmod += klowBeta
	kmod port kmod,0.1
	kindex = 1+klowBeta*10
	;kindex port kindex,0.5
	
	
	kfreq = 100+kattention*200
	kfreq += kmod*8
	kfreq port kfreq,0.25

	aenv linenr 0.01,0.1,3,0.001 ; all envelopes should be with release (madsr, linenr etc)!
	asig foscil aenv, kfreq, 1,kmod, kindex, -1 
	asig = asig*port(gkLevelTarmo,0.05)
	aL, aR pan2 asig, gkPanTarmo
	outs aL, aR

endin

</CsInstruments>
<CsScore>

</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
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
