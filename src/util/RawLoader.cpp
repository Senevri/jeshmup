#include "RawLoader.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

RawLoader::RawLoader()
{

}
RawLoader::~RawLoader()
{
if(!this->m_vpVertices.empty()){
		this->m_vpVertices.clear();
		//this->m_vpVertices.assign; // leak some memory; hopefully someone keeps us in mind...
	}
}

/* loads vertices from a raw file to a private vector */
bool RawLoader::load(string filename){
	

    m_InputFile.open(filename.c_str(), ios::binary);
	/* estimated line max length: 4*(7+10)+2 for a quad. */
	if(!m_InputFile.is_open()){
        return false;
    }
	float coords[12]; /* enough space for a quad */
	Mesh::vertex * triangle = 0;
				
	int ncoords = 0;
	string strcoord=""; /* to parse input with */
	char input = 0;
	int n_tris = 0; /* hau meni tris */
	while(m_InputFile.get(input)) {
		switch(input) {
			case ' ': /* changing coordinate */
			/* store coordinate to vertex */
				coords[ncoords] = strToFloat(strcoord);
				strcoord = "";
				ncoords++;
				break;
			case '\n':
				if(!strcoord.empty()) {
					coords[ncoords] = strToFloat(strcoord);
					strcoord = "";
					ncoords++;
				}
				if(ncoords == 12){ /* we have a quad, convert to tris */
					/* first, make a quad */
					n_tris = 2;
					Mesh::vertex *quad = new Mesh::vertex[4];
					for (int i=0;i<4;i++){
						quad[i].x = coords[i*3];
						quad[i].y = coords[i*3+1];
						quad[i].z = coords[i*3+2];
					}
					triangle = quadToTriangle(quad);
					delete [] quad;

				} else if (ncoords == 9){
					n_tris =1;
					triangle = new Mesh::vertex[3];
					for (int i = 0; i<3;i++){
						triangle[i].x = coords[i*3];
						triangle[i].y = coords[i*3+1];
						triangle[i].z = coords[i*3+2];
					}
				}
				for (int i = 0; i<(n_tris*3);i++){
					m_vpVertices.push_back(&triangle[i]);
				}
				ncoords = 0;
				break;
			default:
				strcoord += input;
		}
	}
	m_InputFile.close();
	return true;
}

/* getter */
std::vector<Mesh::vertex *> RawLoader::getVertices(){
	return this->m_vpVertices;
}

/* convert std::string to float */
float RawLoader::strToFloat(string str){
	float f=0;
	std::istringstream i(str);
	if (!(i >> f )){
		throw "could not convert string to float";
	}
	return f;
}


/* Description: Turn a quad (4 vertices) to two triangles
 * (six vertices)
 */
Mesh::vertex * RawLoader::quadToTriangle(Mesh::vertex *quad)
{
	Mesh::vertex * triangle = new Mesh::vertex[6];
	/* make quad to triangles. */
	/*
		QUAD = 
		a--b 
		|  |	
		|  | 
		d--c
		, never acbd. Thus, triangle = abc, cda or abd, bdc
		In theory.
		what about if it's abdc?  
		we get abd. dca, which is NO GOOD! How do we determine 
		this difference? We need to assert edges ab, bc, cd, da
		exist.
		ab(cd), (cd) (dc) and closest. Yes.
		what about:
		     d
            / \ 
           / b \
		  / / \ \
          c     a
		
		no wait, that's stupid. ABC must always form a fillable 
		triangle or else we're in trouble. 
		So quads _probably_ form abcds not abdcs. Or else they're
		always abdc, which we'll find out shortly.
	*/

	for(int i=0; i<3;i++){
		triangle[i] = quad[i];
	}
	for(int i=0; i<2;i++){
		triangle[i+3] = quad[i+2];
	}
	triangle[5] = quad[0];
	return triangle;

}

