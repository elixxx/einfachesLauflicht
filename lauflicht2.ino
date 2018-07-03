#include <Arduino.h>
#include "lauflicht.h"
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

static int8_t doing = -1;
static uint16_t maxBrightness = 255;

//Lauflicht l(myPins,4, maxBrightness,600, false);
EffectLauflicht l(myPins,4, maxBrightness,600, false);
EffectLauflicht lDim(myPinsPWM,3, maxBrightness,600, true);
EffectRandom rando(myPins,4, maxBrightness,600, false);
EffectRandom randoDim(myPinsPWM,3, maxBrightness,600, true);
EffectPulsating effPuls(myPinsPWM,3, maxBrightness, 10);
CompositionForwardBackward compFB(myPins, 4, maxBrightness, false);
CompositionForwardBackward compFBDim(myPinsPWM, 3, maxBrightness, true);
CompositionPulsatinglauflicht compPL(myPinsPWM, 3, maxBrightness, 100);

ModiPotiHandler modPotiHandler(MODE_POTI, MODE_POTI_MIN_VALUE, MODE_POTI_N_GROUPS);
ModiPotiHandler programmPotiHandler(VALUE_POTI, 7);

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

void loop() {
    static uint32_t configFreqSample=millis();
    static uint8_t configFreqOnOff= LOW;
    static ConfigTimeout configTimeout(1000, nothing);

    static IMode* activeMode = NULL;



    if (activeMode == NULL) {
        digitalWrite(3,LOW);
        activeMode = &compPL;
    }
    Mode actualMode = modPotiHandler.getGroup();
    configTimeout.setActualConfigMode(actualMode);
    // When Timout not reached, just to Light
    if(!configTimeout.isTimeoutOver()) {
        lowerExceptOne(actualMode);
        delay(200);
        lower();
        return;

    }
    switch(actualMode) {
        case brightness:
            digitalWrite(1,LOW);
            digitalWrite(3,LOW);
            digitalWrite(4,LOW);
            setMaxBrightness();
            analogWrite(0, maxBrightness);
            break;
        case mode:
/*             static uint8_t oldroupGId = 0;
            static uint8_t newGid = programmPotiHandler.getGroupID();
            if (oldroupGId != newGid) {
                oldroupGId = newGid;
                lower();
                delay(600);
                higher();
             } */
            switch(programmPotiHandler.getGroupID()) {
                case 0:
                    activeMode = &rando;
                    break;
                case 1:
                    activeMode = &compFB;
                    break;
                case 2:
                    activeMode = &l;
                    break;
                case 3:
                    
                    break;
                case 4:
                    digitalWrite(3,LOW);
                    activeMode = &randoDim;
                    break;
                case 6:
                    digitalWrite(3,LOW);
                    activeMode = &compFBDim;
                    break;
                case 7:
                    digitalWrite(3,LOW);
                    activeMode = &lDim;
                    break;
                default:
                    digitalWrite(3,LOW);
                    activeMode = &effPuls;
            }
            activeMode->step();
            break;
        case frequenz: 
            activeMode->setDelayMs(analogRead(VALUE_POTI));
            digitalWrite(myPins[actualMode], HIGH);
            delay(activeMode->getDelayMS()/2);
            digitalWrite(myPins[actualMode], LOW);
            delay(activeMode->getDelayMS()/2);
     
            break;
        case nothing:
        default: 
            activeMode->step();
            break;
    }

}