#ifndef POINT3D_H
#define POINT3D_H

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

/**
  * Defines a simple class for points in 3d world.
  */
class Point3d
{
public:

    /**
      * Creates a point in origin (0,0,0).
      */
    Point3d() : x(0.0f),y(0.0f),z(0.0f){}

    /**
      * Creates a point the given coordinates
      * @param px The x coordinate of the point
      * @param py The y coordinate of the point
      * @param pz The z coordinate of the point
      */
    Point3d(GLfloat px, GLfloat py, GLfloat pz) : x(px),y(py),z(pz)
    {}

    /**
      * Fills the array with the content of the position.
      * @param array The array to fill with the position. <b>NOTE</b>
      * make sure the array has at least the length of three GLfloats.
      */
    void fillArray(GLfloat *array)
    {
        array[0] = x;
        array[1] = y;
        array[2] = z;
    }

public: //data members

    /**
      * The x coordinate.
      */
    GLfloat x;

    /**
      * The y coordinate.
      */
    GLfloat y;

    /**
      * The z coordinate.
      */
    GLfloat z;
};

#endif // POINT3D_H
