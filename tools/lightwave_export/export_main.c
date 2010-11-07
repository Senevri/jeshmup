#include <lwserver.h>
#include <lwhost.h>
#include <lwrender.h>
#include <lwcmdseq.h>
#include <lwio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>


#define MAXFILESZ 260

#define ID_CHUNKMAIN  LWID_( 'J','M','F','M' )
#define ID_CHUNKVERT  LWID_( 'V','E','R','T' )
#define ID_CHUNKPOLY  LWID_( 'P','O','L','S' )

static LWBlockIdent idroot[] = {
	ID_CHUNKMAIN, "JMFMain",
	ID_CHUNKVERT, "Vertices",
	ID_CHUNKPOLY, "Polys",
	0
};

typedef struct st_ExportMeshData {
	LWMeshInfo *meshInfo;
	int pointCount;
	LWPntID *points;
	int indexCount;
	unsigned int *polygonIndices;
} ExportMeshData;

static size_t polScan(void* vd, LWPolID polID)
{
	ExportMeshData *md = (ExportMeshData*)vd;
	LWMeshInfo *mesh = md->meshInfo;
	int points = mesh->polSize(mesh, polID);
	if( points != 3)
	{
		return 1;
	}

	for( int i = 0; i < 3; ++i )
	{
		LWPntID temp = mesh->polVertex(mesh, polID, i);
		
		for( unsigned int j = 0; j < md->pointCount; ++j )
		{
			if( md->points[j] == temp )
			{
				md->polygonIndices[md->indexCount] = j;
				++md->indexCount;
				break;
			} 
			else if( j-1 == md->pointCount )
			{
				//error nothing found
				return 2;
			}
		}
	}
	
	return 0;
}

static size_t pointScan(void* vd, LWPntID pntID)
{
	ExportMeshData *md = (ExportMeshData*)vd;
	LWMeshInfo *mesh = md->meshInfo;
	md->points[md->pointCount] = pntID;
	++md->pointCount;
	return 0;
}

static int write_vertex_data(LWSaveState *sstate, LWMeshInfo *meshInfo)
{
	ExportMeshData md = {0};
	md.meshInfo = meshInfo;
	md.pointCount = 0;

	int meshPointCount = meshInfo->numPoints(meshInfo);
	md.points = (LWPntID*)calloc(meshPointCount, sizeof(LWPntID));
	int polyCount = meshInfo->numPolygons(meshInfo);
	md.polygonIndices = (unsigned int*)calloc(polyCount *3, sizeof(unsigned int));

	int success = meshInfo->scanPoints(meshInfo, pointScan, &md);
	if( success != 0 )
	{
		return success;
	}

	success  = meshInfo->scanPolys(meshInfo, polScan, &md);
	if( success != 0)
	{
		return success;
	}
	
	float *verts = (float*)calloc(3*meshPointCount, sizeof(float));

	for(int i = 0; i < meshPointCount *3; i += 3 )
	{
		LWFVector lwVector;
		meshInfo->pntBasePos(meshInfo, md.points[i/3], lwVector);
		verts[i] = lwVector[0];
		verts[i+1] = lwVector[1];
		verts[i+2] = lwVector[2];
	}
	
	LWSAVE_BEGIN(sstate, &idroot[1], 1);
	LWSAVE_FP(sstate, verts, meshPointCount * 3);
	LWSAVE_END(sstate);

	LWSAVE_BEGIN(sstate, &idroot[2], 1);
	LWSAVE_U4(sstate, md.polygonIndices, md.indexCount);
	LWSAVE_END(sstate);

	free(md.points);
	free(md.polygonIndices);
	free(verts);

	return 0;
}

static void begin_main_chunk(LWSaveState *sstate)
{
	LWSAVE_BEGIN(sstate, &idroot[0], 0);
}

static bool export_layers(GlobalFunc *global, std::string fullName, int objectIndex, std::vector<int> layers)
{
	LWFileIOFuncs *fiof = (LWFileIOFuncs*) global(LWFILEIOFUNCS_GLOBAL, GFUSE_TRANSIENT);
	LWSaveState *sstate = fiof->openSave(fullName.c_str(), LWIO_BINARY);
	
	LWObjectFuncs *objfunc = (LWObjectFuncs*)global(LWOBJECTFUNCS_GLOBAL, GFUSE_TRANSIENT);

	if( sstate )
	{
		begin_main_chunk(sstate);
		LWMeshInfo *mesh = objfunc->layerMesh(objectIndex, layers[0]);
		if( !mesh )
		{
			return false;
		}
		if( write_vertex_data(sstate, mesh) )
		{
			LWMessageFuncs *msgf = (LWMessageFuncs*)global(LWMESSAGEFUNCS_GLOBAL, GFUSE_TRANSIENT);
			msgf->error("Triangulate polygons!", NULL);
		}
		fiof->closeSave(sstate);
	}
	else
	{
		return false;
	}
}

bool endsWith(const std::string &fullString, const std::string &ending)
{
	if( fullString.length() > ending.length() )
	{
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	} 
	else
	{
		return false;
	}
}

XCALL_( int )
Activate( int version, GlobalFunc *global, void *local,
		 void *serverData )
{
	static char
		node[ MAXFILESZ ] = "",
		path[ MAXFILESZ ] = "",
		name[ MAXFILESZ ] = "";
	static LWFileReqLocal frloc;

	LWFileActivateFunc *filereq;
	int result;

	filereq = (LWFileActivateFunc*)global( LWFILEACTIVATEFUNC_GLOBAL, GFUSE_TRANSIENT );
	if ( !filereq ) return AFUNC_BADGLOBAL;  /* global calls can fail */

	frloc.reqType  = FREQ_SAVE; 
	frloc.title    = "Export object";
	frloc.bufLen   = MAXFILESZ;
	frloc.pickName = NULL;
	frloc.fileType = "Jeshmup Model File";
	frloc.path     = path;
	frloc.baseName = node;
	frloc.fullName = name;

	//export data in here
	LWStateQueryFuncs *query = (LWStateQueryFuncs*)global(LWSTATEQUERYFUNCS_GLOBAL, GFUSE_TRANSIENT);
	std::string current_object(query->object());

	strcpy( frloc.path, "exports" );     /* a relative path */
	strcpy( frloc.baseName, current_object.c_str() );      /* a default name  */

	result = filereq( LWFILEREQ_VERSION, &frloc );
	if ( result == AFUNC_OK && frloc.result > 0 )
	{

		//get all foreground layers
	    std::string layers_string = query->layerList(OPLYR_PRIMARY, NULL);
		std::vector<int> layer_numbers;
		std::stringstream ss(layers_string);

		std::string buf;
		while (ss >> buf)
		{
			layer_numbers.push_back(atoi(buf.c_str())-1);
		}

		//get the object meshinfo
		LWObjectFuncs *objfunc = (LWObjectFuncs*)global(LWOBJECTFUNCS_GLOBAL, GFUSE_TRANSIENT);
		int export_obj_index = -1;
		for( int i = 0; i < objfunc->numObjects(); ++i )
		{
			std::string some_obj(objfunc->filename(i));
			if( some_obj.compare(current_object) == 0 )
			{
				export_obj_index = i;
				break;
			}
		}

		if( export_obj_index >= 0 )
		{
			std::string file_name(frloc.fullName);
			if( !endsWith(file_name, ".jmf") )
			{
				file_name.append(".jmf");
			}
			export_layers(global, file_name, export_obj_index, layer_numbers);
		}
		else
		{
			LWMessageFuncs *msgf = (LWMessageFuncs*)global(LWMESSAGEFUNCS_GLOBAL, GFUSE_TRANSIENT);
			msgf->error("Cannot find object to export!", "Maybe there's no name?");
		}
	}


	return AFUNC_OK;
}

ServerRecord ServerDesc[] = {
	{ LWMODCOMMAND_CLASS, "Jeshmup Export", Activate },
	{ NULL }
};