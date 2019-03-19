#include "SurfEdgeContainer.h"

namespace SurfMesh {
	
	SurfEdgeContainer::SurfEdgeContainer(unsigned long size){
		edgeindexer.reserve(size);
		indexed.reserve(size);
		this->size=0;
	}
	
	SurfEdgeContainer::~SurfEdgeContainer(){
		
	}
	
	unsigned long SurfEdgeContainer::addEdge(unsigned long point1,
										unsigned long point2,
										unsigned long faceindex){
		SurfEdge ne(point1,point2);
		
		if(edgeindexer.size()<ne.getKey()+1){
			//Edge first insertion.
			for(unsigned long i=edgeindexer.size(); i<ne.getKey()+1; i++){
				list<SurfPair> dummy;
				edgeindexer.push_back(dummy);
			}
			ne.addFace(faceindex);
			return addEdge(ne);
		}
		else{
			//at this point the edge key exists in the vector
			list<SurfPair> pairs = edgeindexer[ne.getKey()];
			list<SurfPair>::iterator iter;
			for(iter=pairs.begin();iter!=pairs.end();iter++){
				if((*iter)[0]==ne.getVal()){
					//the edge was found, so the list of faces of it is updated
					indexed[(*iter)[1]].addFace(faceindex);
					return (*iter)[1];
				}
			}
			//the edge was not found, so it must be inserted;
			ne.addFace(faceindex);
			return addEdge(ne);
		}
	}
	
	unsigned long SurfEdgeContainer::addEdge(SurfEdge &e){
		SurfPair np(e.getVal(),size);
		edgeindexer[e.getKey()].push_back(np);
		indexed.push_back(e);
		return size++;
	}
	
	
	SurfEdge &SurfEdgeContainer::getEdge(unsigned long index){
		if(index>=size)
			std::cerr << "Index out of boundary in EdgeContainer\n";
		return indexed[index];
	}
	
	ostream& operator<<(ostream& o,SurfEdgeContainer &ec){
		for(int i=0;i<ec.length();i++){
			o << ec.getEdge(i) << " [";
			list<unsigned long> ef = ec.getEdge(i).getFaces();
			list<unsigned long>::iterator iter;
			int semicolon=0;
			for(iter=ef.begin();iter!=ef.end();iter++){
				o << *iter;
				if(semicolon++<ef.size()-1)
					o << ",";
			}
			o << "]\n";
		}
		return o;
	}
}
