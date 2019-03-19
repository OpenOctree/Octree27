#include "stdafx.h"
#include "RefinementInputSurfaceRegion.h"

namespace Clobscode
{	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	RefinementInputSurfaceRegion::RefinementInputSurfaceRegion(const unsigned short &level)
	{
		refine_level = level;
        
        local_rot = false;
        input_rot = true;
	}

	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	RefinementInputSurfaceRegion::~RefinementInputSurfaceRegion()
	{
		
	}

    //--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
    GeometricTransform RefinementInputSurfaceRegion::rotateWithinYou(TriMesh &input) {
		GeometricTransform gt;
        gt.rotateSurfaceMesh(input);
        //rotate input and save it in gt variable (see .h). then return gt.
        return gt;
        //gt defined in parent class
    }
    
    //--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
    
    void RefinementInputSurfaceRegion::rotate(GeometricTransform &gt) {
        //nothing to do
    }
	
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	bool RefinementInputSurfaceRegion::intersectsOctant(vector<MeshPoint> &points, Octant &oct)
    {
        return !oct.getIntersectedFaces().empty();
	}
}
