#ifndef DRAWENGINE_H
#define DRAWENGINE_H

#include <string>
#include <SDL_ttf.h>
#include "Point3d.h"

class Mesh;
//class Point3d;
class Point2d;

class DrawEngine
{
public:
    DrawEngine();
    virtual ~DrawEngine();
    bool initialize();

    void translateTo(const Point3d &point);
	void renderMeshAt(const Mesh &mesh, Point3d &location);
    void renderMesh(const Mesh &mesh);
    void renderLine(const Point3d &start, const Point3d &end);
    void renderText(const std::string &text, const Point2d &position);

private:
	Point3d * m_location; /* where to shift */
    void glEnable2D() const;
    void glDisable2D() const;

private:
    TTF_Font *m_uiFont;
};

#endif // DRAWENGINE_H
