
<CsoundSynthesizer>

<CsOptions>
-odac:system:playback_ -+rtaudio=jack -d
</CsOptions>
<CsInstruments>

sr = 48000
nchnls = 2
0dbfs = 1
ksmps = 32

;;CHANNELS:

; the channels are: 1)  brainsensors (values scaled to 0..1, updated in every second - USE PORT): attention1, attention2, attention3; HighBt ta - hb1 , hb2, hb3; low beta - lb1,lb2,lb3 ; - everything scaled to 0..1
;raw data (around -1000...1000, sent 512 times per second), must check, rhough; USE LIMIT!
; skin conductance: (scaled to 0..1) - skin1, skin2 - not TESTED YET!


schedule  "emulate",0, -1 ; mimics the sensors. comment out for performance! 
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
	kattention chnget "attention1" ; 0..1
	krawValue chnget "raw1" ; anything, between -60000 and 60000

	if (abs(krawValue)<1000) then ; ignore big changes. or limit(kRawValue,-1000,1000)
		 kmod = (krawValue+1000)/1000 + 1 ; to tremble around 2.0
	endif
	kmod limit kmod, 0, 5
	
	klowBeta chnget "lb1" ; 0..1
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
gkLevelFrank init  0.1
gkEmulate init 0
instr Frankenstein ; text
	setksmps 1
	kattention chnget "attention1" ; 0..100
	
	klowBetaRelative chnget "lb1"
	khighBetaRelative chnget "hb1"
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
	
	
	adisk diskin2 "Dec-Francis-E_rant1_Frankenstein_Earphone_radio.wav", kindex, 0, 1
	adisk = adisk*0.5
	ktime = 1.5 + port(klowBetaRelative,0.5)*5
	
	khdif port kskin,0.05
	arev reverb2 adisk*port(gkrvbAmount,0.1), ktime, khdif 
	aenv linenr 1,0.1,3,0.001
	asig = (adisk + arev)*port(gkLevelFrank,0.05)*aenv
	outs asig, asig
	
endin


; MATTI ---------------------------


; control params
gitimo_M init 0.8 ; vibr timeout
gkFscale_M init 80 ; freq span
gkFdepth_M init 0.05 ; vibr depth
giBaseF_M init 100 ; base freq
gkTamp_M init 0.5 ; total amp
gkLevel_M init 0.1 ; to be able to control level
;==========================================================================;
; Schottstaedt FM String Instrument from Dodge ;
;
;schedule "matti_3",0,10 ; NB! cannot be indefinite since uses p3!

instr matti_3

kattention chnget "attention1" ; 0..1 you may want to use port to smoothen it
kattegat port kattention,0.25
kdeckl linseg 0,p3/50,1,p3,1,p3/100,1
kattegat = kdeckl*kattegat ; declick
kvibfrq = kattegat
kampatt port kattegat,0.01 ; even slower changes
kpanL chnget "lb1" ; these may be both quite low, like 0.01
kpanR chnget "hb1"
kf1 port kpanL,0.5
kf2 port kpanR,0.45

kamp = kampatt
kfc line i(kf1),p3,i(kf2)
kfc = kfc*gkFscale_M + giBaseF_M
kfm1 = kfc
kfm2 = kfc*3
kfm3 = kfc*4
kindx1 = 7.5/log(kfc) ; RANGE FROM CA 2 TO 1
kindx2 = 15/sqrt(kfc) ; RANGE FROM CA 2.6 TO .5
kindx3 = 1.25/sqrt(kfc) ; RANGE FROM CA .2 TO .038
kvib init 0


timout 0,gitimo_M,transient ; DELAYS VIBRATO FOR p8 SECONDS

kvbctl linen 1,.5,p3-gitimo_M,.1 ; VIBRATO CONTROL ENVELOPE
krnd randi .0075,15 ; RANDOM DEVIATION IN VIB WIDTH
kvib oscili kvbctl*gkFdepth_M+krnd,kvibfrq*kvbctl,-1 ; VIBRATO GENERATOR

transient:
timout .2,p3,continue ; EXECUTE FOR .2 SECS ONLY
ktrans linseg 1,.15,0,1,0 ; TRANSIENT ENVELOPE

;anoise randi ktrans,.2*kfc ; NOISE...
;attack oscil anoise,2000,-1 ; ...CENTERED AROUND 2kHz
;perhaps:
anoise pinkish ktrans
ifreq random 1500,2500
kcutoff linseg ifreq,0.15, giBaseF_M
attack butterlp anoise, linseg:k(ifreq,0.15,giBaseF_M*2) ;butterbp anoise, ifreq, 50
attack balance attack, anoise ; to recover from the filter volume reduction

continue:

amod1 oscili kfm1*(kindx1+ktrans),kfm1,-1
amod2 oscili kfm2*(kindx2+ktrans),kfm2,-1
amod3 oscili kfm3*(kindx3+ktrans),kfm3,-1
asig oscili gkTamp_M*kamp,(kfc+amod1+amod2+amod3)*(1+kvib),-1
asig linen asig+attack,0.2,p3,0.3 
asig *= gkLevel_M ; to be able to control the level and mix with other instruments 
outs asig, asig 

endin





;; STEVEN

opcode adsr140_calc_coef, k, kk
  
  knum_samps, kratio xin
  xout exp( -log((1.0 + kratio) / kratio) / knum_samps)
    
endop

/* Gated, Re-triggerable ADSR modeled after the Doepfer A-140 */
opcode adsr140, a, aakkkk

agate, aretrig, kattack, kdecay, ksustain, krelease xin

kstate init 0  ; 0 = attack, 1 = decay, 2 = sustain
klasttrig init -1
kval init 0.0
asig init 0
kindx = 0

kattack_base init 0
kdecay_base init 0
krelease_base init 0

kattack_samps init 0
kdecay_samps init 0
krelease_samps init 0

kattack_coef init 0
kdecay_coef init 0
ksustain_coef init 0

klast_attack init -1
klast_decay init -1
klast_release init -1

if (klast_attack != kattack) then
  klast_attack = kattack
  kattack_samps = kattack * sr
  kattack_coef = adsr140_calc_coef(kattack_samps, 0.3)
  kattack_base = (1.0 + 0.3) * (1 - kattack_coef)
endif

if (klast_decay != kdecay) then
  klast_decay = kdecay
  kdecay_samps = kdecay * sr
  kdecay_coef = adsr140_calc_coef(kdecay_samps, 0.0001)
  kdecay_base = (ksustain - 0.0001) * (1.0 - kdecay_coef)
endif

if (klast_release != krelease) then
  klast_release = krelease
  krelease_samps = krelease * sr
  krelease_coef = adsr140_calc_coef(krelease_samps, 0.0001)
  krelease_base =  -0.0001 * (1.0 - krelease_coef)
endif


while (kindx < ksmps) do
  if (agate[kindx] > 0) then
    kretrig = aretrig[kindx]
    if (kretrig > 0 && klasttrig <= 0) then
      kstate = 0
    endif
    klasttrig = kretrig

    if (kstate == 0) then
      kval = kattack_base + (kval * kattack_coef)
      if(kval >= 1.0) then
        kval = 1.0
        kstate = 1
      endif
      asig[kindx] = kval

    elseif (kstate == 1) then
      kval = kdecay_base + (kval * kdecay_coef)
      if(kval <= ksustain) then
        kval = ksustain
        kstate = 2
      endif
      asig[kindx] = kval 

    else
      asig[kindx] = ksustain
    endif

  else ; in a release state
    kstate = 0
    if (kval == 0.0) then
      asig[kindx] = 0
    else 
    ; releasing
      kval = krelease_base + (kval * krelease_coef)
    if(kval <= 0.0) then
      kval = 0.0
    endif
    asig[kindx] = kval  
    endif

  endif

  kindx += 1
od

xout asig

endop

gi_sine ftgen 1,0, 4096, 10, 1

; demo instrument:
gkLevelSyi init 0.2 ; re-evaluate thes constants to change sound! 
gkPanSyi init 0.25

;schedule "syi",0,-1 ; turn on
/*
schedule -nstrnum("syi"),0,0 ; turn off
*/

ga_syi1 init 0
ga_syi2 init 0
gk_syi_failsafe init 0

chnset(0.03, "gate.freq")
chnset(200, "base.freq")

instr syi ; FM
	kattention chnget "attention1" ; 0..1
	krawValue chnget "raw1" ; anything, between -60000 and 60000

	if (abs(krawValue)<1000) then ; ignore big changes. or limit(kRawValue,-1000,1000)
		 kmod = (krawValue+1000)/1000 + 1 ; to tremble around 2.0
	endif
	kmod limit kmod, 0, 5
	
	klowBeta chnget "lb1" ; 0..1
	kmod += klowBeta
	kmod port kmod,0.1
	kindex = 1+klowBeta*10
	kindex port kindex,0.2
	
	kskin port chnget:k("skin1"),0.1
	aenv2 lfo 1-kskin, 1+10*(1-kskin),1 ; to give some pulsation
	
	kfreq = chnget:k("base.freq") +kattention*200
	kfreq += kmod*8
	kfreq port kfreq,0.25

    
	aenv = linenr:a(0.01,0.1,3,0.001) ; all envelopes should be with release (madsr, linenr etc)!
	
	agate = lfo(1.0, port(chnget:k("gate.freq") + (kmod * 0.02), 0.5)) ; + (kmod * 12))
	;agate = vco(1.0, port(chnget:k("gate.freq"), 0.25), 2, 0.75)
    aretrig init 0
	aenvMain = adsr140(agate, aretrig, 0.01, 3.75, 0.0, 3.0)
	asig = vco2(0.75, kfreq) + vco2(0.25, kfreq * 2 * klowBeta)
	asig = moogladder(asig * aenvMain, 400 + (3200 * aenvMain), 0.5)
    
	apulse = asig*aenv
	asig = 0.8*(asig+apulse)*port(gkLevelSyi,0.05)
	aL, aR pan2 asig, gkPanSyi
	ga_syi1 = aL
	ga_syi2 = aR
	;outs aL, aR
	;chnset aL, "syi.left"
	;chnset aR, "syi.right"
	
	if (gk_syi_failsafe == 1) then
	  turnoff
	endif

endin

instr syi_mixer
;aL  chnget "syi.left"
;aR  chnget "syi.right"

aL comb ga_syi1, 23.0, 8.2
aL comb aL, 40, 20
aR comb ga_syi2, 23.0, 8.2
aR comb aR, 40, 20

aL1, aR1 reverbsc aL, aR, 0.9, 2000

outs aL1, aR1
ga_syi1 = 0
ga_syi2 = 0

endin
schedule "syi_mixer",0,-1 ; turn on
/*
schedule -nstrnum("syi_mixer"),0,-1 ; turn off
*/




; schedule "enrico",0,5
; schedule  -nstrnum("enrico"),0,0
giSine =  -1
;=============================
instr enrico	; brain sing
;=============================

;if gk_trigger != 0 goto cont
;turnoff
;cont:
    
katn1		chnget "attention1"
khb1		chnget "hb1"
klb1		chnget "lb1"
kskin1	chnget "skin1"	
kraw1		chnget "raw1"

irise init 0.125
isus init 86400 - (2 * irise)
akenv linseg 0, irise, 1, isus, 1, irise, 0
akenvinv = 1 - akenv

; kpitch
if katn1 <= .4 then
kpitch	=	1.5
elseif katn1 > .4 then
kpitch	=	.8
endif
kpitch	port	kpitch, .1

; kverse
if kskin1 <= .4 then
kverse	=	1
elseif kskin1 > .4 then
kverse	=	-1
endif
kverse	port	kverse, .1

iskiptim	=	0
iwrap		=	1
asig		diskin2	"Brain_sing.wav", kpitch*kverse, iskiptim, iwrap	; original clip https://www.youtube.com/watch?v=eCKzNkW5GMI

; kamount
if khb1 <= .4 then
kamount	=	1
elseif khb1 > .4 then
kamount	=	.6
endif
kamount	port	kamount, .1

; kdrywet
if klb1 <= .4 then
kdrywet	=	1
elseif klb1 > .4 then
kdrywet	=	.1
endif
kdrywet	port	kdrywet, .1

kamountInv = 1 - kdrywet

; kfreq
kcps, kamp ptrack asig, 2^10
;printk	1, abs(kcps)
;printk	1, abs(kraw1), 10

if kcps <= 80 then
kfreq port	abs(kraw1), .1

elseif kcps > 80 then
kfreq1 	port	kcps, .1
kfreq  	= kfreq1 + (kfreq/2)
endif


afx 	oscili kamount, kfreq, giSine
afx = afx * asig
afx		=	(afx * kdrywet) + (asig  * kamountInv)
asig = (afx * akenv) + (akenvinv * asig)

outs asig *.7, asig *.7

endin

;=============================

;VICTOR:

instr V1
S1 sprintf "raw%d",int(p4)
prints S1
kraw chnget S1
araw upsamp kraw
kenv linenr 0dbfs*p5*0.001,1,0.1,0.01
	; tarmo changed (added noise):
	kfreq = 100+5000*chnget:k("skin1") 
	kfreq port kfreq,0.02, chnget:i("skin1") 
	
	anoise butterbp pinkish(0.6),kfreq,kfreq/4
	chnmix araw*kenv*anoise, "raw_audio"
endin

;schedule "V100",0,-1
instr V100 ; central control & mix
prints "V100"
khb1 chnget "hb1"
khb2 chnget "hb2"
khb3 chnget "hb3"
khb port (khb1+khb2+khb3)/3,0.1

araw chnget "raw_audio"
;araw *= khb ; may make it too small and unadible. I commented it out

      outs araw, araw

katt1 chnget "attention1"
kskin1 chnget "skin1"
if trigger(katt1,0.7,0)==1 then
printk2 katt1
event "i", "V1",0,rnd(3),1,kskin1
endif

katt2 chnget "attention2"
kskin2 chnget "skin2"
if trigger(katt2,0.7,0)==1 then
event "i", "V1",0,rnd(3),1,kskin2
endif

katt3 chnget "attention3"
kskin3 chnget "skin3"
if trigger(katt3,0.7,0)==1 then
event "i", "V1",0,rnd(3),1,kskin3
endif

chnclear "raw_audio"
endin

;; OEYVIND


#include "Oeyvind_include.inc"

        chnset 0.3, "levelOeyvind"
	chnset 0.9, "sc_Feed"
	chnset 7000, "sc_FiltFq"
	chnset 0.9, "sc_PitchMod"	
	chnset 0.0, "sc_Mix"
        chnset 900, "p_pitchModeThresh"
        chnset .1, "p_pitchModulate"
        chnset 1, "p_grModulate"

instr 18; sensor data mapping

        kraw1   chnget "raw1"
	katn1	chnget "attention1"
	khb1	chnget "hb1"
	klb1	chnget "lb1"
	kskin1  chnget "skin1"
        kpModeThresh chnget "p_pitchModeThresh"

        kpitchModulate chnget "p_pitchModulate"
        kgrModulate    chnget "p_grModulate"

        kpitch1         = cpsmidinn((katn1*kpitchModulate*12)+60)
        kgrLowRate1     = (khb1*kgrModulate*6)+4
        kpitchMode1     = (kraw1 > kpModeThresh ? 1 : 0)
        kpitch1         portk kpitch1, 0.1
        kgrLowRate1     portk kgrLowRate1, 0.1
	                chnset kpitch1, "p1_pitch"		
	                chnset kpitchMode1, "p1_pitchMode"		
	                chnset kgrLowRate1, "p1_grLowRate"	

        kpitch2         = cpsmidinn((klb1*kpitchModulate*12)+72)
        kgrLowRate2     = (kskin1*kgrModulate*5)+6
        kpitchMode2     = (kraw1 > kpModeThresh ? 1 : 0)
        kpitch2         portk kpitch2, 0.1
        kgrLowRate2     portk kgrLowRate2, 0.1
	                chnset kpitch2, "p2_pitch"		
	                chnset kpitchMode2, "p2_pitchMode"		
	                chnset kgrLowRate2, "p2_grLowRate"	
endin


;; Oeyvind event control *********
; set sync gravity
;                v, phaseGravity, rateGravity
schedule 12,1,1, 1, 0.01,           0.01
schedule 12,1,1, 2, 0.01,           0.01
schedule 12,1,1, 3, 0.001,           0.001

;                   v,  amp, atck, rel, ptch, lowRate, ptchMode
;schedule 201.1, 0, -1,1, -20,  1,    1,   65,   10,      0
;schedule -201.1, 0, 1

;schedule 201.2, 0, -1,2, -20,  1,    1,   63,   16,      0
;schedule -201.2, 0, 1

;schedule 201.3, 0, -1,3, -20,  1,    1,   84,   2,      0
;schedule -201.3, 0, 1

schedule 18, 1, -1
;schedule -18, 1, 1

;; End Oeyvind event control *********


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
