#pragma once
#include <Arduino.h>
// асинхронный 8-битный одноосевой переход

#include "RGBMath.h"

#ifndef TRANSM_MIN_PRD
#define TRANSM_MIN_PRD 20
#endif

class Transition {
   public:
    // начать переход
    bool start(uint8_t from, uint8_t to, uint16_t durationMs) {
        _prd = 0;
        _cur = from;
        _tar = to;

        if (!durationMs) {
            _cur = to;
            return false;
        }

        const uint8_t distance = RGBMath::diff(from, to);
        if (!distance) return false;

        uint8_t step = 1;
        uint16_t period = durationMs / distance;

        if (period < TRANSM_MIN_PRD) {
            uint8_t maxSteps = durationMs / TRANSM_MIN_PRD;
            if (!maxSteps) maxSteps = 1;

            step = RGBMath::ceilDiv<uint8_t>(distance, maxSteps);
            const uint8_t actualSteps = RGBMath::ceilDiv<uint8_t>(distance, step);
            period = durationMs / actualSteps;
        }

        _tmr = millis();
        _prd = period ? period : 1;
        _step = from < to ? step : -int16_t(step);
        return true;
    }

    // вызывать в loop. Вернёт true на каждом шаге, если запущен
    bool tick() {
        if (!_prd || uint16_t(uint16_t(millis()) - _tmr) < _prd) return false;
        _tmr += _prd;

        const int16_t next = int16_t(_cur) + _step;
        if ((_step > 0 && next >= _tar) || (_step < 0 && next <= _tar)) {
            _cur = _tar;
            _prd = 0;
        } else {
            _cur = next;
        }
        return true;
    }

    // получить текущее значение
    uint8_t getCurrent() const {
        return _cur;
    }

    // получить целевое значение
    uint8_t getTarget() const {
        return _tar;
    }

    // в процессе изменения
    bool running() const {
        return _prd;
    }

   private:
    uint16_t _tmr, _prd = 0;
    int16_t _step = 0;
    uint8_t _cur = 0, _tar = 0;
};
