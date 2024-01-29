//
// Created by Igor on 16/01/2024.
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <complex>
#include <vector>
using namespace std;

class NewtonFractalGenerator;

class Polynomial {
    vector<complex<double>> coeffs;
    vector<complex<double>> roots;
    complex<double> a;
public:
    explicit Polynomial(vector<complex<double>> coeffs) : coeffs(coeffs), a(coeffs[0]) {}
    Polynomial(const vector<complex<double>>& roots, complex<double> a);
    Polynomial() = default;
    Polynomial(const Polynomial& p) = default;
    complex<double> operator()(complex<double> x) const;
    Polynomial Derivative() const;
    complex<double> Derivative(complex<double> x) const;
    tuple<complex<double>, complex<double>> ValAndDer(complex<double> x) const;

    Polynomial operator*(const Polynomial& p) const;
    Polynomial operator*(complex<double> a) const;

    friend class NewtonFractalGenerator;
};



#endif //POLYNOMIAL_H
