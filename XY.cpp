//
// Created by 研究用 on 2017/08/29.
//

#include "XY.h"

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

XY::XY(double x_input, double y_input) {
    x=x_input;
    y=y_input;
}

void XY::show() {
    cout<<"["<<x<<", "<<y<<"]"<<endl;
}

void XY::set_XY(double x_input, double y_input) {
    x=x_input;
    y=y_input;
}

double XY::getX() const {
    return x;
}

double XY::getY() const {
    return y;
}

double XY::distance(XY other) {
    return sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));
}

void XY::show_nonewline() {
    cout<<"["<<x<<", "<<y<<"]";
}
