
void checkInterface(){
    // Read pots + CVs
    int param1Pot = analogRead(CHORD_POT_PIN); 
    param1CV = analogRead(CHORD_CV_PIN); 
    int param2Pot = analogRead(ROOT_POT_PIN); 
    param2CV = analogRead(ROOT_CV_PIN); 
    int param1Raw;
    int param2Raw;
    if (instrument != 2 && instrument != 3 )
    {
        // cv pot and input summing
       param1Raw = param1Pot + param1CV; 
       param1Raw = constrain(param1Raw, 0, ADC_MAX_VAL - 1);
       param2Raw = param2Pot + param2CV; 
       param2Raw = constrain(param2Raw, 0, ADC_MAX_VAL - 1);
    }
    else if (instrument == 2)
    {
      param1Raw = param1Pot + param1CV; 
      param1Raw = constrain(param1Raw, 0, ADC_MAX_VAL - 1); 
      param2Raw = param2Pot;
    }   
    else if (instrument == 3)
    {
      param1Raw = param1Pot; 
      param2Raw = param2Pot + param2CV; 
      param2Raw = constrain(param2Raw, 0, ADC_MAX_VAL - 1);
    }   
    param1 = param1Raw / 64.5;
    param2 = param2Raw / 64.5;
}

void checkButton(){
    buttonState = digitalRead(RESET_BUTTON);
    if (pushbutton1.update())
    {
        if (pushbutton1.risingEdge() ) 
        {
            shiftTimer  = 0;
            startCounter = true;
        }
        else if (pushbutton1.fallingEdge() ) 
        {
            startCounter = false;
            if ( shiftTimer < 3000 )
            {
                instrument++;
            }
            shiftTimer  = 0;
            modeChanged = false;
        }
    }
    if (buttonState == 1 && shiftTimer > 4500 && modeChanged == false)
    {   
        if (controlPage2 == true)
        {
           controlPage2 = false;
        }
        else
        {
            controlPage2 = true;
        }
        modeChanged = true;
    }
    if (instrument >= 4)
    {
        instrument = 0;
    }
    if (startCounter == true)
    {
      shiftTimer ++;
    }
    
   frame++;
   if (frame%FRAME_DIVIDER == 0)
   {
      dividedFrame ++;
   }
   if (frame > 10000)
   {
      frame = 0;
   }
   if (dividedFrame > 1000)
   {
      dividedFrame = 0;
   }
  
   if (controlPage2 == true)
   {
      if (dividedFrame%2 == 0)
      {
         digitalWrite(RESET_LED, HIGH);
      }
      else
      {
         digitalWrite (RESET_LED, LOW);
      }
   }
   else
   {
      digitalWrite (RESET_LED, LOW);
   }
    if ( modeChanged == true)
   {
      EEPROM_Mode_Frame ++;
      if (EEPROM_Mode_Frame > 15000)
      {
          if (hasBeenSaved == false)
          {
            int address = 0;
            for (int i = 0; i < 4; i ++)
            {
              for( int j = 0; j <4; j++)
              {
                  EEPROM.write(address, instrumentsParams[i][j]);
                  address ++;
              }
            }
            EEPROM.write(17, instrument);
            hasBeenSaved = true;
          }
          if (EEPROM_Mode_Frame%(FRAME_DIVIDER / 4) == 0)
          {
              DIVIDED_EEPROM_Mode_Frame ++;
          }
          if (EEPROM_Mode_Frame > 1000)
          {
              DIVIDED_EEPROM_Mode_Frame = 0;
          }
          if (DIVIDED_EEPROM_Mode_Frame%2 == 0)
          {
             digitalWrite(RESET_LED, HIGH);
          }
          else
          {
             digitalWrite (RESET_LED, LOW);
          }
      }
   }
}

void controlInstrumentParams(){
    // BD: 30 tune, 31 decay, 33 pitchenv, 34 hardness, 
    // SD: 35 tune, 36 decay, 37 noise decay, 38 noise balance
    // HH: 39 tune , 40 decay, 41 open decay, 42 noise balance
   if (instrument == BASS_DRUM)
   {
      voice1.controlChange(30, instrumentsParams[instrument][0], 1);
      voice1.controlChange(31, instrumentsParams[instrument][1], 1);
      voice1.controlChange(33, instrumentsParams[instrument][2], 1);
      voice1.controlChange(34, instrumentsParams[instrument][3], 1);
   }
   else if (instrument == SNARE_DRUM)
   {
      for (int i = 0; i < 4; i++)
      {
        voice1.controlChange(35 + i, instrumentsParams[instrument][i], 1);
      }
   }
   else if (instrument == CLOSED_HI_HAT)
   {
      for (int j = 0; j < 4; j++)
      {
       voice1.controlChange(39 + j, instrumentsParams[instrument][j], 1);
      }
   }
}

void setControlValues(){  
   
    if (buttonState == 0)
    {
        for (int i = 0; i < 2; i++)
        {
           if (controlPage2 == false)
          {
              param[0] = param1;
              param[1] = param2;
              if ((analogRead(CHORD_CV_PIN) < 15 && i == 0) || instrument == 3)
              {
                if ((param[i] < instrumentsParams[instrument][i] + POT_TOLERANCE && param[i] > instrumentsParams[instrument][i] - POT_TOLERANCE) )
                {
                  instrumentsParams[instrument][i] = param[i];
                }
              }
              else if (analogRead(CHORD_CV_PIN) > 15 && i == 0)
              {
                  instrumentsParams[instrument][i] = param[i];
              }
              if ((analogRead(ROOT_CV_PIN) < 15 && i == 1 ) || instrument == 3)
              {
                if ((param[i] < instrumentsParams[instrument][i] + POT_TOLERANCE && param[i] > instrumentsParams[instrument][i] - POT_TOLERANCE) )
                {
                  instrumentsParams[instrument][i] = param[i];
                }
              }
              else if (analogRead(ROOT_CV_PIN) > 15 && i == 1)
              {
                  instrumentsParams[instrument][i] = param[i];
              }
          }
          else
          {
              param[2] = param1;
              param[3] = param2;
              if ((analogRead(CHORD_CV_PIN) < 15 && i == 0 ) || instrument == 3)
              {
                if ((param[i + 2] < instrumentsParams[instrument][i + 2] + POT_TOLERANCE && param[i + 2] > instrumentsParams[instrument][i + 2] - POT_TOLERANCE) )
                {
                  instrumentsParams[instrument][i + 2] = param[i + 2];
                }
              }
              else if (analogRead(CHORD_CV_PIN) > 15 && i == 0)
              {
                  instrumentsParams[instrument][i + 2] = param[i + 2];
              }
              if ((analogRead(ROOT_CV_PIN) < 15 && i == 1) || instrument == 3)
              {
                if ((param[i + 2] < instrumentsParams[instrument][i + 2] + POT_TOLERANCE && param[i + 2] > instrumentsParams[instrument][i + 2] - POT_TOLERANCE) )
                {
                  instrumentsParams[instrument][i + 2] = param[i + 2];
                }
              }
              else if (analogRead(ROOT_CV_PIN) > 15 && i == 1)
              {
                  instrumentsParams[instrument][i + 2] = param[i + 2];
              }
          }
        }
    }
}

void selectInstrument(){
    // select sound : control 28 <35 => kick, <75 => snare, >75 => hihat
    int currentInstrument;
    if (instrument == BASS_DRUM)
    {
     digitalWrite(LED3, HIGH);
      currentInstrument = 15;
    }
    else 
    {
     digitalWrite(LED3, LOW);
    }
    if (instrument == SNARE_DRUM)
    {
     digitalWrite(LED2, HIGH);
      currentInstrument = 60;
    }
    else
    {
     digitalWrite(LED2, LOW);
    }
    if (instrument == CLOSED_HI_HAT)
    {
     digitalWrite(LED1, HIGH);
      currentInstrument = 80;
    }
    else
    {
     digitalWrite(LED1, LOW);
    }
    if (instrument == SAMPLES)
    {
      digitalWrite(LED0, HIGH);
      currentInstrument = 80;
    }
    else
    {
      digitalWrite(LED0, LOW);
    }
    voice1.controlChange(28, currentInstrument , 1);
}

void trigInstrument(){
     int param2CV = analogRead(ROOT_CV_PIN); 
    // trig drums 32 => kick, 33 => snare, 34 => hihat closed, 35 => hihat open
    int currentInstrument = 32 + instrument;
    if (digitalRead (RESET_CV) == 1 && activeTrig == false && instrument < 3 )
    {
      voice1.noteOn(currentInstrument ,127,1);
      activeTrig = true;
    }
    if (digitalRead(RESET_CV) == 0 && instrument < 3 )
    {
      voice1.noteOff(currentInstrument, 0, 1);
      activeTrig = false;
    }
    
    if (instrument == CLOSED_HI_HAT)
    {
       if (param2CV >500 && activeOpenHatTrig == false)
       {
         voice1.noteOn(currentInstrument + 1 ,127,1);
         activeOpenHatTrig = true;
       }
       if (param2CV < 200)
       {
         voice1.noteOff(currentInstrument + 1 ,0,1);
         activeOpenHatTrig = false;
       }
    } 
    
    if (instrument == SAMPLES)
    {
      //param2CV = analogRead(CHORD_CV_PIN); 
        if (controlPage2 == false)
        {
            sampleNumber1 = instrumentsParams[instrument][1] /20;
            if (sampleNumber1 == 0)
            {
              if (instrumentsParams[instrument][0] < 110)
              {
                 envelope0.decay((instrumentsParams[instrument][0] * 1.5) + 10);
              }
              else
              {
                envelope0.decay(10000);
              }
            }
            else if (sampleNumber1 == 1)
            {
              if (instrumentsParams[instrument][0] < 110)
              {
                 envelope0.decay((instrumentsParams[instrument][0] * 2.1) + 10);
              }
              else
              {
                envelope0.decay(10000);
              }
            }
             else if (sampleNumber1 == 2)
            {
              if (instrumentsParams[instrument][0] < 110)
              {
                 envelope0.decay((instrumentsParams[instrument][0] * 2.2) + 10);
              }
              else
              {
                envelope0.decay(10000);
              }
            }
             else if (sampleNumber1 == 3)
            {
              if (instrumentsParams[instrument][0] < 110)
              {
                 envelope0.decay((instrumentsParams[instrument][0] * 4) + 10);
              }
              else
              {
                envelope0.decay(10000);
              }
            }
             else if (sampleNumber1 == 4)
            {
              if (instrumentsParams[instrument][0] < 110)
              {
                 envelope0.decay((instrumentsParams[instrument][0] * 0.5) + 5);
              }
              else
              {
                envelope0.decay(5000);
              }
            }
             else if (sampleNumber1 == 5)
            {
              if (instrumentsParams[instrument][0] < 110)
              {
                 envelope0.decay((instrumentsParams[instrument][0] * 15) + 5);
              }
              else
              {
                envelope0.decay(15000);
              }
            }
        }

        if (controlPage2 == true)
        {
          sampleNumber2 = instrumentsParams[instrument][3]/20;
          if (sampleNumber2 == 0)
          {
              if (instrumentsParams[instrument][2] < 110)
              {
                 envelope1.decay((instrumentsParams[instrument][2] * 1.5) + 10);
              }
              else
              {
                envelope1.decay(10000);
              }
          }
          else if (sampleNumber2 == 1)
          {
             if (instrumentsParams[instrument][2] < 110)
              {
                 envelope1.decay((instrumentsParams[instrument][2] * 2.1) + 10);
              }
              else
              {
                envelope1.decay(10000);
              }
          }
          else if (sampleNumber2 == 2)
          {
              if (instrumentsParams[instrument][2] < 110)
              {
                 envelope1.decay((instrumentsParams[instrument][2] * 2.2) + 10);
              }
              else
              {
                envelope1.decay(10000);
              }
          }
          else if (sampleNumber2 == 3)
          {
            if (instrumentsParams[instrument][2] < 110)
              {
                 envelope1.decay((instrumentsParams[instrument][2] * 4) + 10);
              }
              else
              {
                envelope1.decay(10000);
              }
          }
          else if (sampleNumber2 == 4)
          {
            if (instrumentsParams[instrument][2] < 110)
              {
                 envelope1.decay((instrumentsParams[instrument][2] * 0.5) + 5);
              }
              else
              {
                envelope1.decay(5000);
              }
          }
          else if (sampleNumber2 == 5)
          {
             if (instrumentsParams[instrument][2] < 110)
              {
                 envelope1.decay((instrumentsParams[instrument][2] * 15) + 5);
              }
              else
              {
                envelope1.decay(15000);
              }
          } 
        }


        if (sampleNumber1 == 0)
            {
              if (digitalRead(RESET_CV) == 1 && activeTrig == false )
              {
                  sound0.play(AudioSampleKick);
                  activeTrig = true;
                  envelope0.noteOn();
              }
            }
            else if (sampleNumber1 == 1)
            {
              if (digitalRead(RESET_CV) == 1 && activeTrig == false )
              {
                  sound0.play(AudioSampleSnare);
                  activeTrig = true;
                  envelope0.noteOn();
              }
            }
            else if (sampleNumber1 == 2)
            {
              if (digitalRead(RESET_CV) == 1 && activeTrig == false )
              {
                  sound0.play(AudioSampleClap);
                  activeTrig = true;
                  envelope0.noteOn();
              }
            }
            else if (sampleNumber1 == 3)
            {
              if (digitalRead(RESET_CV) == 1 && activeTrig == false )
              {
                  sound0.play(AudioSampleHihatopened);
                  activeTrig = true;
                  envelope0.noteOn();
              }
            }
            else if (sampleNumber1 == 4)
            {
              if (digitalRead(RESET_CV) == 1 && activeTrig == false )
              {
                  sound0.play(AudioSampleHihatclosed);
                  activeTrig = true;
                  envelope0.noteOn();
              }
            }
            else if (sampleNumber1 == 5)
            {
              if (digitalRead(RESET_CV) == 1 && activeTrig == false )
              {
                  sound0.play(AudioSampleExtraSound);
                  activeTrig = true;
                  envelope0.noteOn();
              }
            }
            if (sampleNumber2 == 0)
            {
              
              if (param1CV >500 && activeOpenHatTrig == false )
              {
                  sound1.play(AudioSampleKick);
                  activeOpenHatTrig = true;
                  envelope1.noteOn();
              }
            }
            else if (sampleNumber2 == 1)
            {
              if (param1CV >500 && activeOpenHatTrig == false )
              {
                  sound1.play(AudioSampleSnare);
                  activeOpenHatTrig = true;
                  envelope1.noteOn();
              }
            }
            else if (sampleNumber2 == 2)
            {
              if (param1CV >500 && activeOpenHatTrig == false )
              {
                  sound1.play(AudioSampleClap);
                  activeOpenHatTrig = true;
                  envelope1.noteOn();
              }
            }
            else if (sampleNumber2 == 3)
            {
              if (param1CV >500 && activeOpenHatTrig == false )
              {
                  sound1.play(AudioSampleHihatopened);
                  activeOpenHatTrig = true;
                  envelope1.noteOn();
              }
            }
            else if (sampleNumber2 == 4)
            {
              if (param1CV >500 && activeOpenHatTrig == false )
              {
                  sound1.play(AudioSampleHihatclosed);
                  activeOpenHatTrig = true;
                  envelope1.noteOn() ;
              }
            }
            else if (sampleNumber2 == 5)
            {
              if (param1CV >500 && activeOpenHatTrig == false )
              {
                  sound1.play(AudioSampleExtraSound);
                  activeOpenHatTrig = true;
                  envelope1.noteOn();
              }
            }
            if (digitalRead(RESET_CV) == 0)
            {
                activeTrig = false;
            }
            
            if (param1CV < 200)
            { 
                  activeOpenHatTrig = false;
            }
            if (digitalRead(RESET_CV) == 0)
            {
                 activeTrig = false;
            }
    }
}

/*
void setReverb(){
  
  if ((buttonState == 1 && param1 < reverbKnobParam + 5 && param1 > reverbKnobParam - 5) || (buttonState == 1 && delock == true))
  {
    float gainValue = param1/40.0;
    mixer2.gain(0, gainValue);
    mixer2.gain(1, gainValue);
    reverbKnobParam = param1;
    delock = true;
  }
  if (buttonState == false) 
  {
    delock = false;
  }
  if ((buttonState == 1 && param2 < reverbKnobParam2 + 5 && param2 > reverbKnobParam2 - 5) || (buttonState == 1 && delock2 == true))
  {
    float timeValue = param2/10.0;
    reverb1.reverbTime(timeValue);
    reverbKnobParam2 = param2;
    delock2 = true;
  }
  if (buttonState == false) 
  {
    delock2 = false;
  }
 }
*/


