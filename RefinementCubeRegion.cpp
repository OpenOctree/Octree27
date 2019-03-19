#include "stdafx.h"
#include "RefinementCubeRegion.h"

namespace Clobscode
{
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	RefinementCubeRegion::RefinementCubeRegion(Point3D &p1, Point3D &p2,
									   const unsigned short &level)
	{
		this->pts.reserve(2);
		this->pts.push_back(p1);
		this->pts.push_back(p2);
		refine_level = level;
        
        local_rot = true;
        input_rot = false;
        
        rotated = false;
	}
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	RefinementCubeRegion::~RefinementCubeRegion()
	{
		
	}
    
    //--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
    GeometricTransform RefinementCubeRegion::rotateWithinYou(TriMesh &input) {
		//~ GeometricTransform gt;
        //~ gt.rotateSurfaceMesh(input);
        //~ rotate(gt);
        //~ rotated = true;
        //rotate input and save it in gt variable (see .h). then return gt.
        return gt;
        //gt defined in parent class
    }

	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
    
    void RefinementCubeRegion::rotate(GeometricTransform &gt){
		
		//~ gt.apply(this->pts[0]);
		//~ gt.apply(this->pts[1]);
        rotated = true;

        this->gt = gt;
        
    }
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	bool RefinementCubeRegion::intersectsOctant(vector<MeshPoint> &points, Octant &oct)
    {
        
        Point3D p1 = points[oct.getPoints()[0]].getPoint();
        Point3D p2 = points[oct.getPoints()[6]].getPoint();
     
        //if the input mesh was rotated w.r.t. this cube, apply inverse
        
        if (rotated) {
            gt.applyInverse(p1);
            gt.applyInverse(p2);
        }
        
        if (p2[0]<=pts[0][0] || pts[1][0] <= p1[0] ||
            p2[1]<=pts[0][1] || pts[1][1] <= p1[1] ||
            p2[2]<=pts[0][2] || pts[1][2] <= p1[2]) {
            return false;
        }
        
        return true;
	}
}
