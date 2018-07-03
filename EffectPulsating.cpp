#include "EffectPulsating.h"

EffectPulsating::EffectPulsating(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs)
:BaseTimedEvent(steps, nled, brightness, delayMs, true),
direction(1),
value(0)  {}

void EffectPulsating::validRun() {
    this->value += this->direction;
    if (this->value < 1) {
        this->direction = 1;
    }
    if(this->value > this->brightness-1) {
        this->direction = -1;
    }
    this->setAll();
}
void EffectPulsating::setAll() {
    for(int i =0; i<this->nled; i++) {
        analogWrite(this->steps[i], this->value);
    }
}

void EffectPulsating::setValue(int16_t value) {
    this->value = value;
}
