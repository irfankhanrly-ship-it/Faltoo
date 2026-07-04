#include "addons/dcn.h"
#include "storagemanager.h"
#include "pico/time.h"

void DCNAddon::setup() {
    prevDpad = 0;
    neutralUntilMicros = 0;
}

void DCNAddon::process() {
    Gamepad* gp = Storage::getInstance().GetGamepad();
    uint32_t now = time_us_32();
    uint16_t curDpad = gp->state.dpad;

    // Inside 1ms forced-neutral window
    if (now < neutralUntilMicros) {
        gp->state.dpad = 0;
        prevDpad = 0;
        return;
    }

    // Detect active-to-active dpad transition
    if (prevDpad != 0 && curDpad != 0 && prevDpad != curDpad) {
        neutralUntilMicros = now + 1000;  // 1ms forced neutral
        gp->state.dpad = 0;
        prevDpad = 0;
        return;
    }

    prevDpad = curDpad;
}
