#include "GLScene.h"
#include <iostream>

/**
	NOTE: Ripped off tutorials a lot here, so there's 
	some copypasta cleanup to do.
*/



GLScene::GLScene(void)
{
	this->camera.location.x = 0.0f;
	this->camera.location.y = 0.0f;
	this->camera.location.z = -2.0f;
	this->camera.angle.x = 0.0f;
	this->camera.angle.y = 0.0f;
	this->camera.angle.z = 0.0f;
}

GLScene::~GLScene(void)
{
	std::vector<Mesh *>::iterator itr;
	for ( itr = meshes.begin(); itr < meshes.end(); ++itr )
	{	
		delete *itr;
	}
}

// int sdl gl stuff
void GLScene::init(void)
{
    glShadeModel( GL_SMOOTH ); /* GL_FLAT, GL_SMOOTH shade model */

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 100.0f );
	
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	/*make stuff translucent */
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	/* the following could be tweaked on per-mesh basis.*/
	//glEnable(GL_BLEND);		// Turn Blending On 
	//glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off

	/*end make stuff translucent*/

	//return undefined();
}

/**
	Todo: Parameters
	much copypasta
*/
void GLScene::setup(int width, int height)
{
    /* Height / width ration */
    GLfloat ratio;
 
    /* Protect against a divide by zero */
   if ( height == 0 )
		height = 1;

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.01f, 1000.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );
}

void GLScene::addMesh(Mesh * mesh){
	this->meshes.push_back(mesh);
}

void GLScene::drawMesh(unsigned int index){
	this->drawMesh(*meshes[index]);
}

void GLScene::drawScene(void){
	/* clear buffers */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glTranslatef( this->camera.location.x, this->camera.location.y, this->camera.location.z );
	/*camera moves HERE.*/

	std::vector<Mesh *>::iterator itr;
	for ( itr = this->meshes.begin(); itr < this->meshes.end(); ++itr )
	{	
		this->drawMesh(**itr);
	}

//	translate += tradd;
}

void GLScene::translateMesh(int mesh_id, float x, float y, float z)
{

}

void GLScene::rotateMesh(int mesh_id, float x, float y, float z)
{

}


void GLScene::drawMesh(Mesh mesh)
{    
	
	static GLfloat rotate = 0.0f;
	GLubyte white[] = {224, 224, 224, 128}; /* rgba? a no effect*/
	GLubyte green[] = {0, 196, 0, 128}; 
    //glMatrixMode( GL_MODELVIEW );
	//glLoadIdentity( );
	GLubyte * color = white;

	/* jottei olla naamassa kiinni*/
	//glTranslatef( 0.0f, 0.0f, -2.0f );

	if(rotate==360.0f) rotate=0.0f;

    glRotatef( rotate, 1.0f, 1.0f, 1.0f );

	GLubyte tmp=0;

	std::vector<Mesh::vertex *> vertices = mesh.getMeshVertices();
	
	GLenum type;

	switch(mesh.getType()){
		case Mesh::POINTS:
			type = GL_POINTS;
			break;
		case Mesh::TRIANGLES:
			type = GL_TRIANGLES;
			break;
		case Mesh::QUADS:
			type = GL_QUADS;
			break;
	}

	//glPointSize(4.0f);
	int i=1;
	glBegin( type );
		std::vector<Mesh::vertex *>::iterator itr;
		for ( itr = vertices.begin(); itr < vertices.end(); ++itr )
		{	
			Mesh::vertex *v = *itr;
			glColor4ubv( color );
			//glVertex3fv( v->xyz );
			glVertex3f( v->x, v->y, v->z );
			if( i%3 == 0) { /*if face then change color */
				if(color == white) color = green;
				else color = white;
			}
			i++;
		}
	glEnd();
	//rotate += 0.2f;
}


