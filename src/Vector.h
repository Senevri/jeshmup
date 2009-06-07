#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <math.h>
#include <GL/gl.h>

class Vector
{
    static const int SIZE;
public:
    Vector();
    Vector(GLfloat x, GLfloat y, GLfloat z);

    ~Vector();

    GLfloat x() {return data[0];}
    GLfloat y() {return data[1];}
    GLfloat z() {return data[2];}

    GLfloat length() const
    {
        return sqrt(data[0]^2,
                    data[1]^2,
                    data[2]^2);
    }

    Vector normalized() const
    {
        GLfloat length = length();
        return Vector(data[0]/length, data[1]/length, data[2]/length);
    }

    void normalize()
    {
        GLfloat length = length();
        data[0] /= length;
        data[1] /= length;
        data[2] /= length;
    }

    GLfloat dot(const Vector& vector) const
    {
        return ((data[0] * vector.data[0])
                + (data[1] * vector.data[1])
                + (data[2] * vector.data[2]));
    }

    Vector cross(const Vector& vector) const
    {
        return Vector(
                (data[1] * vector.data[2]) - (data[2] * vector.data[1]),
                (data[2] * vector.data[0]) - (data[0] * vector.data[2]),
                (data[0] * vector.data[1]) - (data[1] * vector.data[0]));

    }

    Vector& operator+ (const Vector& addition)
    {
        data[0] += addition.data[0];
        data[1] += addition.data[1];
        data[2] += addition.data[2];
        return *this;
    }

    Vector& operator+= (const Vector& addition)
    {
        data[0] += addition.data[0];
        data[1] += addition.data[1];
        data[2] += addition.data[2];
        return *this;
    }

    Vector& operator- (const Vector& minus)
    {
        data[0] -= addition.data[0];
        data[1] -= addition.data[1];
        data[2] -= addition.data[2];
        return *this;
    }

    Vector& operator-= (const Vector& minus)
    {
        data[0] -= addition.data[0];
        data[1] -= addition.data[1];
        data[2] -= addition.data[2];
        return *this;
    }

    template <typename T>
    Vector& operator* (const T& multiplication)
    {
        data[0] *= multiplication;
        data[1] *= multiplication;
        data[2] *= multiplication;
    }

    template <typename T>
    Vector& operator*= (const T& multiplication)
    {
        data[0] *= multiplication;
        data[1] *= multiplication;
        data[2] *= multiplication;
    }

    template <typename T>
    Vector& operator/ (const T& divisor)
    {
        data[0] /= divisor;
        data[1] /= divisor;
        data[2] /= divisor;
    }

    template <typename T>
    Vector& operator/= (const T& divisor)
    {
        data[0] /= divisor;
        data[1] /= divisor;
        data[2] /= divisor;
    }

private:
    GLfloat data[3];
};

#endif // VECTOR_H
