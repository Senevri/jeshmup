#include "LevelFactory.h"

#include "Level.h"
#include "MeshObject.h"
#include "Logging.h"
#include "3dsLoader.h"
#include "RawLoader.h"

using namespace std;

LevelFactory::LevelFactory()
{
}

LevelFactory::~LevelFactory()
{
	/* are we leaking?*/
}

Level* LevelFactory::level(int index)
{
    Level *level = new Level();
    //this needs some logic or some way to read level description from file etc etc
    //this just a hack to get things rolling...
	MeshObject * mo;
	mo = loadObjectFromFile(*level, "..\\data\\model\\monkey.3ds");
	//mo->setVisibility(false);
    //loadObjectFromFile(*level, "data/model/monkey.3ds");
	mo->location(Point3d(0, 0, 0));
	mo->setName("apina");
	level->addObject(mo);
	mo = loadObjectFromFile(*level, "..\\data\\model\\monkey.3ds");
	mo->location(Point3d(0, 1, 0));
	mo->setName("apina2");
	level->addObject(mo);
	
	RawLoader *r = new RawLoader();
	mo = new MeshObject(r->load("..\\data\\model\\arby_whole.raw"));
	mo->location(Point3d(0, 2, 0));
	mo->setName("arbyfish");
	level->addObject(mo);
	delete(r);

	r = new RawLoader();
	mo = new MeshObject(r->load("..\\data\\model\\blendertest.raw"));
	mo->location(Point3d(0, -1.5, 0));
	mo->setName("blendertest");
	level->addObject(mo);	
	delete(r);
	
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
