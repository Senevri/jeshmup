#pragma once
#include "SDL.h"
#ifdef _WINDOWS
	#include <windows.h>
#endif
#include "GL/gl.h"
#include "GL/glu.h"

#include <vector>
/**
 *  OpenGL wrapper for the disgusting state machine
 *
 */
class GLScene
{
public:
	GLScene(void);
	~GLScene(void);
	// int sdl gl stuff
	void init(void);
	void setup(int width, int height);
	void intArrayToVertices(int * arr, int size);
	void drawQuads(void);
	void testDrawing(void);

private:	
	typedef struct {
		GLfloat xyz[3];
	}struct_vertex;
	std::vector<struct_vertex *> vertices;

};
