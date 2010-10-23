#ifndef LEVELFACTORY_H
#define LEVELFACTORY_H

#include <string>
#include <vector>

class MeshObject;
class Level;

class LevelFactory
{
public:
    LevelFactory();
    virtual ~LevelFactory();

    Level *level(int index);
    int levels() const;

private:
    MeshObject * loadObjectFromFile(Level& level, const std::string& fileName);

private: //data
    std::vector<Level*> m_loadedLevels;
};

#endif // LEVELFACTORY_H
