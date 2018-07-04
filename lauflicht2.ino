#include <Arduino.h>
#include "Imode.h"
#include "ModiPotiHandler.h"
#include "ConfigTimeout.h"
#include "EffectPulsating.h"
#include "EffectLauflicht.h"
#include "EffectRandom.h"
#include "CompositionForwardBackward.h"
#include "CompositionPulsatinglauflicht.h"


#define VALUE_POTI 1 // Refers to P2
#define MODE_POTI 0 //Referes to P5

#define MODE_POTI_MIN_VALUE 538
#define MODE_POTI_N_GROUPS 4

uint8_t myPins[4] = {4,1,3,0};
uint8_t myPinsPWM[3] = {4,1,0};


static IMode* activeLightMode = NULL;
static uint16_t maxBrightness = 255;

//Lauflicht l(myPins,4, maxBrightness,600, false);
EffectLauflicht l(myPins,4, maxBrightness,600, false);
EffectLauflicht lDim(myPinsPWM,3, maxBrightness,600, true);
EffectRandom rando(myPins,4, maxBrightness,600, false);
EffectRandom randoDim(myPinsPWM,3, maxBrightness,600, true);
EffectPulsating effPuls(myPinsPWM,3, maxBrightness, 10);
CompositionForwardBackward compFB(myPins, 4, maxBrightness, false);
CompositionForwardBackward compFBDim(myPinsPWM, 3, maxBrightness, true);
CompositionPulsatinglauflicht compPL(myPinsPWM, 3, maxBrightness, 1);

ModiPotiHandler modPotiHandler(MODE_POTI, MODE_POTI_MIN_VALUE, MODE_POTI_N_GROUPS);
ModiPotiHandler programmPotiHandler(VALUE_POTI, 9);

void lower() {
    for (int i = 0; i<4; i++) {
        digitalWrite(i, LOW);
    }
}

void higher() {
    for (int i = 0; i<4; i++) {
        digitalWrite(i, HIGH);
    }
}

void setMaxBrightness() {
    maxBrightness = analogRead(VALUE_POTI)/4;
}

void setup() {
    for (int i = 0 ; i<4;i++) {
        pinMode(myPins[i],OUTPUT);
    }
}

void lowerExceptOne(uint8_t except) {
    for ( int i = 0; i < 4; i++) {
        uint8_t selection = myPins[i];
        if(selection != except) {
            digitalWrite(selection, LOW);
        } else {
            digitalWrite(selection, HIGH);
        }
    }
}
static bool randomActive = true;
void setActiveMode(uint8_t mode) {
    switch(mode) {
        case 0:
            activeLightMode = &rando;
            break;
        case 1:
            activeLightMode = &compFB;
            break;
        case 2:
            activeLightMode = &l;
            break;
        case 3:
            digitalWrite(3,LOW);
            activeLightMode = &randoDim;
            break;
        case 4:
            digitalWrite(3,LOW);
            activeLightMode = &compFBDim;
            break;
        case 5:
            digitalWrite(3,LOW);
            activeLightMode = &lDim;
            break;
        case 6:
            digitalWrite(3,LOW);
            activeLightMode = &compPL;
            break;
        case 7:
            digitalWrite(3,LOW);
            activeLightMode = &effPuls;
            break;
        case 8:
            randomActive = true;
        default:
            break;
    }
}

void loop() {
    static uint32_t configFreqSample=millis();
    static uint8_t configFreqOnOff= LOW;
    static ConfigTimeout configTimeout(1000, nothing);

    if (activeLightMode == NULL) {
        digitalWrite(3,LOW);
        activeLightMode = &compPL;
    }
    Mode actualPotiMode = modPotiHandler.getGroup();
    configTimeout.setActualConfigMode(actualPotiMode);

    // When Timout not reached, just show related light as feedback
    if(!configTimeout.isTimeoutOver()) {
        lowerExceptOne(actualPotiMode);
        delay(200);
        lower();
        return;

    }
    switch(actualPotiMode) {
        case brightness:
            digitalWrite(1,LOW);
            digitalWrite(3,LOW);
            digitalWrite(4,LOW);
            setMaxBrightness();
            analogWrite(0, maxBrightness);
            break;
        case mode:
            randomActive = false;
            setActiveMode(programmPotiHandler.getGroupID());
            activeLightMode->step();
            break;
        case frequenz: 
            activeLightMode->setDelayMs(analogRead(VALUE_POTI));
            digitalWrite(myPins[actualPotiMode], HIGH);
            delay(activeLightMode->getDelayMS()/2);
            digitalWrite(myPins[actualPotiMode], LOW);
            delay(activeLightMode->getDelayMS()/2);
     
            break;
        case nothing:
        default: 
            if(randomActive && activeLightMode->isFinished()) {
                setActiveMode(random(-1, 8));
                activeLightMode->setDurationMs(5000);
            } 
            activeLightMode->step();
            break;
    }

}