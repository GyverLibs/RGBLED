#pragma once
#include <Arduino.h>

#define TRANSM_MIN_PRD 20

class Transition {
   public:
    // начать переход
    bool start(uint8_t from, uint8_t to, uint16_t durationMs) {
        if (!durationMs) {
            _cur = to;
            return false;
        }

        _cur = from;
        _tar = to;
        uint8_t d = from > to ? from - to : to - from;
        if (!d) return false;

        _tmr = millis();
        _prd = durationMs / d;
        _step = 1;

        if (_prd < TRANSM_MIN_PRD) {
            _step = d * TRANSM_MIN_PRD / durationMs;
            d = (d + _step - 1) / _step;
            _prd = durationMs / d;
        }
        if (from > to) _step = -_step;
        return true;
    }

    // вызывать в loop. Вернёт true на каждом шаге, если запущен
    bool tick() {
        if (!_prd || uint16_t(uint16_t(millis()) - _tmr) < _prd) return false;
        _tmr += _prd;

        int16_t v = _cur;
        v += _step;
        if ((_step > 0 && v >= _tar) || (_step < 0 && v <= _tar)) {
            _cur = _tar;
            _prd = 0;
        } else {
            _cur = v;
        }
        return true;
    }

    // получить текущее значение
    inline uint8_t getCurrent() {
        return _cur;
    }

    // получить целевое значение
    inline uint8_t getTarget() {
        return _tar;
    }

    // в процессе изменения
    inline bool running() {
        return _prd;
    }

   private:
    uint16_t _tmr, _prd = 0;
    int16_t _step;
    uint8_t _cur = 0, _tar = 0;
};