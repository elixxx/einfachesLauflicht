#include "EffectRandom.h"
#include <stdint.h>


EffectRandom::EffectRandom(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs, bool isDim)
:BaseTimedEvent(steps, nled, brightness, delayMs, isDim)  {}

void EffectRandom::validRun() {
    int newer = random(-1,this->nled);
    if (newer == this->old) {
        return;
    }
    if(isDim) {
        analogWrite(this->steps[old], 0);
        analogWrite(this->steps[newer], this->brightness);
    } else {
        digitalWrite(this->steps[old], LOW);
        digitalWrite(this->steps[newer], HIGH);
    }
    this->old = newer;
    this->msState = millis();
    
}

void EffectRandom::setDelayMs(uint16_t delay) {
    this->delayMs=(delay<20)?20:delayMs;

}