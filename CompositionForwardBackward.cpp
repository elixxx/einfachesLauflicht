#include "CompositionForwardBackward.h"

CompositionForwardBackward::CompositionForwardBackward(uint8_t* steps,uint8_t nled, uint16_t& brightness, bool isDim)
:EffectLauflicht(steps, nled, brightness, 200, isDim)  {
    this->setDurationMs(5000);
}

void CompositionForwardBackward::validRun() {
    EffectLauflicht::validRun();
    if(this->EffectLauflicht::isFinished()) {
        this->backward(!this->isBackward());
        this->EffectLauflicht::setDurationMs(2500);

    } 
}
 void CompositionForwardBackward::setDurationMs(uint16_t durationMs) {
     this->finishTime = millis() + durationMs;
 }

 bool CompositionForwardBackward::isFinished() {
     return ( this->finishTime <= millis());
 }