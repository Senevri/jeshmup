#include "DrawEngine.h"

#include "Mesh.h"
#include "Point3d.h"
#include "Point2d.h"
#include "MathHelp.h"
#include "Logging.h"
#include "Resource.h"

#include "SDL_ttf.h"

#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glext.h"

#include <SDL_video.h>
#include <stdlib.h>

#ifndef GL_BGRA
#define GL_BGRA GL_BGRA_EXT
#endif

DrawEngine::DrawEngine()
{
}

DrawEngine::~DrawEngine()
{
    TTF_Quit();
}

bool DrawEngine::initialize()
{
    if(TTF_Init() == -1)
    {
        LOG("TTF_Init: %s", TTF_GetError());
        return false;
    }
	/*still ugly but doesn't break.*/
	std::string path = FONTPATH_;
	path +="ttf-bitstream-vera-1.10";
	path +=_SEPARATOR_;
	path +="Vera.ttf";
	m_uiFont=TTF_OpenFont(path.c_str(), 16);
    if( !m_uiFont )
    {
        LOG("TTF_OpenFont: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

void DrawEngine::translateTo(const Point3d& point)
{
    glLoadIdentity();
    glTranslatef(point.x, point.y, point.z);
}
void DrawEngine::renderMeshAt(const Mesh &mesh, Point3d &location, float angle, Point3d &vector){
	this->m_location = &location;
	this->m_rotation = &vector;
	this->m_angle = angle;
	renderMesh(mesh);
	this->m_location = 0;
	this->m_rotation = 0;
}

void DrawEngine::renderMesh(const Mesh &mesh)
{
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
    GLfloat reddish[] = {0.3f, 0.3f, 0.9f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, reddish);
    GLfloat diffmat[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffmat);

    glPushMatrix();
    /* move object in coords*/
    glTranslatef(this->m_location->x, -this->m_location->y, this->m_location->z);
    /*rotate object */
    if (0 != this->m_angle ) {
	    glRotatef(this->m_angle,
		    this->m_rotation->x,
		    this->m_rotation->y,
		    this->m_rotation->z);
    }
    /* problem! the whole coord system is now rotated! */
    /* I think that comment predated push/pop matrix commands.*/

    glBegin( GL_TRIANGLES );
    if(faces.empty()){
	    std::vector<Mesh::Vertex*>::iterator itr;
	    for ( itr = vertices.begin(); itr < vertices.end(); ++itr )
	    {
		    Mesh::Vertex* face = *itr;
		    //Vector normal = face->faceNormal(vertices);
		    //normal.normalize();
		    //glNormal3f(normal.x(), normal.y(), normal.z());

		    Mesh::Vertex *v = face;
		    glVertex3f(v->x, v->y, v->z);

	    }
    } else {
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
    }
    glEnd();
    glPopMatrix();
}

void DrawEngine::renderLine(const Point3d &start, const Point3d &end)
{

}

/// @todo Should the position work via the translateTo function?
void DrawEngine::renderText(const std::string &text, const Point2d &position)
{
    // Render some text in solid black to a new surface
    // then blit to the upper left of the screen
    // then free the text surface
    SDL_Color color={212,255,255};
    SDL_Surface *text_surface;
    GLint x = static_cast<GLint>(position.x);
    GLint y = static_cast<GLint>(position.y);
    if( !(text_surface=TTF_RenderText_Blended(m_uiFont, text.c_str(), color)) )
    {
        LOG_ERROR("Text printing failed!");
    }
    else
    {
        glEnable2D();
        /* Convert the rendered text to a known format */
        int w = Math::nextpoweroftwo(text_surface->w);
        int h = Math::nextpoweroftwo(text_surface->h);

        SDL_Surface *intermediary = SDL_CreateRGBSurface(0, w, h, 32,
                0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

        SDL_BlitSurface(text_surface, 0, intermediary, 0);

        /* Tell GL about our new texture */
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA,
                GL_UNSIGNED_BYTE, intermediary->pixels );

        /* GL_NEAREST looks horrible, if scaled... */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        /* prepare to render our texture */
        glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor3f(1.0f, 1.0f, 1.0f);

        /* Draw a quad at location */
        glBegin(GL_QUADS);
            /* Recall that the origin is in the lower-left corner
               That is why the TexCoords specify different corners
               than the Vertex coors seem to. */
            glTexCoord2f(0.0f, 1.0f);
	    glVertex2i(x, y);

            glTexCoord2f(1.0f, 1.0f);
	    glVertex2i(x + w, y);

            glTexCoord2f(1.0f, 0.0f);
	    glVertex2i(x + w, y + h);

            glTexCoord2f(0.0f, 0.0f);
	    glVertex2i(x, y + h);
			//glVertex2i(position.x    , position.y + h);
        glEnd();

        /* Bad things happen if we delete the texture before it finishes */
        glFinish();

        /* Clean up */
        SDL_FreeSurface(text_surface);
        SDL_FreeSurface(intermediary);
        glDeleteTextures(1, &texture);
	glDisable2D();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
    }
}

/*
    so that esa understands textures, too...
*/
void DrawEngine::renderBackground(void){
    int height=600;
    GLint data[4][2] = {{0,0},
			  {800,0},
			  {800,height},
			  {0,height}};
    int i=0;
    glEnable2D();    

    //glOrtho(0, 1, 0, 1, -1, 1);

    GLuint picture[800*600];
    GLuint c=255;
    GLuint c2=0;
    memset(picture, 0 , 800*600*4);
    while(i<(480000)){

/*	c = (32) | // Alpha
		((128)<<8)| //Red
		(96+((rand() % 96)<<16))| //green
		((255)<<24); //blue
  */
        c = (32) | // Alpha
                ((0)<<8)| //Red
                (0)| //green
                ((255-(255*i/480000))<<24); //blue

	//c2= c-(0<<24 | 32<<16 | 32<<8 | 32);
        //int position = (800+(rand() % 799)* (rand() % 600));
        picture[i] = c;
        /*picture[position-801] = c2;
	picture[position-800] = c2;
	picture[position-799] = c2;
	picture[position-1600] = c2;
        */
        i++;
    }
    //glOrtho(0, data[2][0], 0, data[2][1], -1, 1);
    glDisable(GL_LIGHTING);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, 800, 600, 0, GL_BGRA,
		 GL_UNSIGNED_INT_8_8_8_8, picture );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering



    /* from bisqwit */
    //glActiveTextureARB(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_TEXTURE);
    glColor3f(1,1,1);
    /* for some reason this is super-slow*/
    /*
    glRasterPos2s(0,0);
    glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, picture);

    */
    /* no texture yet... */
    /* end temp material */
    /*for (i=0; i!=3; i++){
	glTexCoord2i(data[i][0], data[i][1]);
	glVertex2i(data[i][0], data[i][1]);
    }
    */

    glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2i(0, 0);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2i(800, 0);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2i(800, 600);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2i(0, 600);

    glEnd();
    glFinish();

    /* bisqwit... */
    glDeleteTextures(1, &texture);
    //glActiveTextureARB(GL_TEXTURE0_ARB);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glDisable2D();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);






}

void DrawEngine::glEnable2D() const
{
    int vPort[4];
    glGetIntegerv(GL_VIEWPORT, vPort);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, vPort[2], 0, vPort[3], -1, 0);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    //glPushMatrix();
    glLoadIdentity();
}

void DrawEngine::glDisable2D() const
{
    //glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
