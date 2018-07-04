#ifndef COMPOSITIONFORWARDBACKWARD_H
#define COMPOSITIONFORWARDBACKWARD_H

#include "EffectLauflicht.h"
#include <stdint.h>



class CompositionForwardBackward: public EffectLauflicht {
    public:
        CompositionForwardBackward(uint8_t* steps,uint8_t nled, uint16_t& brightness, bool isDim);
        void validRun() override;
        bool isFinished();
        void setDurationMs(uint16_t durationMs);
    private:
        unsigned long finishTime;
};
#endif