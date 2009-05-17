/* 
 * GLScene. h
 * by: Esa Karjalaine
 * has: wrapper class for OpenGL. Knows objects and how to render.
 */

#pragma once
#include "SDL.h"
#ifdef _WINDOWS
	#include <windows.h>
#endif
#include "GL/gl.h"
#include "GL/glu.h"

#include "Mesh.h"
#include "object.h"
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
	void translateMesh(int mesh_id, float x, float y, float z);
	void rotateMesh(int mesh_id, float x, float y, float z);

	void drawScene(void);

	/* TODO: seems insufficient */
	struct camera {
		Mesh::vertex location;
		Mesh::vertex angle; /* hey, it's an array of three floats. */
	} camera;	
private:	

	/* mesh = mesh. 
	 * visible = "do we render this? 
	 * data = location, name, facing etc.
	 */
	typedef struct {
		Mesh *mesh; /* should mesh keep model/texture ? or new class?*/
		bool visible;
		Mesh::vertex location;
		Mesh::vertex angle; /* hey, it's an array of three floats. */		
	} scene_obj;
	std::vector<scene_obj> scene_objs; /* stupid ? */
	

	/* this won't do, at least not alone. */
	std::vector<Mesh *> meshes; /* so meshy */

};
