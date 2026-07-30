#pragma once
#include <Arduino.h>
// реактивный драйвер для RGBColor

#include "RGBColor.h"

#ifndef FADER_MIN_PRD
#define FADER_MIN_PRD 20
#endif

// =================== RGBReact ===================
class RGBReact {
   public:
    RGBReact(const RGBReact&) = delete;
    RGBReact& operator=(const RGBReact&) = delete;

    // получить сохранённый цвет
    const RGBColor& color() const {
        return _color;
    }

    // в RGB
    uint32_t toRGB24() const {
        return _color.toRGB24();
    }

    // в RB16
    uint16_t toRGB16() const {
        return _color.toRGB16();
    }

    // в HSV
    HSVColor toHSV() const {
        return _color.toHSV();
    }

    // плавно синхронно изменить цвет к to за durationMs мс
    void fadeTo(const RGBColor& to, uint16_t durationMs);

    // убавить яркость сохранённого цвета
    void fadeBlack(uint8_t bright) {
        if (bright == 255) return;

        RGBColor next = _color;
        next.fadeBlack(bright);
        _apply(next);
    }

    // применить цвет
    void setColor(const RGBColor& color) {
        _apply(color);
    }

    // RGBColor::Color
    void setColor(RGBColor::Color color) {
        _apply(RGBColor::fromColor(color));
    }

    // RGB888
    void setRGB(uint8_t r, uint8_t g, uint8_t b) {
        _apply(RGBColor(r, g, b));
    }

    // RGB888
    void setRGB24(uint32_t col) {
        _apply(RGBColor::fromRGB24(col));
    }

    // RGB565 полная конвертация (медленнее)
    void setRGB16(uint16_t col) {
        _apply(RGBColor::fromRGB16(col));
    }

    // RGB565 быстрая конвертация с потерей точности
    void setRGB16Fast(uint16_t col) {
        _apply(RGBColor::fromRGB16Fast(col));
    }

    // радуга 8 бит (более красивая версия setHue)
    void setRainbow(uint8_t col) {
        _apply(RGBColor::fromRainbow(col));
    }

    // радуга 16 бит (реальный шаг - 100 единиц)
    void setRainbow16(uint16_t col) {
        _apply(RGBColor::fromRainbow16(col));
    }

    // цветовое колесо 8 бит
    void setHue(uint8_t col) {
        _apply(RGBColor::fromHue(col));
    }

    // цветовое колесо 16 бит (реальный шаг - 43 единицы)
    void setHue16(uint16_t col) {
        _apply(RGBColor::fromHue16(col));
    }

    // цветовая температура 1000-10000К
    void setKelvin(uint16_t K) {
        _apply(RGBColor::fromKelvin(K));
    }

    // цветовая температура 1000-10000К, быстрый алгоритм
    void setKelvinFast(uint16_t K) {
        _apply(RGBColor::fromKelvinFast(K));
    }

    // HSV
    void setHSV(const HSVColor& hsv) {
        _apply(RGBColor::fromHSV(hsv));
    }

    void setHSV(uint8_t h, uint8_t s, uint8_t v) {
        _apply(RGBColor::fromHSV(h, s, v));
    }

    // HSV, быстрый алгоритм
    void setHSVFast(const HSVColor& hsv) {
        _apply(RGBColor::fromHSVFast(hsv));
    }

    void setHSVFast(uint8_t h, uint8_t s, uint8_t v) {
        _apply(RGBColor::fromHSVFast(h, s, v));
    }

   protected:
    RGBColor _color;

    explicit RGBReact(const RGBColor& color) : _color(color) {}
    RGBReact() = default;
    ~RGBReact() = default;

    // вызывается после сохранения нового цвета
    virtual void show() = 0;

   private:
    void _apply(const RGBColor& color) {
        _color = color;
        show();
    }
};

// =================== RGBFader ===================
class RGBFader {
   public:
    explicit RGBFader(RGBReact& rgb) : _rgb(rgb) {}

    // плавно изменить цвет к to за durationMs мс
    bool fadeTo(const RGBColor& to, uint16_t durationMs) {
        _prd = 0;

        if (!durationMs) {
            _rgb.setColor(to);
            return false;
        }

        const RGBColor& current = _rgb.color();
        uint8_t steps = RGBMath::max3(
            RGBMath::diff(current.R, to.R),
            RGBMath::diff(current.G, to.G),
            RGBMath::diff(current.B, to.B));

        if (!steps) return false;

        uint16_t maxSteps = durationMs / FADER_MIN_PRD;
        if (!maxSteps) maxSteps = 1;
        if (steps > maxSteps) steps = maxSteps;

        _n = 0;
        while (steps >>= 1) ++_n;

        _tmr = millis();
        _from = current;
        _to = to;
        _step = 0;
        _prd = durationMs / (1u << _n);
        if (!_prd) _prd = 1;
        return true;
    }

    // вызывать в loop. Вернёт true при окончании процесса
    bool tick() {
        if (!_prd || uint16_t(uint16_t(millis()) - _tmr) < _prd) return false;
        _tmr += _prd;

        if (_step + 1u == (1u << _n)) {
            _prd = 0;
            _rgb.setColor(_to);
            return true;
        }
        ++_step;

        _rgb.setRGB(
            RGBMath::lerp8(_from.R, _to.R, _step, _n),
            RGBMath::lerp8(_from.G, _to.G, _step, _n),
            RGBMath::lerp8(_from.B, _to.B, _step, _n));

        return false;
    }

    // цвет в процессе изменения
    bool running() const {
        return _prd;
    }

   private:
    RGBReact& _rgb;
    uint16_t _tmr, _prd = 0;
    uint8_t _n = 0, _step = 0;
    RGBColor _from, _to;
};

inline void RGBReact::fadeTo(const RGBColor& to, uint16_t durationMs) {
    RGBFader fader(*this);
    if (!fader.fadeTo(to, durationMs)) return;
    while (!fader.tick()) yield();
}
