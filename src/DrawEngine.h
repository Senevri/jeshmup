#ifndef DRAWENGINE_H
#define DRAWENGINE_H

class Mesh;
class Point3d;

class DrawEngine
{
public:
    DrawEngine();
    virtual ~DrawEngine();

    void translateTo(const Point3d &point);
    void renderMesh(const Mesh &mesh);
    void renderLine(const Point3d &start, const Point3d &end);
};

#endif // DRAWENGINE_H
