#ifndef EFFECTLAUFLICHT_H
#define EFFECTLAUFLICHT_H
#include "BaseTimedEvent.h"

class EffectLauflicht: public BaseTimedEvent
 {
    public:
        EffectLauflicht(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs, bool isDim);
        virtual void validRun();
        void setDelayMs(uint16_t delayMs);
        void backward(bool backward);
        bool isBackward();

    private:
        int8_t direction;
        int8_t ledId;

};

#endif