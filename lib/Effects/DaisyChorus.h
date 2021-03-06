#ifndef CHORUS_H
#define CHORUS_H

#include "daisy_seed.h"
#include "daisysp.h"
#include "../../../include/IEffect.h"
#include "../../../include/PedalConfig.h"
#include "../Inputs/Knob.h"

using namespace daisy;
using namespace daisysp;

/**********************************************
 * Chorus Effect
 * 
 * SPST 1 - 
 * SPST 2 - 
 * SPST 3 - 
 * SPST 4 - 
 * 
 * SPDT 1 - 
 * SPDT 2 - 
 * 
 * Knob 1 - Volume Boost
 * Knob 2 - LFO Rate
 * Knob 3 - Width
 * Knob 4 - Delay
 * 
 * LED 1 - 
 * LED 2 - 
 * LED 3 - 
 * LED 4 - 
 **********************************************/

class DaisyChorus : public IEffect
{
public:
    void Setup(daisy::DaisySeed *hardware);
    void Cleanup();
    void AudioCallback(float **in, float **out, size_t size);
    void Loop();
    char *GetEffectName();

private:
    const float boostLevelMin = 10.0f;
    const float boostLevelMax = 30.0f;
    const float rateMin = 0.0f;
    const float rateMax = 1.0f;

    float boostLevel = 10.0f;
    float rate = 0.0f;
    float width = 0.0f;
    float delay = 0.0f;

    Knob boostKnob;
    Knob rateKnob;
    Knob widthKnob;
    Knob delayKnob;

    Chorus chorus;
};

#endif