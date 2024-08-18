#include <iostream>
// #include <castdio> //cstdio, 과거 stdio.h
#include <string>
#include <cmath>
using namespace std;
class Shape{
    //abstract class
    public:

    Shape(){}
    virtual ~Shape(){cout<<"Shape destructor"<<endl;} // 꼭 virtual 해야 함. 상속이라면.
    virtual double calc_area() =0; // for abstract class : pure virtual function
    virtual string get_name() =0;

};


class Rectangle: public Shape{

    public :

        double width;
        double height;
        Rectangle(double w, double h): width(w), height(h) {};
        ~Rectangle(){cout<<"Rectangular destructor"<<endl;}
        double calc_area() override { return width*height;}
        string get_name() override {return "Rectangle";} // 굳이 여기다가 virtual을 쓰지 않아도 됨.

};


//Shape -> Rectangle -> Square
class Square : public Rectangle{
    public:

        Square(double w): Rectangle(w, w){}
        ~Square(){cout<<"Square destructor"<<endl;}
        string get_name() override{return "Square";} // override를 씀으로써 이게 가장 최신 함수로 반영됨.
};

class Triangle: public Shape{

    public:
        double a;
        double b;
        double c;

        Triangle(double a, double b, double c): a(a), b(b), c(c){};
        ~Triangle(){cout<<"Triangle destructor"<<endl;}
        double calc_area() override {
            double s = (a+b+c) /2;
            return sqrt(s*(s-a)*(s-b)*(s-c));
        }
        string get_name() override{return "Triangle";}

};



// Shape -> Triangle -> RightTriangle
class RightTriangle: public Triangle{
    public:
        RightTriangle(double a, double b): Triangle(a, b, sqrt(a*a+b*b)){}
        ~RightTriangle(){cout<<"RightTriangle destructor"<<endl;}
        double calc_area() override{
            return (a*b)/2;
        }
        string get_name() override{return "RightTriangle";}


};



int main(){
    double width = 3.0;
    double height = 4.0;
    Rectangle rectangle(width, height);
    cout<<"Rectangle Area : " << rectangle.calc_area()<<endl;
    cout<<"Name : "<<rectangle.get_name()<<endl;



    Square square(width);
    cout<<"Sqaure Area: "<<square.calc_area()<<endl;
    cout<<"Name : "<<square.get_name()<<endl;

    double a = 2;
    double b = 3;
    double c = 4;

    Triangle triangle(a, b,c);
    cout<<"Triangle Area : " <<triangle.calc_area() <<endl;
    cout<<"Name : "<<triangle.get_name()<<endl;

    RightTriangle righttri(a,b);
    cout<<"RightTriangle Area : "<<righttri.calc_area() <<endl;
    cout<<"Name : "<<righttri.get_name()<<endl;




    return 0;
}

//destrctor call

/*

RightTriangle destructor
Triangle destructor
Shape destructor

Triangle destructor
Shape destructor

Square destructor
Rectangular destructor
Shape destructor

Rectangular destructor
Shape destructor
*/