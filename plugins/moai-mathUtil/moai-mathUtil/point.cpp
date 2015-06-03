#include "point.h"
#include <iostream>
mPoint::~mPoint(){}
mPoint::mPoint(float x, float y){
    _x	= x;
    _y	= y;
	_tag = -1;
	_mag =  sqrtf(x*x + y*y);
}
void mPoint::show(){std::cout << "(" << x() << "," << y() << ")";}
void mPoint::x(float x){_x = x;}
void mPoint::y(float y){_y = y;}
float mPoint::x(){return _x;}
float mPoint::y(){return _y;}