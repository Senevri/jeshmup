#ifndef POINT2D_H
#define POINT2D_H

#include <GL/gl.h>

/**
  * Defines a simple class for points in 3d world.
  */
class Point2d
{
public:

    /**
      * Creates a point in origin (0,0).
      */
    Point2d() : x(0.0f),y(0.0f)
    {}

    /**
      * Creates a point the given coordinates
      * @param px The x coordinate of the point
      * @param py The y coordinate of the point
      */
    Point2d(GLint px, GLint py) : x(px),y(py)
    {}

    /**
      * Fills the array with the content of the position.
      * @param array The array to fill with the position. <b>NOTE</b>
      * make sure the array has at least the length of two GLints.
      */
    void fillArray(GLint *array)
    {
        array[0] = x;
        array[1] = y;
    }

public: //data members

    /**
      * The x coordinate.
      */
    GLint x;

    /**
      * The y coordinate.
      */
    GLint y;
};

#endif // POINT2D_H
