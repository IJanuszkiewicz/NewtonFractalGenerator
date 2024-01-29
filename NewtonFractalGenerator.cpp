//
// Created by Igor on 16/01/2024.
//

#include "NewtonFractalGenerator.h"

#include <algorithm>
#include <iostream>
#include <fstream>

vector<double> NewtonFractalGenerator::LinearSpacedArray(double a, double b, size_t N) {
    {
        double h = (b - a) / static_cast<double>(N-1);
        std::vector<double> xs(N);
        std::vector<double>::iterator x;
        double val;
        for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h) {
            *x = val;
        }
        return xs;
    }
}
complex<double> NewtonFractalGenerator::NewtonMethod(complex<double> startingPoint) {
    int maxIters = 1000;
    double eps = 1e-7;
    complex<double> result = startingPoint, prev = startingPoint + complex<double>(1,1);
    pair<complex<double>, complex<double>> valDerPair;
    int i = 0;
    while(abs((result - prev)) > eps && i < maxIters) {
        prev = result;
        auto [val, der] = p.ValAndDer(result);
        result = result - val/der;
        ++i;
    }
    return result;
}
int NewtonFractalGenerator::GetPointColor(complex<double> point) {
    complex<double> resoult = NewtonMethod(point);
    int closestRoot = 0;
    double minDist = numeric_limits<double>::max();
    for(int i = 0; i < p.roots.size(); ++i) {
        if(abs(resoult - p.roots[i]) < minDist) {
            minDist = abs(resoult - p.roots[i]);
            closestRoot = i;
        }
    }
    return closestRoot;
}
void NewtonFractalGenerator::GeneratePoints() {
    int ymax = INT_MIN;
    int ymin = INT_MAX;
    int xmax = INT_MIN;
    int xmin = INT_MAX;
    for_each(p.roots.begin(), p.roots.end(), [&](complex<double> root) {
        if (root.real() > xmax) xmax = ceil(root.real());
        if (root.real() < xmin) xmin = floor(root.real());
        if (root.imag() > ymax) ymax = ceil(root.imag());
        if (root.imag() < ymin) ymin = floor(root.imag());
    });

    complex<double> bottomLeft(xmin, ymin);
    complex<double> topRight(xmax, ymax);

    vector<double> yAxis = LinearSpacedArray(bottomLeft.imag(), topRight.imag(), PlaneHight);
    vector<double> xAxis = LinearSpacedArray(bottomLeft.real(), topRight.real(), PlaneWidth);
    for(int i = 0; i < PlaneWidth; ++i) {
        plane[i] = vector<ColoredPoint>(PlaneHight);
        for(int j = 0; j < PlaneHight; ++j) {
            plane[i][j] = ColoredPoint(complex(xAxis[i], yAxis[j]), -1);
        }
    }
}
void NewtonFractalGenerator::ColorPoints() {
    for(int i = 0; i < PlaneWidth; ++i) {
        for(int j = 0; j < PlaneHight; ++j) {
            plane[i][j].color = GetPointColor(plane[i][j].point);
        }
    }
}
void NewtonFractalGenerator::ShowPoints() const {
    for(int i = 0; i < PlaneWidth; ++i) {
        for(int j = 0; j < PlaneHight; ++j) {
            char c;
            switch (plane[i][j].color) {
                case 0:
                    c = '0';
                    break;
                case 1:
                    c = '.';
                    break;
                case 2:
                    c = '*';
                    break;
            }
            cout << c;
        }
        cout << endl;
    }
}
void NewtonFractalGenerator::WriteToFile(string filePath) {
    vector<rgb> colors;
    colors.push_back(rgb(byte(200),byte(0),byte(0)));
    colors.push_back(rgb(byte(0),byte(250),byte(0)));
    colors.push_back(rgb(byte(50),byte(0),byte(250)));

    ofstream file(filePath);
    if(!file.is_open()) return;

    file << "P3" << endl << PlaneHight << ' ' << PlaneWidth << endl
    << 255 << endl;

    for(int i = 0; i < PlaneHight; ++i) {
        for(int j = 0; j < PlaneWidth; ++j) {
            rgb color = colors[plane[i][j].color];
            file << to_integer<int>(color.r) << ' ' <<
                to_integer<int>(color.g) << ' ' <<
                to_integer<int>(color.b) << "    ";
        }
        file << endl;
    }
    file.close();

}
