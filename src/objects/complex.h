#pragma once

struct Complex {
  double re;
  double im;

  Complex add(const Complex &other) const {
    return {
        .re = this->re + other.re,
        .im = this->im + other.im,
    };
  }

  Complex mul(const Complex &other) const {
    return {.re = this->re * this->re - other.re * other.re,
            .im = this->re * other.im + this->im * other.re};
  }

  double sqrt_mag() const { return this->re * this->re + this->im * this->im; }
};
