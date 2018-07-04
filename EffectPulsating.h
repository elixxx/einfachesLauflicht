#ifndef EFFECTPULSATION_H
#define EFFECTPULSATION_H
#include "BaseTimedEvent.h"

class EffectPulsating: public BaseTimedEvent
 {
    public:
        EffectPulsating(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs);
        void validRun();
        void setValue(int16_t value);
/*         void setDelayMs(uint16_t delay);
 */
    protected:
        void setAll();
        int8_t direction;
        int16_t value;

};
#endif