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

void GLScene::intArrayToVertices(int * arr, int size)
{
	for (int i=0; i<size; i=i+3) {
		/*GLint v[] = {
			arr[i], arr[i+1], arr[i+2]
		};*/
		struct_vertex * s_v = new struct_vertex;
		s_v->xyz[0] = arr[i];
		s_v->xyz[1] = arr[i+1];
		s_v->xyz[2] = arr[i+2];

		this->vertices.push_back(s_v);
	}
}

/*
	gets data from local array
*/
void GLScene::drawQuads(void)
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

	//glPointSize(4.0f);
	glBegin( GL_QUADS );
		std::vector<struct_vertex *>::iterator itr;
		for ( itr = vertices.begin(); itr < vertices.end(); ++itr )
		{	
			struct_vertex *v = *itr;
			glColor4ubv( color );
			//glVertex3fv( v->xyz );
			glVertex3fv( v->xyz );
			tmp =color[0];
			color[0] = color [1];
			color[1] = tmp;
		}
	glEnd();
	rotate += 10.0f;
}

void GLScene::testDrawing(GLvoid)
{    
    /* rotational vars for the triangle and quad, respectively */
    static GLfloat rtri, rquad;
    /* These are to calculate our fps */
    static GLint T0     = 0;
    static GLint Frames = 0;


    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef( -1.5f, 0.0f, -6.0f );

    /* Rotate The Triangle On The Y axis ( NEW ) */
    glRotatef( rtri, 0.0f, 1.0f, 0.0f );

    glBegin( GL_TRIANGLES );             /* Drawing Using Triangles       */
      glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
      glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle (Front)       */
      glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
      glVertex3f( -1.0f, -1.0f,  1.0f ); /* Left Of Triangle (Front)      */
      glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
      glVertex3f(  1.0f, -1.0f,  1.0f ); /* Right Of Triangle (Front)     */

      glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
      glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle (Right)       */
      glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
      glVertex3f(  1.0f, -1.0f,  1.0f ); /* Left Of Triangle (Right)      */
      glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
      glVertex3f(  1.0f, -1.0f, -1.0f ); /* Right Of Triangle (Right)     */

      glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
      glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle (Back)        */
      glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
      glVertex3f(  1.0f, -1.0f, -1.0f ); /* Left Of Triangle (Back)       */
      glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
      glVertex3f( -1.0f, -1.0f, -1.0f ); /* Right Of Triangle (Back)      */

      glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
      glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle (Left)        */
      glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
      glVertex3f( -1.0f, -1.0f, -1.0f ); /* Left Of Triangle (Left)       */
      glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
      glVertex3f( -1.0f, -1.0f,  1.0f ); /* Right Of Triangle (Left)      */
    glEnd( );                            /* Finished Drawing The Triangle */

    /* Move Right 3 Units */
    glLoadIdentity( );
    glTranslatef( 1.5f, 0.0f, -6.0f );

    /* Rotate The Quad On The X axis ( NEW ) */
    glRotatef( rquad, 1.0f, 0.0f, 0.0f );

    /* Set The Color To Blue One Time Only */
    glColor3f( 0.5f, 0.5f, 1.0f);

    glBegin( GL_QUADS );                 /* Draw A Quad                      */
      glColor3f(   0.0f,  1.0f,  0.0f ); /* Set The Color To Green           */
      glVertex3f(  1.0f,  1.0f, -1.0f ); /* Top Right Of The Quad (Top)      */
      glVertex3f( -1.0f,  1.0f, -1.0f ); /* Top Left Of The Quad (Top)       */
      glVertex3f( -1.0f,  1.0f,  1.0f ); /* Bottom Left Of The Quad (Top)    */
      glVertex3f(  1.0f,  1.0f,  1.0f ); /* Bottom Right Of The Quad (Top)   */

      glColor3f(   1.0f,  0.5f,  0.0f ); /* Set The Color To Orange          */
      glVertex3f(  1.0f, -1.0f,  1.0f ); /* Top Right Of The Quad (Botm)     */
      glVertex3f( -1.0f, -1.0f,  1.0f ); /* Top Left Of The Quad (Botm)      */
      glVertex3f( -1.0f, -1.0f, -1.0f ); /* Bottom Left Of The Quad (Botm)   */
      glVertex3f(  1.0f, -1.0f, -1.0f ); /* Bottom Right Of The Quad (Botm)  */

      glColor3f(   1.0f,  0.0f,  0.0f ); /* Set The Color To Red             */
      glVertex3f(  1.0f,  1.0f,  1.0f ); /* Top Right Of The Quad (Front)    */
      glVertex3f( -1.0f,  1.0f,  1.0f ); /* Top Left Of The Quad (Front)     */
      glVertex3f( -1.0f, -1.0f,  1.0f ); /* Bottom Left Of The Quad (Front)  */
      glVertex3f(  1.0f, -1.0f,  1.0f ); /* Bottom Right Of The Quad (Front) */

      glColor3f(   1.0f,  1.0f,  0.0f ); /* Set The Color To Yellow          */
      glVertex3f(  1.0f, -1.0f, -1.0f ); /* Bottom Left Of The Quad (Back)   */
      glVertex3f( -1.0f, -1.0f, -1.0f ); /* Bottom Right Of The Quad (Back)  */
      glVertex3f( -1.0f,  1.0f, -1.0f ); /* Top Right Of The Quad (Back)     */
      glVertex3f(  1.0f,  1.0f, -1.0f ); /* Top Left Of The Quad (Back)      */

      glColor3f(   0.0f,  0.0f,  1.0f ); /* Set The Color To Blue            */
      glVertex3f( -1.0f,  1.0f,  1.0f ); /* Top Right Of The Quad (Left)     */
      glVertex3f( -1.0f,  1.0f, -1.0f ); /* Top Left Of The Quad (Left)      */
      glVertex3f( -1.0f, -1.0f, -1.0f ); /* Bottom Left Of The Quad (Left)   */
      glVertex3f( -1.0f, -1.0f,  1.0f ); /* Bottom Right Of The Quad (Left)  */

      glColor3f(   1.0f,  0.0f,  1.0f ); /* Set The Color To Violet          */
      glVertex3f(  1.0f,  1.0f, -1.0f ); /* Top Right Of The Quad (Right)    */
      glVertex3f(  1.0f,  1.0f,  1.0f ); /* Top Left Of The Quad (Right)     */
      glVertex3f(  1.0f, -1.0f,  1.0f ); /* Bottom Left Of The Quad (Right)  */
      glVertex3f(  1.0f, -1.0f, -1.0f ); /* Bottom Right Of The Quad (Right) */
    glEnd( );                            /* Done Drawing The Quad            */

	/* Draw it to the screen */
    SDL_GL_SwapBuffers( );

    /* Gather our frames per second */
    Frames++;
    {
	GLint t = SDL_GetTicks();
	if (t - T0 >= 5000) {
	    GLfloat seconds = (t - T0) / 1000.0;
	    GLfloat fps = Frames / seconds;
	    printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
	    T0 = t;
	    Frames = 0;
	}
    }

    /* Increase The Rotation Variable For The Triangle ( NEW ) */
    rtri  += 0.2f;
    /* Decrease The Rotation Variable For The Quad     ( NEW ) */
    rquad -=0.15f;
    //return( TRUE );
}

