#ifndef RefinementAllRegion_h
#define RefinementAllRegion_h 1

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
	class RefinementAllRegion : public RefinementRegion
	{
	public:
		
		// Construction / destruction
		RefinementAllRegion(const unsigned short &level);
		
		virtual ~RefinementAllRegion();
        
        virtual GeometricTransform rotateWithinYou(TriMesh &input);
        
        virtual void rotate(GeometricTransform &gt);
		
        virtual bool intersectsOctant(vector<MeshPoint> &points, Octant &oct);

	};
}

#endif
