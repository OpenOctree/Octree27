#ifndef RefinementSurfaceRegion_h
#define RefinementSurfaceRegion_h 1

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
using Clobscode::GeometricTransform;


namespace Clobscode
{
	class RefinementSurfaceRegion : public RefinementRegion
	{
	public:
		
		// Construction / destruction
		RefinementSurfaceRegion(TriMesh &tm, const unsigned short &level);
		
		virtual ~RefinementSurfaceRegion();
        
        virtual GeometricTransform rotateWithinYou(TriMesh &input);
		
        virtual void rotate(GeometricTransform &gt);
        
        virtual vector<Point3D> &getPoints();
		
        virtual bool intersectsOctant(vector<MeshPoint> &points, Octant &oct);
        
    protected:
        
        virtual bool edgeIntersection(Point3D &oct_p1, Point3D &oct_p2,
                                      Point3D &seg_p1, Point3D &seg_p2);
        
        virtual unsigned long computePosition(const Point3D &p, const Point3D &pmin,
                                             const Point3D &pmax);

		
	protected:
		// Data
        TriMesh tm;
	};
	
	inline vector<Point3D> &RefinementSurfaceRegion::getPoints(){
		return tm.getPoints();
	}
	
}

#endif
