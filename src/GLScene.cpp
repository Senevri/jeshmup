#include "GLScene.h"

#include "Vector.h"
#include "util/Logging.h"

#include <iostream>

/**
	NOTE: Ripped off tutorials a lot here, so there's 
	some copypasta cleanup to do.
*/



GLScene::GLScene(void)
{
    this->Camera.location.x = 0.0f;
    this->Camera.location.y = 0.0f;
    this->Camera.location.z = -2.0f;
    this->Camera.angle.x = 0.0f;
    this->Camera.angle.y = 0.0f;
    this->Camera.angle.z = 0.0f;

    Point3d point(0.0f, 50.0f, 5.0f);
    m_mainLight.setPosition(point);
    m_mainLight.setAmbient(Color::GRAY);
    m_mainLight.setDiffuse(Color::RED);

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
    glShadeModel( GL_FLAT ); /* GL_FLAT, GL_SMOOTH shade model */

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 100.0f );
	
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /*Lights enabled in the scene */
    glEnable( GL_LIGHTING );
    /* Which polygons face forwards, affects lightning and */
    glFrontFace( GL_CCW );

    //no insides
    glEnable(GL_CULL_FACE);

    /* something to do with easying the color declaration i.e. Color tracking*/
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

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

    //how to handle moving lights? etc...
    drawLights();

    glTranslatef( this->Camera.location.x, this->Camera.location.y, this->Camera.location.z );
    LOG("Camera at: %f %f %f", Camera.location.x, Camera.location.y, Camera.location.z);
	/*camera moves HERE.*/

	std::vector<Mesh *>::iterator itr;
	for ( itr = this->meshes.begin(); itr < this->meshes.end(); ++itr )
	{	
		this->drawMesh(**itr);
	}
    glFlush();

//	translate += tradd;
}

void GLScene::drawLights()
{
    GLfloat tmp[4];
    m_mainLight.ambient().fillArray(tmp);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, tmp);

    m_mainLight.diffuse().fillArray(tmp);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, tmp);

    glEnable(GL_LIGHT0);

    m_mainLight.fillWithPosition(tmp);
    glLightfv(GL_LIGHT0, GL_POSITION, tmp);

    //automatically rescales normals
    //should the removed, and implemented faster by ourselves
    //glEnable( GL_NORMALIZE );
}

void GLScene::translateMesh(int mesh_id, float x, float y, float z)
{

}

void GLScene::rotateMesh(int mesh_id, float x, float y, float z)
{

}


void GLScene::drawMesh(Mesh &mesh)
{    
	
	static GLfloat rotate = 0.0f;
	GLubyte white[] = {224, 224, 224, 128}; /* rgba? a no effect*/
	GLubyte green[] = {0, 196, 0, 128}; 
    //glMatrixMode( GL_MODELVIEW );
	//glLoadIdentity( );
	GLubyte * color = white;

    glBegin( GL_POINTS );
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(m_mainLight.position().x,
                   m_mainLight.position().y,
                   m_mainLight.position().z);
    glEnd();

	/* jottei olla naamassa kiinni*/
	//glTranslatef( 0.0f, 0.0f, -2.0f );

	if(rotate==360.0f) rotate=0.0f;

    glRotatef( rotate, 1.0f, 1.0f, 1.0f );

	GLubyte tmp=0;

    std::vector<Mesh::Vertex *> vertices = mesh.vertices();
    std::vector<Mesh::Face*> faces = mesh.faces();
	
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

    //how we incorporate material to mesh....
    GLfloat reddish[] = {0.3f, 0.3f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, reddish);

    glColor3f(0.0f,1.0f,0.0f);
    glBegin( GL_TRIANGLES );
        std::vector<Mesh::Face*>::iterator itr;
        for ( itr = faces.begin(); itr < faces.end(); ++itr )
        {
            Mesh::Face* face = *itr;
            Vector normal = face->faceNormal(vertices);
            normal.normalize();
            glNormal3f(normal.x(), normal.y(), normal.z());
            for(int i = 0; i < face->format; i++)
            {
                Mesh::Vertex *v = vertices[face->indices[i]];
                glVertex3f(v->x, v->y, v->z);
            }
		}
	glEnd();
	//rotate += 0.2f;
}


