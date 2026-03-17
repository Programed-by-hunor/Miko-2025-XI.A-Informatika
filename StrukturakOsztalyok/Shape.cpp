#include <iostream>
#include <cmath>
#include <list>
const float pi=3.14;

using namespace std;

class Shape
{
    public:
    virtual float area() = 0;
    virtual float perimiter() = 0;
    virtual void name()
    {
        cout << "Shape" << endl;
    }
};

class Triangle: public Shape
{
    float a,b,c;
public:
    Triangle(float a, float b, float c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    float perimiter() override
    {
        return a + b + c;
    }
    float area() override
    {
        float p = perimiter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    void name()
    {
         cout << "Triangle" << endl;
    }
};

class Circle: public Shape
{
    float r;
public:
    Circle(float r)
     {
    this->r=r;

    }
    float perimiter()
    {
        return 2*r*pi;
    }
    float area() override
    {
        return pi*r*r;
    }
    void name()
    {
         cout << "Circle" << endl;
    }
};

class Quadrangle: public Shape
{
protected:
    float a,b,c,d;
public:
    Quadrangle(float a, float b, float c, float d)
    {
        this->a=a;
        this->b=b;
        this->c=c;
        this->d=d;
    }
    float perimiter()
    {
        return a+b+c+d;
    }
    float area() override
    {
        //nem tudjuk
        return 0;
    }
    void name()
    {
         cout << "Quadrangle" << endl;
    }
};

class Rectangle: public Quadrangle
{
public:
    Rectangle(float a, float b) : Quadrangle(a, b, a, b) {}
    float area() override
    {
        return a*b;
    }
    void name()
    {
         cout << "Rectangle" << endl;
    }
};

class Square: public Rectangle
{
public:
    Square(float a) : Rectangle(a,a) {}
    float area() override
    {
        return a*a;
    }
    void name()
    {
         cout << "Square" << endl;
    }
};

int main()
{
    Triangle a(3, 4, 5);
    Circle b(2);
    Quadrangle c(1,2,3,4);
    Rectangle d(2,4);
    Square e(9);

    list<Shape *> lista;
    lista.push_back(&a);
    lista.push_back(&b);
    lista.push_back(&c);
    lista.push_back(&d);
    lista.push_back(&e);

    for (Shape *s : lista) {
        s->name();
        cout<<"terulet:"<<s->area()<<endl;
        cout<<"kerulet:"<<s->perimiter()<<endl;
        cout<<endl;
    }


    return 0;
}
