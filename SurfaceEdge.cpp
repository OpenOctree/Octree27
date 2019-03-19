#include "SurfaceEdge.h"

namespace Clobscode
{
	
	SurfaceEdge::SurfaceEdge(){
		info.assign(2,0);
	}
	
	SurfaceEdge::SurfaceEdge(const unsigned long &point1, const unsigned long &point2){
		info.assign(3,0);
		if (point1<point2) {
			info[0]=point1;
			info[1]=point2;
		}
		else {
			info[1]=point1;
			info[0]=point2;
		}
	}
	
	SurfaceEdge::~SurfaceEdge(){
		
	}
	
	void SurfaceEdge::assign(const unsigned long &point1, const unsigned long &point2){
		if (point1<point2) {
			info[0]=point1;
			info[1]=point2;
		}
		else {
			info[1]=point1;
			info[0]=point2;
		}
	}
	
	ostream& operator<<(ostream& o, const SurfaceEdge &e){
		o << e[0] << " ";
		o << e[1];
		return o;
	}
	
	bool operator==(const SurfaceEdge &e1, const SurfaceEdge &e2) {
		//this possible as SurfaceEdges are sorted by min index
		if (e1[0]==e2[0] && e1[1]==e2[1])
			return true;
		return false;
	}
	
	bool operator!=(const SurfaceEdge &e1, const SurfaceEdge &e2) {
		return !(e1==e2);
	}

	bool operator<(const SurfaceEdge &e1, const SurfaceEdge &e2) {
		if (e1[0]!=e2[0]){
			return e1[0]<e2[0];
		}
		return e1[1] < e2[1];
	}
	
	void SurfaceEdge::operator=(const SurfaceEdge &e){
		info[0]=e[0];
		info[1]=e[1];
	}
	
}