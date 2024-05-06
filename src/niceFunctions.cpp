#include "niceFunctions.hpp"
#include "math.h"

double angleXY(int x, int y) {
    double length = atan(float(y)/float(x));
    return length;
}

double angleXZ(int x, int z) {
    double length = atan(float(z)/float(x));
    return length;
}

double andgleYZ(int y, int z) {
    double length = atan(float(z)/float(y));
    return length;
}

double angleYX(int y, int x) {
    double length = atan(float(x)/float(y));
    return length;
}

double angleZX(int z, int x) {
    double length = atan(float(x)/float(z));
    return length;
}

double angleZY(int z, int y) {
    double length = atan(float(y)/float(z));
    return length;
}