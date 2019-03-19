#ifndef SurfTriangle_h
#define SurfTriangle_h 1

#include "Point3D.h"
#include <vector>
#include <iostream>

using Clobscode::Point3D;
using std::vector;
using std::cout;

namespace SurfMesh 
{
	class SurfTriangle
	{
	public:
		
		// Construction / destruction
		SurfTriangle(vector<unsigned long> &fpts);
		
		virtual ~SurfTriangle();
		
		virtual void computeNormal(vector<Point3D> &pts);
		
		virtual Point3D computeNormalAtNode(unsigned long nidx, 
											vector<Point3D> &pts);
		
		virtual Point3D projection(const Point3D &p1, 
								   const Point3D &p2);
		
		virtual vector<unsigned long> &getPoints();
		
		virtual Point3D &getNormal();
		
		virtual Point3D getNormalizedNormal();
		
		virtual Point3D getSemiNormalizedNormal();
		
		virtual unsigned long &operator[](unsigned long pos);
		
		virtual unsigned long operator[](unsigned long pos) const;
		
		virtual bool segmentIntersection(vector<Point3D> &pts,
										 const Point3D &ep1,
										 const Point3D &ep2);
	
		//computes the distant of pPoint to the plane formed 
		//by this triangle.
		virtual double distance(const Point3D &pPoint);
		
		
	protected:
		// Data
		vector<unsigned long> mIdxV;
		Point3D mTriangleNormal, onepoint;
		
	};
	
	inline vector<unsigned long> &SurfTriangle::getPoints(){
		return mIdxV;
	}
	
	inline Point3D &SurfTriangle::getNormal(){
		return mTriangleNormal;
	}	
	
	inline Point3D SurfTriangle::getNormalizedNormal(){
		Point3D normal = mTriangleNormal/(mTriangleNormal.Norm());
		return normal;
	}
	
	inline Point3D SurfTriangle::getSemiNormalizedNormal(){
		Point3D normal = mTriangleNormal/10000;
		return normal;
	}
}

#endif
