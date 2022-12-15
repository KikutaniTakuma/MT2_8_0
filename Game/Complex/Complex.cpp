#include "Game/Complex/Complex.h"

Complex::Complex() {
	this->real = 0.0f;
	this->imag = 0.0f;
}

Complex::Complex(const float& re, const float& im) {
	this->real = re;
	this->imag = im;
}

Complex::Complex(const Complex& tmp) {
	*this = tmp;
}

Complex Complex::operator+(const Complex& num) {
	Complex tmp;

	tmp.real = this->real + num.real;
	tmp.imag = this->imag + num.real;

	return tmp;
}

Complex Complex::operator*(const Complex& num) {
	Complex tmp;

	tmp.real = (this->real * num.real) - (this->imag * num.imag);
	tmp.imag = (this->real * num.imag) + (this->imag * num.real);

	return tmp;
}

const Complex& Complex::operator=(const Complex& num) {
	this->real = num.real;
	this->imag = num.imag;

	return *this;
}

const Complex& Complex::operator+=(const Complex& num) {
	*this = *this + num;

	return *this;
}

const Complex& Complex::operator*=(const Complex& num) {
	*this = *this * num;

	return *this;
}