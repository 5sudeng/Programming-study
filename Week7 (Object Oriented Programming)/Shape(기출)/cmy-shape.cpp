#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Shape {
public:
    Shape() {}

    virtual double calc_area() = 0;
    virtual string get_name() { return "Shape"; }
};

class Rectangle : public Shape {
public:
    double w, h;

    Rectangle(double weight, double height) : Shape(), w(weight), h(height) {}

    double calc_area() override {
        return w*h;
    }
    string get_name() override { return "Rectangle"; }
};

class Square : public Rectangle {
public:
    Square(double weight) : Rectangle(weight, weight) {}
    
    string get_name() override { return "Square"; }
};

class Triangle : public Shape {
public:
    double a, b, c;

    Triangle(double a, double b, double c) : Shape(), a(a), b(b), c(c) {}

    double calc_area() override {
        double s = (a+b+c)/2;
        double area = sqrt(s*(s-a)*(s-b)*(s-c));
        return area;
    }
    string get_name() override { return "Triangle"; }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(double a, double b) : Triangle(a, b, sqrt(a*a+b*b)) {}

    double calc_area() override {
        return (a*b)/2;
    }
    string get_name() override { return "RightTriangle"; }
};

int main() {
    Rectangle rec(10, 5);
    cout << rec.get_name() << ": " << rec.calc_area() << endl;
    // Rectangle: 50

    Square squa(10);
    cout << squa.get_name() << ": " << squa.calc_area() << endl;
    // Square: 100

    Triangle tri(6, 6, 6);
    cout << tri.get_name() << ": " << tri.calc_area() << endl;
    // Triangle: 15.5885

    RightTriangle rightTri(6, 6);
    cout << rightTri.get_name() << ": " << rightTri.calc_area() << endl;
    // RightTriangle: 18
}