[![latest](https://img.shields.io/github/v/release/GyverLibs/RGBLED.svg?color=brightgreen)](https://github.com/GyverLibs/RGBLED/releases/latest/download/RGBLED.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/RGBLED.svg)](https://registry.platformio.org/libraries/gyverlibs/RGBLED)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/RGBLED?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# RGBLED
Библиотека для управления RGB светодиодом и работы с цветом
- Режимы RGB/HSV/Hue/Цветовая теплота
- Оптимизированные функции конвертации
- Квадратная гамма яркости
- Поддержка общего анода и катода
- Фейдер для плавной смены цвета, синхронный и асинхронный

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Использование](#usage)
- [Версии](#versions)
- [Установка](#install)
- [Баги и обратная связь](#feedback)

<a id="usage"></a>

## Использование
### RGB
Базовый класс с конвертацией и установкой цветов
```cpp
// =================== STATIC ===================

// уменьшить яркость
static uint8_t fade8(uint8_t x, uint8_t bright);

// квадратная гамма
static uint8_t sqGamma(uint8_t x);

// кубическая гамма
static uint8_t cubeGamma(uint8_t x);

static uint32_t makeRGB24(uint8_t r, uint8_t g, uint8_t b);

static uint32_t makeRGB16(uint8_t r, uint8_t g, uint8_t b);

// =================== GETTER ===================

// вывести как 24-бит RGB
uint32_t toRGB24();

// вывести как 16-бит RGB
uint16_t toRGB16();

// =================== UTIL ===================

// плавно изменить цвет к to за durationMs мс
void fadeTo(const RGB& to, uint16_t durationMs);

// понизить яркость (чем меньше значение, тем ниже яркость)
void fadeBlack(uint8_t bright);

// =================== SETTER ===================

// RGB888
virtual void setRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255);

// RGB
void setFrom(const RGB_t& rgb, uint8_t bright = 255);

// RGB::Color
void setColor(Color color, uint8_t bright = 255);

// RGB888
void setRGB24(uint32_t col, uint8_t bright = 255);

// RGB565 полная конвертация (медленнее)
void setRGB16(uint16_t col, uint8_t bright = 255);

// RGB565 быстрая конвертация с потерей точности
void setRGB16Fast(uint16_t col, uint8_t bright = 255);

// радуга 8 бит (более красивая версия setHue)
void setRainbow(uint8_t col, uint8_t bright = 255);

// радуга 16 бит (реальный шаг - 100 единиц)
void setRainbow16(uint16_t col, uint8_t bright = 255);

// цветовое колесо 8 бит
void setHue(uint8_t col, uint8_t bright = 255);

// цветовое колесо 16 бит (реальный шаг - 43 единицы)
void setHue16(uint16_t col, uint8_t bright = 255);

// цветовая температура 1000-10000К
void setKelvin(uint16_t K, uint8_t bright = 255);

// цветовая температура 1000-10000К, быстрый алгоритм
void setKelvinFast(uint16_t K, uint8_t bright = 255);

// HSV
void setHSV(uint8_t h, uint8_t s, uint8_t v);

// HSV, быстрый алгоритм
void setHSVFast(uint8_t h, uint8_t s, uint8_t v);

// ================== FABRIC ==================

static RGB fromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255);
static RGB fromColor(Color color, uint8_t bright = 255);
static RGB fromRGB24(uint32_t col, uint8_t bright = 255);
static RGB fromRGB16(uint16_t col, uint8_t bright = 255);
static RGB fromRGB16Fast(uint16_t col, uint8_t bright = 255);
static RGB fromRainbow(uint8_t col, uint8_t bright = 255);
static RGB fromRainbow16(uint16_t col, uint8_t bright = 255);
static RGB fromHue(uint8_t col, uint8_t bright = 255);
static RGB fromHue16(uint16_t col, uint8_t bright = 255);
static RGB fromKelvin(uint16_t K, uint8_t bright = 255);
static RGB fromKelvinFast(uint16_t K, uint8_t bright = 255);
static RGB fromHSV(uint8_t h, uint8_t s, uint8_t v);
static RGB fromHSVFast(uint8_t h, uint8_t s, uint8_t v);
```

### RGB::Color
Набор предустановленных цветов

```cpp
White = 0xFFFFFF,
Gray = 0x808080,
LightGray = 0xD3D3D3,
DarkGray = 0xA9A9A9,
Black = 0x000000,
Red = 0xFF0000,
Green = 0x00FF00,
Blue = 0x0000FF,
Yellow = 0xFFFF00,
Cyan = 0x00FFFF,
Magenta = 0xFF00FF,
Orange = 0xFFA500,
Pink = 0xFFC0CB,
Brown = 0xA52A2A,
Purple = 0x800080,
Violet = 0xEE82EE,
Indigo = 0x4B0082,
Teal = 0x008080,
Navy = 0x000080,
Lime = 0x32CD32,
Olive = 0x808000,
Maroon = 0x800000,
Gold = 0xFFD700,
Coral = 0xFF7F50,
Salmon = 0xFA8072,
Khaki = 0xF0E68C,
Turquoise = 0x40E0D0,
SkyBlue = 0x87CEEB,
SteelBlue = 0x4682B4,
Chocolate = 0xD2691E
```

### RGB::Fader
Асинхронный фейдер (плавный переход между цветами)

```cpp
Fader(RGB& rgb);

// плавно изменить цвет к to за durationMs мс
bool fadeTo(const RGB& to, uint16_t durationMs);

// вызывать в loop. Вернёт true при окончании процесса
bool tick();

// цвет в процессе изменения
bool running();
```

### Transition
"Одноосевой" 8 бит фейдер

```cpp
// начать переход
bool start(uint8_t from, uint8_t to, uint16_t durationMs);

// вызывать в loop. Вернёт true на каждом шаге, если запущен
bool tick();

// получить текущее значение
uint8_t getCurrent();

// получить целевое значение
uint8_t getTarget();

// в процессе изменения
bool running();
```

### RGBLED
Класс для управления физическим светодиодом, наследует `RGB`

```cpp
RGBLED(uint8_t rpin, uint8_t gpin, uint8_t bpin, bool com = COM_CATHODE);

// установить и применить яркость
void setBrightness(uint8_t bright);

// обновить цвет
void show();

// вкл
void enable();

// выкл
void disable();

// вкл/выкл
void setPower(bool power);
```

## Примеры
### Демо
```cpp
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
```

### Фейдер
```cpp
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
```

<a id="versions"></a>

## Версии
- v1.0

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **RGBLED** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/RGBLED/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!

<a id="feedback"></a>

## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!

При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код