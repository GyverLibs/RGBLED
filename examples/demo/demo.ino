#include <RGBLED.h>

void setup() {
    // на пинах 3,5,6, общий катод
    RGBLED rgb(3, 5, 6);  // по умолчанию
    // RGBLED rgb(3, 5, 6, RGBLED::COM_CATHODE);

    // на пинах 9,10,11, общий анод
    RGBLED rgbAnode(9, 10, 11, RGBLED::COM_ANODE);

    rgb.setRGB(123, 0, 12);  // установить как RGB
    delay(1000);

    rgb.setRainbow(50);  // установить как радуга 8 бит
    delay(1000);

    rgb.setRGB24(0xaabb22);  // установить как RGB888 HEX
    delay(1000);

    rgb.setColor(RGB::Color::Blue);  // установить из списка
    delay(1000);

    // плавно привести к красному за 2 секунды (синхронно, блокирующий вызов)
    rgb.fadeTo(RGB::fromRGB(50, 0, 0), 2000);

    // плавно привести к розовому за 2 секунды (синхронно, блокирующий вызов)
    rgb.fadeTo(RGB::fromColor(RGB::Color::Pink), 1000);
}

void loop() {
}