#include "DaisyChorus.h"

void DaisyChorus::Setup(daisy::DaisySeed *hardware)
{
    hw = hardware;

    // Initialize the knobs
    boostKnob.Init(hw, KNOB_1_CHN, boostLevel, boostLevelMin, boostLevelMax);
    rateKnob.Init(hw, KNOB_2_CHN, rate, rateMin, rateMax);
    widthKnob.Init(hw, KNOB_3_CHN, width);

    // Initialize the Chorus
    float sample_rate = hw->AudioSampleRate();
    chorus.Init(sample_rate);
    chorus.SetLfoFreq(rate);
    chorus.SetLfoDepth(width);
    chorus.SetDelay(.75f);
}

void DaisyChorus::AudioCallback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        float wet, dry;

        // Adjust the input signal by the boost
        dry = in[AUDIO_IN_CH][i] * boostLevel;

        // Process the chorus
        wet = chorus.Process(dry);

        // Output the processed signal
        out[AUDIO_OUT_CH][i] = wet;
    }
}

void DaisyChorus::Cleanup()
{
}

void DaisyChorus::Loop()
{
    // Knob 1 controls the boost level
    if (boostKnob.SetNewValue(boostLevel))
    {
        debugPrintlnF(hw, "Updated the boost level to: %f", boostLevel);
    }

    // Knob 2 controls the LFO rate
    if (rateKnob.SetNewValue(rate))
    {
        chorus.SetLfoFreq(rate);

        debugPrintlnF(hw, "Updated the rate to: %f", rate);
    }

    // Knob 3 controls the LFO width
    if (widthKnob.SetNewValue(width))
    {
        chorus.SetLfoDepth(width);

        debugPrintlnF(hw, "Updated the width to: %f", width);
    }
}

char *DaisyChorus::GetEffectName()
{
    return (char *)"Chorus";
}