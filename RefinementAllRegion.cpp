#include "stdafx.h"
#include "RefinementAllRegion.h"

namespace Clobscode
{	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	RefinementAllRegion::RefinementAllRegion(const unsigned short &level)
	{
		refine_level = level;
        local_rot = false;
        input_rot = true;
	}

	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	RefinementAllRegion::~RefinementAllRegion()
	{
		
	}

    
    //--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
    GeometricTransform RefinementAllRegion::rotateWithinYou(TriMesh &input) {
        //rotate input and return transformation
        GeometricTransform gt;
        gt.rotateSurfaceMesh(input);
        return gt;
        //gt defined in parent class
    }
    
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
    void RefinementAllRegion::rotate(GeometricTransform &gt) {
    
        //do nothing
    }
    	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	bool RefinementAllRegion::intersectsOctant(vector<MeshPoint> &points, Octant &oct)
    {
        return true;
	}
}
