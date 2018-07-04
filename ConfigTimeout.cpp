#include "ConfigTimeout.h"

ConfigTimeout::ConfigTimeout(uint16_t timeoutMs, Mode startupMode)
    :configTimeoutMs(timeoutMs),
    configLastMode(startupMode),
    msState(millis()) {}

void ConfigTimeout::setActualConfigMode(Mode configMode) {
    if (this->configLastMode != configMode) {
        this->configLastMode = configMode;
        this->msState=millis();
    }
}

bool ConfigTimeout::isTimeoutOver() {
    return (this->msState < millis() - this->configTimeoutMs);
}