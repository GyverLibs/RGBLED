#include <RGBLED.h>

RGBLED rgb(3, 5, 6);
RGB::Fader f(rgb);

void setup() {
}

void loop() {
    // асинхронно переходить на случайный цвет из Hue, когда предыдущий переход закончился
    if (!f.running()) f.fadeTo(RGB::fromHue(random(0, 256)), 1000);
    f.tick();
}