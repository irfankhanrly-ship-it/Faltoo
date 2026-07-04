#pragma once
#include "gpaddon.h"
#include "gamepad.h"

#define DCNAddonName "DirectionChangeNeutral"

class DCNAddon : public GPAddon {
public:
    virtual bool available() { return true; }
    virtual void setup();
    virtual void process();
    virtual std::string name() { return DCNAddonName; }
private:
    uint16_t prevDpad = 0;
    uint32_t neutralUntilMicros = 0;
};
