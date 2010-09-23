#include "DrawEngine.h"

#include "Mesh.h"
#include "Point3d.h"

#include "GL/gl.h"
#include "GL/glu.h"

DrawEngine::DrawEngine()
{
}

DrawEngine::~DrawEngine()
{
}

void DrawEngine::translateTo(const Point3d& point)
{
    glLoadIdentity();
    glTranslatef(point.x, point.y, point.z);
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
    GLfloat reddish[] = {0.3f, 0.3f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, reddish);

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
}

void DrawEngine::renderLine(const Point3d &start, const Point3d &end)
{

}
