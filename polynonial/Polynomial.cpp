#include "Polynomial.h"

istream& operator>>(istream& in, Monomial& u) {
	bool negative = false;
	if (in.peek() == '-') {
		negative = true;
		in.ignore(1);
	}
	in >> u.coefficent;
	if (in.fail()) {
		in.clear();
		u.coefficent = 1;
	}
	u.coefficent *= (negative ? -1 : 1);
	if (in.peek() != 'x') {
		u.power = 0;
		return in;
	}
	in.ignore(1);
	if (in.peek() != '^') {
		u.power = 1;
		return in;
	}
	in.ignore(1);
	in >> u.power;
	return in;
}

ostream& operator<<(ostream& out, Monomial u) {
	if (u.coefficent == 0) {
		out << 0;
		return out;
	}
	if (u.coefficent != 1 && u.coefficent != -1) {
		out << u.coefficent;
	}
	if (u.power == 0) {
		if (u.coefficent == 1 || u.coefficent == -1) {
			out << u.coefficent;
		}
		return out;
	}
	if (u.coefficent == -1) out << "-";
	out << "x";
	if (u.power != 1) {
		out << "^" << u.power;
	}
	return out;
}

Monomial Monomial::operator+(Monomial u) {
	return { coefficent + u.coefficent, u.power };
}


Monomial Monomial::operator-(Monomial u) {
	return { coefficent - u.coefficent, u.power };
}

Monomial Monomial::operator*(Monomial u) {
	return { coefficent * u.coefficent, power + u.power };
}

Monomial Monomial::operator/(Monomial u) {
	return { coefficent / u.coefficent , power - u.power };
}

istream& operator>>(istream& in, Polynomial& P) {
	Monomial u = {};
	while (in.peek() != '\n' && in.peek() != -1) {
		in >> u;
		P.arr[u.power] = u;
		P.degree = max(P.degree, u.power);
	}
	P.setPower();
	in.ignore();
	return in;
}

ostream& operator<<(ostream& out, Polynomial P) {
	if (P.degree == 0) {
		out << P.arr[0];
		return out;
	}
	for (int i = P.degree; i >= 0; i--) {
		if (i < P.degree && P.arr[i].coefficent > 0) {
			out << "+";
		}
		if (P.arr[i].coefficent != 0) {
			out << P.arr[i];
		}
	}
	return out;
}

void printInfo(Polynomial P) {
	cout << P.degree << "\n";
	for (int i = 0; i <= P.degree; i++) {
		cout << P.arr[i].coefficent << " " << P.arr[i].power << "\n";
	}
}

void Polynomial::setPower() {
	for (int i = 0; i <= degree; i++) {
		arr[i].power = i;
	}
}

Polynomial Polynomial::operator+(Polynomial P) {
	Polynomial result;
	int deg = 0;
	for (int i = 0; i <= max(degree, P.degree); i++) {
		result.arr[i] = arr[i] + P.arr[i];
		if (result.arr[i].coefficent != 0) {
			deg = max(deg, i);
		}
	}
	result.degree = deg;
	return result;
}


Polynomial Polynomial::operator-(Polynomial P) {
	Polynomial result;
	int deg = 0;
	for (int i = 0; i <= max(degree, P.degree); i++) {
		result.arr[i] = arr[i] - P.arr[i];
		if (result.arr[i].coefficent != 0) {
			deg = max(deg, i);
		}
	}
	result.degree = deg;
	return result;
}

Polynomial Polynomial::operator*(Monomial u) {
	Polynomial result;
	result.degree = u.power + degree;
	for (int i = 0; i <= degree; i++) {
		result.arr[u.power + i] = arr[i] * u;
	}
	return result;
}

Polynomial Polynomial::operator*(Polynomial P) {
	Polynomial result;
	for (int i = 0; i <= degree; i++) {
		result = result + P * arr[i];
	}
	return result;
}

Polynomial Polynomial::operator/(Polynomial P) {
	Polynomial result;
	if ((*this) == 0 || degree < P.degree) {
		return result;
	}
	Polynomial remain = *this;
	result.degree = degree - P.degree;
	result.setPower();
	Monomial u = {};
	while (remain.degree >= P.degree && remain != 0) {
		u = remain.arr[remain.degree] / P.arr[P.degree];
		result.arr[u.power] = u;
		remain = remain - P * u;
	}
	return result;
}

Polynomial Polynomial::operator%(Polynomial P) {
	if ((*this) == 0 || degree < P.degree) {
		return (*this);
	}
	Polynomial remain = *this;
	Monomial u = {};
	while (remain.degree >= P.degree && remain != 0) {
		u = remain.arr[remain.degree] / P.arr[P.degree];
		remain = remain - P * u;
	}
	return remain;
}

bool Polynomial::operator==(int num) {
	return (degree == 0 && arr[0].coefficent == num);
}

bool Polynomial::operator!=(int num) {
	return (degree != 0 || arr[0].coefficent != num);
}

