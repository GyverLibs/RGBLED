#pragma once
#include <Arduino.h>

#include "RGB.h"

class RGBLED : public RGB {
   public:
    static const bool COM_ANODE = true;
    static const bool COM_CATHODE = false;

    RGBLED(uint8_t rpin, uint8_t gpin, uint8_t bpin, bool com = COM_CATHODE) : _rpin(rpin), _gpin(gpin), _bpin(bpin), _anode(com) {
        disable();
    }

    void setRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t bright = 255) override {
        RGB::setRGB(r, g, b, bright);
        show();
    }

    // установить и применить яркость
    void setBrightness(uint8_t bright) {
        _bright = sqGamma(bright);
        show();
    }

    // обновить цвет
    void show() {
        analogWrite(_rpin, _anode ? 255 - RGB::fade8(R, _bright) : RGB::fade8(R, _bright));
        analogWrite(_gpin, _anode ? 255 - RGB::fade8(G, _bright) : RGB::fade8(G, _bright));
        analogWrite(_bpin, _anode ? 255 - RGB::fade8(B, _bright) : RGB::fade8(B, _bright));
    }

    // вкл
    inline void enable() {
        show();
    }

    // выкл
    void disable() {
        analogWrite(_rpin, _anode ? 255 : 0);
        analogWrite(_gpin, _anode ? 255 : 0);
        analogWrite(_bpin, _anode ? 255 : 0);
    }

    // вкл/выкл
    void setPower(bool power) {
        power ? enable() : disable();
    }

   private:
    const uint8_t _rpin, _gpin, _bpin;
    const bool _anode;
    uint8_t _bright = 255;
};
