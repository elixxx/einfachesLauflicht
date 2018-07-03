#include "CompositionForwardBackward.h"

CompositionForwardBackward::CompositionForwardBackward(uint8_t* steps,uint8_t nled, uint16_t& brightness, bool isDim)
:EffectLauflicht(steps, nled, brightness, 200, isDim)  {
    this->setDurationMs(5000);
}

void CompositionForwardBackward::validRun() {
    EffectLauflicht::validRun();
    if(this->isFinished()) {
        this->backward(!this->isBackward());
        this->setDurationMs(5000);

    } 
}
