#include "RGBColor.h"

uint32_t RGBColor::distRGB2(const RGBColor& c1, const RGBColor& c2) {
    const uint32_t dR = RGBMath::diff(c1.R, c2.R);
    const uint32_t dG = RGBMath::diff(c1.G, c2.G);
    const uint32_t dB = RGBMath::diff(c1.B, c2.B);
    return dR * dR + dG * dG + dB * dB;
}

uint16_t RGBColor::distRGB(const RGBColor& c1, const RGBColor& c2) {
    return sqrt(distRGB2(c1, c2));
}

uint16_t RGBColor::distRGBFast(const RGBColor& c1, const RGBColor& c2) {
    const uint8_t dR = RGBMath::diff(c1.R, c2.R);
    const uint8_t dG = RGBMath::diff(c1.G, c2.G);
    const uint8_t dB = RGBMath::diff(c1.B, c2.B);
    const uint8_t maxd = RGBMath::max3(dR, dG, dB);
    const uint8_t mind = RGBMath::min3(dR, dG, dB);
    const uint16_t midd = uint16_t(dR) + dG + dB - maxd - mind;
    return (maxd * 961ul + midd * 398ul + mind * 305ul + 512) >> 10;
}

uint8_t RGBColor::distHue(const RGBColor& c1, const RGBColor& c2) {
    return RGBMath::circularDiff<uint8_t>(c1.toHSV().H, c2.toHSV().H, 255);
}

HSVColor RGBColor::toHSV() const {
    const uint8_t mx = RGBMath::max3(R, G, B);
    const uint8_t mn = RGBMath::min3(R, G, B);
    const uint8_t delta = mx - mn;

    HSVColor hsv;
    hsv.V = mx;

    if (!delta) return hsv;

    hsv.S = (uint16_t(delta) * 255) / mx;

    int16_t h;
    if (mx == R) {
        h = 43 * (int16_t(G) - int16_t(B)) / delta;
    } else if (mx == G) {
        h = 85 + 43 * (int16_t(B) - int16_t(R)) / delta;
    } else {
        h = 171 + 43 * (int16_t(R) - int16_t(G)) / delta;
    }

    if (h < 0) {
        h += 256;
    } else if (h > 255) {
        h -= 256;
    }

    hsv.H = h;
    return hsv;
}

void RGBColor::setHue(uint8_t col, uint8_t bright) {
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

void RGBColor::setHue16(uint16_t col, uint8_t bright) {
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

void RGBColor::setKelvin(uint16_t K, uint8_t bright) {
    const float tmpKelvin = constrain(K, uint16_t(1000), uint16_t(10000)) / 100.0f;
    float tmp;
    uint8_t r, g, b;

    if (tmpKelvin <= 66) {
        r = 255;
    } else {
        tmp = pow(tmpKelvin - 60, -0.1332047592) * 329.698727446;
        r = constrain(tmp, 0.0f, 255.0f);
    }

    if (tmpKelvin <= 66) {
        tmp = 99.4708025861 * log(tmpKelvin) - 161.1195681661;
    } else {
        tmp = pow(tmpKelvin - 60, -0.0755148492) * 288.1221695283;
    }
    g = constrain(tmp, 0.0f, 255.0f);

    if (tmpKelvin >= 66) {
        b = 255;
    } else if (tmpKelvin <= 19) {
        b = 0;
    } else {
        tmp = 138.5177312231 * log(tmpKelvin - 10) - 305.0447927307;
        b = constrain(tmp, 0.0f, 255.0f);
    }

    setRGB(r, g, b, bright);
}

void RGBColor::setKelvinFast(uint16_t K, uint8_t bright) {
    K = constrain(K, uint16_t(1000), uint16_t(10000));

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

void RGBColor::setHSV(uint8_t h, uint8_t s, uint8_t v) {
    const float H = h / 255.0f;
    const float S = s / 255.0f;
    const float V = v / 255.0f;

    const uint16_t i = H * 6;
    const float f = H * 6 - i;
    const float p = V * (1 - S);
    const float q = V * (1 - f * S);
    const float t = V * (1 - (1 - f) * S);

    switch (i % 6) {
        case 0: setRGB(255.0f * V, 255.0f * t, 255.0f * p); break;
        case 1: setRGB(255.0f * q, 255.0f * V, 255.0f * p); break;
        case 2: setRGB(255.0f * p, 255.0f * V, 255.0f * t); break;
        case 3: setRGB(255.0f * p, 255.0f * q, 255.0f * V); break;
        case 4: setRGB(255.0f * t, 255.0f * p, 255.0f * V); break;
        case 5: setRGB(255.0f * V, 255.0f * p, 255.0f * q); break;
    }
}

void RGBColor::setHSVFast(uint8_t h, uint8_t s, uint8_t v) {
    const uint16_t h2 = h * 24 / 17;
    const uint8_t vs = uint32_t(v) * s / 255;
    const uint8_t a = uint32_t(vs) * (h2 % 60) / 60;

    switch ((h2 / 60) % 6) {
        case 0: setRGB(v, v - vs + a, v - vs); break;
        case 1: setRGB(v - a, v, v - vs); break;
        case 2: setRGB(v - vs, v, v - vs + a); break;
        case 3: setRGB(v - vs, v - a, v); break;
        case 4: setRGB(v - vs + a, v - vs, v); break;
        case 5: setRGB(v, v - vs, v - a); break;
    }
}
