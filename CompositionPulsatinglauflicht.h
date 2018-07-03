#ifndef COMPOSITIONPULSATINLAUFLICHT_H
#define COMPOSITIONFORWARDBACKWARD_H

#include "BaseTimedEvent.h"
#include "EffectPulsating.h"
#include <stdint.h>



class CompositionPulsatinglauflicht: public BaseTimedEvent {
    public:
        CompositionPulsatinglauflicht(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs);
        void validRun() override;
    private:
        void updateValuesAndOutput(uint8_t i);
        int8_t directions[3];
        int16_t values[3];
};
#endif