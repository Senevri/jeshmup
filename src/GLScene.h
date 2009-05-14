#pragma once
#include "SDL.h"
#ifdef _WINDOWS
	#include <windows.h>
#endif
#include "GL/gl.h"
#include "GL/glu.h"

#include "Mesh.h"
#include <vector>
/**
 *  OpenGL wrapper for the disgusting state machine
 *  (well, not _that_ disgusting.)
 */
class GLScene
{
public:
	GLScene(void);
	~GLScene(void);
	// int sdl gl stuff
	void init(void);
	/* takes screen /viewport w / h */
	void setup(int width, int height);
	void intArrayToVertices(int * arr, int size);
	void drawMesh(Mesh mesh);
	void drawMesh(unsigned int index); /* use nth mesh in meshes */
	void addMesh(Mesh * mesh);
	void testDrawing(void);

private:	
	std::vector<Mesh *> meshes; /* so meshy */

};
