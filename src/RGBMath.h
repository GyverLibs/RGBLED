#pragma once
#include <stdint.h>

class RGBMath {
   public:
    // уменьшить яркость
    static constexpr uint8_t fade8(uint8_t value, uint8_t brightness) {
        return brightness == 255 ? value : (uint16_t(value) * (brightness + 1u)) >> 8;
    }

    // квадратная гамма
    static constexpr uint8_t gamma2(uint8_t value) {
        return value == 255 ? value : (uint16_t(value + 1u) * value) >> 8;
    }

    // кубическая гамма
    static constexpr uint8_t gamma3(uint8_t value) {
        return value == 255 ? value : (uint32_t(value + 1u) * (value + 1u) * value) >> 16;
    }

    static constexpr uint32_t makeRGB24(uint8_t r, uint8_t g, uint8_t b) {
        return (uint32_t(r) << 16) | (uint32_t(g) << 8) | b;
    }

    static constexpr uint16_t makeRGB16(uint8_t r, uint8_t g, uint8_t b) {
        return (uint16_t(r & 0b11111000) << 8) |
               (uint16_t(g & 0b11111100) << 3) |
               ((b & 0b11111000) >> 3);
    }

    static constexpr uint8_t diff(uint8_t a, uint8_t b) {
        return a > b ? a - b : b - a;
    }

    static constexpr uint8_t max3(uint8_t a, uint8_t b, uint8_t c) {
        return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    }

    static constexpr uint8_t min3(uint8_t a, uint8_t b, uint8_t c) {
        return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
    }

    // круговая разница для диапазона 0..maxValue включительно
    // a и b должны находиться внутри диапазона
    template <typename T>
    static T circularDiff(T a, T b, T maxValue) {
        const T direct = a > b ? a - b : b - a;
        if (!direct) return 0;

        const T reverse = maxValue - direct + T(1);
        return direct < reverse ? direct : reverse;
    }

    // округление положительного целого вверх
    template <typename T>
    static T ceilDiv(T value, T divider) {
        return (value + divider - 1) / divider;
    }

    // интерполяция uint8_t по шагу step / 2^shift
    static uint8_t lerp8(uint8_t from, uint8_t to, uint8_t step, uint8_t shift) {
        const uint8_t delta = (uint16_t(diff(from, to)) * step) >> shift;
        return to >= from ? from + delta : from - delta;
    }
};
