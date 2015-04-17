	; classic waveforms
	giSine		ftgen	0, 0, 65536, 10, 1					; sine wave
	giCosine	ftgen	0, 0, 8192, 9, 1, 1, 90					; cosine wave
	giTri		ftgen	0, 0, 8192, 7, 0, 2048, 1, 4096, -1, 2048, 0		; triangle wave 
	giHalfSine      ftgen   0, 0, 8193, 9, 0.5, 1, 0                		; half sine

	; grain envelope tables
	giSigmoRise 	ftgen	0, 0, 8193, 19, 0.5, 1, 270, 1				; rising sigmoid
	giSigmoFall 	ftgen	0, 0, 8193, 19, 0.5, 1, 90, 1				; falling sigmoid
	giExpFall	ftgen	0, 0, 8193, 5, 1, 8193, 0.00001				; exponential decay
	giTriangleWin 	ftgen	0, 0, 8193, 7, 0, 4096, 1, 4096, 0			; triangular window 

        giPanTab        ftgen   0, 0, 8, -2, 0.3, 0.8, 0.0, 1.0, 0.4, 0.6, 0.25, 0.75	; per voice panning



;******************************************************
; assign each generator to a master clock
		instr 11
	isyncto		= p4	; master
	iclockNum	= p5	; slave

	SmainSyncTo	sprintf "p%i_SyncTo", iclockNum
			chnset isyncto, SmainSyncTo
	SgrSyncTo	sprintf "grLfo%iSyncTo", iclockNum
			chnset isyncto, SgrSyncTo
	SformSyncTo	sprintf "formLfo%iSyncTo", iclockNum
			chnset isyncto, SformSyncTo
	SatckSyncTo	sprintf "atckLfo%iSyncTo", iclockNum
			chnset isyncto, SatckSyncTo
	SdurSyncTo	sprintf "durLfo%iSyncTo", iclockNum
			chnset isyncto, SdurSyncTo
		endin

;******************************************************
; set synchronization strength
		instr 12

	iclockNum	= p4
	iphaSyncGravity	= p5				; strength of phase synchronization
	irateSyncGravity = p6				; strength of rate synchronization

	SmainPhaSyGrav	sprintf "p%i_phaseSyncGravity", iclockNum
	SmainRateSyGrav sprintf "p%i_rateSyncGravity", iclockNum
			chnset iphaSyncGravity, SmainPhaSyGrav
			chnset irateSyncGravity, SmainRateSyGrav	

	SgrPhaSyGrav	sprintf "grLfo%iphaseSyncGravity", iclockNum
	SgrRateSyGrav 	sprintf "grLfo%irateSyncGravity", iclockNum
			chnset iphaSyncGravity, SgrPhaSyGrav
			chnset irateSyncGravity, SgrRateSyGrav	

	SformPhaSyGrav	sprintf "formLfo%iphaseSyncGravity", iclockNum
	SformRateSyGrav sprintf "formLfo%irateSyncGravity", iclockNum
			chnset iphaSyncGravity, SformPhaSyGrav
			chnset irateSyncGravity, SformRateSyGrav	

	SatckPhaSyGrav	sprintf "atckLfo%iphaseSyncGravity", iclockNum
	SatckRateSyGrav sprintf "atckLfo%irateSyncGravity", iclockNum
			chnset iphaSyncGravity, SatckPhaSyGrav
			chnset irateSyncGravity, SatckRateSyGrav	

	SdurPhaSyGrav	sprintf "durLfo%iphaseSyncGravity", iclockNum
	SdurRateSyGrav 	sprintf "durLfo%irateSyncGravity", iclockNum
			chnset iphaSyncGravity, SdurPhaSyGrav
			chnset irateSyncGravity, SdurRateSyGrav	


		endin

;******************************************************
; make slave generator approach (glide to) the parameter settings of the master
		instr 15

	imaster		= p4				; copy parameter values from master
	islave		= p5				; to slave
	ishape		= p6				; glide shape (transeg type, 0=linear)

	SampM		sprintf "p%i_amp", imaster		
;	SpitchM		sprintf "p%i_pitch", imaster		
	SgrLowRateM	sprintf "p%i_grLowRate", imaster	
	SpitchModeM	sprintf "p%i_pitchMode", imaster	
	SgRateDevAmtM	sprintf "p%i_gRateDevAmt", imaster	
	SgrLfoAmpM	sprintf "p%i_grLfoAmp", imaster	
	SgrLfoFreqM	sprintf "p%i_grLfoFreq", imaster	
	SformantOffsetM	sprintf "p%i_formantOffset", imaster	
	SformantFollowM	sprintf "p%i_formantFollow", imaster	
	SformLfoAmpM	sprintf "p%i_formLfoAmp", imaster	
	SformLfoFreqM	sprintf "p%i_formLfoFreq", imaster	
	Sa_d_ratioM	sprintf "p%i_a_d_ratio", imaster	
	SsustainM	sprintf "p%i_sustain", imaster	
	SatckLfoAmpM	sprintf "p%i_atckLfoAmp", imaster	
	SatckLfoFreqM	sprintf "p%i_atckLfoFreq", imaster	
	SrelDurM	sprintf "p%i_relDur", imaster	
	SdurLfoAmpM	sprintf "p%i_durLfoAmp", imaster	
	SdurLfoFreqM	sprintf "p%i_durLfoFreq", imaster	
	SdurDevAmtM	sprintf "p%i_durDevAmt", imaster	
	SrandommaskM	sprintf "p%i_randommask", imaster	
	SdistributionM	sprintf "p%i_distribution", imaster	
	SgChanDevAmtM	sprintf "p%i_gChanDevAmt", imaster	
	SpitchGlissM	sprintf "p%i_pitchGliss", imaster	
	SrndPitchGlissM	sprintf "p%i_rndPitchGliss", imaster	

	SampS		sprintf "p%i_amp", islave		
;	SpitchS		sprintf "p%i_pitch", islave		
	SgrLowRateS	sprintf "p%i_grLowRate", islave	
	SpitchModeS	sprintf "p%i_pitchMode", islave	
	SgRateDevAmtS	sprintf "p%i_gRateDevAmt", islave	
	SgrLfoAmpS	sprintf "p%i_grLfoAmp", islave	
	SgrLfoFreqS	sprintf "p%i_grLfoFreq", islave	
	SformantOffsetS	sprintf "p%i_formantOffset", islave	
	SformantFollowS	sprintf "p%i_formantFollow", islave	
	SformLfoAmpS	sprintf "p%i_formLfoAmp", islave	
	SformLfoFreqS	sprintf "p%i_formLfoFreq", islave	
	Sa_d_ratioS	sprintf "p%i_a_d_ratio", islave	
	SsustainS	sprintf "p%i_sustain", islave	
	SatckLfoAmpS	sprintf "p%i_atckLfoAmp", islave	
	SatckLfoFreqS	sprintf "p%i_atckLfoFreq", islave	
	SrelDurS	sprintf "p%i_relDur", islave	
	SdurLfoAmpS	sprintf "p%i_durLfoAmp", islave	
	SdurLfoFreqS	sprintf "p%i_durLfoFreq", islave	
	SdurDevAmtS	sprintf "p%i_durDevAmt", islave	
	SrandommaskS	sprintf "p%i_randommask", islave	
	SdistributionS	sprintf "p%i_distribution", islave	
	SgChanDevAmtS	sprintf "p%i_gChanDevAmt", islave	
	SpitchGlissS	sprintf "p%i_pitchGliss", islave	
	SrndPitchGlissS	sprintf "p%i_rndPitchGliss", islave	

	iampM		chnget	SampM			; amp
	;ipitchM	chnget 	SpitchM			; perceived pitch in cps
	igrLowRateM   	chnget 	SgrLowRateM		; grain rate if rate is low (if not defining pitch)
	ipitchModeM   	chnget 	SpitchModeM		; 0=gt, 1= gr
	igRateDevAmtM 	chnget 	SgRateDevAmtM		; grain rate random dev
	igrLfoAmpM 	chnget 	SgrLfoAmpM		; grain rate LFO amp
	igrLfoFreqM 	chnget 	SgrLfoFreqM		; grain rate LFO freq
	iformantOffsetM	chnget 	SformantOffsetM		; kwavfreq offset when in gr pitch mode
	iformantFollowM	chnget 	SformantFollowM		; kwavfreq as factor of kgrainfreq when in gr pitch mode
	iformLfoAmpM 	chnget 	SformLfoAmpM		; formant LFO amp (only in gr pitch mode)
	iformLfoFreqM 	chnget 	SformLfoFreqM		; formant LFO freq
	ia_d_ratioM 	chnget 	Sa_d_ratioM		; grain shape, balance between attack time and decay time
	isustainM 	chnget 	SsustainM		; grain shape, sustain duration
	iatckLfoAmpM 	chnget 	SatckLfoAmpM		; grain shape LFO amp
	iatckLfoFreqM 	chnget 	SatckLfoFreqM		; grain shape LFO freq
	irelDurM 	chnget 	SrelDurM		; grain duration
	idurLfoAmpM 	chnget 	SdurLfoAmpM		; grain dur LFO amp
	idurLfoFreqM 	chnget 	SdurLfoFreqM		; grain dur LFO freq
	idurDevAmtM 	chnget 	SdurDevAmtM		; grain dur random deviation
	irandommaskM 	chnget 	SrandommaskM		; random muting of single grains
	idistributionM 	chnget	SdistributionM		; grain random distribution in time
	igChanDevAmtM 	chnget 	SgChanDevAmtM		; output channel random dev
	ipitchGlissM 	chnget 	SpitchGlissM		; pitch glissando amount 
	irndPitchGlissM	chnget 	SrndPitchGlissM		; random pitch glissando amount

	iampS		chnget	SampS			; amp
	;ipitchS	chnget 	SpitchS			; perceived pitch in cps
	igrLowRateS   	chnget 	SgrLowRateS		; grain rate if rate is low (if not defining pitch)
	ipitchModeS   	chnget 	SpitchModeS		; 0=gt, 1= gr
	igRateDevAmtS 	chnget 	SgRateDevAmtS		; grain rate random dev
	igrLfoAmpS 	chnget 	SgrLfoAmpS		; grain rate LFO amp
	igrLfoFreqS 	chnget 	SgrLfoFreqS		; grain rate LFO freq
	iformantOffsetS	chnget 	SformantOffsetS		; kwavfreq offset when in gr pitch mode
	iformantFollowS	chnget 	SformantFollowS		; kwavfreq as factor of kgrainfreq when in gr pitch mode
	iformLfoAmpS 	chnget 	SformLfoAmpS		; formant LFO amp (only in gr pitch mode)
	iformLfoFreqS 	chnget 	SformLfoFreqS		; formant LFO freq
	ia_d_ratioS 	chnget 	Sa_d_ratioS		; grain shape, balance between attack time and decay time
	isustainS 	chnget 	SsustainS		; grain shape, sustain duration
	iatckLfoAmpS 	chnget 	SatckLfoAmpS		; grain shape LFO amp
	iatckLfoFreqS 	chnget 	SatckLfoFreqS		; grain shape LFO freq
	irelDurS 	chnget 	SrelDurS		; grain duration
	idurLfoAmpS 	chnget 	SdurLfoAmpS		; grain dur LFO amp
	idurLfoFreqS 	chnget 	SdurLfoFreqS		; grain dur LFO freq
	idurDevAmtS 	chnget 	SdurDevAmtS		; grain dur random deviation
	irandommaskS 	chnget 	SrandommaskS		; random muting of single grains
	idistributionS 	chnget	SdistributionS		; grain random distribution in time
	igChanDevAmtS 	chnget 	SgChanDevAmtS		; output channel random dev
	ipitchGlissS 	chnget 	SpitchGlissS		; pitch glissando amount 
	irndPitchGlissS	chnget 	SrndPitchGlissS		; random pitch glissando amount

	kamp		transeg iampS		, p3, ishape, iampM		
	;kpitch		transeg ipitchS		, p3, ishape, ipitchM		
	kgrLowRate   	transeg igrLowRateS   	, p3, ishape, igrLowRateM   	
	kpitchMode   	transeg ipitchModeS   	, p3, ishape, ipitchModeM   	
	kgRateDevAmt 	transeg igRateDevAmtS 	, p3, ishape, igRateDevAmtM 	
	kgrLfoAmp 	transeg igrLfoAmpS 	, p3, ishape, igrLfoAmpM 	
	kgrLfoFreq 	transeg igrLfoFreqS 	, p3, ishape, igrLfoFreqM 	
	kformantOffset 	transeg iformantOffsetS	, p3, ishape, iformantOffsetM	
	kformantFollow 	transeg iformantFollowS	, p3, ishape, iformantFollowM	
	kformLfoAmp 	transeg iformLfoAmpS 	, p3, ishape, iformLfoAmpM 	
	kformLfoFreq 	transeg iformLfoFreqS 	, p3, ishape, iformLfoFreqM 	
	ka_d_ratio 	transeg ia_d_ratioS 	, p3, ishape, ia_d_ratioM 	
	ksustain 	transeg isustainS 	, p3, ishape, isustainM 	
	katckLfoAmp 	transeg iatckLfoAmpS 	, p3, ishape, iatckLfoAmpM 	
	katckLfoFreq 	transeg iatckLfoFreqS 	, p3, ishape, iatckLfoFreqM 	
	krelDur 	transeg irelDurS 	, p3, ishape, irelDurM 		
	kdurLfoAmp 	transeg idurLfoAmpS 	, p3, ishape, idurLfoAmpM 	
	kdurLfoFreq 	transeg idurLfoFreqS 	, p3, ishape, idurLfoFreqM 	
	kdurDevAmt 	transeg idurDevAmtS 	, p3, ishape, idurDevAmtM 	
	krandommask 	transeg irandommaskS 	, p3, ishape, irandommaskM 	
	 kdistribution 	transeg idistributionS 	, p3, ishape, idistributionM 	
	kgChanDevAmt 	transeg igChanDevAmtS 	, p3, ishape, igChanDevAmtM 	
	kpitchGliss 	transeg ipitchGlissS 	, p3, ishape, ipitchGlissM 	
	krndPitchGliss 	transeg irndPitchGlissS	, p3, ishape, irndPitchGlissM	

			chnset	kamp,		SampS			; amp
			;chnset kpitch,		SpitchS			; perceived pitch in cps
			chnset 	kgrLowRate,   	SgrLowRateS		; grain rate if rate is low (if not defining pitch)
			chnset 	kpitchMode,   	SpitchModeS		; 0=gt, 1= gr
			chnset 	kgRateDevAmt, 	SgRateDevAmtS		; grain rate random dev
			chnset 	kgrLfoAmp, 	SgrLfoAmpS		; grain rate LFO amp
			chnset 	kgrLfoFreq, 	SgrLfoFreqS		; grain rate LFO freq
			chnset 	kformantOffset, SformantOffsetS		; kwavfreq offset when in gr pitch mode
			chnset 	kformantFollow, SformantFollowS		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset 	kformLfoAmp, 	SformLfoAmpS		; formant LFO amp (only in gr pitch mode)
			chnset 	kformLfoFreq, 	SformLfoFreqS		; formant LFO freq
			chnset 	ka_d_ratio, 	Sa_d_ratioS		; grain shape, balance between attack time and decay time
			chnset 	ksustain, 	SsustainS		; grain shape, sustain duration
			chnset 	katckLfoAmp, 	SatckLfoAmpS		; grain shape LFO amp
			chnset 	katckLfoFreq, 	SatckLfoFreqS		; grain shape LFO freq
			chnset 	krelDur, 	SrelDurS		; grain duration
			chnset 	kdurLfoAmp, 	SdurLfoAmpS		; grain dur LFO amp
			chnset 	kdurLfoFreq, 	SdurLfoFreqS		; grain dur LFO freq
			chnset 	kdurDevAmt, 	SdurDevAmtS		; grain dur random deviation
			chnset 	krandommask, 	SrandommaskS		; random muting of single grains
			chnset	 kdistribution, SdistributionS		; grain random distribution in time
			chnset 	kgChanDevAmt, 	SgChanDevAmtS		; output channel random dev
			chnset 	kpitchGliss, 	SpitchGlissS		; pitch glissando amount 
			chnset 	krndPitchGliss, SrndPitchGlissS		; random pitch glissando amount

		endin


;******************************************************
;******************************************************
; parameter control, set partikkel instrument template values
	instr 21	
;print p1, p4, p5
	iopcode_id	= p4
	instrTemplate	= p5
	kinstrTemplate	= instrTemplate
	includePitch	= p6	; also recall pitch parameter value (otherwise leave as is)
	includeLowRate	= p7	; also recall lowRate parameter value
	includeAmp	= p8	; also recall amp parameter value

	Samp		sprintf "p%i_amp", iopcode_id		
	Spitch		sprintf "p%i_pitch", iopcode_id		
	SgrLowRate	sprintf "p%i_grLowRate", iopcode_id	
	SpitchMode	sprintf "p%i_pitchMode", iopcode_id	
	SgRateDevAmt	sprintf "p%i_gRateDevAmt", iopcode_id	
	SgrLfoAmp	sprintf "p%i_grLfoAmp", iopcode_id	
	SgrLfoFreq	sprintf "p%i_grLfoFreq", iopcode_id	
	SformantOffset	sprintf "p%i_formantOffset", iopcode_id	
	SformantFollow	sprintf "p%i_formantFollow", iopcode_id	
	SformLfoAmp	sprintf "p%i_formLfoAmp", iopcode_id	
	SformLfoFreq	sprintf "p%i_formLfoFreq", iopcode_id	
	Sa_d_ratio	sprintf "p%i_a_d_ratio", iopcode_id	
	Ssustain	sprintf "p%i_sustain", iopcode_id	
	SatckLfoAmp	sprintf "p%i_atckLfoAmp", iopcode_id	
	SatckLfoFreq	sprintf "p%i_atckLfoFreq", iopcode_id	
	SrelDur		sprintf "p%i_relDur", iopcode_id	
	SdurLfoAmp	sprintf "p%i_durLfoAmp", iopcode_id	
	SdurLfoFreq	sprintf "p%i_durLfoFreq", iopcode_id	
	SdurDevAmt	sprintf "p%i_durDevAmt", iopcode_id	
	Srandommask	sprintf "p%i_randommask", iopcode_id	
	Sdistribution	sprintf "p%i_distribution", iopcode_id	
	SgChanDevAmt	sprintf "p%i_gChanDevAmt", iopcode_id	
	SpitchGliss	sprintf "p%i_pitchGliss", iopcode_id	
	SrndPitchGliss	sprintf "p%i_rndPitchGliss", iopcode_id	

	if instrTemplate == -1 then
	if includeAmp > 0 then
			chnset	(-6),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (4.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (1.0), 	SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (0.4), 	SgrLfoFreq		; grain rate LFO freq
			chnset (220), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (1.2), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0.0), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.25),	SformLfoFreq		; formant LFO freq
			chnset (0.5), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0.0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (0.3), 	SatckLfoFreq		; grain shape LFO freq
			chnset (0.5), 	SrelDur			; grain duration
			chnset (0.0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (0.3), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 0 then
	if includeAmp > 0 then
			chnset	(-8),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (1.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (0), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (1), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0.0), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.2), 	SformLfoFreq		; formant LFO freq
			chnset (0.5), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0.0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (2), 	SrelDur			; grain duration
			chnset (0.0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (0.8), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 1 then
	if includeAmp > 0 then
			chnset	(-6),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (1.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (0), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (1.2), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0.0), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.3), 	SformLfoFreq		; formant LFO freq
			chnset (0.5), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0.5), 	SatckLfoAmp		; grain shape LFO amp
			chnset (0.6), 	SatckLfoFreq		; grain shape LFO freq
			chnset (1), 	SrelDur			; grain duration
			chnset (0.0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (0.8), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 2 then
	if includeAmp > 0 then
			chnset	(-7),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (1.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (140), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (1), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0.0), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.3), 	SformLfoFreq		; formant LFO freq
			chnset (0.1), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (1.3), 	SrelDur			; grain duration
			chnset (0.3), 	SdurLfoAmp		; grain dur LFO amp
			chnset (0.7), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 3 then
	if includeAmp > 0 then
			chnset	(-7),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (1.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.02), SgrLfoAmp		; grain rate LFO amp
			chnset (4), 	SgrLfoFreq		; grain rate LFO freq
			chnset (0), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (2), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0.2), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.8), 	SformLfoFreq		; formant LFO freq
			chnset (0.5), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (0.8), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 4 then
	if includeAmp > 0 then
			chnset	(-7),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (1.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (0), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (4), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0.3), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.5), 	SformLfoFreq		; formant LFO freq
			chnset (0.5), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (1), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 5 then
	if includeAmp > 0 then
			chnset	(-6),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (1.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (500), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (0.7), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (1), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (1), 	SformLfoFreq		; formant LFO freq
			chnset (0.5), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (1), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 6 then
	if includeAmp > 0 then
			chnset	(-6),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (1.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (600), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (1.8), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (1), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.6), 	SformLfoFreq		; formant LFO freq
			chnset (0.2), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0.05), SatckLfoAmp		; grain shape LFO amp
			chnset (0.6), 	SatckLfoFreq		; grain shape LFO freq
			chnset (0.3), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 7 then
	if includeAmp > 0 then
			chnset	(-6),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (1.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.015),SgrLfoAmp		; grain rate LFO amp
			chnset (6), 	SgrLfoFreq		; grain rate LFO freq
			chnset (200), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (24), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (1), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.2), 	SformLfoFreq		; formant LFO freq
			chnset (0.5), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0.1), 	SatckLfoAmp		; grain shape LFO amp
			chnset (0.2), 	SatckLfoFreq		; grain shape LFO freq
			chnset (0.1), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
;*** (template 8),9),10 available) ***
	elseif instrTemplate == 11 then
	if includeAmp > 0 then
			chnset	(-7),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (0.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (0), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (4), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (1), 	SformLfoFreq		; formant LFO freq
			chnset (0), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (1), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 12 then
	if includeAmp > 0 then
			chnset	(-6),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (0.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (0), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (1.2), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (1), 	SformLfoFreq		; formant LFO freq
			chnset (0.5), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (0.7), 	SrelDur			; grain duration
			chnset (0.3), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1.3), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 13 then
	if includeAmp > 0 then
			chnset	(-7),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (0.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.02), SgrLfoAmp		; grain rate LFO amp
			chnset (4), 	SgrLfoFreq		; grain rate LFO freq
			chnset (0), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (2), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0.2), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.8), 	SformLfoFreq		; formant LFO freq
			chnset (0), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0.9), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (0.8), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 14 then
	if includeAmp > 0 then
			chnset	(-7),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (0.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (110), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (1), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0.3), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.5), 	SformLfoFreq		; formant LFO freq
			chnset (0.03), Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (1.1), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 15 then
	if includeAmp > 0 then
			chnset	(-6),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (0.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (500), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (0.7), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (1), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (1), 	SformLfoFreq		; formant LFO freq
			chnset (0), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (0.6), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 16 then
	if includeAmp > 0 then
			chnset	(-6),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (220), 	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (7.0), 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (0.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (1), 	SgrLfoFreq		; grain rate LFO freq
			chnset (600), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (1.8), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (0), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.6), 	SformLfoFreq		; formant LFO freq
			chnset (0), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (0.3), 	SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	elseif instrTemplate == 17 then
	if includeAmp > 0 then
			chnset	(-6),	Samp			; amp
	endif
	if includePitch > 0 then
			chnset (1220),	Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset (17.0),	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset (0.0),  SpitchMode		; 0=gt, 1= gr
			chnset (0.0), 	SgRateDevAmt		; grain rate random dev
			chnset (0.0), 	SgrLfoAmp		; grain rate LFO amp
			chnset (6), 	SgrLfoFreq		; grain rate LFO freq
			chnset (200), 	SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset (24), 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset (1), 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset (0.1), 	SformLfoFreq		; formant LFO freq
			chnset (0), 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset (0), 	Ssustain		; grain shape, sustain duration
			chnset (0), 	SatckLfoAmp		; grain shape LFO amp
			chnset (1), 	SatckLfoFreq		; grain shape LFO freq
			chnset (0.15), SrelDur			; grain duration
			chnset (0), 	SdurLfoAmp		; grain dur LFO amp
			chnset (1), 	SdurLfoFreq		; grain dur LFO freq
			chnset (0.0), 	SdurDevAmt		; grain dur random deviation
			chnset (0.0), 	Srandommask		; random muting of single grains
			chnset (0.0), 	Sdistribution		; grain random distribution in time
			chnset (0.0), 	SgChanDevAmt		; output channel random dev
			chnset (0), 	SpitchGliss		; pitch glissando amount 
			chnset (0), 	SrndPitchGliss		; random pitch glissando amount
	else
			Serror		sprintf "Instrument template error: no template %f", instrTemplate
			puts		Serror, 1
	endif
	endin

;******************************************************
; partikkel instrument parameter control, set value
	instr 22	
	iopcode_id	= p4
	Sparm		strget p5
        ;puts Sparm, 1
	kval		= p6
	Sname		sprintf "p%i_", iopcode_id		
	Sname		strcat Sname, Sparm
	; special mapping (note number to cps) of pitch parameter
	isPitch		strrindex Sname, "pitch"
	kisPitch	= isPitch
	if kisPitch >= 0 then
	kval		= cpsmidinn(kval)
	endif
			chnset kval, Sname
	endin

;******************************************************
; partikkel instrument parameter control, glide to new value 
	instr 23	
	iopcode_id	= p4
	Sparm		strget p5
	inew		= p6
	ishape		= p7	; glide shape (transeg type, 0=linear)
	Sname		sprintf "p%i_", iopcode_id		
	Sname		strcat Sname, Sparm
	; special mapping (note number to cps) of pitch parameter
	isPitch		strrindex Sname, "pitch"
	if isPitch >= 0 then
	inew		= cpsmidinn(inew)
	endif
	iold		chnget Sname
	kval		transeg iold, p3, ishape, inew
			chnset kval, Sname
	endin

;******************************************************
; (any) parameter control, set single value
	instr 30	
	Sname		strget p4
	kval		= p5
	; special mapping (note mumer to cps) of pitch parameter
	isPitch		strrindex Sname, "pitch"
	kisPitch	= isPitch
	if kisPitch >= 0 then
	kval		= cpsmidinn(kval)
	endif
			chnset kval, Sname
	endin

;******************************************************
; (any) parameter control, glide to new value 
	instr 31	
	Sname		strget p4
	inew		= p5
	ishape		= p6	; glide shape (transeg type, 0=linear)
	iold		chnget Sname
	kval		transeg iold, p3, ishape, inew
			chnset kval, Sname
	endin

;******************************************************
; filter all parameter changes for a partikkel generator voice
	instr 40	
	iopcode_id	= p4
	ifilterFq	= p5
	includePitch	= p6	; also do pitch filtering (otherwise, leave pitch value unfiltered)
	includeLowRate	= p7	; also do lowRate filtering
;print p1, p2, p3, p4, p5
	Samp		sprintf "p%i_amp", iopcode_id		
	Spitch		sprintf "p%i_pitch", iopcode_id		
	SgrLowRate	sprintf "p%i_grLowRate", iopcode_id	
	SpitchMode	sprintf "p%i_pitchMode", iopcode_id	
	SgRateDevAmt	sprintf "p%i_gRateDevAmt", iopcode_id	
	SgrLfoAmp	sprintf "p%i_grLfoAmp", iopcode_id	
	SgrLfoFreq	sprintf "p%i_grLfoFreq", iopcode_id	
	SformantOffset	sprintf "p%i_formantOffset", iopcode_id	
	SformantFollow	sprintf "p%i_formantFollow", iopcode_id	
	SformLfoAmp	sprintf "p%i_formLfoAmp", iopcode_id	
	SformLfoFreq	sprintf "p%i_formLfoFreq", iopcode_id	
	Sa_d_ratio	sprintf "p%i_a_d_ratio", iopcode_id	
	Ssustain	sprintf "p%i_sustain", iopcode_id	
	SatckLfoAmp	sprintf "p%i_atckLfoAmp", iopcode_id	
	SatckLfoFreq	sprintf "p%i_atckLfoFreq", iopcode_id	
	SrelDur		sprintf "p%i_relDur", iopcode_id	
	SdurLfoAmp	sprintf "p%i_durLfoAmp", iopcode_id	
	SdurLfoFreq	sprintf "p%i_durLfoFreq", iopcode_id	
	SdurDevAmt	sprintf "p%i_durDevAmt", iopcode_id	
	Srandommask	sprintf "p%i_randommask", iopcode_id	
	Sdistribution	sprintf "p%i_distribution", iopcode_id	
	SgChanDevAmt	sprintf "p%i_gChanDevAmt", iopcode_id	
	SpitchGliss	sprintf "p%i_pitchGliss", iopcode_id	
	SrndPitchGliss	sprintf "p%i_rndPitchGliss", iopcode_id	

	kamp		chnget	Samp			; amp
	kpitch		chnget 	Spitch			; perceived pitch in cps
	kgrLowRate   	chnget 	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	kpitchMode   	chnget 	SpitchMode		; 0=gt, 1= gr
	kgRateDevAmt 	chnget 	SgRateDevAmt		; grain rate random dev
	kgrLfoAmp 	chnget 	SgrLfoAmp		; grain rate LFO amp
	kgrLfoFreq 	chnget 	SgrLfoFreq		; grain rate LFO freq
	kformantOffset 	chnget 	SformantOffset		; kwavfreq offset when in gr pitch mode
	kformantFollow 	chnget 	SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
	kformLfoAmp 	chnget 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
	kformLfoFreq 	chnget 	SformLfoFreq		; formant LFO freq
	ka_d_ratio 	chnget 	Sa_d_ratio		; grain shape, balance between attack time and decay time
	ksustain 	chnget 	Ssustain		; grain shape, sustain duration
	katckLfoAmp 	chnget 	SatckLfoAmp		; grain shape LFO amp
	katckLfoFreq 	chnget 	SatckLfoFreq		; grain shape LFO freq
	krelDur 	chnget 	SrelDur			; grain duration
	kdurLfoAmp 	chnget 	SdurLfoAmp		; grain dur LFO amp
	kdurLfoFreq 	chnget 	SdurLfoFreq		; grain dur LFO freq
	kdurDevAmt 	chnget 	SdurDevAmt		; grain dur random deviation
	krandommask 	chnget 	Srandommask		; random muting of single grains
	kdistribution 	chnget	Sdistribution		; grain random distribution in time
	kgChanDevAmt 	chnget 	SgChanDevAmt		; output channel random dev
	kpitchGliss 	chnget 	SpitchGliss		; pitch glissando amount 
	krndPitchGliss 	chnget 	SrndPitchGliss		; random pitch glissando amount

	kamp		tonek kamp, ifilterFq
	kpitch		tonek kpitch, ifilterFq		
	kgrLowRate   	tonek kgrLowRate, ifilterFq   	
	kpitchMode   	tonek kpitchMode, ifilterFq   	
	kgRateDevAmt 	tonek kgRateDevAmt, ifilterFq 	
	kgrLfoAmp 	tonek kgrLfoAmp, ifilterFq 	
	kgrLfoFreq 	tonek kgrLfoFreq, ifilterFq 	
	kformantOffset 	tonek kformantOffset, ifilterFq 	
	kformantFollow 	tonek kformantFollow, ifilterFq 	
	kformLfoAmp 	tonek kformLfoAmp, ifilterFq 	
	kformLfoFreq 	tonek kformLfoFreq, ifilterFq 	
	ka_d_ratio 	tonek ka_d_ratio, ifilterFq 	
	ksustain 	tonek ksustain, ifilterFq 	
	katckLfoAmp 	tonek katckLfoAmp, ifilterFq 	
	katckLfoFreq 	tonek katckLfoFreq, ifilterFq 	
	krelDur 	tonek krelDur, ifilterFq 	
	kdurLfoAmp 	tonek kdurLfoAmp, ifilterFq 	
	kdurLfoFreq 	tonek kdurLfoFreq, ifilterFq 	
	kdurDevAmt 	tonek kdurDevAmt, ifilterFq 	
	krandommask 	tonek krandommask, ifilterFq 	
	kdistribution 	tonek kdistribution, ifilterFq 	
	kgChanDevAmt 	tonek kgChanDevAmt, ifilterFq 	
	kpitchGliss 	tonek kpitchGliss, ifilterFq 	
	krndPitchGliss 	tonek krndPitchGliss, ifilterFq 	

	; do not write back to the same chn before the filters have stabilized (within 1% deviation of the former value)
	kwrite		init 0
	ktest		= 1
	ktest		tonek ktest, ifilterFq
	if ktest > 0.99 then
	kwrite		= 1
	endif
	if kwrite < 1 goto nowrite

			chnset	kamp,		Samp			; amp
	if includePitch > 0 then
			chnset  kpitch,		Spitch			; perceived pitch in cps
	endif
	if includeLowRate > 0 then
			chnset 	kgrLowRate,   	SgrLowRate		; grain rate if rate is low (if not defining pitch)
	endif
			chnset 	kpitchMode,   	SpitchMode		; 0=gt, 1= gr
			chnset 	kgRateDevAmt, 	SgRateDevAmt		; grain rate random dev
			chnset 	kgrLfoAmp, 	SgrLfoAmp		; grain rate LFO amp
			chnset 	kgrLfoFreq, 	SgrLfoFreq		; grain rate LFO freq
			chnset 	kformantOffset, SformantOffset		; kwavfreq offset when in gr pitch mode
			chnset 	kformantFollow, SformantFollow		; kwavfreq as factor of kgrainfreq when in gr pitch mode
			chnset 	kformLfoAmp, 	SformLfoAmp		; formant LFO amp (only in gr pitch mode)
			chnset 	kformLfoFreq, 	SformLfoFreq		; formant LFO freq
			chnset 	ka_d_ratio, 	Sa_d_ratio		; grain shape, balance between attack time and decay time
			chnset 	ksustain, 	Ssustain		; grain shape, sustain duration
			chnset 	katckLfoAmp, 	SatckLfoAmp		; grain shape LFO amp
			chnset 	katckLfoFreq, 	SatckLfoFreq		; grain shape LFO freq
			chnset 	krelDur, 	SrelDur			; grain duration
			chnset 	kdurLfoAmp, 	SdurLfoAmp		; grain dur LFO amp
			chnset 	kdurLfoFreq, 	SdurLfoFreq		; grain dur LFO freq
			chnset 	kdurDevAmt, 	SdurDevAmt		; grain dur random deviation
			chnset 	krandommask, 	Srandommask		; random muting of single grains
			chnset	 kdistribution, Sdistribution		; grain random distribution in time
			chnset 	kgChanDevAmt, 	SgChanDevAmt		; output channel random dev
			chnset 	kpitchGliss, 	SpitchGliss		; pitch glissando amount 
			chnset 	krndPitchGliss, SrndPitchGliss		; random pitch glissando amount
nowrite:
	endin

;******************************************************
; filter parameter changes for a single parameter in a partikkel generator voice
	instr 41	
	iopcode_id	= p4
	Sparm		strget p5
	Sname		sprintf "p%i_", iopcode_id		
	Sname		strcat Sname, Sparm
	ifilterFq	= p6
	kval		chnget Sname			
	kval		tonek kval, ifilterFq		

	; do not write back to the same chn before the filter have stabilized (within 1% deviation of the former value)
	kwrite		init 0
	ktest		= 1
	ktest		tonek ktest, ifilterFq
	if ktest > 0.99 then
	kwrite		= 1
	endif
	if kwrite < 1 goto nowrite

			chnset kval, Sname	
nowrite:
	endin

instr 101
	kattention chnget "attention1" ; 0..1
	krawValue chnget "raw1" ; anything, between -60000 and 60000
	klowBeta chnget "lb1" ; 0..1
	khighBeta chnget "lb1" ; 0..1
	kskin port chnget:k("skin1"),0.1

	aenv linenr 0.01,0.1,3,0.001 ; all envelopes should be with release (madsr, linenr etc)!
	amp     = aenv * kattention
	kfreq   = 880*klowBeta
	asig oscili aenv, kfreq, giSine
	outs asig, asig
  endin
;******************************************************
; partikkel generator 
		instr 201
print p1, p2, p3, p4, p5, p6, p7, p8,p9

	iopcode_id	= p4						; id of opcode, linking partikkel to partikkelsync
	ichan		= iopcode_id
	iamp            = ampdbfs(p5)
	iattackTime	= p6
	ireleaseTime	= p7
	kenv		linsegr 0, iattackTime, 1, ireleaseTime, 0 ; fade in and out
	kenv		= kenv*kenv*iamp
	ipitch		= p8
	if ipitch > 0 then
	Skpitch		sprintf "p%i_pitch", ichan		
			chnset 	cpsmidinn(ipitch), Skpitch		; perceived pitch in cps
	endif
	ilowRate	= p9
	if ilowRate > 0 then
	SkgrLowRate	sprintf "p%i_grLowRate", ichan		
			chnset 	ilowRate, SkgrLowRate			; grain rate (if low)
	endif
	
	ipitchMode= p10
;	if ipitchMode > 0 then
	SkpitchMode	sprintf "p%i_pitchMode", ichan		
			chnset 	ipitchMode, SkpitchMode			; pitch mode (if 1)
;	endif


; create control channel names and get parameter values
	Skamp		sprintf	"p%i_amp", ichan
	Skpitch		sprintf "p%i_pitch", ichan		
	SkgrLowRate	sprintf "p%i_grLowRate", ichan		
	SkpitchMode	sprintf "p%i_pitchMode", ichan		
	SkgRateDevAmt	sprintf "p%i_gRateDevAmt", ichan	
	SkgrLfoAmp	sprintf "p%i_grLfoAmp", ichan		
	SkgrLfoFreq	sprintf "p%i_grLfoFreq", ichan		
	SkformantOffset	sprintf "p%i_formantOffset", ichan	
	SkformantFollow	sprintf "p%i_formantFollow", ichan	
	SkformLfoAmp	sprintf "p%i_formLfoAmp", ichan	
	SkformLfoFreq	sprintf "p%i_formLfoFreq", ichan	
	Ska_d_ratio	sprintf "p%i_a_d_ratio", ichan		
	Sksustain	sprintf "p%i_sustain", ichan		
	SkatckLfoAmp	sprintf "p%i_atckLfoAmp", ichan		
	SkatckLfoFreq	sprintf "p%i_atckLfoFreq", ichan	
	SkrelDur	sprintf "p%i_relDur", ichan		
	SkdurLfoAmp	sprintf "p%i_durLfoAmp", ichan		
	SkdurLfoFreq	sprintf "p%i_durLfoFreq", ichan		
	SkdurDevAmt	sprintf "p%i_durDevAmt", ichan		
	Skrandommask	sprintf "p%i_randommask", ichan		
	Skdistribution	sprintf "p%i_distribution", ichan	
	SkgChanDevAmt	sprintf "p%i_gChanDevAmt", ichan	
	SkpitchGliss	sprintf "p%i_pitchGliss", ichan		
	SkrndPitchGliss	sprintf "p%i_rndPitchGliss", ichan	

	kamp		chnget	Skamp		; amp
	kpitch		chnget 	Skpitch		; perceived pitch in cps
	kgrLowRate	chnget 	SkgrLowRate	; grain rate if rate is low (if not defining pitch)
	kpitchMode	chnget 	SkpitchMode	; 0=gt, 1= gr
	kgRateDevAmt	chnget 	SkgRateDevAmt	; grain rate random dev
	kgrLfoAmp	chnget 	SkgrLfoAmp	; grain rate LFO amp
	kgrLfoFreq	chnget 	SkgrLfoFreq	; grain rate LFO freq
	kformantOffset	chnget 	SkformantOffset	; kwavfreq offset when in gr pitch mode
	kformantFollow	chnget 	SkformantFollow	; kwavfreq as factor of kgrainfreq when in gr pitch mode
	kformLfoAmp	chnget 	SkformLfoAmp	; formant LFO amp (only in gr pitch mode)
	kformLfoFreq	chnget 	SkformLfoFreq	; formant LFO freq
	ka_d_ratio	chnget 	Ska_d_ratio	; grain shape, balance between attack time and decay time
	ksustain	chnget 	Sksustain	; grain shape, balance between attack time and decay time
	katckLfoAmp	chnget 	SkatckLfoAmp	; grain shape LFO amp
	katckLfoFreq	chnget 	SkatckLfoFreq	; grain shape LFO freq
	krelDur		chnget 	SkrelDur	; grain duration
	kdurLfoAmp	chnget 	SkdurLfoAmp	; grain dur LFO amp
	kdurLfoFreq	chnget 	SkdurLfoFreq	; grain dur LFO freq
	kdurDevAmt	chnget 	SkdurDevAmt	; grain dur random deviation
	krandommask	chnget 	Skrandommask	; random muting of single grains
	kdistribution	chnget 	Skdistribution	; grain random distribution in time
	kgChanDevAmt	chnget 	SkgChanDevAmt	; output channel random dev
	kpitchGliss	chnget 	SkpitchGliss	; pitch glissando amount 
	krndPitchGliss	chnget 	SkrndPitchGliss	; random pitch glissando amount

; clock sync setup
	SmainSyncTo	sprintf "p%i_SyncTo", iopcode_id
	;puts SmainSyncTo, 1
	kmainSyncTo	chnget SmainSyncTo
	;Stest sprintfk "%s %f", SmainSyncTo, kmainSyncTo
	;puts Stest,kmainSyncTo+10

	kupdateMaSyncTo	changed kmainSyncTo					; on change of master clock source
	if kupdateMaSyncTo > 0 then
	reinit mainSyncTo
	endif
	mainSyncTo:
	Smaster		sprintf "p%i_clock", i(kmainSyncTo)			; set master clock source
	Sactive		sprintf "p%i_active", i(kmainSyncTo)
	aclockExt	chnget Smaster						; read master clock tick
	kclockExt	downsamp aclockExt, ksmps				; average and scale 
	kclockExt	= kclockExt*ksmps					; for correct downsampling of pulse
	ksyncActive	chnget Sactive						; read flag to check if master clock is still running
	rireturn
	
	kclockIntern	init 0							; init slave clock pulse 
	kphase		init 0
	kOne		= 1							; needed for writing constant to chn at k-rate
	kZero		= 0							; -"-

	SactiveSelf	sprintf "p%i_active", iopcode_id			
			chnset kOne, SactiveSelf				; set flag to tell that this clock is still running (useful if another oscillator is using it as master)
			xtratim 2/kr
	kreleaseFlag	release
	if kreleaseFlag > 0 then
			chnset kZero, SactiveSelf				; set flag to tell that this clock is now stopping (useful if another oscillator is using it as master)	
	endif									; the syncActive variable is needed to prevent oscillator rate change (drop to zero) when master clock stops
										; The clock is meant to continue at unchanged rate if no sync is received


; parameter input
	kamp		= ampdbfs(kamp)*kenv*ampdbfs((-kpitch)/200)		; chn amp, envelope, and (a slight) inverse pitch to amp mapping

; grain rate
	kgrainrate	= (kpitch*kpitchMode)+(kgrLowRate*(1-kpitchMode))	; number of grains per second
	kgrainrateFlex	init 0	
	kupdateGrRate	changed kgrainrate
	if kupdateGrRate > 0 then						; our internal frequency vaule may vary as it drifts to sync, so...
	kgrainrateFlex	= kgrainrate						; update only when external grainrate control signal changes
	endif
	kgrainrateRdev	randh 0.01, kgrainrateFlex, 2				; random deviation
	kgrainrateRdev	= powoftwo(kgrainrateRdev*kgRateDevAmt)			; exponential scale, center LFO around 1.0

	SgrLfoName	= "grLfo"
	SgrSyncTo	sprintf "%iSyncTo", iopcode_id
	SgrSyncTo	strcat SgrLfoName, SgrSyncTo
	kgrsyncTo	chnget SgrSyncTo
	igrphase	= 0.5
	kgrLfo		oscil 1, kgrLfoFreq, giSine; igrphase, SgrLfoName, iopcode_id, kgrsyncTo ; grain rate LFO
	kgrLfoScale	= tanh(kgrLfoFreq)					; empirical trick to scale LFO amount according to LFO frequency 
										; (low LFO freq allows more time to modulate the clock speed 
										; so we need to compensate to make for a similar amount of modulation at all frequencies)
	kgrLfo		= kgrLfo*kgrLfoAmp*0.035*kgrLfoScale
	kgrLfo		= powoftwo(kgrLfo)					; exponential scale, center LFO around 1.0
	kgrainrateFlex	= (kgrainrateFlex*kgrLfo*kgrainrateRdev)
	kgrainrateFlex	= (abs(kgrainrateFlex) < 0.1 ? 0.1 : kgrainrateFlex)	; ensure that the clock never stops no matter how it is modulated

; grain pitch
	SformLfoName	= "formLfo"
	SformSyncTo	sprintf "%iSyncTo", iopcode_id
	SformSyncTo	strcat SformLfoName, SformSyncTo
	kformsyncTo	chnget SformSyncTo
	iformphase	= 0.5
	kformLfo	oscil 1, kformLfoFreq, giSine;iformphase, SformLfoName, iopcode_id, kformsyncTo ; grain pitch LFO
	kformLfo	= kformLfo*kformLfoAmp
	kformLfo	= kformLfo + 1						; center LFO around 1.0
	kwavfreq	= (kformantOffset+\
			  (kgrainrateFlex*kformantFollow*kformLfo))*kpitchMode+\; if in gr mode, link grain pitch to grain rate,
			  (kpitch*(1-kpitchMode))				; if in gr mode, use pitch parameter to specify
	
	kwaveform1	= giSine;
	kwaveform2	= giSine;
	kwaveform3	= giSine;
	kwaveform4	= giSine;
;	kLen1		tableng	kwaveform1			; use for sampled waveforms (only!!)
;	kwavfreq	= (kwavfreq/440)*(sr/kLen1)		; use for sampled waveforms (only!!)


; grain shape
	SatckLfoName	= "atckLfo"
	SatckSyncTo	sprintf "%iSyncTo", iopcode_id
	SatckSyncTo	strcat SatckLfoName, SatckSyncTo
	katcksyncTo	chnget SatckSyncTo
	iatckphase	= 0.5
	katckLfo	oscil 1, katckLfoFreq, giSine;iatckphase, SatckLfoName, iopcode_id, katcksyncTo ; grain shape LFO
	katckLfo	= katckLfo*katckLfoAmp
	ka_d_ratio      chnget "a_d_override"
	ka_d_ratio	= ka_d_ratio+katckLfo					; add LFO as explicit value
	ksustain_amount	= ksustain
	ienv_attack	= giSigmoRise 						; grain attack shape (from table)
	ienv_decay	= giSigmoFall 						; grain decay shape (from table)
	;printk2 ka_d_ratio
	;puts Ska_d_ratio, 1

; grain dur
	kduration	= (krelDur*1000)/kgrainrateFlex				; grain dur in milliseconds, relative to grain rate
	;printk2 krelDur, 10
	;puts SkrelDur, 1
	;printk2 kduration, 20
	SdurLfoName	= "durLfo"
	SdurSyncTo	sprintf "%iSyncTo", iopcode_id
	SdurSyncTo	strcat SdurLfoName, SdurSyncTo
	kdursyncTo	chnget SdurSyncTo
	idurphase	= 0.5
	kdurLfo		oscil 1, kdurLfoFreq, giSine;idurphase, SdurLfoName, iopcode_id, kdursyncTo ; grain dur LFO
	kdurLfo		= kdurLfo*kdurLfoAmp
	kdurLfo		= kdurLfo + 1						; center LFO around 1.0
	kdurationDev	randh 1, kgrainrateFlex, 2				; random deviation
	kduration	= (kduration*kdurLfo)+\					; add LFO and random dev as percentage of value
			  (kduration*kdurationDev*kdurDevAmt)			

; sweep
	ksweepshape		= 0.9						; grain wave pitch sweep shape (sweep speed), 0.5 is linear sweep
	iwavfreqstarttab 	ftgentmp	0, 0, 16, -2, 0, 0,   1		; start freq scalers, per grain
	iwavfreqendtab		ftgentmp	0, 0, 16, -2, 0, 0,   1		; end freq scalers, per grain
	kStartFreq		randh	krndPitchGliss, kgrainrateFlex		; random start frequency multiplier
	kStartFreq		= 1+(kpitchGliss+kStartFreq)			; offset, center multiplier at 1
				tablew	kStartFreq, 2, iwavfreqstarttab		; write start freq multiplier to table
; distribution and masking
	idisttab	ftgentmp	0, 0, 16, 16, 1, 16, -10, 0		; probability distribution for random grain masking
	igainmasks	ftgentmp	0, 0, 16, -2, 0, 0,   1			; gain masking table
	ichannelmasks	ftgentmp	0, 0, 16, -2, 0, 0,   0			; channel masking table
	iwaveamptab	ftgentmp	0, 0, 32, -2, 0, 0,   1,1,1,1,0		; wave mix masking

; channel masking modification
			tablew	((kgrainrateRdev*0.5)+0.5)*kgChanDevAmt, 2, ichannelmasks

; misc defaults
	asamplepos	= 0
	awavfm		= 0
	icosine		= giCosine						; needs to be a cosine wave to create trainlets
	kTrainCps	= kgrainrateFlex					; set cps equal to grain freq, creating a single cycle of a trainlet inside each grain
	knumpartials	= 7							; number of partials in trainlet
	kchroma		= 3							; chroma, falloff of partial amplitude towards sr/2

; clock sync

if kmainSyncTo == iopcode_id then						; (if it is not synced to any external clock)
	async		= 0.0							; set the sync input 
else
	; phase sync

	SphaSyncGravity	sprintf "p%i_phaseSyncGravity", iopcode_id
	kphaSyncGravity chnget SphaSyncGravity					; strength of synchronization
	aphase		init 0					
	asyncPolarity	limit (int(aphase*2)*2)-1, -1, 1
	asyncStrength	= abs(abs(aphase-0.5)-0.5)*asyncPolarity
	; use the phase of partikkelsync instance 2 to find sync polarity for partikkel instance 2.
	; If the phase of instance 2 is less than 0.5, we want to nudge it down when synchronizing,
	; and if the phase is > 0.5 we want to nudge it upwards.
	async		= aclockExt*kphaSyncGravity*asyncStrength  		; prepare sync signal with polarity and strength

	; rate sync
	SrateSyncGravity sprintf "p%i_rateSyncGravity", iopcode_id
	krateSyncGravity chnget SrateSyncGravity		     		; strength of synchronization
	krateSyncGravity = krateSyncGravity*ksyncActive				; do not change rate if master clock has stopped, as that would slowly stop this oscillator as well
	ksyncPulseCount	init 0
	ksyncPulseCount	= ksyncPulseCount + kclockExt				; count the number of master clock pulses within this (slave)clock period
	ksyncRateDev	init 0
	ksyncStrength	downsamp asyncStrength
	ksyncRateDev	= ksyncRateDev + (ksyncStrength*kclockExt)		; get the sum of deviations within this (slave)clock period

  	if kclockIntern > 0 then 						; adjust rate only on slave clock tick
    	    if ksyncPulseCount == 0 then					; if no master clock ticks, my tempo is too high
	        krateAdjust = -krateSyncGravity
    	    elseif ksyncPulseCount > 1 then					; if more than one master clock tick, my tempo is too low
	        krateAdjust = krateSyncGravity
    	    elseif ksyncPulseCount == 1 then					; if exactly one master clock tick, it depends on the phase value at the time when the master clock tick was received
	        krateAdjust = ksyncRateDev*krateSyncGravity*0.02
    	    endif

	ksyncPulseCount	= 0							; Reset counters on (slave)clock tick
	ksyncRateDev	= 0
  	endif										
endif										
	kgrainrateFlex	= kgrainrateFlex+(krateAdjust*kgrainrateFlex*0.1)
	agrainrateFlex	upsamp kgrainrateFlex

	a1,a2,a3,a4,a5,a6,a7,a8	partikkel \
			agrainrateFlex, kdistribution, idisttab, async, 0, \
       			-1,ienv_attack, ienv_decay, ksustain_amount, ka_d_ratio, \
			kduration, kamp, igainmasks, kwavfreq, ksweepshape, \
			iwavfreqstarttab, iwavfreqendtab, awavfm, -1, -1, \
			icosine, kTrainCps, knumpartials, kchroma, ichannelmasks, \
			krandommask, kwaveform1, kwaveform2, kwaveform3, kwaveform4, \
			iwaveamptab, asamplepos, asamplepos, asamplepos, asamplepos, \
			1, 1, 1, 1, 100, iopcode_id

; sync
	aclock, aphase	partikkelsync	iopcode_id				; clock pulse and phase of the partikkel instance 
	SclockIntern	sprintf "p%i_clock", iopcode_id
			chnset aclock, SclockIntern				; send clock, to be used as master for other clocks
	kclockIntern	downsamp aclock, ksmps
	kclockIntern	= kclockIntern*ksmps

; amp and output
        ipan            table iopcode_id-1, giPanTab
        ao1     	= a1*sqrt(1-ipan)
	ao2		= a1*sqrt(ipan)
			chnmix	ao1, "dryL"
			chnmix	ao2, "dryR"

	endin

;******************************************************
; effects, output, cleanup

        instr   991     ; reverb
        a1              chnget "dryL"
        a2              chnget "dryR"
	kFeed		chnget "Feed"
	kFiltFq		chnget "FiltFq"
	kPitchMod	chnget "PitchMod"	
	kMix		chnget "Mix"
	kupdate		changed kPitchMod
	if kupdate > 0 then
	reinit update
	endif
update:
	aL,aR		reverbsc a1, a2, kFeed, kFiltFq, sr, i(kPitchMod)
	aL		dcblock2 (aL*kMix*0.7)+(a1*(1-kMix))
	aR		dcblock2 (aR*kMix*0.7)+(a2*(1-kMix))
			chnmix aL, "dryL"
			chnmix aR, "dryR"
        endin

        instr   998     ; master out
        a1              chnget "dryL"
        a2              chnget "dryR"

        klevelOeyvind   chnget "levelOeyvind"
        printk2 klevelOeyvind
        aL              = a1*klevelOeyvind
        aR              = a2*klevelOeyvind  

			outch 1, aL, 2, aR

	a0		= 0
			chnset	a0, "dryL"
			chnset	a0, "dryR"
			
        endin


;******************************************************
	instr 19
	iopcode_id	= 1
	Samp		sprintf "p%i_amp", iopcode_id		
	Spitch		sprintf "p%i_pitch", iopcode_id		
	SgrLowRate	sprintf "p%i_grLowRate", iopcode_id	
	SpitchMode	sprintf "p%i_pitchMode", iopcode_id	
	SgRateDevAmt	sprintf "p%i_gRateDevAmt", iopcode_id	
	SgrLfoAmp	sprintf "p%i_grLfoAmp", iopcode_id	
	SgrLfoFreq	sprintf "p%i_grLfoFreq", iopcode_id	
	SformantOffset	sprintf "p%i_formantOffset", iopcode_id	
	SformantFollow	sprintf "p%i_formantFollow", iopcode_id	
	SformLfoAmp	sprintf "p%i_formLfoAmp", iopcode_id	
	SformLfoFreq	sprintf "p%i_formLfoFreq", iopcode_id	
	Sa_d_ratio	sprintf "p%i_a_d_ratio", iopcode_id	
	Ssustain	sprintf "p%i_sustain", iopcode_id	
	SatckLfoAmp	sprintf "p%i_atckLfoAmp", iopcode_id	
	SatckLfoFreq	sprintf "p%i_atckLfoFreq", iopcode_id	
	SrelDur		sprintf "p%i_relDur", iopcode_id
	;puts SrelDur, 1	
	SdurLfoAmp	sprintf "p%i_durLfoAmp", iopcode_id	
	SdurLfoFreq	sprintf "p%i_durLfoFreq", iopcode_id	
	SdurDevAmt	sprintf "p%i_durDevAmt", iopcode_id	
	Srandommask	sprintf "p%i_randommask", iopcode_id	
	Sdistribution	sprintf "p%i_distribution", iopcode_id	
	SgChanDevAmt	sprintf "p%i_gChanDevAmt", iopcode_id	
	SpitchGliss	sprintf "p%i_pitchGliss", iopcode_id	
	SrndPitchGliss	sprintf "p%i_rndPitchGliss", iopcode_id	

	kamp		chnget Samp		
	kpitch 		chnget Spitch		
	kgrLowRate 	chnget SgrLowRate	
	kpitchMode 	chnget SpitchMode	
	kgRateDevAmt 	chnget SgRateDevAmt	
	kgrLfoAmp 	chnget SgrLfoAmp	
	kgrLfoFreq 	chnget SgrLfoFreq	
	kformantOffset 	chnget SformantOffset	
	kformantFollow 	chnget SformantFollow	
	kformLfoAmp 	chnget SformLfoAmp	
	kformLfoFreq	chnget SformLfoFreq	
	ka_d_ratio 	chnget Sa_d_ratio	
	ksustain 	chnget Ssustain		
	katckLfoAmp 	chnget SatckLfoAmp	
	katckLfoFreq 	chnget SatckLfoFreq	
	krelDur 	chnget SrelDur		
	kdurLfoAmp 	chnget SdurLfoAmp	
	kdurLfoFreq 	chnget SdurLfoFreq	
	kdurDevAmt 	chnget SdurDevAmt	
	krandommask 	chnget Srandommask	
	kdistribution 	chnget Sdistribution	
	kgChanDevAmt 	chnget SgChanDevAmt	
	kpitchGliss 	chnget SpitchGliss	
	krndPitchGliss 	chnget SrndPitchGliss	

	chnset kamp,		Samp		
	chnset kpitch, 		Spitch		
	chnset kgrLowRate, 	SgrLowRate	
	chnset kpitchMode, 	SpitchMode	
	chnset kgRateDevAmt, 	SgRateDevAmt	
	chnset kgrLfoAmp, 	SgrLfoAmp	
	chnset kgrLfoFreq, 	SgrLfoFreq	
	chnset kformantOffset, 	SformantOffset	
	chnset kformantFollow, 	SformantFollow	
	chnset kformLfoAmp, 	SformLfoAmp	
	chnset kformLfoFreq,	SformLfoFreq	
	chnset ka_d_ratio, 	Sa_d_ratio	
	chnset ksustain, 	Ssustain	
	chnset katckLfoAmp, 	SatckLfoAmp	
	chnset katckLfoFreq, 	SatckLfoFreq	
;printk2 krelDur
;krelDur = 0.1
	chnset krelDur, 	SrelDur		
	chnset kdurLfoAmp, 	SdurLfoAmp	
	chnset kdurLfoFreq, 	SdurLfoFreq	
	chnset kdurDevAmt, 	SdurDevAmt	
	chnset krandommask, 	Srandommask	
	chnset kdistribution, 	Sdistribution	
	chnset kgChanDevAmt, 	SgChanDevAmt	
	chnset kpitchGliss, 	SpitchGliss	
	chnset krndPitchGliss, 	SrndPitchGliss	

	endin

;******************************************************

; set template
;                v, template, incPitch, incLowRate, includeAmp
schedule 21,1,1, 1, 11,       1,         1,           1
schedule 21,1,1, 2, 11,       1,         1,           1
schedule 21,1,1, 3, 11,       1,         1,           1
schedule 21,1,1, 4, 11,       1,         1,           1

; set sync master    master slave
schedule 11, 1, 1,   1,      2
schedule 11, 1, 1,   1,      3

schedule 991, 1, -1       ; reverb
schedule 998, 1, -1       ; master

