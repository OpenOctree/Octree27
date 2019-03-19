#ifndef SurfEdgeContainer_h
#define SurfEdgeContainer_h 1

#include <iostream>
#include <vector>
#include <list>
#include "SurfEdge.h"
#include "SurfPair.h"

using std::vector;
using std::list;
using std::ostream;

namespace SurfMesh
{
	class SurfEdgeContainer{
		
	public:
		
		SurfEdgeContainer(unsigned long size);
		
		virtual ~SurfEdgeContainer();
		
		virtual unsigned long addEdge(unsigned long point1,
									 unsigned long point2,
									 unsigned long faceindex);
		
		virtual SurfEdge &getEdge(unsigned long index);
		
		virtual unsigned long length();
		
	protected:
		
		virtual unsigned long addEdge(SurfEdge &e);
		
	protected:
		
		vector<list<SurfPair> > edgeindexer;
		vector<SurfEdge> indexed;
		unsigned long size;
		
	};
	
	inline unsigned long SurfEdgeContainer::length(){
		return size;
	}
	
	ostream& operator<<(ostream& o,SurfEdgeContainer &ec);
}
#endif
