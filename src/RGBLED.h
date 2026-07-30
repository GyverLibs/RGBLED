#pragma once
#include <Arduino.h>

#include "RGBReact.h"

class RGBLED : public RGBReact {
   public:
    enum conn_t {
        COM_CATHODE,
        COM_ANODE,
    };

    RGBLED(uint8_t rpin, uint8_t gpin, uint8_t bpin, conn_t com = COM_CATHODE)
        : _rpin(rpin), _gpin(gpin), _bpin(bpin), _anode(com == COM_ANODE) {}

    // установить и применить яркость
    void setBrightness(uint8_t bright, bool withGamma = true) {
        _bright = withGamma ? RGBMath::gamma2(bright) : bright;
        show();
    }

    // включить и применить сохранённый цвет
    void enable() {
        _enabled = true;
        show();
    }

    void disable() {
        _enabled = false;
        _write(_rpin, 0);
        _write(_gpin, 0);
        _write(_bpin, 0);
    }

    void setPower(bool power) {
        power ? enable() : disable();
    }

    bool enabled() const {
        return _enabled;
    }

   private:
    void show() override {
        if (!_enabled) return;
        _write(_rpin, RGBMath::fade8(_color.R, _bright));
        _write(_gpin, RGBMath::fade8(_color.G, _bright));
        _write(_bpin, RGBMath::fade8(_color.B, _bright));
    }

    void _write(uint8_t pin, uint8_t value) {
        analogWrite(pin, _anode ? 255 - value : value);
    }

    const uint8_t _rpin;
    const uint8_t _gpin;
    const uint8_t _bpin;
    const bool _anode;

    uint8_t _bright = 255;
    bool _enabled = true;
};
