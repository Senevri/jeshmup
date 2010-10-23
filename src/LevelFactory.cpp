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
	MeshObject * mo;
	mo = loadObjectFromFile(*level, "..\\data\\model\\monkey.3ds");

    //loadObjectFromFile(*level, "data/model/monkey.3ds");
	mo->location(Point3d(0, 0, 0));
	mo->setName("apina");
	level->addObject(mo);
	mo = loadObjectFromFile(*level, "..\\data\\model\\monkey.3ds");
	level->addObject(mo);
    //loadObjectFromFile(*level, "data/model/japanese bridge.3ds");
    return level;
}

int LevelFactory::levels() const
{
    return 1;
}

MeshObject * LevelFactory::loadObjectFromFile(Level &level, const string& fileName)
{
    LOG("Trying to load model %s", fileName.c_str());
    dsLoader load;
    Mesh *mesh = load.load(fileName);
    if( !mesh )
    {
        LOG_ERROR("Cannot load file: %s", fileName.c_str());
		return 0;
    }
    else
    {
		return new MeshObject(mesh);		
    }
}
