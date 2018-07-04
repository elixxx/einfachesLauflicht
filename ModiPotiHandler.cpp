#include "ModiPotiHandler.h"

ModiPotiHandler::ModiPotiHandler(uint8_t port, uint16_t startValue, uint8_t nGroupSplits)
    :port(port), 
    startValue(startValue), 
    nGroupSplits(nGroupSplits),
    normalizedMaxValue(1024 - startValue) { }

ModiPotiHandler::ModiPotiHandler(uint8_t port, uint8_t nGroupSplits)
    :ModiPotiHandler(port,0,nGroupSplits) {}


Mode ModiPotiHandler::getGroup() {
    return static_cast<Mode>(this->getGroupID());
}

uint8_t ModiPotiHandler::getGroupID() {
    uint16_t value = normalizedModePoti();
    for ( uint8_t i = 1; i < this->nGroupSplits +1 ; i++ ) {
        if (value <= (i * (normalizedMaxValue / this->nGroupSplits))){
            return (i-1);
        }
    }
    return (this->nGroupSplits-1);
}

uint16_t ModiPotiHandler::normalizedModePoti() {
    int16_t value = this->getValue();
    value = max(0,value - this->startValue);
    return value;
}

uint16_t ModiPotiHandler::getValue() {
    return analogRead(this->port);
}