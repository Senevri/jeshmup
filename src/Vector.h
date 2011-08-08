#pragma once

#include "Point3d.h"

#include <assert.h>

#ifdef WIN32
//#include <windows.h>
#include <cmath>
#else
#include <math.h>
#endif

#include <GL/gl.h>

/**
  * Defines a vector in 3d-space.
  */
class Vector
{

public:

    /**
      * Creates a null vector
      */
    Vector()
    {
        data[0] = 0;
        data[1] = 1;
        data[2] = 2;
    }

    /**
      * Creates a vector with given components values.
      * @param x The x (i) component of the vector
      * @param y The y (j) component of the vector
      * @param z The z (k) component of the vector
      */
    Vector(GLfloat x, GLfloat y, GLfloat z)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }

    /**
      * Creates a vector from two points in 3d space.
      * @param from The starting point of the vector
      * @param to The ending point of the vetor
      */
    Vector(const Point3d& from, const Point3d& to)
    {
        data[0] = to.x - from.x;
        data[1] = to.y - from.y;
        data[2] = to.z - from.z;
    }

    /**
      * The copy constructor. Creates a simple copy.
      * @param copy The vector to copy values from.
      */
    Vector(const Vector& copy)
    {
        this->data[0] = copy.data[0];
        this->data[1] = copy.data[1];
        this->data[2] = copy.data[2];
    }

    /**
      * Default destructor.
      */
    ~Vector()
    {
    }

public:

    /**
      * Returns the x component of the vector.
      * @return The x component of the vector
      */
    GLfloat x() {return data[0];}

    /**
      * Returns the y component of the vector.
      * @return The y component of the vector
      */
    GLfloat y() {return data[1];}

    /**
      * Returns the y component of the vector.
      * @return The z component of the vector
      */
    GLfloat z() {return data[2];}

public: //interface

    /**
      * Return the length of the vector.
      * @return The length of the vector
      */
    GLfloat length() const
    {
        return sqrt((data[0] * data[0])
                    + (data[1] * data[1])
                    + (data[2] * data[2]));
    }

    /**
      * Returns a normalized copy of this vector.
      * @return Normalized (unit length) copy of the vector
      */
    Vector normalized() const
    {
        GLfloat len = length();
        return Vector(data[0]/len, data[1]/len, data[2]/len);
    }

    /**
      * Normalizes this vector to unit length.
      */
    void normalize()
    {
        GLfloat len = length();
        data[0] /= len;
        data[1] /= len;
        data[2] /= len;
    }

    /**
      * Returns the dot product of this and the given vector.
      * @param vector The vector to compute dot product with
      * @return The dot product
      */
    GLfloat dot(const Vector& vector) const
    {
        return ((data[0] * vector.data[0])
                + (data[1] * vector.data[1])
                + (data[2] * vector.data[2]));
    }

    /**
      * Computes the cross product of this and the given vector.
      * @param vector The vector to calculate cross product with
      * @return The result vector of the cross product
      */
    Vector cross(const Vector& vector) const
    {
        return Vector(
                (data[1] * vector.data[2]) - (data[2] * vector.data[1]),
                (data[2] * vector.data[0]) - (data[0] * vector.data[2]),
                (data[0] * vector.data[1]) - (data[1] * vector.data[0]));

    }

    /**
      * Overrided +-operator to implement vector addition.
      */
    Vector& operator+ (const Vector& addition)
    {
        data[0] += addition.data[0];
        data[1] += addition.data[1];
        data[2] += addition.data[2];
        return *this;
    }

    /**
      * Overrided +=operator to implement vector addition.
      */
    Vector& operator+= (const Vector& addition)
    {
        data[0] += addition.data[0];
        data[1] += addition.data[1];
        data[2] += addition.data[2];
        return *this;
    }

    /**
      * Overrided - operator to implement vector subtraction
      */
    Vector& operator- (const Vector& minus)
    {
        data[0] -= minus.data[0];
        data[1] -= minus.data[1];
        data[2] -= minus.data[2];
        return *this;
    }

    /**
      * Overrided -= operator to implement vector subtraction.
      */
    Vector& operator-= (const Vector& minus)
    {
        data[0] -= minus.data[0];
        data[1] -= minus.data[1];
        data[2] -= minus.data[2];
        return *this;
    }

    /**
      * Overrided *-operator to implement scalar multiplication.
      */
    template <typename T>
    Vector& operator* (const T& multiplication)
    {
        data[0] *= multiplication;
        data[1] *= multiplication;
        data[2] *= multiplication;
        return *this;
    }

    /**
      * Overrided *-operator to implement scalar multiplication.
      */
    template <typename T>
    Vector& operator*= (const T& multiplication)
    {
        data[0] *= multiplication;
        data[1] *= multiplication;
        data[2] *= multiplication;
        return *this;
    }

    /**
      * Overrided *-operator to implement scalar division.
      */
    template <typename T>
    Vector& operator/ (const T& divisor)
    {
        data[0] /= divisor;
        data[1] /= divisor;
        data[2] /= divisor;
        return *this;
    }

    /**
      * Overrided *-operator to implement scalar division.
      */
    template <typename T>
    Vector& operator/= (const T& divisor)
    {
        data[0] /= divisor;
        data[1] /= divisor;
        data[2] /= divisor;
        return *this;
    }

    /**
      * Overrided = operator for converting Point3d to Vector.
      * For convenience purposes.
      */
    Vector& operator= (const Point3d& point)
    {
        this->data[0] = point.x;
        this->data[1] = point.y;
        this->data[2] = point.z;
        return *this;
    }

public: //static utility functions

    /**
      * Finds and returns the normal vector of the given three points.
      * @param p1 The first point in the plane
      * @param p2 The second point in the plane
      * @param p3 The third point in the plane
      * @return The vector perpendicular to the plane defined with three points
      */
    static Vector normalVector(const Point3d& p1,
                               const Point3d& p2,
                               const Point3d& p3)
    {
        Vector v1(p1,p2);
        Vector v2(p1,p3);
        return v1.cross(v2);
    }

private:

    /**
      * The vector components in an aray.
      */
    GLfloat data[3];
};

