This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/RGBLED.svg?color=brightgreen)](https://github.com/GyverLibs/RGBLED/releases/latest/download/RGBLED.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/RGBLED.svg)](https://registry.platformio.org/libraries/gyverlibs/RGBLED)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/RGBLED?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# RGBLED
Library for controlling RGB LED and working with color
- RGB/HSV/Hue/Color Heat
- Optimized conversion functions
- Square gamma of brightness
- Support for common anode and cathode
- Fader for smooth color change, synchronous and asynchronous

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Use of use](#usage)
- [Versions](#versions)
- [Installation](#install)
- [Bugs and feedback](#feedback)

<a id="usage"></a>

## Use of use
### RGB
Basic class with conversion and installation of colors
```cpp
// =================== STATIC ===================

// brighten
static uint8_t fade8(uint8_t x, uint8_t bright);

// square scale
static uint8_t gamma2(uint8_t x);

// cubic scale
static uint8_t gamma3(uint8_t x);

static uint32_t makeRGB24(uint8_t r, uint8_t g, uint8_t b);

static uint32_t makeRGB16(uint8_t r, uint8_t g, uint8_t b);

// =================== GETTER ===================

// output as 24-bit RGB
uint32_t toRGB24();

// output as 16-bit RGB
uint16_t toRGB16();

// output
HSV_t toHSV();

// =================== UTIL ===================

// Smoothly change color to to for durationMs MS
void fadeTo(const RGB& to, uint16_t durationMs);

// reduce the brightness (the smaller the value, the lower the brightness)
void fadeBlack(uint8_t bright);

// =================== SETTER ===================

// RGB888
virtual void setRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255);

// RGB
void setRGB(const RGB_t& rgb, uint8_t bright = 255);

// RGB::Color
void setColor(Color color, uint8_t bright = 255);

// RGB888
void setRGB24(uint32_t col, uint8_t bright = 255);

// RGB565 full conversion (slower)
void setRGB16(uint16_t col, uint8_t bright = 255);

// RGB565 Quick conversion with loss of accuracy
void setRGB16Fast(uint16_t col, uint8_t bright = 255);

// 8 bit rainbow (more beautiful version of setHue)
void setRainbow(uint8_t col, uint8_t bright = 255);

// Rainbow 16 bits (real step - 100 units)
void setRainbow16(uint16_t col, uint8_t bright = 255);

// 8-bit color wheel
void setHue(uint8_t col, uint8_t bright = 255);

// Color wheel 16 bits (real pitch - 43 units)
void setHue16(uint16_t col, uint8_t bright = 255);

// color temperature 1000-10000K
void setKelvin(uint16_t K, uint8_t bright = 255);

// Color temperature 1000-10000K, fast algorithm
void setKelvinFast(uint16_t K, uint8_t bright = 255);

// HSV
void setHSV(uint8_t h, uint8_t s, uint8_t v);

// HSV, fast algorithm
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
Set of preset flowers

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
Asynchronous fader (smooth transition between colors)

```cpp
Fader(RGB& rgb);

// Smoothly change color to to for durationMs MS
bool fadeTo(const RGB& to, uint16_t durationMs);

// call in the loop. Return true at the end of the process
bool tick();

// coloration
bool running();
```

### Transition
Single-axis 8-bit fader

```cpp
// transition
bool start(uint8_t from, uint8_t to, uint16_t durationMs);

// call in the loop. It will return true at every step when it is launched.
bool tick();

// currentize
uint8_t getCurrent();

// target
uint8_t getTarget();

// alteration
bool running();
```

### RGBLED
Class for controlling a physical LED, inherits`RGB`

```cpp
RGBLED(uint8_t rpin, uint8_t gpin, uint8_t bpin, bool com = COM_CATHODE);

// brighten
void setBrightness(uint8_t bright);

// color
void show();

// plug-in
void enable();

// off
void disable();

// off
void setPower(bool power);
```

## Examples
### Demo
```cpp
#include <RGBLED.h>

void setup() {
    // on pins 3.5.6, total cathode
    RGBLED rgb(3, 5, 6);  // default
    // RGBLED rgb(3, 5, 6, RGBLED::COM_CATHODE);

    // on pins 9,10,11, total anode
    RGBLED rgbAnode(9, 10, 11, RGBLED::COM_ANODE);

    rgb.setRGB(123, 0, 12);  // install as RGB
    delay(1000);

    rgb.setRainbow(50);  // set up as an 8-bit rainbow
    delay(1000);

    rgb.setRGB24(0xaabb22);  // install as RGB888 HEX
    delay(1000);

    rgb.setColor(RGB::Color::Blue);  // list
    delay(1000);

    // smoothly lead to red in 2 seconds (synchronous, blocking call)
    rgb.fadeTo(RGB::fromRGB(50, 0, 0), 2000);

    // smoothly lead to pink in 2 seconds (synchronous, blocking call)
    rgb.fadeTo(RGB::fromColor(RGB::Color::Pink), 1000);
}

void loop() {
}
```

### fader
```cpp
#include <RGBLED.h>

RGBLED rgb(3, 5, 6);
RGB::Fader f(rgb);

void setup() {
}

void loop() {
    // Asynchronously switch to a random color from Hue when the previous transition is over
    if (!f.running()) f.fadeTo(RGB::fromHue(random(0, 256)), 1000);
    f.tick();
}
```

<a id="versions"></a>

## Versions
- v1.0

<a id="install"></a>
## Installation
- The library can be found under the name **RGBLED** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/RGBLED/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="feedback"></a>

## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
