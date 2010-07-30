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
		/*Object *o = new Object();
		o->name = "test object";
		o->coord.x = 10;
		o->coord.y = 20;
		o->coord.z = 30;
		CHECK(0==o->name.compare("test object"));
		delete o; */
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
		m->meshFromFloatArray(obj, (6*4*3));
		m->setType(Mesh::QUADS);
		CHECK(Mesh::QUADS == m->getType());
		//mesh = m->getMesh();
		std::vector<Mesh::Vertex *> verts = m->vertices();
		CHECK(verts[0]->x == (float)1);

		delete m;
	}
	TEST(RawLoaderFunctions){

		float obj[] = {
			1.0f,  1.0f,  1.0f,  2.0f,  2.0f,  2.0f,  3.0f,  3.0f,  3.0f,  4.0f,  4.0f,  4.0f
		};
		Mesh::Vertex * triangle = new Mesh::Vertex[6];
		Mesh::Vertex * quad = new Mesh::Vertex[4];

		RawLoader *r = new RawLoader();
		Mesh *m = new Mesh();
		std::vector<float *> mesh;

		/*6 faces, 4 vertices*/
		m->meshFromFloatArray(obj, 3*4); // 4 verts, 3 coords per vert
		quad = m->vertexArrayFromMesh();
		triangle = r->quadToTriangle(quad);

 		CHECK(triangle[0].x == 1.0f);
		cout<<triangle[0].x<<endl;
		CHECK(triangle[1].x == 2.0f);
		cout<<triangle[1].x<<endl;
		CHECK(triangle[2].x == 3.0f);
		cout<<triangle[2].x<<endl;
		CHECK(triangle[3].x == 3.0f);
		cout<<triangle[3].x<<endl;
		CHECK(triangle[4].x == 4.0f);
		cout<<triangle[4].x<<endl;
		CHECK(triangle[5].x == 1.0f);
		cout<<triangle[5].x<<endl;
		
		delete m;
		
		delete [] triangle;
		delete [] quad;

		/* test loading */
		std::vector<Mesh::Vertex *> vertices;
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

