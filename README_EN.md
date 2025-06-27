This is an automatic translation, may be incorrect in some places. See sources and examples!

# Rgbled
LED Library Library and Color Work
- RGB/HSV/Hue/Hue/color heat modes
- optimized conversion functions
- square gamut of brightness
- Support for the common anode and cathode
- Fader for a smooth color change, synchronous and asynchronous

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [use] (#usage)
- [versions] (#varsions)
- [installation] (# Install)
- [bugs and feedback] (#fedback)

<a id = "USAGE"> </A>

## Usage
## RGB
Basic class with converting and setting colors
`` `CPP
// =================== STATIC ==================================

// Reduce brightness
Static Uint8_t Fade8 (Uint8_t X, Uint8_t Bright);

// square gamma
static uint8_t sqgamma (uint8_t x);

// cubic gamma
static uint8_t cubegamma (uint8_t x);

Static Uint32_T MAKERGB24 (UINT8_T R, UINT8_T G, UINT8_T B);

Static Uint32_T MAKERGB16 (UINT8_T R, UINT8_T G, UINT8_T B);

// =================== Getter ====================================

// Bring like 24-bit RGB
uint32_t Torgb24 ();

// Bring up like 16-bit rgb
uint16_t Torgb16 ();

// ==================== amu =========================================================================

// smoothly change the color to to for durationms ms
VOID Fadeto (const rgb & to, uint16_t durationms);

// lower brightness (the lower the value, the lower the brightness)
VOID fadeblack (Uint8_t Bright);

// =================== Setter =======================================

// RGB888
Virtual Void Setrgb (Uint8_t R, Uint8_t G, Uint8_t B, Uint8_T Bright = 255);

// rgb
VOID setfrom (const rgb_t & rgb, uint8_t Bright = 255);

// rgb :: color
VOID setcolor (color color, uint8_t bright = 255);

// RGB888
VOID Setrgb24 (Uint32_t Col, Uint8_t Bright = 255);

// RGB565 Full conversion (slower)
VOID Setrgb16 (Uint16_t Col, Uint8_t Bright = 255);

// rgb565 Fast converting with accuracy loss
VOID Setrgb16fast (Uint16_t Col, Uint8_t Bright = 255);

// Rainbow 8 bit (more beautiful version of Sethue)
VOID Setrainbow (Uint8_t Col, Uint8_t Bright = 255);

// Rainbow 16 bit (real step - 100 units)
VOID setRainbow16 (Uint16_t Col, Uint8_t Bright = 255);

// Color wheel 8 bits
VOID sethue (Uint8_t Col, Uint8_t Bright = 255);

// Color wheel 16 bits (real step - 43 units)
VOID sethue16 (Uint16_t Col, Uint8_t Bright = 255);

// Color temperature 1000-10000k
VOID setkelvin (Uint16_t K, Uint8_t Bright = 255);

// Color temperature 1000-10000k, fast algorithm
VOID setkelvinfast (Uint16_t K, Uint8_t Bright = 255);

// hsv
VOID Sethsv (uint8_t h, uint8_t s, uint8_t v);

// hsv, fast algorithm
VOID sethsvfast (uint8_t h, uint8_t s, uint8_t v);

// ====ward

Static RGB Fromrgb (Uint8_t R, Uint8_t G, Uint8_t B, Uint8_T Bright = 255);
Static RGB Fromcolor (Color Color, Uint8_t Bright = 255);
Static RGB FROMRGB24 (UINT32_T COL, UINT8_T BRIGHT = 255);
Static RGB FROMRGB16 (UINT16_T COL, UINT8_T BRIGHT = 255);
Static RGB FROMRGB16FAST (UINT16_T COL, UINT8_T BRIGHT = 255);
Static RGB Fromrainbow (Uint8_t Col, Uint8_t Bright = 255);
Static RGB FROMRAINBOW16 (UINT16_T COL, UINT8_T BRIGHT = 255);
StatiC RGB Fromhue (Uint8_t Col, Uint8_t Bright = 255);
Static RGB FROMHUE16 (UINT16_T COL, UINT8_T BRIGHT = 255);
Static RGB Fromkelvin (Uint16_t K, Uint8_t Bright = 255);
Static RGB Fromkelvinfast (Uint16_t K, Uint8_t Bright = 255);
Static RGB Fromhsv (Uint8_t H, Uint8_t S, Uint8_t v);
Static RGB Fromhsvfast (Uint8_t H, Uint8_t S, Uint8_t v);
`` `

### RGB :: color
A set of pre -installed colors

`` `CPP
White = 0xffffff,
Gray = 0x808080,
Lightgray = 0xD3D3D3,
DarkGray = 0xa9a9a9,
Black = 0x000000,
Red = 0xFF0000,
Green = 0x00F00,
Blue = 0x0000FF,
Yellow = 0xfff00,
Cyan = 0x00FFFF,
Magenta = 0xff00FF,
Orange = 0xffa500,
Pink = 0xFFC0CB,
Brown = 0xa52a2a,
Purple = 0x800080,
Violet = 0xee82ee,
Indigo = 0x4b0082,
Teal = 0x008080,
Navy = 0x000080,
Lime = 0x32CD32,
Olive = 0x808000,
Maroon = 0x800000,
Gold = 0xFFD700,
Coral = 0xff7f50,
Salmon = 0xfa8072,
Khaki = 0xf0e68c,
Turquoise = 0x40e0d0,
Skyblue = 0x87ceb,
Steelblue = 0x4682b4,
Chocolate = 0xd2691e
`` `

## RGB :: Fader
Asynchronous fader (smooth transition between flowers)

`` `CPP
Fader (RGB & RGB);

// smoothly change the color to to for durationms ms
Bool Fadeto (const rgb & to, uint16_t durationms);

// Call in Loop.Will return True at the end of the process
Bool Tick ();

// Color in the process of change
Bool Running ();
`` `

### Transition
"Same -axis" 8 bit fader

`` `CPP
// Start transition
Bool Start (Uint8_t From, Uint8_t To, Uint16_T DurationMS);

// Call in Loop.Will return True at every step if it is launched
Bool Tick ();

// get the current value
uint8_t getcurrent ();

// get the target value
uint8_t gettarget ();

// in the process of change
Bool Running ();
`` `

## rgbled
A class for managing a physical LED, inherits `RGB`

`` `CPP
Rgbled (uint8_t rpin, uint8_t gpin, uint8_t bpin, bool com = com_cathode);

// Install and apply brightness
VOID Setbrightness (Uint8_t Bright);

// update the color
VOID show ();

// VCL
VOID Enable ();

// Off
Void Disable ();

// VKL/Off
Void setpower (Bool Power);
`` `

## Examples
### Demo
`` `CPP
#include <rgbled.h>

VOID setup () {
// on pins 3.5,6, general cathode
RGBLED RGB (3, 5, 6);// by default
// RGBLED RGB (3, 5, 6, rgbled :: com_cathode);

// on pins 9,10,11, general anode
Rgbled rgbanode (9, 10, 11, rgbled :: com_anode);

rgb.setrgb (123, 0, 12);// install as rgb
DELAY (1000);

rgb.setrainbow (50);// install as a rainbow 8 bits
DELAY (1000);

rgb.setrgb24 (0xaabb22);// Install as RGB888 HEX
DELAY (1000);

rgb.setcolor (rgb :: color :: blue);// install from the list
DELAY (1000);

// smoothly lead to red in 2 seconds (synchronously, blocking the call)
rgb.fadeto (rgb :: fromrgb (50, 0, 0), 2000);

// smoothly lead to pink in 2 seconds (synchronously, blocking the call)
rgb.fadeto (rgb :: farmcolor (rgb :: color :: pink), 1000);
}

VOID loop () {
}
`` `

## fader
`` `CPP
#include <rgbled.h>

RGBLED RGB (3, 5, 6);
RGB :: Fader F (RGB);

VOID setup () {
}

VOID loop () {
// asynchronously switch to a random color from hue, when the previous transition ended
if (! F.F.F.FADETO (RGB :: FromHue (Random (0, 256)), 1000);
F.Tick ();
}
`` `

<a ID = "Versions"> </a>

## versions
- V1.0

<a id = "Install"> </a>
## Installation
- The library can be found by the name ** rgbled ** and installed through the library manager in:
- Arduino ide
- Arduino ide v2
- Platformio
- [download the library] (https://github.com/gyverlibs/rgbled/archive/refs/heads/main.zip) .Zip archive for manual installation:
- unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
- unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
- unpack and put in *documents/arduino/libraries/ *
- (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%BD%D0%BE%D0%B2%D0%B8%B8%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!

<a id = "Feedback"> </a>

## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!

When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code