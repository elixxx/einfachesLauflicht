#ifndef ANALOGROUTE_H
#define ANALOGROUTE_H
#include <stdint.h>

#include <TinySoftPwm.h>

inline void analogWriteR(uint8_t pin, int value){
    if(pin==2)
        TinySoftPwm_analogWrite(pin, value);
    else
        analogWrite(pin,value);
}
#endif