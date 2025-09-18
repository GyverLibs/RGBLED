#pragma once
#include <Arduino.h>

// =================== RGB_t ===================
struct RGB_t {
    uint8_t R = 0, G = 0, B = 0;
};

// =================== RGB ===================
class RGB : public RGB_t {
   public:
    class Fader;

    // =================== Color ===================

    enum class Color : uint32_t {
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

    // уменьшить яркость
    static inline constexpr uint8_t fade8(uint8_t x, uint8_t bright) {
        return bright == 255 ? x : (uint16_t(x) * (bright + 1)) >> 8;
    }

    // квадратная гамма
    static inline constexpr uint8_t sqGamma(uint8_t x) {
        return x == 255 ? x : (uint16_t(x + 1) * x) >> 8;
    }

    // кубическая гамма
    static inline constexpr uint8_t cubeGamma(uint8_t x) {
        return x == 255 ? x : (uint32_t(x + 1) * (x + 1) * x) >> 16;
    }

    static inline constexpr uint32_t makeRGB24(uint8_t r, uint8_t g, uint8_t b) {
        return (uint32_t(r) << 16) | (uint32_t(g) << 8) | b;
    }

    static inline constexpr uint32_t makeRGB16(uint8_t r, uint8_t g, uint8_t b) {
        return ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | ((b & 0b11111000) >> 3);
    }

    // =================== GETTER ===================

    // вывести как 24-бит RGB
    uint32_t toRGB24() {
        return makeRGB24(R, G, B);
    }

    // вывести как 16-бит RGB
    uint16_t toRGB16() {
        return makeRGB16(R, G, B);
    }

    // =================== UTIL ===================

    // плавно изменить цвет к to за durationMs мс
    void fadeTo(const RGB& to, uint16_t durationMs);

    // понизить яркость (чем меньше значение, тем ниже яркость)
    void fadeBlack(uint8_t bright) {
        if (bright == 255) return;
        bright = sqGamma(bright);
        R = fade8(R, bright);
        G = fade8(G, bright);
        B = fade8(B, bright);
    }

    // =================== SETTER ===================

    // RGB888
    virtual void setRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255) {
        R = r;
        G = g;
        B = b;
        fadeBlack(bright);
    }

    // RGB
    void setFrom(const RGB_t& rgb, uint8_t bright = 255) {
        setRGB(rgb.R, rgb.G, rgb.B, bright);
    }

    // RGB::Color
    void setColor(Color color, uint8_t bright = 255) {
        setRGB24(uint32_t(color), bright);
    }

    // RGB888
    void setRGB24(uint32_t col, uint8_t bright = 255) {
        setRGB(
            ((uint8_t*)&col)[2],
            ((uint8_t*)&col)[1],
            ((uint8_t*)&col)[0],
            bright);
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
            (col << 3),
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
    void setHue(uint8_t col, uint8_t bright = 255) {
        uint8_t shift;

        switch (col) {
            case 0 ... 85:
                shift = col * 3;
                setRGB(255 - shift, shift, 0, bright);
                break;

            case 86 ... 170:
                shift = (col - 85) * 3;
                setRGB(0, 255 - shift, shift, bright);
                break;

            case 171 ... 255:
                shift = (col - 170) * 3;
                setRGB(shift, 0, 255 - shift, bright);
                break;
        }
    }

    // цветовое колесо 16 бит (реальный шаг - 43 единицы)
    void setHue16(uint16_t col, uint8_t bright = 255) {
        col = (col * 1530ul) >> 16;
        switch (col) {
            case 0 ... 255: setRGB(255, col, 0, bright); break;
            case 256 ... 510: setRGB(510 - col, 255, 0, bright); break;
            case 511 ... 765: setRGB(0, 255, col - 510, bright); break;
            case 766 ... 1020: setRGB(0, 1020 - col, 255, bright); break;
            case 1021 ... 1275: setRGB(col - 1020, 0, 255, bright); break;
            case 1276 ... 1530: setRGB(255, 0, 1530 - col, bright); break;
        }
    }

    // цветовая температура 1000-10000К
    void setKelvin(uint16_t K, uint8_t bright = 255) {
        float tmpKelvin = constrain(K, 1000, 10000) / 100.0;
        float tmp;
        uint8_t r, g, b;

        if (tmpKelvin <= 66) {
            r = 255;
        } else {
            tmp = pow(tmpKelvin - 60, -0.1332047592) * 329.698727446;
            r = constrain(tmp, 0, 255);
        }

        if (tmpKelvin <= 66) {
            tmp = 99.4708025861 * log(tmpKelvin) - 161.1195681661;
        } else {
            tmp = pow(tmpKelvin - 60, -0.0755148492) * 288.1221695283;
        }
        g = constrain(tmp, 0, 255);

        if (tmpKelvin >= 66) {
            b = 255;
        } else if (tmpKelvin <= 19) {
            b = 0;
        } else {
            tmp = 138.5177312231 * log(tmpKelvin - 10) - 305.0447927307;
            b = constrain(tmp, 0, 255);
        }
        setRGB(r, g, b, bright);
    }

    // цветовая температура 1000-10000К, быстрый алгоритм
    void setKelvinFast(uint16_t K, uint8_t bright = 255) {
        K = constrain(K, 1000, 10000);
        if (K < 6700) {
            setRGB(
                255,
                -0.00000408 * K * K + 0.058 * K + 46.3,
                K < 1600 ? 0 : -0.00000644 * K * K + 0.103 * K - 148.75,
                bright);
        } else {
            setRGB(
                0.00000218 * K * K - 0.051f * K + 497.63,
                0.0000013 * K * K - 0.031 * K + 402.43,
                255,
                bright);
        }
    }

    // HSV
    void setHSV(uint8_t h, uint8_t s, uint8_t v) {
        float H = h / 255.0;
        float S = s / 255.0;
        float V = v / 255.0;

        uint16_t i = H * 6;
        float f = H * 6 - i;
        float p = V * (1 - S);
        float q = V * (1 - f * S);
        float t = V * (1 - (1 - f) * S);

        switch (i % 6) {
            case 0: setRGB(255.0 * V, 255.0 * t, 255.0 * p); break;
            case 1: setRGB(255.0 * q, 255.0 * V, 255.0 * p); break;
            case 2: setRGB(255.0 * p, 255.0 * V, 255.0 * t); break;
            case 3: setRGB(255.0 * p, 255.0 * q, 255.0 * V); break;
            case 4: setRGB(255.0 * t, 255.0 * p, 255.0 * V); break;
            case 5: setRGB(255.0 * V, 255.0 * p, 255.0 * q); break;
        }
    }

    // HSV, быстрый алгоритм
    void setHSVFast(uint8_t h, uint8_t s, uint8_t v) {
        uint16_t h2 = h * 24 / 17;
        uint8_t vs = uint32_t(v) * s / 255;
        uint8_t a = uint32_t(vs) * (h2 % 60) / 60;

        switch ((h2 / 60) % 6) {
            case 0: setRGB(v, v - vs + a, v - vs); break;
            case 1: setRGB(v - a, v, v - vs); break;
            case 2: setRGB(v - vs, v, v - vs + a); break;
            case 3: setRGB(v - vs, v - a, v); break;
            case 4: setRGB(v - vs + a, v - vs, v); break;
            case 5: setRGB(v, v - vs, v - a); break;
        }
    }

    // ================== FABRIC ==================

    static RGB fromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255) {
        RGB rgb;
        rgb.setRGB(r, g, b, bright);
        return rgb;
    }
    static RGB fromColor(Color color, uint8_t bright = 255) {
        RGB rgb;
        rgb.setColor(color, bright);
        return rgb;
    }
    static RGB fromRGB24(uint32_t col, uint8_t bright = 255) {
        RGB rgb;
        rgb.setRGB24(col, bright);
        return rgb;
    }
    static RGB fromRGB16(uint16_t col, uint8_t bright = 255) {
        RGB rgb;
        rgb.setRGB16(col, bright);
        return rgb;
    }
    static RGB fromRGB16Fast(uint16_t col, uint8_t bright = 255) {
        RGB rgb;
        rgb.setRGB16Fast(col, bright);
        return rgb;
    }
    static RGB fromRainbow(uint8_t col, uint8_t bright = 255) {
        RGB rgb;
        rgb.setRainbow(col, bright);
        return rgb;
    }
    static RGB fromRainbow16(uint16_t col, uint8_t bright = 255) {
        RGB rgb;
        rgb.setRainbow16(col, bright);
        return rgb;
    }
    static RGB fromHue(uint8_t col, uint8_t bright = 255) {
        RGB rgb;
        rgb.setHue(col, bright);
        return rgb;
    }
    static RGB fromHue16(uint16_t col, uint8_t bright = 255) {
        RGB rgb;
        rgb.setHue16(col, bright);
        return rgb;
    }
    static RGB fromKelvin(uint16_t K, uint8_t bright = 255) {
        RGB rgb;
        rgb.setKelvin(K, bright);
        return rgb;
    }
    static RGB fromKelvinFast(uint16_t K, uint8_t bright = 255) {
        RGB rgb;
        rgb.setKelvinFast(K, bright);
        return rgb;
    }
    static RGB fromHSV(uint8_t h, uint8_t s, uint8_t v) {
        RGB rgb;
        rgb.setHSV(h, s, v);
        return rgb;
    }
    static RGB fromHSVFast(uint8_t h, uint8_t s, uint8_t v) {
        RGB rgb;
        rgb.setHSVFast(h, s, v);
        return rgb;
    }

   private:
    template <typename T, typename Tn, uint8_t bits>
    void _setRainbowT(T col, uint8_t bright = 255) {
#define _RGB_SCALE(x) Tn(x) * 8 / 3

        constexpr Tn top = (1ul << bits);
        constexpr T top1 = top - 1;
        constexpr T topm = top1 / 3 * 2;
        constexpr uint8_t sh = bits - 8;
        constexpr T step = top / 8;
        T shift;

        switch (col) {
            case 0 ... step - 1:
                shift = _RGB_SCALE(col);
                setRGB((top1 - shift) >> sh, shift >> sh, 0, bright);
                break;

            case step ... step * 2 - 1:
                shift = _RGB_SCALE(col);
                setRGB(topm >> sh, shift >> sh, 0, bright);
                break;

            case step * 2 ... step * 3 - 1:
                shift = _RGB_SCALE(col - step * 2);
                setRGB((topm - shift * 2) >> sh, (topm + shift) >> sh, 0, bright);
                break;

            case step * 3 ... step * 4 - 1:
                shift = _RGB_SCALE(col - step * 3);
                setRGB(0, (top1 - shift) >> sh, shift >> sh, bright);
                break;

            case step * 4 ... step * 5 - 1:
                shift = _RGB_SCALE(col - step * 4) * 2;
                setRGB(0, (topm - shift) >> sh, ((top1 / 3) + shift) >> sh, bright);
                break;

            case step * 5 ... top1:
                shift = _RGB_SCALE(col - step * 5);
                setRGB(shift >> sh, 0, (top1 - shift) >> sh, bright);
                break;
        }
    }
};

// ===================== FADER =====================

#define FADER_MIN_PRD 20

class RGB::Fader {
   public:
    Fader(RGB& rgb) : _rgb(rgb) {}

    // плавно изменить цвет к to за durationMs мс
    bool fadeTo(const RGB& to, uint16_t durationMs) {
        if (!durationMs) {
            _rgb.setFrom(to);
            return false;
        }

        uint8_t steps = _max3(_dif(_rgb.R, to.R), _dif(_rgb.G, to.G), _dif(_rgb.B, to.B));
        if (!steps) return false;

        _tmr = millis();
        _from = _rgb;
        _to = to;
        _step = 0;
        _prd = (durationMs + steps - 1) / steps;

        if (_prd < FADER_MIN_PRD) {
            _prd = FADER_MIN_PRD;
            steps = durationMs / _prd;
        }

        _n = 0;
        while (steps) {
            ++_n;
            steps >>= 1;
        }

        _prd = durationMs / (1 << _n);
        return true;
    }

    // вызывать в loop. Вернёт true при окончании процесса
    bool tick() {
        if (!_prd || uint16_t(uint16_t(millis()) - _tmr) < _prd) return false;
        _tmr += _prd;

        if (_step + 1 == (1 << _n)) {
            _prd = 0;
            _rgb.setFrom(_to);
            return true;
        }
        ++_step;

        _rgb.setRGB(
            _from.R + ((((int32_t)_to.R - _from.R) * _step) >> _n),
            _from.G + ((((int32_t)_to.G - _from.G) * _step) >> _n),
            _from.B + ((((int32_t)_to.B - _from.B) * _step) >> _n));

        return false;
    }

    // цвет в процессе изменения
    bool running() {
        return _prd;
    }

   private:
    RGB& _rgb;
    uint16_t _tmr, _prd = 0;
    uint8_t _n, _step = 0;
    RGB_t _from, _to;

    uint8_t _dif(uint8_t a, uint8_t b) {
        return a > b ? a - b : b - a;
    }
    uint8_t _max3(uint8_t a, uint8_t b, uint8_t c) {
        return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    }
};