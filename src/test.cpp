#ifdef _TEST
/**
 * Use this class for running tests from a shell.
 */

#include <iostream>
#include "SDL.h"
#include "UnitTest++.h"
#include "world.h"
#include "Mesh.h"
#include "util/RawLoader.h"

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
		m->meshFromFloatArray(obj, Mesh::QUADS, (6*4*3));
		CHECK(Mesh::QUADS == m->getType());
		//mesh = m->getMesh();
		std::vector<Mesh::vertex *> verts = m->getMeshVertices();
		CHECK(verts[0]->x == (float)1);

		delete m;
	}
	TEST(RawLoaderFunctions){

		float obj[] = {
			1.0f,  1.0f,  1.0f,  2.0f,  2.0f,  2.0f,  3.0f,  3.0f,  3.0f,  4.0f,  4.0f,  4.0f
		};
		Mesh::vertex * triangle = new Mesh::vertex[6];
		Mesh::vertex * quad = new Mesh::vertex[4];

		RawLoader *r = new RawLoader();
		Mesh *m = new Mesh();
		std::vector<float *> mesh;

		/*6 faces, 4 vertices*/
		m->meshFromFloatArray(obj, Mesh::QUADS, (6*4*3));
		quad = m->vertexArrayFromMesh();
		triangle = r->quadToTriangle(quad);

 		CHECK(triangle[0].x == 1.0f);
		CHECK(triangle[1].x == 2.0f);
		CHECK(triangle[2].x == 3.0f);
		CHECK(triangle[3].x == 3.0f);
		CHECK(triangle[4].x == 4.0f);
		CHECK(triangle[5].x == 1.0f);
		
		delete m;
		
		delete [6] triangle;
		delete [4] quad;

		/* test loading */
		std::vector<Mesh::vertex *> vertices;
		if (r->load("..\\data\\model\\blendertest.raw")) {
			vertices = r->getVertices();
			//cout << vertices[0]->x << endl;
		} else {
			CHECK(false && "could not open test file");
		}

		delete r;
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

