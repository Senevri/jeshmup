/* 
 * GLScene. h
 * by: Esa Karjalaine
 * has: wrapper class for OpenGL. Knows objects and how to render.
 */

#ifndef _GLSCENE_H_
#define _GLSCENE_H_

#include <SDL/SDL.h>
#ifdef _WINDOWS
	#include <windows.h>
#endif
#include "GL/gl.h"
#include "GL/glu.h"

#include "Mesh.h"
#include "Light.h"
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
    void drawMesh(Mesh& mesh);
	void drawMesh(unsigned int index); /* use nth mesh in meshes */
	void addMesh(Mesh * mesh);
	void translateMesh(int mesh_id, float x, float y, float z);
	void rotateMesh(int mesh_id, float x, float y, float z);

	void drawScene(void);

	/* TODO: seems insufficient */
    struct Camera {
        Mesh::Vertex location;
        Mesh::Vertex angle; /* hey, it's an array of three floats. */
    } Camera;

private:	

	/* mesh = mesh. 
	 * visible = "do we render this? 
	 * data = location, name, facing etc.
	 */
	typedef struct {
		Mesh *mesh; /* should mesh keep model/texture ? or new class?*/
		bool visible;
        Mesh::Vertex location;
        Mesh::Vertex angle; /* hey, it's an array of three floats. */
    } Scene_obj;
    std::vector<Scene_obj> m_scene_objs; /* stupid ? */
	

	/* this won't do, at least not alone. */
	std::vector<Mesh *> meshes; /* so meshy */
    Light m_mainLight;

};

#endif //_GLSCENE_H_
