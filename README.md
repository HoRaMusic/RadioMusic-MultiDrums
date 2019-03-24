# MultiDrums
Alternative firmware for MTM "chord organ" or "radio music" (eurorack module)

"MultiDrums" is an alternative firmware for both MTM "chord organ" and "radio music" modules witten by "hora music".

This firmawares hallows to play analog drums sounds closed to those used in the Hora music "analog drums" VCV rack plugin 
and 6 Linn drum sounds (samples).

The three "analog sounds" (kick snare and hi hat) are based on modeling and don't use samples, 
this give closer to real analog drums and hallow to offer typical settable parameters of analog drums (most of these are CV controlable).

The 6 linndrum sounds are based on 16bit 44100hz wav files : Kick, Snare, Clap, Closed hi-hat, open hi-hat, crash cymbale. 
Users can set the sample decay, can play 2 samples simultaneously and the sample selection is CV controlable.

This module used DSP write with the Vult transcompiler : https://modlfo.github.io/vult/


MAIN CONTROLS:

![alt text](https://github.com/HoRaMusic/MultiDrums/blob/master/modulePic.png)



The leds indicate the playing instrument 1: kick, 2: snare, 3: hi-hat, 4: samples.
The "chord" and "Root" inputs are also used for cv control of parameter 1 and 2 (0v to 3.3v), here is a more detailed description:




ADVANCED CONTROLS:

![alt text](https://github.com/HoRaMusic/RadioMusic-MultiDrums/blob/master/controlsF.png)




