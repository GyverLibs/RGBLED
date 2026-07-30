#pragma once
#include <Arduino.h>

#include "RGBMath.h"

class RGBColor;

// =================== HSVColor ===================
class HSVColor {
   public:
    uint8_t H;
    uint8_t S;
    uint8_t V;

    constexpr HSVColor() : H(0), S(0), V(0) {}
    constexpr HSVColor(uint8_t h, uint8_t s, uint8_t v) : H(h), S(s), V(v) {}

    RGBColor toRGB() const;
    RGBColor toRGBFast() const;
};

// =================== RGBColor ===================
class RGBColor {
   public:
    uint8_t R;
    uint8_t G;
    uint8_t B;

    constexpr RGBColor() : R(0), G(0), B(0) {}
    constexpr RGBColor(uint8_t r, uint8_t g, uint8_t b) : R(r), G(g), B(b) {}

    // =================== Color ===================

    enum Color : uint32_t {
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
    };

    // =================== STATIC ===================

    // квадрат расстояния между цветами по RGB
    static uint32_t distRGB2(const RGBColor& c1, const RGBColor& c2);

    // расстояние между цветами по RGB
    static uint16_t distRGB(const RGBColor& c1, const RGBColor& c2);

    // приближённое расстояние между цветами по RGB
    static uint16_t distRGBFast(const RGBColor& c1, const RGBColor& c2);

    // круговая разница оттенков
    static uint8_t distHue(const RGBColor& c1, const RGBColor& c2);

    // =================== GETTER ===================

    // вывести как 24-бит RGB
    uint32_t toRGB24() const {
        return RGBMath::makeRGB24(R, G, B);
    }

    // вывести как 16-бит RGB
    uint16_t toRGB16() const {
        return RGBMath::makeRGB16(R, G, B);
    }

    // вывести как HSV
    HSVColor toHSV() const;

    // =================== UTIL ===================

    // понизить яркость (чем меньше значение, тем ниже яркость)
    void fadeBlack(uint8_t bright) {
        if (bright == 255) return;

        bright = RGBMath::gamma2(bright);
        R = RGBMath::fade8(R, bright);
        G = RGBMath::fade8(G, bright);
        B = RGBMath::fade8(B, bright);
    }

    // =================== SETTER ===================

    // RGB888
    void setRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255) {
        R = r;
        G = g;
        B = b;
        fadeBlack(bright);
    }

    // RGBColor
    void setRGB(const RGBColor& rgb, uint8_t bright = 255) {
        setRGB(rgb.R, rgb.G, rgb.B, bright);
    }

    // RGBColor::Color
    void setColor(Color color, uint8_t bright = 255) {
        setRGB24(uint32_t(color), bright);
    }

    // RGB888
    void setRGB24(uint32_t col, uint8_t bright = 255) {
        setRGB(col >> 16, col >> 8, col, bright);
    }

    // RGB565 полная конвертация (медленнее)
    void setRGB16(uint16_t col, uint8_t bright = 255) {
        setRGB(
            ((col >> 11) * 255 + 15) / 31,
            (((col >> 5) & 0b00111111) * 255 + 31) / 63,
            ((col & 0b00011111) * 255 + 15) / 31,
            bright);
    }

    // RGB565 быстрая конвертация с потерей точности
    void setRGB16Fast(uint16_t col, uint8_t bright = 255) {
        setRGB(
            (col >> 8) & 0b11111000,
            (col >> 3) & 0b11111100,
            col << 3,
            bright);
    }

    // радуга 8 бит (более красивая версия setHue)
    void setRainbow(uint8_t col, uint8_t bright = 255) {
        _setRainbowT<uint8_t, uint16_t, 8>(col, bright);
    }

    // радуга 16 бит (реальный шаг - 100 единиц)
    void setRainbow16(uint16_t col, uint8_t bright = 255) {
        _setRainbowT<uint16_t, uint32_t, 16>(col, bright);
    }

    // цветовое колесо 8 бит
    void setHue(uint8_t col, uint8_t bright = 255);

    // цветовое колесо 16 бит (реальный шаг - 43 единицы)
    void setHue16(uint16_t col, uint8_t bright = 255);

    // цветовая температура 1000-10000К
    void setKelvin(uint16_t K, uint8_t bright = 255);

    // цветовая температура 1000-10000К, быстрый алгоритм
    void setKelvinFast(uint16_t K, uint8_t bright = 255);

    // HSV
    void setHSV(const HSVColor& hsv) {
        setHSV(hsv.H, hsv.S, hsv.V);
    }
    void setHSV(uint8_t h, uint8_t s, uint8_t v);

    // HSV, быстрый алгоритм
    void setHSVFast(const HSVColor& hsv) {
        setHSVFast(hsv.H, hsv.S, hsv.V);
    }
    void setHSVFast(uint8_t h, uint8_t s, uint8_t v);

    // ================== FABRIC ==================

    static RGBColor fromRGB(const RGBColor& rgb, uint8_t bright = 255) {
        return fromRGB(rgb.R, rgb.G, rgb.B, bright);
    }

    static RGBColor fromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setRGB(r, g, b, bright);
        return rgb;
    }

    static RGBColor fromColor(Color color, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setColor(color, bright);
        return rgb;
    }

    static RGBColor fromRGB24(uint32_t col, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setRGB24(col, bright);
        return rgb;
    }

    static RGBColor fromRGB16(uint16_t col, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setRGB16(col, bright);
        return rgb;
    }

    static RGBColor fromRGB16Fast(uint16_t col, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setRGB16Fast(col, bright);
        return rgb;
    }

    static RGBColor fromRainbow(uint8_t col, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setRainbow(col, bright);
        return rgb;
    }

    static RGBColor fromRainbow16(uint16_t col, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setRainbow16(col, bright);
        return rgb;
    }

    static RGBColor fromHue(uint8_t col, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setHue(col, bright);
        return rgb;
    }

    static RGBColor fromHue16(uint16_t col, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setHue16(col, bright);
        return rgb;
    }

    static RGBColor fromKelvin(uint16_t K, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setKelvin(K, bright);
        return rgb;
    }

    static RGBColor fromKelvinFast(uint16_t K, uint8_t bright = 255) {
        RGBColor rgb;
        rgb.setKelvinFast(K, bright);
        return rgb;
    }

    static RGBColor fromHSV(uint8_t h, uint8_t s, uint8_t v) {
        RGBColor rgb;
        rgb.setHSV(h, s, v);
        return rgb;
    }

    static RGBColor fromHSV(const HSVColor& hsv) {
        return fromHSV(hsv.H, hsv.S, hsv.V);
    }

    static RGBColor fromHSVFast(uint8_t h, uint8_t s, uint8_t v) {
        RGBColor rgb;
        rgb.setHSVFast(h, s, v);
        return rgb;
    }

    static RGBColor fromHSVFast(const HSVColor& hsv) {
        return fromHSVFast(hsv.H, hsv.S, hsv.V);
    }

    void setFrom(const RGBColor& rgb, uint8_t bright = 255) {
        setRGB(rgb, bright);
    }

   private:
    template <typename T, typename Tn, uint8_t bits>
    void _setRainbowT(T col, uint8_t bright) {
        constexpr Tn top = (1ul << bits);
        constexpr T top1 = top - 1;
        constexpr T topm = top1 / 3 * 2;
        constexpr uint8_t sh = bits - 8;
        constexpr T step = top / 8;
        T shift;

        switch (col) {
            case 0 ... step - 1:
                shift = Tn(col) * 8 / 3;
                setRGB((top1 - shift) >> sh, shift >> sh, 0, bright);
                break;

            case step ... step * 2 - 1:
                shift = Tn(col) * 8 / 3;
                setRGB(topm >> sh, shift >> sh, 0, bright);
                break;

            case step * 2 ... step * 3 - 1:
                shift = Tn(col - step * 2) * 8 / 3;
                setRGB((topm - shift * 2) >> sh, (topm + shift) >> sh, 0, bright);
                break;

            case step * 3 ... step * 4 - 1:
                shift = Tn(col - step * 3) * 8 / 3;
                setRGB(0, (top1 - shift) >> sh, shift >> sh, bright);
                break;

            case step * 4 ... step * 5 - 1:
                shift = Tn(col - step * 4) * 8 / 3 * 2;
                setRGB(0, (topm - shift) >> sh, ((top1 / 3) + shift) >> sh, bright);
                break;

            case step * 5 ... top1:
                shift = Tn(col - step * 5) * 8 / 3;
                setRGB(shift >> sh, 0, (top1 - shift) >> sh, bright);
                break;
        }
    }
};

inline RGBColor HSVColor::toRGB() const {
    return RGBColor::fromHSV(*this);
}

inline RGBColor HSVColor::toRGBFast() const {
    return RGBColor::fromHSVFast(*this);
}
