#include "GLScene.h"

#include "object.h"
#include "DrawEngine.h"
#include "Vector.h"
#include "Level.h"
#include "Logging.h"

#include "UI.h"
#include "Point2d.h"

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
    this->Camera.location.y = -4.5f;
    this->Camera.location.z = 6.0f;
    this->Camera.angle.x = 0.0f;
    this->Camera.angle.y = 0.0f;
    this->Camera.angle.z = 0.0f;
    this->Camera.target.x = 0.0f;
    this->Camera.target.y = 0.0f;
    this->Camera.target.z = 0.0f;


    Point3d point(0.0f, -5.0f, -5.0f);
    m_mainLight.setPosition(point);
    //m_mainLight.setAmbient(Color::DARKGRAY);
    m_mainLight.setDiffuse(Color::RED);

}

GLScene::~GLScene(void)
{
    LOG("Deleting GLScene");
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

    glBlendFunc(GL_ONE, GL_ONE);
    glEnable(GL_BLEND);
}

/**
	Todo: Parameters
	much copypasta
*/
void GLScene::setup(int width, int height)
{
    /* Irrelevant stuff for this demo */
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    /* Required if you want alpha-blended textures (for our fonts) */
    glBlendFunc(GL_ONE, GL_ONE);
	/* then only do this for fonts by default!*/
    glDisable(GL_BLEND);


    /* Required setup stuff */
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0f, static_cast<float>(width) / static_cast<float>(height), 0.01f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLScene::setLevel(Level* level)
{
    m_level = level;
}

Level * GLScene::getLevel()
{
    return m_level;
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


    //glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	this->m_drawEngine->renderBackground();
	//how to handle moving lights? etc...
	drawLights();

	//glTranslatef( -this->Camera.location.x, this->Camera.location.y, this->Camera.location.z );
	gluLookAt( this->Camera.location.x, 
		this->Camera.location.y, 
		this->Camera.location.z,
		this->Camera.target.x, this->Camera.target.y, this->Camera.target.z,//look at target - now we can move camera
		0, 1, 0
		);
	//doesn't quite do what I want....
	//EDIT: Started working, actually. Huh.
    //LOG("Camera at: %f %f %f", Camera.location.x, Camera.location.y, Camera.location.z);


    std::vector<Object*> objects = m_level->objects();
    std::vector<Object*>::const_iterator itr = objects.begin();
    std::vector<Object*>::const_iterator itrEnd = objects.end();
    //glPushMatrix();
    //this->m_drawEngine->renderBackground();
    //glPopMatrix();
    for(; itr != itrEnd; ++itr)
    {
        (*itr)->draw(*m_drawEngine);
    }

    UI::instance()->update(*m_drawEngine);
	
    SDL_GL_SwapBuffers();

}

void GLScene::drawLights()
{
    GLfloat tmp[4];
    m_mainLight.ambient().fillArray(tmp);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, tmp);

    m_mainLight.diffuse().fillArray(tmp);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, tmp);

    glEnable(GL_LIGHT0);

    m_mainLight.fillWithPosition(tmp);
    glLightfv(GL_LIGHT0, GL_POSITION, tmp);

    //automatically rescales normals
    //should the removed, and implemented faster by ourselves
    //glEnable( GL_NORMALIZE );

    /* Load lights from Level
	Hox: only handles one light, right now.
    */
    const std::vector<Light*>& lights = m_level->lights();
    std::vector<Light*>::const_iterator itr = lights.begin();
    std::vector<Light*>::const_iterator itrEnd = lights.end();
    Light * lt;
    bool enable = false;
    itr = lights.begin();
    for(; itr != itrEnd; ++itr)
    {
	lt = *itr;
	if(lt->isAmbient()){
	    lt->ambient().fillArray(tmp);
	    glLightfv(GL_LIGHT1, GL_AMBIENT, tmp);
	    enable = true;
	}
	if(lt->isDiffuse()){
	    lt->diffuse().fillArray(tmp);
	    glLightfv(GL_LIGHT1, GL_DIFFUSE, tmp);
	    enable = true;
	}
	if(lt->isSpecular()){
	    lt->specular().fillArray(tmp);
	    glLightfv(GL_LIGHT1, GL_SPECULAR, tmp);
	    enable = true;
	}
	if (enable) {
	    glEnable(GL_LIGHT1);
	    lt->fillWithPosition(tmp);
	    glLightfv(GL_LIGHT1, GL_POSITION, tmp);
	}
	//(*itr)->update(ticks);
    }
}


