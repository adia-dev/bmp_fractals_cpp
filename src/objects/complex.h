#pragma once

#include <cmath>
struct Complex {
  double re;
  double im;

  Complex() : re(0), im(0) {}
  Complex(double re, double im) : re(re), im(im) {}

  Complex add(const Complex &other) const {
    return {
        this->re + other.re,
        this->im + other.im,
    };
  }

  Complex mul(const Complex &other) const {
    return {this->re * other.re - this->im * other.im,
            this->re * other.im + this->im * other.re};
  }

  Complex abs() const { return {std::abs(this->re), std::abs(this->im)}; }

  double sq_mag() const { return this->re * this->re + this->im * this->im; }
};
