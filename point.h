#ifndef UNTITLED_POINT_H
#define UNTITLED_POINT_H

#include <iostream>
#include <math.h>

using namespace std;

class Point
{
    int x;
    int y;
public:
    int get_x() {return x;};
    int get_y() {return y;};
    void set_x(int x){this->x = x;};
    void set_y(int y){this->y = y;};
    Point(int x, int y);
    Point();
    Point operator+(Point);
    Point operator-(Point);
    int operator*(Point);
    int operator%(Point);//косое произведение
    Point operator*(int);
    Point operator/(int);
    int length();
    int angle(Point a);
    bool operator==(Point);
    bool operator!=(Point);
    friend ostream& operator<<(ostream&, const Point&);
};

Point::Point() {
    x = 0;
    y = 0;
}
Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}
Point Point::operator+(Point a) {
    return Point(this->x + a.x, this->y + a.y);
}
Point Point::operator-(Point a) {
    return Point(this->x - a.x, this->y - a.y);
}
Point Point::operator*(int a) {
    return Point(this->x * a, this->y * a);
}
Point Point::operator/(int a) {
    return Point(this->x / a, this->y / a);
}
int Point::operator*(Point a) {
    return this->x * a.x + this->y * a.y;
}
int Point::operator%(Point a) {
    return this->x * a.y - this->y * a.x;
}
int Point::length() {
    return sqrt(x*x+y*y);
}
int Point::angle(Point a) {
    return (a * *this / a.length() / this->length());
}
bool Point::operator==(Point) {
    bool answer;
    if(this->x == x && this->y == y)
        answer = true;
    else
        answer = false;
    return answer;
}
bool Point::operator!=(Point) {
    bool answer;
    if(this->x != x || this->y != y)
        answer = true;
    else
        answer = false;
    return answer;
}
ostream& operator<<(ostream& out, const Point& a)
{
    return out << "(" << a.x << ", " << a.y << ")";
}
#endif //UNTITLED_POINT_H
//main()
/*
 *  int x1, y1, x2, y2;
    cout << "Enter coordinates of the first vector/point:" << endl;
    cin >> x1 >> y1;
    Point v1(x1, y1);
    cout << "Enter coordinates of the second vector/point:" << endl;
    cin >> x2 >> y2;
    Point v2(x2, y2);
    cout << "Enter number (int): " << endl;
    int a;
    cin >> a;
    cout << "Sum: " << v1 + v2 << endl
    << "Difference: " << v1 - v2 << endl
    << "Scalar: " << v1 * v2 << endl
    << "Division (with rounding): " << v1/a << " and " << v2/a << endl
    << "Product on number: " << v1*a << " and " << v2*a << endl
    << "Skew(?): " << (v1 % v2) << endl
    << "Length: " << v1.length() << " and " << v2.length() << endl
    << "Angle: " << v1.angle(v1) << endl
    << "Operator==: " << (v1==v2) << endl
    << "Operator!=: " << (v1==v2) << endl;
 */