#ifndef RefinementCubeRegion_h
#define RefinementCubeRegion_h 1

#include <vector>
#include <iostream>
#include "RefinementRegion.h"

using Clobscode::Point3D;
using std::vector;
using std::cout;
using Clobscode::RefinementRegion;
using Clobscode::Octant;

namespace Clobscode
{
	class RefinementCubeRegion : public RefinementRegion
	{
	public:
				
		RefinementCubeRegion(Point3D &p1, Point3D &p2,
                             const unsigned short &level);
				
		virtual ~RefinementCubeRegion();
        
        virtual GeometricTransform rotateWithinYou(TriMesh &input);
		
        virtual void rotate(GeometricTransform &gt);
		
        virtual bool intersectsOctant(vector<MeshPoint> &points, Octant &oct);
        
        
    protected:

        bool rotated;
        GeometricTransform gt;

	};
	
}

#endif
