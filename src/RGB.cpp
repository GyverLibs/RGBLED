#include "RGB.h"

void RGB::fadeTo(const RGB& to, uint16_t durationMs) {
    Fader f(*this);
    if (!f.fadeTo(to, durationMs)) return;
    while (!f.tick()) yield();
}