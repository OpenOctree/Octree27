#ifndef RefinementRegion_h
#define RefinementRegion_h 1

#include "SurfTriangle.h"
#include "MeshPoint.h"
#include "GeometricTransform.h"
#include "Octant.h"
#include <vector>
#include <iostream>

using SurfMesh::SurfTriangle;
using Clobscode::Point3D;
using std::vector;
using std::cout;
using Clobscode::Octant;
using Clobscode::GeometricTransform;

namespace Clobscode
{	
	class RefinementRegion
	{
	public:
		
		// Construction / destruction
		RefinementRegion();
				
		virtual ~RefinementRegion();

		virtual vector<Point3D> &getPoints();
        
        virtual void updatePoints(vector<Point3D> &npts);
        
        //virtual void rotate(Point3D &centroid, double &xAxisRotationAngle,
        //                    double &yAxisRotationAngle, double &zAxisRotationAngle)=0;
        
        virtual void rotate(GeometricTransform &gt)=0;
        
        virtual GeometricTransform rotateWithinYou(TriMesh &input)=0;
        
        virtual bool intersectsOctant(vector<MeshPoint> &points, Octant &oct)=0;
        
        virtual bool needsLocalRotation();
        
        virtual bool needsInputRotation();
        
        virtual void forceInputRotation();
		
		virtual unsigned short getRefinementLevel();
		
	protected:
		// Data
		unsigned short refine_level;
        bool local_rot, input_rot;
        vector<Point3D> pts;
        GeometricTransform gt;
	};
	
	inline unsigned short RefinementRegion::getRefinementLevel(){
		return refine_level;
	}
    
    inline vector<Point3D> &RefinementRegion::getPoints() {
        return pts;
    }
    
    inline void RefinementRegion::updatePoints(vector<Point3D> &npts) {
        
        pts.clear();
        pts.reserve(npts.size());
        
        for (unsigned long i=0; i<npts.size(); i++) {
            pts.push_back(npts[i]);
        }
    }
    
    inline bool RefinementRegion::needsLocalRotation() {
        return local_rot;
    }
    
    inline bool RefinementRegion::needsInputRotation() {
        return input_rot;
    }
    
    inline void RefinementRegion::forceInputRotation() {
        input_rot = true;
    }
}

#endif
