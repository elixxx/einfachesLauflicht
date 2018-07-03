#include "EffectLauflicht.h"

EffectLauflicht::EffectLauflicht(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs, bool isDim)
:BaseTimedEvent(steps, nled, brightness, delayMs, isDim),
direction(1),
ledId(0)  {}

void EffectLauflicht::validRun() {
        /* uint8_t step_id = this->stepId %4; */
        if(this->isDim) {
            analogWrite(steps[ledId],0);
        } else {
            digitalWrite(steps[ledId],LOW);
        }
        
        this->ledId = (this->ledId + this->direction) % this->nled;
        if ( this->ledId <0) {
            this->ledId = this->nled-1;
        }
        if(this->isDim) {
            analogWrite(steps[this->ledId], this->brightness);
        } else {
            digitalWrite(steps[this->ledId],HIGH);
        }
}

 void EffectLauflicht::backward(bool backward) {
     this->direction = (backward)?-1:1;
 }

 void EffectLauflicht::setDelayMs(uint16_t delayMs) {
     this->delayMs=(delayMs<100)?100:delayMs;
 }

 bool EffectLauflicht::isBackward() {
     return (this->direction==-1);
 }