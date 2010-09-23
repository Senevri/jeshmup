#include "GLScene.h"

#include "object.h"
#include "DrawEngine.h"
#include "Vector.h"
#include "Level.h"
#include "Logging.h"

#include <iostream>

/**
	NOTE: Ripped off tutorials a lot here, so there's 
	some copypasta cleanup to do.
*/



GLScene::GLScene(DrawEngine *drawEngine) :
        m_level(0),
        m_drawEngine(drawEngine)
{
    this->Camera.location.x = 0.0f;
    this->Camera.location.y = 0.0f;
    this->Camera.location.z = -150.0f;
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
    LOG("Deleteting GLScene");
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
    /* Which polygons face forwards, affects lighting and */
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

void GLScene::setLevel(Level* level)
{
    m_level = level;
}

void GLScene::updateScene(int ticks)
{
    const std::vector<Object*>& objects = m_level->objects();
    std::vector<Object*>::const_iterator itr = objects.begin();
    std::vector<Object*>::const_iterator itrEnd = objects.end();

    itr = objects.begin();
    for(; itr != itrEnd; ++itr)
    {
        (*itr)->update(ticks);
    }
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

    std::vector<Object*> objects = m_level->objects();
    std::vector<Object*>::const_iterator itr = objects.begin();
    std::vector<Object*>::const_iterator itrEnd = objects.end();

    for(; itr != itrEnd; ++itr)
    {
        (*itr)->draw(*m_drawEngine);
    }
    glFlush();
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


