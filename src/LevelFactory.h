#ifndef LEVELFACTORY_H
#define LEVELFACTORY_H

#include <string>
#include <vector>

class Level;

class LevelFactory
{
public:
    LevelFactory();
    virtual ~LevelFactory();

    Level *level(int index);
    int levels() const;

private:
    void loadObjectFromFile(Level& level, const std::string& fileName);

private: //data
    std::vector<Level*> m_loadedLevels;
};

#endif // LEVELFACTORY_H
