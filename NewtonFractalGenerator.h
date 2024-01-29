//
// Created by Igor on 16/01/2024.
//

#ifndef NEWTONFRACTALGENERATOR_H
#define NEWTONFRACTALGENERATOR_H
#include <vector>

#include "Polynomial.h"
using namespace  std;
struct rgb {
    byte r;
    byte g;
    byte b;
    rgb(byte r, byte g, byte b): r(r), g(g), b(b){}
    rgb() = default;
};
class NewtonFractalGenerator {
    struct ColoredPoint {
        complex<double> point;
        int color;
        ColoredPoint(complex<double> point, int color): point(point), color(color){}
        ColoredPoint() = default;

        ColoredPoint operator=(ColoredPoint p){point = p.point; color = p.color; return*this;}
    };

    Polynomial p;
    vector<vector<ColoredPoint>> plane;
    int PlaneHight, PlaneWidth; // TODO: do something smarter

    static vector<double> LinearSpacedArray(double a, double b, size_t N);

    int GetPointColor(complex<double> point);
public:
    NewtonFractalGenerator(const Polynomial& p, const int PlaneHight, const int PlaneWidth)
    : p(p), PlaneHight(PlaneHight), PlaneWidth(PlaneWidth), plane(PlaneWidth) { }
    void GeneratePoints();
    void ColorPoints();
    void ShowPoints() const;
    void WriteToFile(string filePath);
    complex<double> NewtonMethod(complex<double> startingPoint);
};



#endif //NEWTONFRACTALGENERATOR_H
