#include "SurfPair.h"

namespace SurfMesh {
	
	SurfPair::SurfPair(){
		key=val=-1;
	}
	
	SurfPair::SurfPair(unsigned long key, unsigned long val){
		this->key=key;
		this->val=val;
	}
	
	SurfPair::~SurfPair(){
		
	}
	
	void SurfPair::operator=(SurfPair p2){
		key=p2[0];
		val=p2[1];
	}
	
	ostream& operator<<(ostream& o,SurfPair &p){
		o << p[0] << " ";
		o << p[1];
		return o;
	}
	
	bool operator==(SurfPair &p1,SurfPair &p2){
		if(p1[0]==p2[0] && p1[1]==p2[1])
			return true;
		return false;
	}
	
	bool operator!=(SurfPair &p1,SurfPair &p2){
		return !(p1==p2);
	}
	
	unsigned long &SurfPair::operator[](unsigned long pos){
		if(pos==0)
			return key;
		return val;
	}
	
}