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
Библиотека разделена на два уровня:

- `RGBColor` и `HSVColor` — хранение и преобразование цвета без привязки к устройству
- `RGBReact` — базовый реактивный класс, который хранит текущий `RGBColor` и применяет его в наследнике
- `RGBLED` — драйвер физического RGB-светодиода
- `RGBFader` и `Transition` — асинхронные плавные переходы

### HSVColor
Класс хранения HSV-цвета:

```cpp
HSVColor();
HSVColor(uint8_t h, uint8_t s, uint8_t v);

uint8_t H;
uint8_t S;
uint8_t V;

// преобразование в RGB
RGBColor toRGB() const;
RGBColor toRGBFast() const;
```

### RGBColor
Класс хранения и преобразования RGB-цвета

```cpp
RGBColor();
RGBColor(uint8_t r, uint8_t g, uint8_t b);

uint8_t R;
uint8_t G;
uint8_t B;
```

#### Расстояние между цветами
```cpp
// квадрат расстояния по RGB
static uint32_t distRGB2(const RGBColor& c1, const RGBColor& c2);

// точное расстояние по RGB
static uint16_t distRGB(const RGBColor& c1, const RGBColor& c2);

// приближённое расстояние по RGB
static uint16_t distRGBFast(const RGBColor& c1, const RGBColor& c2);

// круговая разница оттенков
static uint8_t distHue(const RGBColor& c1, const RGBColor& c2);
```

#### Получение значения
```cpp
uint32_t toRGB24() const;
uint16_t toRGB16() const;
HSVColor toHSV() const;
```

#### Изменение цвета
Параметр `bright` изменяет компоненты самого `RGBColor`

```cpp
// уменьшить яркость текущего цвета
void fadeBlack(uint8_t bright);

// RGB888
void setRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255);
void setRGB(const RGBColor& rgb, uint8_t bright = 255);

// предустановленный цвет
void setColor(RGBColor::Color color, uint8_t bright = 255);

// RGB888 HEX и RGB565
void setRGB24(uint32_t col, uint8_t bright = 255);
void setRGB16(uint16_t col, uint8_t bright = 255);
void setRGB16Fast(uint16_t col, uint8_t bright = 255);

// радуга и цветовое колесо
void setRainbow(uint8_t col, uint8_t bright = 255);
void setRainbow16(uint16_t col, uint8_t bright = 255);
void setHue(uint8_t col, uint8_t bright = 255);
void setHue16(uint16_t col, uint8_t bright = 255);

// цветовая температура
void setKelvin(uint16_t K, uint8_t bright = 255);
void setKelvinFast(uint16_t K, uint8_t bright = 255);

// HSV
void setHSV(const HSVColor& hsv);
void setHSV(uint8_t h, uint8_t s, uint8_t v);
void setHSVFast(const HSVColor& hsv);
void setHSVFast(uint8_t h, uint8_t s, uint8_t v);
```

#### Фабрики
```cpp
static RGBColor fromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255);
static RGBColor fromColor(RGBColor::Color color, uint8_t bright = 255);
static RGBColor fromRGB24(uint32_t col, uint8_t bright = 255);
static RGBColor fromRGB16(uint16_t col, uint8_t bright = 255);
static RGBColor fromRGB16Fast(uint16_t col, uint8_t bright = 255);
static RGBColor fromRainbow(uint8_t col, uint8_t bright = 255);
static RGBColor fromRainbow16(uint16_t col, uint8_t bright = 255);
static RGBColor fromHue(uint8_t col, uint8_t bright = 255);
static RGBColor fromHue16(uint16_t col, uint8_t bright = 255);
static RGBColor fromKelvin(uint16_t K, uint8_t bright = 255);
static RGBColor fromKelvinFast(uint16_t K, uint8_t bright = 255);
static RGBColor fromHSV(uint8_t h, uint8_t s, uint8_t v);
static RGBColor fromHSV(const HSVColor& hsv);
static RGBColor fromHSVFast(uint8_t h, uint8_t s, uint8_t v);
static RGBColor fromHSVFast(const HSVColor& hsv);
```

### RGBColor::Color
```cpp
RGBColor color = RGBColor::fromColor(RGBColor::Red);
```

Доступные значения:

```cpp
RGBColor::White
RGBColor::Gray
RGBColor::LightGray
RGBColor::DarkGray
RGBColor::Black
RGBColor::Red
RGBColor::Green
RGBColor::Blue
RGBColor::Yellow
RGBColor::Cyan
RGBColor::Magenta
RGBColor::Orange
RGBColor::Pink
RGBColor::Brown
RGBColor::Purple
RGBColor::Violet
RGBColor::Indigo
RGBColor::Teal
RGBColor::Navy
RGBColor::Lime
RGBColor::Olive
RGBColor::Maroon
RGBColor::Gold
RGBColor::Coral
RGBColor::Salmon
RGBColor::Khaki
RGBColor::Turquoise
RGBColor::SkyBlue
RGBColor::SteelBlue
RGBColor::Chocolate
```

### RGBReact
Базовый класс для реактивных RGB-устройств. Хранит текущий `RGBColor`; все setter-ы применяют новый цвет через реализацию `show()` в наследнике.

```cpp
// текущий сохранённый цвет
const RGBColor& color() const;

// преобразование текущего цвета
uint32_t toRGB24() const;
uint16_t toRGB16() const;
HSVColor toHSV() const;

// синхронный блокирующий переход
void fadeTo(const RGBColor& to, uint16_t durationMs);

// изменить сохранённый цвет
void fadeBlack(uint8_t bright);
void setColor(const RGBColor& color);
void setColor(RGBColor::Color color);
void setRGB(uint8_t r, uint8_t g, uint8_t b);
void setRGB24(uint32_t col);
void setRGB16(uint16_t col);
void setRGB16Fast(uint16_t col);
void setRainbow(uint8_t col);
void setRainbow16(uint16_t col);
void setHue(uint8_t col);
void setHue16(uint16_t col);
void setKelvin(uint16_t K);
void setKelvinFast(uint16_t K);
void setHSV(const HSVColor& hsv);
void setHSV(uint8_t h, uint8_t s, uint8_t v);
void setHSVFast(const HSVColor& hsv);
void setHSVFast(uint8_t h, uint8_t s, uint8_t v);
```

Setter-ы `RGBReact` не принимают яркость. Для `RGBLED` общая яркость регулируется отдельно через `setBrightness()` и не изменяет сохранённый `color()`.


### RGBLED
Класс управления физическим RGB-светодиодом, наследует `RGBReact`.

```cpp
RGBLED(
    uint8_t rpin,
    uint8_t gpin,
    uint8_t bpin,
    conn_t com = COM_CATHODE
);

// установить общую яркость физического выхода
// withGamma = true включает квадратную гамму
void setBrightness(uint8_t bright, bool withGamma = true);

// включить и применить сохранённый цвет
void enable();

// выключить светодиод, сохранив цвет
void disable();

// включить или выключить
void setPower(bool power);

// светодиод включён
bool enabled() const;
```

Общая яркость `RGBLED` применяется поверх сохранённого цвета и не изменяет его:

```cpp
led.setRGB(255, 80, 20);
led.setBrightness(128);

const RGBColor& saved = led.color();  // по-прежнему 255, 80, 20
```

### RGBFader
Асинхронный плавный переход между цветами реактивного объекта:

```cpp
RGBFader(RGBReact& rgb);

// начать переход к цвету за durationMs мс
bool fadeTo(const RGBColor& to, uint16_t durationMs);

// вызывать в loop, вернёт true при окончании процесса
bool tick();

// переход выполняется
bool running() const;
```

### Transition
Асинхронный одноосевой 8-битный переход:

```cpp
// начать переход
bool start(uint8_t from, uint8_t to, uint16_t durationMs);

// вызывать в loop, вернёт true на каждом выполненном шаге
bool tick();

// получить текущее и целевое значение
uint8_t getCurrent() const;
uint8_t getTarget() const;

// переход выполняется
bool running() const;
```

## Примеры
### Работа с цветом
```cpp
#include <RGBColor.h>

RGBColor color(255, 100, 20);
HSVColor hsv = color.toHSV();

RGBColor red = RGBColor::fromColor(RGBColor::Red);
RGBColor wheel = RGBColor::fromHue(80);
RGBColor warm = RGBColor::fromKelvin(3200);
```

### Управление светодиодом
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

    rgb.setColor(RGBColor::Blue);  // установить из списка
    delay(1000);

    // плавно привести к красному за 2 секунды (синхронно, блокирующий вызов)
    rgb.fadeTo(RGBColor::fromRGB(50, 0, 0), 2000);

    // плавно привести к розовому за 2 секунды (синхронно, блокирующий вызов)
    rgb.fadeTo(RGBColor::fromColor(RGBColor::Pink), 1000);
}

void loop() {
}
```

### Асинхронный фейдер
```cpp
#include <RGBLED.h>

RGBLED led(3, 5, 6);
RGBFader fader(led);

void setup() {
}

void loop() {
    // начать новый переход после завершения предыдущего
    if (!fader.running()) {
        fader.fadeTo(RGBColor::fromHue(random(0, 256)), 1000);
    }

    fader.tick();
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