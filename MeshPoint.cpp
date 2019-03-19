#include "stdafx.h"
#include "MeshPoint.h"

namespace Clobscode
{
	MeshPoint::MeshPoint(){
		//we assume that every point is outisde by default.
		inside = false;
		//checking if a point is outside or not is a very expensive 
		//operation, so we try to do it only once
		outsidechecked = false;
		projected = false;
		maxdistance = 0;
	}
	
	MeshPoint::MeshPoint(const Point3D &p){
		point = p;
		//we assume that every point is outisde by default.
		inside = false;
		//checking if a point is outside or not is a very expensive 
		//operation, so we try to do it only once
		outsidechecked = false;
		projected = false;
		maxdistance = 0;
	}
	
	MeshPoint::~MeshPoint(){
		
	}
		
	std::ostream& operator<<(std::ostream& o,MeshPoint &p){
		o << p.getPoint();
		return o;
	}
	
}
