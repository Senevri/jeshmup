#ifndef MATH_H
#define MATH_H

#ifdef WIN32
#include <cmath>
#endif

#ifndef WIN32
#include <math.h>
#endif

namespace Math {

    int round(double x)
    {
        return static_cast<int>(x + 0.5);
    }

    int nextpoweroftwo(int x)
    {
        double logbase2 = log((float)x) / log((float)2);
        return round(pow(2,ceil(logbase2)));
    }

}

#endif // MATH_H
