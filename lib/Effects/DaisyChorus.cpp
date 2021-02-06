#include "DaisyChorus.h"

void DaisyChorus::Setup(daisy::DaisySeed *hardware)
{
    hw = hardware;

    // Initialize the knobs
    boostKnob.Init(hw, KNOB_1_CHN, boostLevel, boostLevelMin, boostLevelMax);

    // Initialize the Chorus
    float sample_rate = hw->AudioSampleRate();
    chorus.Init(sample_rate);
    chorus.SetLfoFreq(.33f, .2f);
    chorus.SetLfoDepth(1.f, 1.f);
    chorus.SetDelay(.75f, .9f);
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
}

char *DaisyChorus::GetEffectName()
{
    return (char *)"Chorus";
}