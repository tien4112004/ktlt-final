#pragma once

#include <iostream>
#include <cmath>
using namespace std;

struct Monomial {
	int coefficent;
	int power;

	friend istream& operator>>(istream& in, Monomial& u);
	friend ostream& operator<<(ostream& out, Monomial u);

	Monomial operator+(Monomial u);
	Monomial operator-(Monomial u);
	Monomial operator*(Monomial u);
	Monomial operator/(Monomial u);
};

struct Polynomial {
	int degree;
	Monomial arr[201] = {};

	Polynomial() : degree(0) {}

	void setPower();

	friend istream& operator>>(istream& in, Polynomial& P);
	friend ostream& operator<<(ostream& out, Polynomial P);

	Polynomial operator+(Polynomial P);
	Polynomial operator-(Polynomial P);
	Polynomial operator*(Monomial u);
	Polynomial operator*(Polynomial P);
	Polynomial operator/(Polynomial P);
	Polynomial operator%(Polynomial P);

	bool operator==(int num);
	bool operator!=(int num);
};