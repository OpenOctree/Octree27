#include "OctreeEdge.h"

namespace Clobscode
{
	
	OctreeEdge::OctreeEdge(){
		info.assign(4,0);
	}
	
	OctreeEdge::OctreeEdge(const unsigned long &point1, const unsigned long &point2){
		info.assign(4,0);

		info[0]=point1;
		info[1]=point2;

		info[2]=0;
		info[3]=0;
	}
	
	OctreeEdge::~OctreeEdge(){
		
	}
	
	void OctreeEdge::assign(const unsigned long &point1, const unsigned long &point2){

		info[0]=point1;
		info[1]=point2;

	}
	
	bool OctreeEdge::split(set<OctreeEdge> &allOctreeEdges, unsigned long maxp){
		
		pair<set<OctreeEdge>::iterator , bool> result;
		//create possible new OctreeEdge
		OctreeEdge ne1(info[0],maxp);
		
		cout << "trying to insert " << ne1 << "\n";
		
		result = allOctreeEdges.insert(ne1);
		
		
		if (!result.second) {
			cout << "cannot split this OctreeEdge " << *this << "\n";
			return false;
		}
		else {
			
			OctreeEdge ne2(info[1],maxp);
			allOctreeEdges.insert(ne2);
			cout << "OctreeEdge " << *this << " was split\n";
		}
		return true;

	}
	
	ostream& operator<<(ostream& o, const OctreeEdge &e){
		o << e[0] << " ";
		o << e[1] << " ";
		o << e[2] << " ";
		o << e[3];
		return o;
	}
	
	bool operator==(const OctreeEdge &e1, const OctreeEdge &e2) {
		//this possible as OctreeEdges are sorted by min index
		if (e1[0]==e2[0] && e1[1]==e2[1])
			return true;
		return false;
	}
	
	bool operator!=(const OctreeEdge &e1, const OctreeEdge &e2) {
		return !(e1==e2);
	}

	bool operator<(const OctreeEdge &e1, const OctreeEdge &e2) {
		if (e1[0]!=e2[0]){
			return e1[0]<e2[0];
		}
		return e1[1] < e2[1];
	}
	
	void OctreeEdge::operator=(const OctreeEdge &e){
		info[0]=e[0];
		info[1]=e[1];
		info[2]=e[2];
		info[3]=e[3];
	}
	
}