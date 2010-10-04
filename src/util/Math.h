#ifndef MATH_H
#define MATH_H

#include <math.h>

namespace Math {

    int round(double x)
    {
        return static_cast<int>(x + 0.5);
    }

    int nextpoweroftwo(int x)
    {
        double logbase2 = log(x) / log(2);
        return round(pow(2,ceil(logbase2)));
    }

}

#endif // MATH_H
