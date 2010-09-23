#include "LevelFactory.h"

#include "Level.h"
#include "MeshObject.h"
#include "Logging.h"
#include "3dsLoader.h"

using namespace std;

LevelFactory::LevelFactory()
{
}

LevelFactory::~LevelFactory()
{
}

Level* LevelFactory::level(int index)
{
    Level *level = new Level();
    //this needs some logic or some way to read level description from file etc etc
    //this just a hack to get things rolling...
    loadObjectFromFile(*level, "data/model/monkey.3ds");
    //loadObjectFromFile(*level, "data/model/japanese bridge.3ds");
    return level;
}

int LevelFactory::levels() const
{
    return 1;
}

void LevelFactory::loadObjectFromFile(Level &level, const string& fileName)
{
    LOG("Trying to load model %s", fileName.c_str());
    dsLoader load;
    Mesh *mesh = load.load(fileName);
    if( !mesh )
    {
        LOG_ERROR("Cannot load file: %s", fileName.c_str());
    }
    else
    {
       level.addObject(new MeshObject(mesh));
    }
}
