#include <RGBLED.h>

RGBLED rgb(3, 5, 6);
RGBFader f(rgb);

void setup() {
}

void loop() {
    // асинхронно переходить на случайный цвет из Hue, когда предыдущий переход закончился
    if (!f.running()) f.fadeTo(RGBColor::fromHue(random(0, 256)), 1000);
    f.tick();
}