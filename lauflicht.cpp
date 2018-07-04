#include "lauflicht.h"
#include <TinySoftPwm.h>

Lauflicht::Lauflicht(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs, bool isDim):
    brightness(brightness),
    steps(steps),
    step_id(0),
    direction(1),
    msState(millis()),
    nled(nled),
    isDim(isDim) {
        this->setDelayMs(delayMs);
        digitalWrite(steps[this->step_id],0);

    }

void Lauflicht::step() {
    if ( this->msState  <(millis() - this->delayMs) ) {
        if(this->isDim) {
            analogWrite(steps[this->step_id],0);
        } else {
            digitalWrite(steps[this->step_id],LOW);
        }
        
        this->step_id = (this->step_id + 1) % this->nled;
        if ( this->step_id <0) {
            this->step_id = this->nled-1;
        }
        if(this->isDim) {
            analogWrite(steps[this->step_id], this->brightness);
        } else {
            digitalWrite(steps[this->step_id],HIGH);
        }
        this->msState = millis();
    }
 }

 void Lauflicht::backward(bool backward) {
     if(backward) {
         this->direction=-1;
     } else {
         this->direction=1;
     }
 }

 void Lauflicht::setDelayMs(uint16_t delayMs) {
     this->delayMs=(delayMs<100)?100:delayMs;
 }

 bool Lauflicht::isFinished() {
     return false;
 }

 uint16_t Lauflicht::getDelayMS() {
     return this->delayMs;
 }