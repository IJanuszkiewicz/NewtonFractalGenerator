//
// Created by Igor on 16/01/2024.
//

#include "Polynomial.h"


Polynomial::Polynomial(const vector<complex<double>>& roots, complex<double> a) : roots(roots), a(a) {
    Polynomial p({1,-roots[0]});
    for(int i = 1; i < roots.size(); ++i) {
        p = p*Polynomial({1, -roots[i]});
    }
    coeffs = (p*a).coeffs;
}

complex<double> Polynomial::operator()(complex<double> x) const {
    complex<double> val = a;
    if(!roots.empty()) {
        for(int i = 0; i < roots.size(); ++i) {
            val *= x - roots[i];
        }
    } else {
        // horner
        for( int i = 1; i < coeffs.size(); ++i) {
            val = val*x + coeffs[i];
        }
    }
    return val;

}

complex<double> Polynomial::Derivative(complex<double> x) const {
    auto [val, dval] = ValAndDer(x);
    return dval;
}
tuple<complex<double>, complex<double>> Polynomial::ValAndDer(complex<double> x) const {
    complex<double> dval(0, 0), val(0,0);
    for(int i = 0; i < coeffs.size(); ++i) {
        dval = dval*x + val;
        val = val*x + coeffs[coeffs.size() - 1 - i];
    }
    return {val, dval};
}
Polynomial Polynomial::operator*(const Polynomial& p) const {
    vector<complex<double>> newCoeffs(coeffs.size() + p.coeffs.size() - 1);

    complex<double> sum;
    for( int i = 0; i < coeffs.size(); ++i) {
        sum = 0;
        for(int l = 0; l < p.coeffs.size(); l++) {
            newCoeffs[i + l] += coeffs[i] * p.coeffs[l];
        }
    }
    return Polynomial(newCoeffs);
}

Polynomial Polynomial::operator*(complex<double> a) const {
    Polynomial p(this->coeffs);

    for(auto coeff : p.coeffs) {
        coeff *= a;
    }
    return p;
}
