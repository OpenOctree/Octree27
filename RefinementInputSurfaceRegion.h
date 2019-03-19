#ifndef RefinementInputSurfaceRegion_h
#define RefinementInputSurfaceRegion_h 1

#include <vector>
#include <set>
#include <iostream>
#include "RefinementRegion.h"
#include "TriMesh.h"
#include "Octant.h"

using Clobscode::Point3D;
using std::vector;
using std::cout;
using std::set;
using Clobscode::RefinementRegion;
using Clobscode::TriMesh;
using Clobscode::Octant;

namespace Clobscode
{
	class RefinementInputSurfaceRegion : public RefinementRegion
	{
	public:
		
		// Construction / destruction
		RefinementInputSurfaceRegion(const unsigned short &level);
		
		virtual ~RefinementInputSurfaceRegion();
        
        virtual GeometricTransform rotateWithinYou(TriMesh &input);
		
        virtual void rotate(GeometricTransform &gt);
		
        virtual bool intersectsOctant(vector<MeshPoint> &points, Octant &oct);
	};
	
}

#endif
