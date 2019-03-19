#ifndef GeometricTransform_h
#define GeometricTransform_h 1

#include <iostream>
#include <math.h>
#include "Point3D.h"
#include "TriMesh.h"
#include <vector>
#include <list>

using Clobscode::Point3D;
using std::list;
using std::vector;
using Clobscode::TriMesh;

namespace Clobscode
{	
	class GeometricTransform{
		
	public:
		
		GeometricTransform();
		
		GeometricTransform(Point3D &centroid, double &xAxisRotationAngle,
                           double &yAxisRotationAngle, double &zAxisRotationAngle);
				
		virtual ~GeometricTransform();
        
        //to implement
        virtual void rotateSurfaceMesh(TriMesh &tm);
        
        virtual void rotateSurfaceMeshInverse(TriMesh &tm);
        
        virtual void calculateAnglesAndCentroid(TriMesh &tm);
        
        virtual void apply(Point3D &p);
        
        virtual void applyInverse(Point3D &p);
		
		virtual void setCentroid(Point3D &p);
        
        virtual void setXAxis(double x);
        
        virtual void setYAxis(double y);
        
        virtual void setZAxis(double z);
        
        virtual Point3D &getCentroid();
        
        virtual double &getXAxis();
        
        virtual double &getYAxis();
        
        virtual double &getZAxis();
		
	protected:
		
		Point3D centroid;
        double x,y,z;
		
	};
	
    inline void GeometricTransform::setCentroid(Point3D &p) {
        centroid = p;
    }
    
    inline void GeometricTransform::setXAxis(double x) {
        this->x = x;
    }

    inline void GeometricTransform::setYAxis(double y) {
        this->y = y;
    }
    
    inline void GeometricTransform::setZAxis(double z) {
        this->z = z;
    }
    
    inline Point3D &GeometricTransform::getCentroid() {
        return centroid;
    }
    
    inline double &GeometricTransform::getXAxis() {
        return x;
    }
    
    inline double &GeometricTransform::getYAxis() {
        return y;
    }
    
    inline double &GeometricTransform::getZAxis() {
        return z;
    }
    
    inline bool largestNormal (Point3D n1, Point3D n2){
		 return (n1.Norm() > n2.Norm()); 
	}
}
#endif
