
#include "Brain.h"

void Snare__ctx_type_0_init(Snare__ctx_type_0 &_output_){
   Snare__ctx_type_0 _ctx;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

void Snare_change_init(Snare__ctx_type_0 &_output_){
   Snare__ctx_type_0_init(_output_);
   return ;
}

uint8_t Snare_change(Snare__ctx_type_0 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

fix16_t Snare_pitchToRate(fix16_t d){
   return fix_mul(0x5 /* 0.000091 */,d);
}

fix16_t Snare_decayToFallingRate(fix16_t d){
   return fix_div(0x10000 /* 1.000000 */,fix_mul(d,0x15b3e7c /* 347.244094 */));
}

void Snare__ctx_type_3_init(Snare__ctx_type_3 &_output_){
   Snare__ctx_type_3 _ctx;
   _ctx.pre = 0;
   _output_ = _ctx;
   return ;
}

void Snare_edge_init(Snare__ctx_type_3 &_output_){
   Snare__ctx_type_3_init(_output_);
   return ;
}

uint8_t Snare_edge(Snare__ctx_type_3 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

void Snare__ctx_type_4_init(Snare__ctx_type_4 &_output_){
   Snare__ctx_type_4 _ctx;
   _ctx.envelope = 0x0 /* 0.000000 */;
   Snare__ctx_type_3_init(_ctx._inst5);
   _output_ = _ctx;
   return ;
}

void Snare_envelope_init(Snare__ctx_type_4 &_output_){
   Snare__ctx_type_4_init(_output_);
   return ;
}

fix16_t Snare_envelope(Snare__ctx_type_4 &_ctx, fix16_t dec, uint8_t g){
   fix16_t fallingRate;
   fallingRate = Snare_decayToFallingRate((dec + 0x50000 /* 5.000000 */));
   uint8_t _cond_47;
   _cond_47 = Snare_edge(_ctx._inst5,g);
   if(_cond_47){
      _ctx.envelope = 0x10000 /* 1.000000 */;
   }
   uint8_t _cond_48;
   _cond_48 = (_ctx.envelope > 0x0 /* 0.000000 */);
   if(_cond_48){
      _ctx.envelope = (_ctx.envelope + (- fallingRate));
   }
   uint8_t _cond_49;
   _cond_49 = (_ctx.envelope <= 0x0 /* 0.000000 */);
   if(_cond_49){
      _ctx.envelope = 0x0 /* 0.000000 */;
   }
   return fix_mul(_ctx.envelope,_ctx.envelope);
}

void Snare__ctx_type_5_init(Snare__ctx_type_5 &_output_){
   Snare__ctx_type_5 _ctx;
   _ctx.z2 = 0x0 /* 0.000000 */;
   _ctx.z1 = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

void Snare_HP_init(Snare__ctx_type_5 &_output_){
   Snare__ctx_type_5_init(_output_);
   return ;
}

fix16_t Snare_HP(Snare__ctx_type_5 &_ctx, fix16_t x){
   fix16_t g;
   g = 0xccc /* 0.050000 */;
   fix16_t R;
   R = 0x10000 /* 1.000000 */;
   fix16_t inv_den;
   inv_den = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + fix_mul(g,g)));
   fix16_t high;
   high = fix_mul((x + (- fix_mul(((R << 1) + g),_ctx.z1)) + (- _ctx.z2)),inv_den);
   fix16_t band;
   band = (fix_mul(g,high) + _ctx.z1);
   fix16_t low;
   low = (fix_mul(g,band) + _ctx.z2);
   _ctx.z1 = (fix_mul(g,high) + band);
   _ctx.z2 = (fix_mul(g,band) + low);
   return high;
}

void Snare__ctx_type_6_init(Snare__ctx_type_6 &_output_){
   Snare__ctx_type_6 _ctx;
   _ctx.counter = 0;
   _output_ = _ctx;
   return ;
}

void Snare_divideFreq_init(Snare__ctx_type_6 &_output_){
   Snare__ctx_type_6_init(_output_);
   return ;
}

uint8_t Snare_divideFreq(Snare__ctx_type_6 &_ctx, int divider){
   _ctx.counter = (_ctx.counter + 1);
   uint8_t tick;
   tick = 0;
   uint8_t _cond_50;
   _cond_50 = ((_ctx.counter % divider) == 0);
   if(_cond_50){
      _ctx.counter = divider;
      tick = 1;
   }
   return tick;
}

void Snare__ctx_type_7_init(Snare__ctx_type_7 &_output_){
   Snare__ctx_type_7 _ctx;
   _ctx.rate = 0x0 /* 0.000000 */;
   _ctx.phase = 0x0 /* 0.000000 */;
   _ctx.env = 0x0 /* 0.000000 */;
   Snare__ctx_type_0_init(_ctx._inst20);
   Snare__ctx_type_0_init(_ctx._inst19);
   Snare__ctx_type_4_init(_ctx._inst18);
   Snare__ctx_type_6_init(_ctx._inst16);
   Snare__ctx_type_3_init(_ctx._inst13);
   _output_ = _ctx;
   return ;
}

void Snare_customBridgeT_init(Snare__ctx_type_7 &_output_){
   Snare__ctx_type_7_init(_output_);
   return ;
}

fix16_t Snare_customBridgeT(Snare__ctx_type_7 &_ctx, fix16_t tune, uint8_t g, fix16_t envInt, fix16_t dec){
   uint8_t reset;
   uint8_t _cond_51;
   _cond_51 = Snare_edge(_ctx._inst13,g);
   if(_cond_51){
      reset = 1;
   }
   else
   {
      reset = 0;
   }
   uint8_t _cond_52;
   _cond_52 = Snare_divideFreq(_ctx._inst16,16);
   if(_cond_52){
      _ctx.env = (fix_mul(Snare_envelope(_ctx._inst18,(dec >> 4),g),envInt) >> 1);
   }
   uint8_t _cond_53;
   _cond_53 = (Snare_change(_ctx._inst19,tune) || Snare_change(_ctx._inst20,_ctx.env));
   if(_cond_53){
      _ctx.rate = (Snare_pitchToRate((tune + _ctx.env)) + 0x106 /* 0.004000 */);
   }
   if(reset){ _ctx.phase = 0x0 /* 0.000000 */; }
   else
   { _ctx.phase = ((_ctx.phase + _ctx.rate) % 0x10000 /* 1.000000 */); }
   fix16_t sine;
   sine = fix_sin(fix_mul(0x6487e /* 6.283185 */,_ctx.phase));
   return sine;
}

void Snare__ctx_type_8_init(Snare__ctx_type_8 &_output_){
   Snare__ctx_type_8 _ctx;
   _ctx.w1 = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

void Snare_pinker_init(Snare__ctx_type_8 &_output_){
   Snare__ctx_type_8_init(_output_);
   return ;
}

fix16_t Snare_pinker(Snare__ctx_type_8 &_ctx, fix16_t x){
   fix16_t b0;
   b0 = 0x718 /* 0.027713 */;
   fix16_t b1;
   b1 = 0x718 /* 0.027713 */;
   fix16_t a1;
   a1 = -0xf1cf /* -0.944574 */;
   fix16_t w0;
   w0 = (x + (- fix_mul(a1,_ctx.w1)));
   fix16_t y0;
   y0 = (fix_mul(b0,w0) + fix_mul(b1,_ctx.w1));
   _ctx.w1 = w0;
   return y0;
}

void Snare__ctx_type_9_init(Snare__ctx_type_9 &_output_){
   Snare__ctx_type_9 _ctx;
   _ctx.x2 = 0;
   _ctx.x1 = 0;
   Snare__ctx_type_8_init(_ctx._inst24);
   _output_ = _ctx;
   return ;
}

void Snare_noise_init(Snare__ctx_type_9 &_output_){
   Snare__ctx_type_9_init(_output_);
   return ;
}

fix16_t Snare_noise(Snare__ctx_type_9 &_ctx, fix16_t color){
   _ctx.x1 = (((_ctx.x1 * 17389) + 7919) % 32768);
   fix16_t y1;
   y1 = fix_mul(int_to_fix(_ctx.x1),0x2 /* 0.000031 */);
   _ctx.x2 = (((_ctx.x2 * 27449) + 12553) % 32768);
   fix16_t y2;
   y2 = fix_mul(int_to_fix(_ctx.x2),0x2 /* 0.000031 */);
   fix16_t out;
   uint8_t _cond_54;
   _cond_54 = (color > 0x8000 /* 0.500000 */);
   if(_cond_54){ out = Snare_pinker(_ctx._inst24,(y1 + (- y2))); }
   else
   { out = (y1 + (- y2)); }
   return (out << 1);
}

fix16_t Snare_balance(fix16_t bal, fix16_t sig1, fix16_t sig2){
   fix16_t balanceTemp;
   balanceTemp = (bal >> 6);
   fix16_t attenutedSig1;
   fix16_t attenutedSig2;
   fix16_t mixedSig;
   uint8_t _cond_56;
   _cond_56 = (balanceTemp < 0x10000 /* 1.000000 */);
   if(_cond_56){
      attenutedSig1 = fix_mul(sig1,balanceTemp);
      attenutedSig2 = sig2;
   }
   else
   {
      uint8_t _cond_55;
      _cond_55 = (balanceTemp >= 0x10000 /* 1.000000 */);
      if(_cond_55){
         attenutedSig1 = sig1;
         attenutedSig2 = fix_mul(sig2,(0x10000 /* 1.000000 */ + (- (balanceTemp + -0x10000 /* -1.000000 */))));
      }
   }
   mixedSig = (attenutedSig1 + attenutedSig2);
   return mixedSig;
}

void Snare__ctx_type_11_init(Snare__ctx_type_11 &_output_){
   Snare__ctx_type_11 _ctx;
   _ctx.tune = 0x0 /* 0.000000 */;
   _ctx.pitchEnvelopeActive = 0;
   _ctx.pitchEnvInt = 0x0 /* 0.000000 */;
   _ctx.pitchEnv = 0;
   _ctx.noiseDecay = 0x0 /* 0.000000 */;
   _ctx.noiseBalance = 0x0 /* 0.000000 */;
   _ctx.noise = 0x0 /* 0.000000 */;
   _ctx.gate = 0;
   _ctx.decay = 0x0 /* 0.000000 */;
   Snare__ctx_type_5_init(_ctx._inst46);
   Snare__ctx_type_4_init(_ctx._inst45);
   Snare__ctx_type_4_init(_ctx._inst44);
   Snare__ctx_type_7_init(_ctx._inst43);
   Snare__ctx_type_9_init(_ctx._inst42);
   Snare__ctx_type_6_init(_ctx._inst40);
   Snare__ctx_type_3_init(_ctx._inst35);
   _output_ = _ctx;
   return ;
}

void Snare_process_init(Snare__ctx_type_11 &_output_){
   Snare__ctx_type_11_init(_output_);
   return ;
}

fix16_t Snare_process(Snare__ctx_type_11 &_ctx, fix16_t gateI, fix16_t tuneI, fix16_t decayI, fix16_t noiseDecayI, fix16_t noiseBalanceI){
   uint8_t _cond_58;
   _cond_58 = (gateI >= 0x8000 /* 0.500000 */);
   if(_cond_58){
      _ctx.gate = 1;
   }
   else
   {
      uint8_t _cond_57;
      _cond_57 = (gateI < 0x8000 /* 0.500000 */);
      if(_cond_57){
         _ctx.gate = 0;
      }
   }
   _ctx.tune = tuneI;
   _ctx.decay = (decayI >> 1);
   _ctx.noiseDecay = (noiseDecayI >> 1);
   _ctx.noiseBalance = noiseBalanceI;
   uint8_t _cond_59;
   _cond_59 = (_ctx.tune > 0x7c0000 /* 124.000000 */);
   if(_cond_59){
      _ctx.pitchEnv = 1;
   }
   else
   {
      _ctx.pitchEnv = 0;
   }
   uint8_t _cond_62;
   _cond_62 = Snare_edge(_ctx._inst35,_ctx.pitchEnv);
   if(_cond_62){
      uint8_t _cond_61;
      _cond_61 = (_ctx.pitchEnvelopeActive == 0);
      if(_cond_61){
         _ctx.pitchEnvelopeActive = 1;
         _ctx.pitchEnvInt = 0x320000 /* 50.000000 */;
      }
      else
      {
         uint8_t _cond_60;
         _cond_60 = (_ctx.pitchEnvelopeActive == 1);
         if(_cond_60){
            _ctx.pitchEnvelopeActive = 0;
            _ctx.pitchEnvInt = 0x0 /* 0.000000 */;
         }
      }
   }
   fix16_t snare;
   uint8_t _cond_63;
   _cond_63 = Snare_divideFreq(_ctx._inst40,2);
   if(_cond_63){
      _ctx.noise = Snare_noise(_ctx._inst42,0x0 /* 0.000000 */);
   }
   fix16_t sine;
   sine = Snare_customBridgeT(_ctx._inst43,_ctx.tune,_ctx.gate,_ctx.pitchEnvInt,_ctx.decay);
   fix16_t strand;
   strand = fix_mul(fix_mul(_ctx.noise,0x3333 /* 0.200000 */),Snare_envelope(_ctx._inst44,_ctx.noiseDecay,_ctx.gate));
   fix16_t body;
   body = (fix_mul(sine,Snare_envelope(_ctx._inst45,_ctx.decay,_ctx.gate)) << 1);
   snare = Snare_balance(_ctx.noiseBalance,strand,body);
   return Snare_HP(_ctx._inst46,snare);
}

void Kick__ctx_type_0_init(Kick__ctx_type_0 &_output_){
   Kick__ctx_type_0 _ctx;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

void Kick_change_init(Kick__ctx_type_0 &_output_){
   Kick__ctx_type_0_init(_output_);
   return ;
}

uint8_t Kick_change(Kick__ctx_type_0 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

fix16_t Kick_pitchToRate(fix16_t d){
   return fix_mul(0x2 /* 0.000045 */,d);
}

fix16_t Kick_decayToFallingRate(fix16_t d){
   return fix_div(0x10000 /* 1.000000 */,fix_mul(d,0x15b3e7c /* 347.244094 */));
}

void Kick__ctx_type_3_init(Kick__ctx_type_3 &_output_){
   Kick__ctx_type_3 _ctx;
   _ctx.pre = 0;
   _output_ = _ctx;
   return ;
}

void Kick_edge_init(Kick__ctx_type_3 &_output_){
   Kick__ctx_type_3_init(_output_);
   return ;
}

uint8_t Kick_edge(Kick__ctx_type_3 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

void Kick__ctx_type_4_init(Kick__ctx_type_4 &_output_){
   Kick__ctx_type_4 _ctx;
   _ctx.envelope = 0x0 /* 0.000000 */;
   Kick__ctx_type_3_init(_ctx._inst69);
   _output_ = _ctx;
   return ;
}

void Kick_envelope_init(Kick__ctx_type_4 &_output_){
   Kick__ctx_type_4_init(_output_);
   return ;
}

fix16_t Kick_envelope(Kick__ctx_type_4 &_ctx, fix16_t dec, uint8_t g){
   fix16_t fallingRate;
   fallingRate = Kick_decayToFallingRate(((dec >> 1) + 0x50000 /* 5.000000 */));
   uint8_t _cond_93;
   _cond_93 = Kick_edge(_ctx._inst69,g);
   if(_cond_93){
      _ctx.envelope = 0x10000 /* 1.000000 */;
   }
   uint8_t _cond_94;
   _cond_94 = (_ctx.envelope > 0x0 /* 0.000000 */);
   if(_cond_94){
      _ctx.envelope = (_ctx.envelope + (- fallingRate));
   }
   uint8_t _cond_95;
   _cond_95 = (_ctx.envelope <= 0x0 /* 0.000000 */);
   if(_cond_95){
      _ctx.envelope = 0x0 /* 0.000000 */;
   }
   return _ctx.envelope;
}

void Kick__ctx_type_5_init(Kick__ctx_type_5 &_output_){
   Kick__ctx_type_5 _ctx;
   _ctx.z2 = 0x0 /* 0.000000 */;
   _ctx.z1 = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

void Kick_LP_init(Kick__ctx_type_5 &_output_){
   Kick__ctx_type_5_init(_output_);
   return ;
}

fix16_t Kick_LP(Kick__ctx_type_5 &_ctx, fix16_t x){
   fix16_t g;
   g = 0x3333 /* 0.200000 */;
   fix16_t R;
   R = 0x10000 /* 1.000000 */;
   fix16_t inv_den;
   inv_den = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + fix_mul(g,g)));
   fix16_t high;
   high = fix_mul((x + (- fix_mul(((R << 1) + g),_ctx.z1)) + (- _ctx.z2)),inv_den);
   fix16_t band;
   band = (fix_mul(g,high) + _ctx.z1);
   fix16_t low;
   low = (fix_mul(g,band) + _ctx.z2);
   _ctx.z1 = (fix_mul(g,high) + band);
   _ctx.z2 = (fix_mul(g,band) + low);
   return low;
}

void Kick__ctx_type_6_init(Kick__ctx_type_6 &_output_){
   Kick__ctx_type_6 _ctx;
   _ctx.counter = 0;
   _output_ = _ctx;
   return ;
}

void Kick_divideFreq_init(Kick__ctx_type_6 &_output_){
   Kick__ctx_type_6_init(_output_);
   return ;
}

uint8_t Kick_divideFreq(Kick__ctx_type_6 &_ctx, int divider){
   _ctx.counter = (_ctx.counter + 1);
   uint8_t tick;
   tick = 0;
   uint8_t _cond_96;
   _cond_96 = ((_ctx.counter % divider) == 0);
   if(_cond_96){
      _ctx.counter = divider;
      tick = 1;
   }
   return tick;
}

void Kick__ctx_type_7_init(Kick__ctx_type_7 &_output_){
   Kick__ctx_type_7 _ctx;
   _ctx.rate = 0x0 /* 0.000000 */;
   _ctx.phase = 0x0 /* 0.000000 */;
   _ctx.env = 0x0 /* 0.000000 */;
   Kick__ctx_type_0_init(_ctx._inst84);
   Kick__ctx_type_0_init(_ctx._inst83);
   Kick__ctx_type_4_init(_ctx._inst82);
   Kick__ctx_type_6_init(_ctx._inst80);
   Kick__ctx_type_3_init(_ctx._inst77);
   _output_ = _ctx;
   return ;
}

void Kick_customBridgeT_init(Kick__ctx_type_7 &_output_){
   Kick__ctx_type_7_init(_output_);
   return ;
}

fix16_t Kick_customBridgeT(Kick__ctx_type_7 &_ctx, fix16_t tune, uint8_t g, fix16_t envInt, fix16_t dec, fix16_t hardness){
   uint8_t reset;
   uint8_t _cond_97;
   _cond_97 = Kick_edge(_ctx._inst77,g);
   if(_cond_97){
      reset = 1;
   }
   else
   {
      reset = 0;
   }
   uint8_t _cond_98;
   _cond_98 = Kick_divideFreq(_ctx._inst80,16);
   if(_cond_98){
      _ctx.env = (fix_mul(Kick_envelope(_ctx._inst82,(dec >> 4),g),envInt) >> 1);
   }
   uint8_t _cond_99;
   _cond_99 = (Kick_change(_ctx._inst83,tune) || Kick_change(_ctx._inst84,_ctx.env));
   if(_cond_99){
      _ctx.rate = (Kick_pitchToRate((tune + _ctx.env)) + 0x41 /* 0.001000 */);
   }
   if(reset){ _ctx.phase = fix_mul(hardness,0x81 /* 0.001969 */); }
   else
   { _ctx.phase = ((_ctx.phase + _ctx.rate) % 0x10000 /* 1.000000 */); }
   fix16_t sine;
   sine = fix_sin(fix_mul(0x6487e /* 6.283185 */,_ctx.phase));
   return sine;
}

void Kick__ctx_type_8_init(Kick__ctx_type_8 &_output_){
   Kick__ctx_type_8 _ctx;
   _ctx.tune = 0x0 /* 0.000000 */;
   _ctx.pitchEnvInt = 0x0 /* 0.000000 */;
   _ctx.hardness = 0x0 /* 0.000000 */;
   _ctx.gate = 0;
   _ctx.decay = 0x0 /* 0.000000 */;
   Kick__ctx_type_5_init(_ctx._inst92);
   Kick__ctx_type_4_init(_ctx._inst91);
   Kick__ctx_type_7_init(_ctx._inst90);
   _output_ = _ctx;
   return ;
}

void Kick_process_init(Kick__ctx_type_8 &_output_){
   Kick__ctx_type_8_init(_output_);
   return ;
}

fix16_t Kick_process(Kick__ctx_type_8 &_ctx, fix16_t gateI, fix16_t tuneI, fix16_t decayI, fix16_t pitchEnvIntI, fix16_t hardnessI){
   uint8_t _cond_101;
   _cond_101 = (gateI >= 0x8000 /* 0.500000 */);
   if(_cond_101){
      _ctx.gate = 1;
   }
   else
   {
      uint8_t _cond_100;
      _cond_100 = (gateI < 0x8000 /* 0.500000 */);
      if(_cond_100){
         _ctx.gate = 0;
      }
   }
   _ctx.tune = tuneI;
   _ctx.decay = decayI;
   _ctx.pitchEnvInt = pitchEnvIntI;
   _ctx.hardness = hardnessI;
   fix16_t kick;
   fix16_t sine;
   sine = Kick_customBridgeT(_ctx._inst90,_ctx.tune,_ctx.gate,_ctx.pitchEnvInt,_ctx.decay,_ctx.hardness);
   kick = fix_mul(sine,Kick_envelope(_ctx._inst91,_ctx.decay,_ctx.gate));
   return Kick_LP(_ctx._inst92,kick);
}

void HiHat__ctx_type_0_init(HiHat__ctx_type_0 &_output_){
   HiHat__ctx_type_0 _ctx;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

void HiHat_change_init(HiHat__ctx_type_0 &_output_){
   HiHat__ctx_type_0_init(_output_);
   return ;
}

uint8_t HiHat_change(HiHat__ctx_type_0 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

fix16_t HiHat_pitchToRate(fix16_t d){
   return fix_mul(d,0x1 /* 0.000023 */);
}

fix16_t HiHat_decayToFallingRate(fix16_t d){
   return fix_div(0x10000 /* 1.000000 */,fix_mul(d,0x15b3e7c /* 347.244094 */));
}

void HiHat__ctx_type_3_init(HiHat__ctx_type_3 &_output_){
   HiHat__ctx_type_3 _ctx;
   _ctx.pre = 0;
   _output_ = _ctx;
   return ;
}

void HiHat_edge_init(HiHat__ctx_type_3 &_output_){
   HiHat__ctx_type_3_init(_output_);
   return ;
}

uint8_t HiHat_edge(HiHat__ctx_type_3 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

void HiHat__ctx_type_4_init(HiHat__ctx_type_4 &_output_){
   HiHat__ctx_type_4 _ctx;
   _ctx.envelope = 0x0 /* 0.000000 */;
   HiHat__ctx_type_3_init(_ctx._inst107);
   _output_ = _ctx;
   return ;
}

void HiHat_envelope_init(HiHat__ctx_type_4 &_output_){
   HiHat__ctx_type_4_init(_output_);
   return ;
}

fix16_t HiHat_envelope(HiHat__ctx_type_4 &_ctx, fix16_t dec, uint8_t g){
   fix16_t fallingRate;
   fallingRate = HiHat_decayToFallingRate((dec + 0x50000 /* 5.000000 */));
   uint8_t _cond_143;
   _cond_143 = HiHat_edge(_ctx._inst107,g);
   if(_cond_143){
      _ctx.envelope = 0x10000 /* 1.000000 */;
   }
   uint8_t _cond_144;
   _cond_144 = (_ctx.envelope > 0x0 /* 0.000000 */);
   if(_cond_144){
      _ctx.envelope = (_ctx.envelope + (- fallingRate));
   }
   uint8_t _cond_145;
   _cond_145 = (_ctx.envelope <= 0x0 /* 0.000000 */);
   if(_cond_145){
      _ctx.envelope = 0x0 /* 0.000000 */;
   }
   return fix_mul(_ctx.envelope,_ctx.envelope);
}

void HiHat__ctx_type_5_init(HiHat__ctx_type_5 &_output_){
   HiHat__ctx_type_5 _ctx;
   _ctx.z2 = 0x0 /* 0.000000 */;
   _ctx.z1 = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

void HiHat_HP_init(HiHat__ctx_type_5 &_output_){
   HiHat__ctx_type_5_init(_output_);
   return ;
}

fix16_t HiHat_HP(HiHat__ctx_type_5 &_ctx, fix16_t x){
   fix16_t g;
   g = 0x2666 /* 0.150000 */;
   fix16_t R;
   R = 0x10000 /* 1.000000 */;
   fix16_t inv_den;
   inv_den = fix_div(0x10000 /* 1.000000 */,(0x10000 /* 1.000000 */ + fix_mul(g,g)));
   fix16_t high;
   high = fix_mul((x + (- fix_mul(((R << 1) + g),_ctx.z1)) + (- _ctx.z2)),inv_den);
   fix16_t band;
   band = (fix_mul(g,high) + _ctx.z1);
   fix16_t low;
   low = (fix_mul(g,band) + _ctx.z2);
   _ctx.z1 = (fix_mul(g,high) + band);
   _ctx.z2 = (fix_mul(g,band) + low);
   return high;
}

void HiHat__ctx_type_6_init(HiHat__ctx_type_6 &_output_){
   HiHat__ctx_type_6 _ctx;
   _ctx.counter = 0;
   _output_ = _ctx;
   return ;
}

void HiHat_divideFreq_init(HiHat__ctx_type_6 &_output_){
   HiHat__ctx_type_6_init(_output_);
   return ;
}

uint8_t HiHat_divideFreq(HiHat__ctx_type_6 &_ctx, int divider){
   _ctx.counter = (_ctx.counter + 1);
   uint8_t tick;
   tick = 0;
   uint8_t _cond_146;
   _cond_146 = ((_ctx.counter % divider) == 0);
   if(_cond_146){
      _ctx.counter = divider;
      tick = 1;
   }
   return tick;
}

void HiHat__ctx_type_7_init(HiHat__ctx_type_7 &_output_){
   HiHat__ctx_type_7 _ctx;
   _ctx.rate = 0x0 /* 0.000000 */;
   _ctx.phase = 0x0 /* 0.000000 */;
   HiHat__ctx_type_0_init(_ctx._inst115);
   _output_ = _ctx;
   return ;
}

void HiHat_pulse_init(HiHat__ctx_type_7 &_output_){
   HiHat__ctx_type_7_init(_output_);
   return ;
}

fix16_t HiHat_pulse(HiHat__ctx_type_7 &_ctx, fix16_t tune, fix16_t pw){
   fix16_t pulseWidth;
   pulseWidth = pw;
   uint8_t widthReached;
   uint8_t _cond_147;
   _cond_147 = HiHat_change(_ctx._inst115,tune);
   if(_cond_147){
      _ctx.rate = HiHat_pitchToRate(tune);
   }
   _ctx.phase = ((_ctx.phase + _ctx.rate) % 0x10000 /* 1.000000 */);
   uint8_t _cond_148;
   _cond_148 = (_ctx.phase >= pulseWidth);
   if(_cond_148){
      widthReached = 1;
   }
   else
   {
      widthReached = 0;
   }
   fix16_t pulse;
   if(widthReached){ pulse = 0x10000 /* 1.000000 */; }
   else
   { pulse = -0x10000 /* -1.000000 */; }
   return pulse;
}

void HiHat__ctx_type_8_init(HiHat__ctx_type_8 &_output_){
   HiHat__ctx_type_8 _ctx;
   _ctx.w1 = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

void HiHat_pinker_init(HiHat__ctx_type_8 &_output_){
   HiHat__ctx_type_8_init(_output_);
   return ;
}

fix16_t HiHat_pinker(HiHat__ctx_type_8 &_ctx, fix16_t x){
   fix16_t b0;
   b0 = 0x718 /* 0.027713 */;
   fix16_t b1;
   b1 = 0x718 /* 0.027713 */;
   fix16_t a1;
   a1 = -0xf1cf /* -0.944574 */;
   fix16_t w0;
   w0 = (x + (- fix_mul(a1,_ctx.w1)));
   fix16_t y0;
   y0 = (fix_mul(b0,w0) + fix_mul(b1,_ctx.w1));
   _ctx.w1 = w0;
   return y0;
}

void HiHat__ctx_type_9_init(HiHat__ctx_type_9 &_output_){
   HiHat__ctx_type_9 _ctx;
   _ctx.x2 = 0;
   _ctx.x1 = 0;
   HiHat__ctx_type_8_init(_ctx._inst121);
   _output_ = _ctx;
   return ;
}

void HiHat_noise_init(HiHat__ctx_type_9 &_output_){
   HiHat__ctx_type_9_init(_output_);
   return ;
}

fix16_t HiHat_noise(HiHat__ctx_type_9 &_ctx, fix16_t color){
   _ctx.x1 = (((_ctx.x1 * 17389) + 7919) % 32768);
   fix16_t y1;
   y1 = fix_mul(int_to_fix(_ctx.x1),0x2 /* 0.000031 */);
   _ctx.x2 = (((_ctx.x2 * 27449) + 12553) % 32768);
   fix16_t y2;
   y2 = fix_mul(int_to_fix(_ctx.x2),0x2 /* 0.000031 */);
   fix16_t out;
   uint8_t _cond_149;
   _cond_149 = (color > 0x8000 /* 0.500000 */);
   if(_cond_149){ out = HiHat_pinker(_ctx._inst121,(y1 + (- y2))); }
   else
   { out = (y1 + (- y2)); }
   return (out << 1);
}

fix16_t HiHat_balance(fix16_t bal, fix16_t sig1, fix16_t sig2){
   fix16_t balanceTemp;
   balanceTemp = (bal >> 6);
   fix16_t attenutedSig1;
   fix16_t attenutedSig2;
   fix16_t mixedSig;
   uint8_t _cond_151;
   _cond_151 = (balanceTemp < 0x10000 /* 1.000000 */);
   if(_cond_151){
      attenutedSig1 = fix_mul(sig1,balanceTemp);
      attenutedSig2 = sig2;
   }
   else
   {
      uint8_t _cond_150;
      _cond_150 = (balanceTemp >= 0x10000 /* 1.000000 */);
      if(_cond_150){
         attenutedSig1 = sig1;
         attenutedSig2 = fix_mul(sig2,(0x10000 /* 1.000000 */ + (- (balanceTemp + -0x10000 /* -1.000000 */))));
      }
   }
   mixedSig = (attenutedSig1 + attenutedSig2);
   return mixedSig;
}

void HiHat__ctx_type_11_init(HiHat__ctx_type_11 &_output_){
   HiHat__ctx_type_11 _ctx;
   _ctx.tune = 0x0 /* 0.000000 */;
   _ctx.square2 = 0x0 /* 0.000000 */;
   _ctx.square1 = 0x0 /* 0.000000 */;
   _ctx.openedHiHat = 0x0 /* 0.000000 */;
   _ctx.noiseBalance = 0x0 /* 0.000000 */;
   _ctx.noise = 0x0 /* 0.000000 */;
   _ctx.gate2 = 0;
   _ctx.gate1 = 0;
   _ctx.decay2 = 0x0 /* 0.000000 */;
   _ctx.decay1 = 0x0 /* 0.000000 */;
   _ctx.closedHiHat = 0x0 /* 0.000000 */;
   HiHat__ctx_type_5_init(_ctx._inst142);
   HiHat__ctx_type_4_init(_ctx._inst141);
   HiHat__ctx_type_4_init(_ctx._inst140);
   HiHat__ctx_type_7_init(_ctx._inst139);
   HiHat__ctx_type_7_init(_ctx._inst138);
   HiHat__ctx_type_6_init(_ctx._inst136);
   HiHat__ctx_type_9_init(_ctx._inst135);
   HiHat__ctx_type_6_init(_ctx._inst133);
   _output_ = _ctx;
   return ;
}

void HiHat_process_init(HiHat__ctx_type_11 &_output_){
   HiHat__ctx_type_11_init(_output_);
   return ;
}

fix16_t HiHat_process(HiHat__ctx_type_11 &_ctx, fix16_t gate1I, fix16_t gate2I, fix16_t tuneI, fix16_t decay1I, fix16_t decay2I, fix16_t noiseBalanceI){
   uint8_t _cond_153;
   _cond_153 = (gate1I >= 0x8000 /* 0.500000 */);
   if(_cond_153){
      _ctx.gate1 = 1;
   }
   else
   {
      uint8_t _cond_152;
      _cond_152 = (gate1I < 0x8000 /* 0.500000 */);
      if(_cond_152){
         _ctx.gate1 = 0;
      }
   }
   uint8_t _cond_155;
   _cond_155 = (gate2I >= 0x8000 /* 0.500000 */);
   if(_cond_155){
      _ctx.gate2 = 1;
   }
   else
   {
      uint8_t _cond_154;
      _cond_154 = (gate2I < 0x8000 /* 0.500000 */);
      if(_cond_154){
         _ctx.gate2 = 0;
      }
   }
   _ctx.tune = (tuneI >> 1);
   _ctx.decay1 = (decay1I >> 3);
   _ctx.decay2 = (decay2I >> 2);
   _ctx.noiseBalance = noiseBalanceI;
   uint8_t _cond_156;
   _cond_156 = HiHat_divideFreq(_ctx._inst133,2);
   if(_cond_156){
      _ctx.noise = fix_mul(HiHat_noise(_ctx._inst135,0x0 /* 0.000000 */),0x3333 /* 0.200000 */);
   }
   uint8_t _cond_157;
   _cond_157 = HiHat_divideFreq(_ctx._inst136,4);
   if(_cond_157){
      _ctx.square1 = HiHat_pulse(_ctx._inst138,fix_mul(0x2c00000 /* 704.000000 */,_ctx.tune),0x8000 /* 0.500000 */);
      _ctx.square2 = HiHat_pulse(_ctx._inst139,fix_mul(0x4bc0000 /* 1212.000000 */,_ctx.tune),0x8000 /* 0.500000 */);
   }
   fix16_t metalNoise;
   metalNoise = (_ctx.square1 + _ctx.square2);
   metalNoise = fix_mul(metalNoise,0x1999 /* 0.100000 */);
   fix16_t filteredNoise;
   filteredNoise = HiHat_balance(_ctx.noiseBalance,(_ctx.noise >> 1),(metalNoise >> 1));
   _ctx.closedHiHat = fix_mul(filteredNoise,HiHat_envelope(_ctx._inst140,_ctx.decay1,_ctx.gate1));
   _ctx.openedHiHat = fix_mul(filteredNoise,HiHat_envelope(_ctx._inst141,_ctx.decay2,_ctx.gate2));
   return HiHat_HP(_ctx._inst142,(_ctx.closedHiHat + _ctx.openedHiHat));
}

void Brain__ctx_type_0_init(Brain__ctx_type_0 &_output_){
   Brain__ctx_type_0 _ctx;
   _ctx.voice2Sound = 0;
   fix_init_array(5,0x0 /* 0.000000 */,_ctx.voice2Param);
   _ctx.voice2 = 0x0 /* 0.000000 */;
   _ctx.voice1Sound = 0;
   fix_init_array(5,0x0 /* 0.000000 */,_ctx.voice1Param);
   _ctx.voice1 = 0x0 /* 0.000000 */;
   fix_init_array(5,0x0 /* 0.000000 */,_ctx.snareParam);
   fix_init_array(5,0x0 /* 0.000000 */,_ctx.kickParam);
   fix_init_array(6,0x0 /* 0.000000 */,_ctx.hiHatParam);
   HiHat__ctx_type_11_init(_ctx._inst166);
   Snare__ctx_type_11_init(_ctx._inst163);
   Kick__ctx_type_8_init(_ctx._inst160);
   _output_ = _ctx;
   return ;
}

void Brain_process_init(Brain__ctx_type_0 &_output_){
   Brain__ctx_type_0_init(_output_);
   return ;
}

fix16_t Brain_process(Brain__ctx_type_0 &_ctx, fix16_t input){
   uint8_t _cond_218;
   _cond_218 = (_ctx.voice1Sound == 0);
   if(_cond_218){
      _ctx.voice1 = Kick_process(_ctx._inst160,_ctx.kickParam[0],_ctx.kickParam[1],_ctx.kickParam[2],_ctx.kickParam[3],_ctx.kickParam[4]);
   }
   else
   {
      uint8_t _cond_217;
      _cond_217 = (_ctx.voice1Sound == 1);
      if(_cond_217){
         _ctx.voice1 = Snare_process(_ctx._inst163,_ctx.snareParam[0],_ctx.snareParam[1],_ctx.snareParam[2],_ctx.snareParam[3],_ctx.snareParam[4]);
      }
      else
      {
         uint8_t _cond_216;
         _cond_216 = (_ctx.voice1Sound == 2);
         if(_cond_216){
            _ctx.voice1 = HiHat_process(_ctx._inst166,_ctx.hiHatParam[0],_ctx.hiHatParam[1],_ctx.hiHatParam[2],_ctx.hiHatParam[3],_ctx.hiHatParam[4],_ctx.hiHatParam[5]);
         }
      }
   }
   uint8_t _cond_221;
   _cond_221 = (_ctx.voice2Sound == 0);
   if(bool_not(_cond_221)){
      uint8_t _cond_220;
      _cond_220 = (_ctx.voice2Sound == 1);
      if(bool_not(_cond_220)){
         uint8_t _cond_219;
         _cond_219 = (_ctx.voice2Sound == 2);
         if(_cond_219){
         }
      }
   }
   return (_ctx.voice1 >> 1);
}

void Brain_noteOn_init(Brain__ctx_type_0 &_output_){
   Brain__ctx_type_0_init(_output_);
   return ;
}

void Brain_noteOn(Brain__ctx_type_0 &_ctx, int note, int velocity, int channel){
   uint8_t _cond_222;
   _cond_222 = (note == 32);
   if(_cond_222){
      _ctx.kickParam[0] = 0x10000 /* 1.000000 */;
   }
   uint8_t _cond_223;
   _cond_223 = (note == 33);
   if(_cond_223){
      _ctx.snareParam[0] = 0x10000 /* 1.000000 */;
   }
   uint8_t _cond_224;
   _cond_224 = (note == 34);
   if(_cond_224){
      _ctx.hiHatParam[0] = 0x10000 /* 1.000000 */;
   }
   uint8_t _cond_225;
   _cond_225 = (note == 35);
   if(_cond_225){
      _ctx.hiHatParam[1] = 0x10000 /* 1.000000 */;
   }
}

void Brain_noteOff_init(Brain__ctx_type_0 &_output_){
   Brain__ctx_type_0_init(_output_);
   return ;
}

void Brain_noteOff(Brain__ctx_type_0 &_ctx, int note, int channel){
   uint8_t _cond_226;
   _cond_226 = (note == 32);
   if(_cond_226){
      _ctx.kickParam[0] = 0x0 /* 0.000000 */;
   }
   uint8_t _cond_227;
   _cond_227 = (note == 33);
   if(_cond_227){
      _ctx.snareParam[0] = 0x0 /* 0.000000 */;
   }
   uint8_t _cond_228;
   _cond_228 = (note == 34);
   if(_cond_228){
      _ctx.hiHatParam[0] = 0x0 /* 0.000000 */;
   }
   uint8_t _cond_229;
   _cond_229 = (note == 35);
   if(_cond_229){
      _ctx.hiHatParam[1] = 0x0 /* 0.000000 */;
   }
}

void Brain_controlChange_init(Brain__ctx_type_0 &_output_){
   Brain__ctx_type_0_init(_output_);
   return ;
}

void Brain_controlChange(Brain__ctx_type_0 &_ctx, int control, int value, int channel){
   uint8_t _cond_232;
   _cond_232 = (control == 28);
   if(_cond_232){
      uint8_t _cond_231;
      _cond_231 = (int_to_fix(value) < 0x230000 /* 35.000000 */);
      if(_cond_231){
         _ctx.voice1Sound = 0;
      }
      else
      {
         uint8_t _cond_230;
         _cond_230 = (int_to_fix(value) < 0x4b0000 /* 75.000000 */);
         if(_cond_230){
            _ctx.voice1Sound = 1;
         }
         else
         {
            _ctx.voice1Sound = 2;
         }
      }
   }
   uint8_t _cond_235;
   _cond_235 = (control == 29);
   if(_cond_235){
      uint8_t _cond_234;
      _cond_234 = (int_to_fix(value) < 0x230000 /* 35.000000 */);
      if(_cond_234){
         _ctx.voice2Sound = 0;
      }
      else
      {
         uint8_t _cond_233;
         _cond_233 = (int_to_fix(value) < 0x4b0000 /* 75.000000 */);
         if(_cond_233){
            _ctx.voice2Sound = 1;
         }
         else
         {
            _ctx.voice2Sound = 2;
         }
      }
   }
   uint8_t _cond_243;
   _cond_243 = (control == 30);
   if(_cond_243){
      _ctx.kickParam[1] = int_to_fix(value);
   }
   else
   {
      uint8_t _cond_242;
      _cond_242 = (control == 31);
      if(_cond_242){
         _ctx.kickParam[2] = int_to_fix(value);
      }
      else
      {
         uint8_t _cond_241;
         _cond_241 = (control == 33);
         if(_cond_241){
            _ctx.kickParam[3] = int_to_fix(value);
         }
         else
         {
            uint8_t _cond_240;
            _cond_240 = (control == 34);
            if(_cond_240){
               _ctx.kickParam[4] = int_to_fix(value);
            }
            else
            {
               uint8_t _cond_239;
               _cond_239 = (control == 35);
               if(_cond_239){
                  _ctx.snareParam[1] = int_to_fix(value);
               }
               else
               {
                  uint8_t _cond_238;
                  _cond_238 = (control == 36);
                  if(_cond_238){
                     _ctx.snareParam[2] = int_to_fix(value);
                  }
                  else
                  {
                     uint8_t _cond_237;
                     _cond_237 = (control == 37);
                     if(_cond_237){
                        _ctx.snareParam[3] = int_to_fix(value);
                     }
                     else
                     {
                        uint8_t _cond_236;
                        _cond_236 = (control == 38);
                        if(_cond_236){
                           _ctx.snareParam[4] = int_to_fix(value);
                        }
                     }
                  }
               }
            }
         }
      }
   }
   uint8_t _cond_247;
   _cond_247 = (control == 39);
   if(_cond_247){
      _ctx.hiHatParam[2] = int_to_fix(value);
   }
   else
   {
      uint8_t _cond_246;
      _cond_246 = (control == 40);
      if(_cond_246){
         _ctx.hiHatParam[3] = ((int_to_fix(value) << 1) + 0x10000 /* 1.000000 */);
      }
      else
      {
         uint8_t _cond_245;
         _cond_245 = (control == 41);
         if(_cond_245){
            _ctx.hiHatParam[4] = int_to_fix(value);
         }
         else
         {
            uint8_t _cond_244;
            _cond_244 = (control == 42);
            if(_cond_244){
               _ctx.hiHatParam[5] = int_to_fix(value);
            }
         }
      }
   }
}

void Brain_default_init(Brain__ctx_type_0 &_output_){
   Brain__ctx_type_0_init(_output_);
   return ;
}

void Brain_default(Brain__ctx_type_0 &_ctx){
   _ctx.kickParam[0] = 0x0 /* 0.000000 */;
   _ctx.kickParam[1] = 0x200000 /* 32.000000 */;
   _ctx.kickParam[2] = 0x200000 /* 32.000000 */;
   _ctx.kickParam[3] = 0x200000 /* 32.000000 */;
   _ctx.kickParam[4] = 0x200000 /* 32.000000 */;
   _ctx.snareParam[0] = 0x0 /* 0.000000 */;
   _ctx.snareParam[1] = 0x200000 /* 32.000000 */;
   _ctx.snareParam[2] = 0x200000 /* 32.000000 */;
   _ctx.snareParam[3] = 0x200000 /* 32.000000 */;
   _ctx.snareParam[4] = 0x200000 /* 32.000000 */;
   _ctx.hiHatParam[0] = 0x0 /* 0.000000 */;
   _ctx.hiHatParam[1] = 0x0 /* 0.000000 */;
   _ctx.hiHatParam[2] = 0x200000 /* 32.000000 */;
   _ctx.hiHatParam[3] = 0x200000 /* 32.000000 */;
   _ctx.hiHatParam[4] = 0x200000 /* 32.000000 */;
   _ctx.hiHatParam[5] = 0x200000 /* 32.000000 */;
}



void Brain::update(void)
{
  audio_block_t *block;
  short *bp;

  block = allocate();
  if (block) {
    bp = block->data;
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        fix16_t v = Brain_process(data, 0);
        *bp++ = (int16_t)(v / 2);
      }

    transmit(block, 0);
    release(block);
  }
}

