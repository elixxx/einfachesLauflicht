#include "BaseTimedEvent.h"
#include <Arduino.h>

BaseTimedEvent::BaseTimedEvent(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs, bool isDim):
    brightness(brightness),
    steps(steps),
    stepId(0),
    msState(millis()),
    nled(nled),
    isDim(isDim) {
        this->setDelayMs(delayMs);
    }

void BaseTimedEvent::step() {
    if ( this->msState  <(millis() - this->delayMs) ) {
        this->validRun();
        this->stepId++;
        this->msState = millis();
    }
 }

 void BaseTimedEvent::setDelayMs(uint16_t delayMs) {
     this->delayMs=delayMs;
 }

 uint16_t BaseTimedEvent::getDelayMS() {
     return this->delayMs;
 }
 void BaseTimedEvent::validRun() {
     
 }

 void BaseTimedEvent::setDurationMs(uint16_t durationMs) {
     this->finishTime = millis() + durationMs;
 }

 bool BaseTimedEvent::isFinished() {
     return ( this->finishTime <= millis());
 }