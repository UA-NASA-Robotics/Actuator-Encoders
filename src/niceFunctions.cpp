#include "niceFunctions.h"
#include "math.h"

double convertToTheta(int x, int y, int z) {
    double length = atan(float(y)/float(x));
    return length;
}