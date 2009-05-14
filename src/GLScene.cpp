#include "GLScene.h"
#include <iostream>

/**
	NOTE: Ripped off tutorials a lot here, so there's 
	some copypasta cleanup to do.
*/



GLScene::GLScene(void)
{

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
   
    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 1.0f );
	
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

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
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

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

void GLScene::drawMesh(Mesh mesh)
{    
	static GLfloat rotate = 0.0f;
	GLubyte color[] = {128, 0, 32, 100}; /* rgba? a no effect*/
    glMatrixMode( GL_MODELVIEW );
	/* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity( );

	/* jottei olla naamassa kiinni*/
	glTranslatef( 0.0f, 0.0f, -10.0f );

	//if(rotate==360.0f) rotate=0.0f;

    glRotatef( rotate, 0.2f, 1.0f, 0.1f );

	GLubyte tmp=0;

	std::vector<Mesh::vertex *> vertices = mesh.getMeshVertices();
	
	GLenum type;

	switch(mesh.getType()){
		case Mesh::POINTS:
			type = GL_POINTS;
			break;
		case Mesh::TRIANGLES:
			break;
			type = GL_TRIANGLES;
		case Mesh::QUADS:
			type = GL_QUADS;
			break;
	}

	//glPointSize(4.0f);
	glBegin( type );
		std::vector<Mesh::vertex *>::iterator itr;
		for ( itr = vertices.begin(); itr < vertices.end(); ++itr )
		{	
			Mesh::vertex *v = *itr;
			glColor4ubv( color );
			//glVertex3fv( v->xyz );
			glVertex3f( v->x, v->y, v->z );
			tmp =color[0];
			color[0] = color [1];
			color[1] = tmp;
		}
	glEnd();
	rotate += 10.0f;
}


