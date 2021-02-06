#ifndef EFFECT_TYPE_H
#define EFFECT_TYPE_H

#include "IEffect.h"
#include "../lib/Effects/SimpleBypass.h"
#include "../lib/Effects/DaisyChorus.h"
#include "../lib/Effects/DaisyFlanger.h"

// Effect Objects
SimpleBypass simpleBypass;
DaisyChorus chorus;
DaisyFlanger flanger;

/**
 * The rotary encoder is using Gray code, not standard hex.
 * The sequence of decimal numbers that it produces is as follows:
 * 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
 */
enum EffectType
{
    SIMPLEBYPASS = 0,
    DAISYCHORUS = 1,
    DAISYFLANGER = 3,

    UNSET = 99
};

/**
 * Returns the effect object based on the passed in enum
 */
extern IEffect *GetEffectObject(EffectType type)
{
    switch (type)
    {
    case DAISYCHORUS:
        return (IEffect *)&chorus;
    case DAISYFLANGER:
        return (IEffect *)&flanger;
    case SIMPLEBYPASS:
    case UNSET:
    default:
        return (IEffect *)&simpleBypass;
    }
};

#endif