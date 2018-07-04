#include "CompositionPulsatinglauflicht.h"

CompositionPulsatinglauflicht::CompositionPulsatinglauflicht(uint8_t* steps,uint8_t nled, uint16_t& brightness, uint16_t delayMs)
:BaseTimedEvent(steps, nled, brightness, delayMs, true), old_brightness(brightness)  {
    this->values[0] = 0;
    this->values[1] = 126;
    this->values[2] = 255;
    this->directions[0] = 1;
    this->directions[1] = 1;
    this->directions[2] = -1;
/*     this->pulsator = new EffectPulsating*[5];
 *//*     this->pulsator = (EffectPulsating*) malloc(sizeof(EffectPulsating)*this->nled);
/*   this->e1 = new EffectPulsating(&steps[0], 2, this->brightness, delayMs); 
    this->e2 = new EffectPulsating(&steps[0], 2, this->brightness, delayMs); 
    this->e3 = new EffectPulsating(&steps[0], 2, this->brightness, delayMs);   
    for(int i=0; i<this->nled; i++) {
         this->pulsator[i] = new EffectPulsating(steps, 2, this->brightness, delayMs); */
/*           new(this->pulsator[i]) EffectPulsating(&steps[i], 1, this->brightness, delayMs);
 */       /*   this->pulsator[i]->setValue((255/(this->nled-1))*i);
         this->pulsator[i]->validRun(); */
    
}


void CompositionPulsatinglauflicht::validRun() {
    for(int i=0; i<this->nled; i++) {
        this->updateValuesAndOutput(i);
    }
}

void CompositionPulsatinglauflicht::updateValuesAndOutput(uint8_t i) {
    if(this->brightness != this->old_brightness) {
        double factor = this->values[i] / this->old_brightness;
        this->values[i] = this->brightness * factor;
        this->old_brightness = this->brightness;
    }
    this->values[i] += this->directions[i];
    if (this->values[i] < 1) {
        this->directions[i] = 1;
    }
    if(this->values[i] > this->brightness-1) {
        this->directions[i] = -1;
    }
    analogWrite(this->steps[i], this->values[i]);
}