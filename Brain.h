
#ifndef BRAIN_H
#define BRAIN_H

#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "AudioStream.h"

typedef struct Snare__ctx_type_0 {
   fix16_t pre_x;
} Snare__ctx_type_0;

typedef Snare__ctx_type_0 Snare_change_type;

void Snare__ctx_type_0_init(Snare__ctx_type_0 &_output_);

void Snare_change_init(Snare__ctx_type_0 &_output_);

uint8_t Snare_change(Snare__ctx_type_0 &_ctx, fix16_t x);

fix16_t Snare_pitchToRate(fix16_t d);

fix16_t Snare_decayToFallingRate(fix16_t d);

typedef struct Snare__ctx_type_3 {
   uint8_t pre;
} Snare__ctx_type_3;

typedef Snare__ctx_type_3 Snare_edge_type;

void Snare__ctx_type_3_init(Snare__ctx_type_3 &_output_);

void Snare_edge_init(Snare__ctx_type_3 &_output_);

uint8_t Snare_edge(Snare__ctx_type_3 &_ctx, uint8_t x);

typedef struct Snare__ctx_type_4 {
   fix16_t envelope;
   Snare__ctx_type_3 _inst5;
} Snare__ctx_type_4;

typedef Snare__ctx_type_4 Snare_envelope_type;

void Snare__ctx_type_4_init(Snare__ctx_type_4 &_output_);

void Snare_envelope_init(Snare__ctx_type_4 &_output_);

fix16_t Snare_envelope(Snare__ctx_type_4 &_ctx, fix16_t dec, uint8_t g);

typedef struct Snare__ctx_type_5 {
   fix16_t z2;
   fix16_t z1;
} Snare__ctx_type_5;

typedef Snare__ctx_type_5 Snare_HP_type;

void Snare__ctx_type_5_init(Snare__ctx_type_5 &_output_);

void Snare_HP_init(Snare__ctx_type_5 &_output_);

fix16_t Snare_HP(Snare__ctx_type_5 &_ctx, fix16_t x);

typedef struct Snare__ctx_type_6 {
   int counter;
} Snare__ctx_type_6;

typedef Snare__ctx_type_6 Snare_divideFreq_type;

void Snare__ctx_type_6_init(Snare__ctx_type_6 &_output_);

void Snare_divideFreq_init(Snare__ctx_type_6 &_output_);

uint8_t Snare_divideFreq(Snare__ctx_type_6 &_ctx, int divider);

typedef struct Snare__ctx_type_7 {
   fix16_t rate;
   fix16_t phase;
   fix16_t env;
   Snare__ctx_type_0 _inst20;
   Snare__ctx_type_0 _inst19;
   Snare__ctx_type_4 _inst18;
   Snare__ctx_type_6 _inst16;
   Snare__ctx_type_3 _inst13;
} Snare__ctx_type_7;

typedef Snare__ctx_type_7 Snare_customBridgeT_type;

void Snare__ctx_type_7_init(Snare__ctx_type_7 &_output_);

void Snare_customBridgeT_init(Snare__ctx_type_7 &_output_);

fix16_t Snare_customBridgeT(Snare__ctx_type_7 &_ctx, fix16_t tune, uint8_t g, fix16_t envInt, fix16_t dec);

typedef struct Snare__ctx_type_8 {
   fix16_t w1;
} Snare__ctx_type_8;

typedef Snare__ctx_type_8 Snare_pinker_type;

void Snare__ctx_type_8_init(Snare__ctx_type_8 &_output_);

void Snare_pinker_init(Snare__ctx_type_8 &_output_);

fix16_t Snare_pinker(Snare__ctx_type_8 &_ctx, fix16_t x);

typedef struct Snare__ctx_type_9 {
   int x2;
   int x1;
   Snare__ctx_type_8 _inst24;
} Snare__ctx_type_9;

typedef Snare__ctx_type_9 Snare_noise_type;

void Snare__ctx_type_9_init(Snare__ctx_type_9 &_output_);

void Snare_noise_init(Snare__ctx_type_9 &_output_);

fix16_t Snare_noise(Snare__ctx_type_9 &_ctx, fix16_t color);

fix16_t Snare_balance(fix16_t bal, fix16_t sig1, fix16_t sig2);

typedef struct Snare__ctx_type_11 {
   fix16_t tune;
   uint8_t pitchEnvelopeActive;
   fix16_t pitchEnvInt;
   uint8_t pitchEnv;
   fix16_t noiseDecay;
   fix16_t noiseBalance;
   fix16_t noise;
   uint8_t gate;
   fix16_t decay;
   Snare__ctx_type_5 _inst46;
   Snare__ctx_type_4 _inst45;
   Snare__ctx_type_4 _inst44;
   Snare__ctx_type_7 _inst43;
   Snare__ctx_type_9 _inst42;
   Snare__ctx_type_6 _inst40;
   Snare__ctx_type_3 _inst35;
} Snare__ctx_type_11;

typedef Snare__ctx_type_11 Snare_process_type;

void Snare__ctx_type_11_init(Snare__ctx_type_11 &_output_);

void Snare_process_init(Snare__ctx_type_11 &_output_);

fix16_t Snare_process(Snare__ctx_type_11 &_ctx, fix16_t gateI, fix16_t tuneI, fix16_t decayI, fix16_t noiseDecayI, fix16_t noiseBalanceI);

typedef struct Kick__ctx_type_0 {
   fix16_t pre_x;
} Kick__ctx_type_0;

typedef Kick__ctx_type_0 Kick_change_type;

void Kick__ctx_type_0_init(Kick__ctx_type_0 &_output_);

void Kick_change_init(Kick__ctx_type_0 &_output_);

uint8_t Kick_change(Kick__ctx_type_0 &_ctx, fix16_t x);

fix16_t Kick_pitchToRate(fix16_t d);

fix16_t Kick_decayToFallingRate(fix16_t d);

typedef struct Kick__ctx_type_3 {
   uint8_t pre;
} Kick__ctx_type_3;

typedef Kick__ctx_type_3 Kick_edge_type;

void Kick__ctx_type_3_init(Kick__ctx_type_3 &_output_);

void Kick_edge_init(Kick__ctx_type_3 &_output_);

uint8_t Kick_edge(Kick__ctx_type_3 &_ctx, uint8_t x);

typedef struct Kick__ctx_type_4 {
   fix16_t envelope;
   Kick__ctx_type_3 _inst69;
} Kick__ctx_type_4;

typedef Kick__ctx_type_4 Kick_envelope_type;

void Kick__ctx_type_4_init(Kick__ctx_type_4 &_output_);

void Kick_envelope_init(Kick__ctx_type_4 &_output_);

fix16_t Kick_envelope(Kick__ctx_type_4 &_ctx, fix16_t dec, uint8_t g);

typedef struct Kick__ctx_type_5 {
   fix16_t z2;
   fix16_t z1;
} Kick__ctx_type_5;

typedef Kick__ctx_type_5 Kick_LP_type;

void Kick__ctx_type_5_init(Kick__ctx_type_5 &_output_);

void Kick_LP_init(Kick__ctx_type_5 &_output_);

fix16_t Kick_LP(Kick__ctx_type_5 &_ctx, fix16_t x);

typedef struct Kick__ctx_type_6 {
   int counter;
} Kick__ctx_type_6;

typedef Kick__ctx_type_6 Kick_divideFreq_type;

void Kick__ctx_type_6_init(Kick__ctx_type_6 &_output_);

void Kick_divideFreq_init(Kick__ctx_type_6 &_output_);

uint8_t Kick_divideFreq(Kick__ctx_type_6 &_ctx, int divider);

typedef struct Kick__ctx_type_7 {
   fix16_t rate;
   fix16_t phase;
   fix16_t env;
   Kick__ctx_type_0 _inst84;
   Kick__ctx_type_0 _inst83;
   Kick__ctx_type_4 _inst82;
   Kick__ctx_type_6 _inst80;
   Kick__ctx_type_3 _inst77;
} Kick__ctx_type_7;

typedef Kick__ctx_type_7 Kick_customBridgeT_type;

void Kick__ctx_type_7_init(Kick__ctx_type_7 &_output_);

void Kick_customBridgeT_init(Kick__ctx_type_7 &_output_);

fix16_t Kick_customBridgeT(Kick__ctx_type_7 &_ctx, fix16_t tune, uint8_t g, fix16_t envInt, fix16_t dec, fix16_t hardness);

typedef struct Kick__ctx_type_8 {
   fix16_t tune;
   fix16_t pitchEnvInt;
   fix16_t hardness;
   uint8_t gate;
   fix16_t decay;
   Kick__ctx_type_5 _inst92;
   Kick__ctx_type_4 _inst91;
   Kick__ctx_type_7 _inst90;
} Kick__ctx_type_8;

typedef Kick__ctx_type_8 Kick_process_type;

void Kick__ctx_type_8_init(Kick__ctx_type_8 &_output_);

void Kick_process_init(Kick__ctx_type_8 &_output_);

fix16_t Kick_process(Kick__ctx_type_8 &_ctx, fix16_t gateI, fix16_t tuneI, fix16_t decayI, fix16_t pitchEnvIntI, fix16_t hardnessI);

typedef struct HiHat__ctx_type_0 {
   fix16_t pre_x;
} HiHat__ctx_type_0;

typedef HiHat__ctx_type_0 HiHat_change_type;

void HiHat__ctx_type_0_init(HiHat__ctx_type_0 &_output_);

void HiHat_change_init(HiHat__ctx_type_0 &_output_);

uint8_t HiHat_change(HiHat__ctx_type_0 &_ctx, fix16_t x);

fix16_t HiHat_pitchToRate(fix16_t d);

fix16_t HiHat_decayToFallingRate(fix16_t d);

typedef struct HiHat__ctx_type_3 {
   uint8_t pre;
} HiHat__ctx_type_3;

typedef HiHat__ctx_type_3 HiHat_edge_type;

void HiHat__ctx_type_3_init(HiHat__ctx_type_3 &_output_);

void HiHat_edge_init(HiHat__ctx_type_3 &_output_);

uint8_t HiHat_edge(HiHat__ctx_type_3 &_ctx, uint8_t x);

typedef struct HiHat__ctx_type_4 {
   fix16_t envelope;
   HiHat__ctx_type_3 _inst107;
} HiHat__ctx_type_4;

typedef HiHat__ctx_type_4 HiHat_envelope_type;

void HiHat__ctx_type_4_init(HiHat__ctx_type_4 &_output_);

void HiHat_envelope_init(HiHat__ctx_type_4 &_output_);

fix16_t HiHat_envelope(HiHat__ctx_type_4 &_ctx, fix16_t dec, uint8_t g);

typedef struct HiHat__ctx_type_5 {
   fix16_t z2;
   fix16_t z1;
} HiHat__ctx_type_5;

typedef HiHat__ctx_type_5 HiHat_HP_type;

void HiHat__ctx_type_5_init(HiHat__ctx_type_5 &_output_);

void HiHat_HP_init(HiHat__ctx_type_5 &_output_);

fix16_t HiHat_HP(HiHat__ctx_type_5 &_ctx, fix16_t x);

typedef struct HiHat__ctx_type_6 {
   int counter;
} HiHat__ctx_type_6;

typedef HiHat__ctx_type_6 HiHat_divideFreq_type;

void HiHat__ctx_type_6_init(HiHat__ctx_type_6 &_output_);

void HiHat_divideFreq_init(HiHat__ctx_type_6 &_output_);

uint8_t HiHat_divideFreq(HiHat__ctx_type_6 &_ctx, int divider);

typedef struct HiHat__ctx_type_7 {
   fix16_t rate;
   fix16_t phase;
   HiHat__ctx_type_0 _inst115;
} HiHat__ctx_type_7;

typedef HiHat__ctx_type_7 HiHat_pulse_type;

void HiHat__ctx_type_7_init(HiHat__ctx_type_7 &_output_);

void HiHat_pulse_init(HiHat__ctx_type_7 &_output_);

fix16_t HiHat_pulse(HiHat__ctx_type_7 &_ctx, fix16_t tune, fix16_t pw);

typedef struct HiHat__ctx_type_8 {
   fix16_t w1;
} HiHat__ctx_type_8;

typedef HiHat__ctx_type_8 HiHat_pinker_type;

void HiHat__ctx_type_8_init(HiHat__ctx_type_8 &_output_);

void HiHat_pinker_init(HiHat__ctx_type_8 &_output_);

fix16_t HiHat_pinker(HiHat__ctx_type_8 &_ctx, fix16_t x);

typedef struct HiHat__ctx_type_9 {
   int x2;
   int x1;
   HiHat__ctx_type_8 _inst121;
} HiHat__ctx_type_9;

typedef HiHat__ctx_type_9 HiHat_noise_type;

void HiHat__ctx_type_9_init(HiHat__ctx_type_9 &_output_);

void HiHat_noise_init(HiHat__ctx_type_9 &_output_);

fix16_t HiHat_noise(HiHat__ctx_type_9 &_ctx, fix16_t color);

fix16_t HiHat_balance(fix16_t bal, fix16_t sig1, fix16_t sig2);

typedef struct HiHat__ctx_type_11 {
   fix16_t tune;
   fix16_t square2;
   fix16_t square1;
   fix16_t openedHiHat;
   fix16_t noiseBalance;
   fix16_t noise;
   uint8_t gate2;
   uint8_t gate1;
   fix16_t decay2;
   fix16_t decay1;
   fix16_t closedHiHat;
   HiHat__ctx_type_5 _inst142;
   HiHat__ctx_type_4 _inst141;
   HiHat__ctx_type_4 _inst140;
   HiHat__ctx_type_7 _inst139;
   HiHat__ctx_type_7 _inst138;
   HiHat__ctx_type_6 _inst136;
   HiHat__ctx_type_9 _inst135;
   HiHat__ctx_type_6 _inst133;
} HiHat__ctx_type_11;

typedef HiHat__ctx_type_11 HiHat_process_type;

void HiHat__ctx_type_11_init(HiHat__ctx_type_11 &_output_);

void HiHat_process_init(HiHat__ctx_type_11 &_output_);

fix16_t HiHat_process(HiHat__ctx_type_11 &_ctx, fix16_t gate1I, fix16_t gate2I, fix16_t tuneI, fix16_t decay1I, fix16_t decay2I, fix16_t noiseBalanceI);

typedef struct Brain__ctx_type_0 {
   int voice2Sound;
   fix16_t voice2Param[5];
   fix16_t voice2;
   int voice1Sound;
   fix16_t voice1Param[5];
   fix16_t voice1;
   fix16_t snareParam[5];
   fix16_t kickParam[5];
   fix16_t hiHatParam[6];
   HiHat__ctx_type_11 _inst166;
   Snare__ctx_type_11 _inst163;
   Kick__ctx_type_8 _inst160;
} Brain__ctx_type_0;

typedef Brain__ctx_type_0 Brain_process_type;

void Brain__ctx_type_0_init(Brain__ctx_type_0 &_output_);

void Brain_process_init(Brain__ctx_type_0 &_output_);

fix16_t Brain_process(Brain__ctx_type_0 &_ctx, fix16_t input);

typedef Brain__ctx_type_0 Brain_noteOn_type;

void Brain_noteOn_init(Brain__ctx_type_0 &_output_);

void Brain_noteOn(Brain__ctx_type_0 &_ctx, int note, int velocity, int channel);

typedef Brain__ctx_type_0 Brain_noteOff_type;

void Brain_noteOff_init(Brain__ctx_type_0 &_output_);

void Brain_noteOff(Brain__ctx_type_0 &_ctx, int note, int channel);

typedef Brain__ctx_type_0 Brain_controlChange_type;

void Brain_controlChange_init(Brain__ctx_type_0 &_output_);

void Brain_controlChange(Brain__ctx_type_0 &_ctx, int control, int value, int channel);

typedef Brain__ctx_type_0 Brain_default_type;

void Brain_default_init(Brain__ctx_type_0 &_output_);

void Brain_default(Brain__ctx_type_0 &_ctx);



class Brain : public AudioStream
{
public:
  Brain(void) : AudioStream(0, NULL)
  {
     Brain_process_init(data);
  }

  void begin() {
    Brain_default(data);
  }

  // Handles note on events
  void noteOn(int note, int velocity, int channel){
    // If the velocity is larger than zero, means that is turning on
    if(velocity) Brain_noteOn(data, note, velocity, channel);
    else         Brain_noteOff(data, note, channel);
  }

  // Handles note off events
  void noteOff(int note, int velocity, int channel) {
    Brain_noteOff(data, note, channel);

  }

  // Handles control change events
  void controlChange(int control, int value, int channel) {
    Brain_controlChange(data, control, value, channel);
  }

  virtual void update(void);

private:
  Brain_process_type data;

};

#endif // BRAIN_H
