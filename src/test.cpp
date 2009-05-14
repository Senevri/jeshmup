#ifdef _TEST
/**
 * Use this class for running tests from a shell.
 */

#include <iostream>
#include "SDL.h"
#include "UnitTest++.h"
#include "world.h"
#include "Mesh.h"

using namespace std;

SUITE(ZaWarudoTests) {
	TEST(InitTest){
		cout << "ZA WARUDO TESTS\n";
		Object *o = new Object();
		o->name = "test object";
		o->coord.x = 10;
		o->coord.y = 20;
		o->coord.z = 30;
		CHECK(0==o->name.compare("test object"));
		delete o;
	}
	TEST(ConstructMesh){
		Mesh *m = new Mesh();
		delete m;
	}
	TEST(FillMesh) {
		float obj[] = {
		1.000000f, 1.000000f, -1.000000f, 1.000000f, -1.000000f, -1.000000f, -1.000000f, -1.000000f, -1.000000f, -1.000000f, 1.000000f, -1.000000f, 
1.000000f, 0.999999f, 1.000000f, -1.000000f, 1.000000f, 1.000000f, -1.000000f, -1.000000f, 1.000000f, 0.999999f, -1.000001f, 1.000000f, 
1.000000f, 1.000000f, -1.000000f, 1.000000f, 0.999999f, 1.000000f, 0.999999f, -1.000001f, 1.000000f, 1.000000f, -1.000000f, -1.000000f, 
1.000000f, -1.000000f, -1.000000f, 0.999999f, -1.000001f, 1.000000f, -1.000000f, -1.000000f, 1.000000f, -1.000000f, -1.000000f, -1.000000f, 
-1.000000f, -1.000000f, -1.000000f, -1.000000f, -1.000000f, 1.000000f, -1.000000f, 1.000000f, 1.000000f, -1.000000f, 1.000000f, -1.000000f, 
1.000000f, 0.999999f, 1.000000f, 1.000000f, 1.000000f, -1.000000f, -1.000000f, 1.000000f, -1.000000f, -1.000000f, 1.000000f, 1.000000
		};
		Mesh *m = new Mesh();
		std::vector<float *> mesh;

		/*6 faces, 4 vertices*/
		m->meshFromFloatArray(obj, Mesh::QUADS, (6*4));
		CHECK(Mesh::QUADS == m->getType());
		//mesh = m->getMesh();
		std::vector<Mesh::vertex *> verts = m->getMeshVertices();
		CHECK(verts[0]->x == (float)1);

		delete m;
	}

}
;

int main(int argc, char * argv[]){
	int result = 0;
	result = UnitTest::RunAllTests();
	cout<<"Enter Key Exits" << endl;
	cin.get();
	return result;
}
#endif //_TEST

