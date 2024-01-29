#include <iostream>

#include "Polynomial.h"
#include "NewtonFractalGenerator.h"

#define PLANE_SIZE 2000
#define PATH_WRITE "fractal.ppm"

int main() {
    vector<complex<double>> roots;
    roots.push_back(complex<double>(1,0));
    roots.push_back(complex<double>(-0.5,sqrt(3)/2));
    roots.push_back(complex<double>(-0.5,-sqrt(3)/2));

    Polynomial p(roots, complex<double>(1,0));

    NewtonFractalGenerator gen(p, PLANE_SIZE, PLANE_SIZE);
    gen.GeneratePoints();
    //gen.ShowPoints();
    cout << endl;
    gen.ColorPoints();

    gen.WriteToFile(PATH_WRITE);


}
