#include "BaseTimedEvent.h"

class EffectRandom: public BaseTimedEvent
 {
    public:
        EffectRandom(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs, bool isDim);
        void validRun();
        void setDelayMs(uint16_t delay);

    private:
        int8_t old;

};