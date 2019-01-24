#include <Wire.h>
#include <SPI.h>
#include <Audio.h>
#include <Bounce.h>
#include <EEPROM.h>
#include "Brain.h"

#include "AudioSampleKick.h"
#include "AudioSampleSnare.h"        
#include "AudioSampleClap.h"       
#include "AudioSampleHihatopened.h"
#include "AudioSampleHihatclosed.h"
#include "AudioSampleExtraSound.h" 
//#include "MIDI.h"

#define ADC_BITS 13
#define ADC_MAX_VAL 8192
#define POT_TOLERANCE 5

#define BASS_DRUM 0
#define SNARE_DRUM 1
#define CLOSED_HI_HAT 2
#define SAMPLES 3

#define CHORD_POT_PIN 9 // pin for Chord pot
#define CHORD_CV_PIN 6 // pin for Chord CV 
#define ROOT_POT_PIN 7 // pin for Root Note pot
#define ROOT_CV_PIN 8 // pin for Root Note CV
#define RESET_BUTTON 8 // Reset button 
#define RESET_LED 11 // Reset LED indicator 
#define RESET_CV 9 // Reset pulse in / out
#define BANK_BUTTON 2 // Bank Button 
#define LED0 6
#define LED1 5
#define LED2 4
#define LED3 3
#define FRAME_DIVIDER 1000
#define SHORT_PRESS_DURATION 10
#define LONG_PRESS_DURATION 500
#define shiftTime 1000

Bounce pushbutton1 = Bounce(RESET_BUTTON, 40);  // 10 ms debounce

boolean hasBeenReleased = false;
boolean startCounter = false;
byte mode = 0;
int param1 = 64;
int param2 = 64;
int param[4] = {64, 64, 64, 64};
int instrumentsParams[4][4]; // [instrument][paramNumber]
int previousInstrumentsParams[4][4]; // [instrument][paramNumber]
int frame;
int dividedFrame;
int param1CV;
int param2CV;
//byte bassDrumParams[4];
int shiftTimer = 0;
boolean activeTrig = false;
boolean activeOpenHatTrig = false;
boolean delock = true;
boolean delock2 = true;
elapsedMillis buttonTimer = 0;
elapsedMillis lockOut = 0;
boolean shortPress = false;
boolean longPress = false;
elapsedMillis pulseOutTimer = 0;
uint32_t flashTime = 10;
int reverbKnobParam = 0;
int reverbKnobParam2 = 0;
int sampleNumber1 = 0;
int sampleNumber2 = 0;
boolean flashing = false;
boolean modeChanged = false; 
boolean hasBeenSaved = false;
byte instrument;
int buttonState = 0;
boolean controlPage2 = false;
boolean hasBeenLoad = false;
int DIVIDED_EEPROM_Mode_Frame = 0;
int EEPROM_Mode_Frame = 0;

Brain                    voice1;
AudioPlayMemory          sound0;
AudioPlayMemory          sound1;
AudioEffectEnvelope      envelope0;
AudioEffectEnvelope      envelope1;
AudioMixer4              mixer2;           //xy=181,387
//AudioEffectReverb      reverb1;        //xy=330,382
AudioMixer4              mixer1;         //xy=489,362
AudioOutputAnalog        dac1;           //xy=655,361
AudioConnection          patchCord12(sound0, envelope0);
AudioConnection          patchCord8(sound1, envelope1);
AudioConnection          patchCord1(voice1, 0, mixer1, 0);
//AudioConnection          patchCord2(voice1, 0, mixer2, 0);
/*
AudioConnection          patchCord9(envelope0, 0, mixer2, 1);
AudioConnection          patchCord10(envelope1, 0, mixer2, 2);
AudioConnection          patchCord6(mixer2, 0, reverb1, 0);
AudioConnection          patchCord4(reverb1, 0, mixer1, 1);
*/
AudioConnection          patchCord7(envelope0, 0, mixer1, 2);
AudioConnection          patchCord11(envelope1, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, dac1);
// GUItool: end automatically generated code

void setup() {
  mixer1.gain(0, 3.0);
  mixer1.gain(1, 3.0);
  mixer1.gain(2, 1.5);
  mixer1.gain(3, 1.5);
  AudioMemory(12); //50
  voice1.begin();
  pinMode(BANK_BUTTON,INPUT);
  pinMode(RESET_BUTTON, INPUT);
  pinMode(RESET_CV, INPUT); 
  pinMode(RESET_LED, OUTPUT);
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  analogReadRes(ADC_BITS); 

  envelope0.attack(0);
  envelope0.hold(0);
  envelope0.decay(100);
  envelope0.sustain(0);
  envelope1.attack(0);
  envelope1.hold(0);
  envelope1.decay(100);
  envelope1.sustain(0);
  
}

void loop() {

  if (hasBeenLoad == false)
  {
       int address = 0;
       for (int i = 0; i < 4; i ++)
       {
           for( int j = 0; j <4; j++)
           {
            int value = EEPROM.read(address);
            if (value < 128)
            {
              instrumentsParams[i][j] =value;
            }
            else
            {
              instrumentsParams[i][j] =0;
            }
            address ++;
           }
       }
       int recInst = EEPROM.read(17);
       if (recInst < 4)
       {
          instrument = recInst;
       }
       else
       {
          instrument = 0;
       }
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
        hasBeenLoad = true;
  }
  
  checkButton(); // get button state and determine short or long press and increment instrument 
  checkInterface(); // get pot and cv values, mix these depending on the selected instrument and constrain these to 0-127 values
  selectInstrument(); // select the current playing and editable insrument and display leds
  setControlValues();
  controlInstrumentParams(); // use the cv and pot value to control the voice1 paramete for the current instrument 
  trigInstrument(); // trig the sound demending on the choosen instrument and trig input 
 
  /*
  Serial.println("AUDIO_CPU: ");
  Serial.println(AudioMemoryUsage());
  Serial.println(voice1.processorUsage());
  Serial.println("all=");
  Serial.println(AudioProcessorUsage());*/
}


