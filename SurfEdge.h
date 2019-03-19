#ifndef SurfEdge_h
#define SurfEdge_h 1

#include <iostream>
#include <vector>
#include <list>

using std::list;
using std::vector;
using std::ostream;

namespace SurfMesh {

	class SurfEdge{
		
	public:
		
		SurfEdge();
		
		SurfEdge(unsigned long point1, unsigned long point2);
		
		virtual ~SurfEdge();
		
		virtual unsigned long getKey();
		
		virtual unsigned long getVal();
		
		virtual unsigned long numberOfFaces();
		
		virtual void addFace(unsigned long faceindex);
		
		virtual list<unsigned long> &getFaces();
		
		virtual unsigned long getOtherFace(unsigned long vf);
		
	protected:
		
		vector<unsigned long> nodes;
		list<unsigned long> faces;
		
	};
	
	inline unsigned long SurfEdge::getKey(){
		return nodes[0];
	}
	
	inline unsigned long SurfEdge::getVal(){
		return nodes[1];
	}
	
	inline unsigned long SurfEdge::numberOfFaces(){
		return faces.size();
	}
	
	inline void SurfEdge::addFace(unsigned long faceindex){
		list<unsigned long>::iterator iter;
		for(iter=faces.begin();iter!=faces.end(); iter++){
			if(faceindex==*iter)
				return;
		}
		faces.push_back(faceindex);
	}
	
	inline list<unsigned long> &SurfEdge::getFaces(){
		return faces;
	}
		
	inline unsigned long SurfEdge::getOtherFace(unsigned long vf){
		list<unsigned long>::iterator iter;
		for(iter=faces.begin();iter!=faces.end(); iter++){
			if (*iter!=vf) {
				return *iter;
			}
		}
		return 0;
	}
		
	ostream& operator<<(ostream& o,SurfEdge &p);
	
	bool operator==(SurfEdge &p1,SurfEdge &p2);
	
	bool operator!=(SurfEdge &p1,SurfEdge &p2); 
}
#endif
