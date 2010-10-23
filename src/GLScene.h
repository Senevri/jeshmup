/* 
 * GLScene. h
 * by: Esa Karjalaine
 * has: wrapper class for OpenGL. Knows objects and how to render.
 */

#ifndef _GLSCENE_H_
#define _GLSCENE_H_

#include <SDL.h>
#ifdef _WINDOWS
	#include <windows.h>
#endif
#include "GL/gl.h"
#include "GL/glu.h"

#include "Mesh.h"
#include "Light.h"
#include "object.h"
#include <vector>

class Level;

/**
 *  OpenGL wrapper for the disgusting state machine
 *  (well, not _that_ disgusting.)
 */
class GLScene
{
public:
    GLScene(DrawEngine *drawEngine);
    ~GLScene();
    // int sdl gl stuff
    void init(void);
    /* takes screen /viewport w / h */
    void setup(int width, int height);
	Level * getLevel();

    void setLevel(Level* level);

    void drawScene();
    void updateScene(int ticks);

    /**
     * "Draws" the lights i.e. sets up the lights in the GL scene
     */
    void drawLights();

    /* TODO: seems insufficient */
    struct Camera {
        Mesh::Vertex location;
        Mesh::Vertex angle; /* hey, it's an array of three floats. */
    } Camera;

private:
    Light m_mainLight;
    Level *m_level;
    DrawEngine *m_drawEngine;

};

#endif //_GLSCENE_H_
