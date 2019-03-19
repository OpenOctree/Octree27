#ifndef SurfHexahedron_h
#define SurfHexahedron_h 3

#include <vector>
#include <list>
#include <iostream>
#include "MeshPoint.h"
#include "TriMesh.h"
#include "SurfTemplate1.h"
#include "SurfTemplate2.h"
#include "SurfTemplate3.h"
#include "SurfTemplate4.h"
#include "SurfTemplate5.h"
#include "SurfTemplate6.h"
#include "SurfTemplate7.h"


using std::vector;
using std::list;
using Clobscode::MeshPoint;
using Clobscode::TriMesh;

namespace Clobscode
{
	class SurfHexahedron {
		
	public:
		
		SurfHexahedron(vector<unsigned long> &mypoints);
		
		virtual ~SurfHexahedron();
		
        virtual vector<vector<unsigned long> > getSubElements(vector<MeshPoint> &meshpoints, list<MeshPoint> &newpts,
                                                             TriMesh &input, unsigned long &e_idx,
                                                             vector<vector<unsigned long> > &possibles,
                                                             vector<vector<unsigned long> > &continuity,
                                                             list<unsigned long> &intersected_faces);        
    protected:
        
        vector<unsigned long> points;
		
	};
}
#endif
