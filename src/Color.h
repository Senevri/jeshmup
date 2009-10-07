#pragma once

#ifdef WIN32
#include <windows.h>
#undef RGB
#endif
#include <GL/gl.h>

namespace Color {

    class RGB
    {
    public:
        RGB() : red(0.5f),green(0.5f),blue(0.5f)
        {}

        RGB(GLfloat red, GLfloat green, GLfloat blue)
            : red(red), green(green), blue(blue)
        {}

        virtual ~RGB()
        {}

        virtual void fillArray(GLfloat *array)
        {
            array[0] = red;
            array[1] = green;
            array[2] = blue;
        }

        GLfloat red;
        GLfloat green;
        GLfloat blue;

    };

    class RGBA : public RGB
    {
    public:

        RGBA() : RGB(), alpha(1.0f)
        {}

        RGBA(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
            : RGB(red, green, blue), alpha(alpha)
        {}

        virtual void fillArray(GLfloat *array)
        {
            array[0] = red;
            array[1] = green;
            array[2] = blue;
            array[3] = alpha;
        }

        GLfloat alpha;
    };

    static const RGBA WHITE(1.0f, 1.0f, 1.0f, 1.0f);
    static const RGBA BLUE(0.0f, 0.0f, 1.0f, 1.0f);
    static const RGBA GREEN(0.0f, 1.0f, 0.0f, 1.0f);
    static const RGBA RED(1.0f, 0.0f, 0.0f, 1.0f);
    static const RGBA GRAY(0.5f, 0.5f, 0.5f, 1.0f);
}

