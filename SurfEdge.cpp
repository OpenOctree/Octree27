#include "SurfEdge.h"

namespace SurfMesh {
	
	SurfEdge::SurfEdge(unsigned long point1, unsigned long point2){
		nodes.reserve(2);
		if(point1 < point2){
			nodes.push_back(point1);
			nodes.push_back(point2);
		}
		else{ 
			nodes.push_back(point2);
			nodes.push_back(point1);
		}
	}
	
	SurfEdge::~SurfEdge(){
		
	}
	
	ostream& operator<<(ostream& o,SurfEdge &e){
		o << "e(" << e.getKey() << ",";
		o << e.getVal() << ")" << " f(";
		list<unsigned long> faces = e.getFaces();
		for (list<unsigned long>::iterator iter=faces.begin(); iter!=faces.end(); iter++) {
			o << " " << *iter;
		}
		o << " )";
		return o;
	}
	
	bool operator==(SurfEdge &e1,SurfEdge &e2){
		if(e1.getKey()==e2.getKey() && e1.getVal()==e2.getVal())
			return true;
		return false;
	}
	
	bool operator!=(SurfEdge &p1,SurfEdge &p2){
		return !(p1==p2);
	}
}
