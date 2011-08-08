#include "LevelFactory.h"

#include "Level.h"
#include "MeshObject.h"
#include "Logging.h"
#include "3dsLoader.h"
#include "RawLoader.h"
#include "JMFImport.h"
#include "Resource.h"

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
	std::string path = MODELPATH_;
    Level *level = new Level();
    //this needs some logic or some way to read level description from file etc etc
    //this just a hack to get things rolling...
	MeshObject * mo;
	//mo = loadObjectFromFile(*level, "..\\data\\model\\monkey.3ds");
    	mo = loadObjectFromFile(*level, path + "monkey.3ds");
	//mo->setVisibility(false);

	mo->location(Point3d(2, 0, -2));
	mo->setName("apina");
	level->addObject(mo);

	JMFImport jmfImport(path+"player_ship.jmf");
	if( !jmfImport.import() )
	{
		LOG_ERROR("Level creation failed!");
	}
	mo = new MeshObject(jmfImport.mesh());
	mo->location(Point3d(0,4,-5));
	mo->rotation(90, Point3d(0, 1, 0));
	mo->setName("shippi");
	level->addObject(mo);

	mo = loadObjectFromFile(*level, path+"monkey.3ds");
	mo->location(Point3d(3, 2, 0));
	mo->setName("apina2");
	level->addObject(mo);
	
	RawLoader *r = new RawLoader();
	mo = new MeshObject(r->load(path+"Arby_whole.raw"));
	mo->location(Point3d(0, 3, 0));
	mo->setName("arbyfish");
	level->addObject(mo);
	delete(r);

	r = new RawLoader();
	mo = new MeshObject(r->load(path+"blendertest.raw"));
	mo->location(Point3d(0, -3, 0));
	mo->setName("blendertest");
	level->addObject(mo);	
	delete(r);
	
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
