#ifndef OctreeEdge_h
#define OctreeEdge_h 1

#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::ostream;
using std::set;
using std::cout;
using std::pair;

namespace Clobscode
{
	
	//class OctreeEdge;
	
	class OctreeEdge{
		
	public:
        
		OctreeEdge();
		
		OctreeEdge(const unsigned long &idx1, const unsigned long &idx2);
		
		virtual ~OctreeEdge();
		
		virtual void assign(const unsigned long &idx1, const unsigned long &idx2);
		
		virtual void updateMidPoint(const unsigned long &idx1, const unsigned long &idx2);
		
		virtual bool split(set<OctreeEdge> &allOctreeEdges, unsigned long maxp);
		
		virtual void setMidPoint(unsigned long &mid1, unsigned long &mid2);
		
		//virtual unsigned long &operator[](unsigned const int &pos);
		
		virtual unsigned long operator[](unsigned const int &pos) const;
		
		virtual void operator=(const OctreeEdge &e);
		
		friend ostream& operator<<(ostream& o, const OctreeEdge &e);
		
		friend bool operator==(const OctreeEdge &e1, const OctreeEdge &e2);
		
		friend bool operator!=(const OctreeEdge &e1, const OctreeEdge &e2);
		
		friend bool operator<(const OctreeEdge &e1, const OctreeEdge &e2);
		
		
	protected:
		
		vector<unsigned long> info;
		
		//set<OctreeEdge>::iterator mypointer;
	};
	
	/*inline unsigned long &OctreeEdge::operator[](unsigned const int &pos){
		return info.at(pos);
	}*/
	
	inline void OctreeEdge::updateMidPoint(const unsigned long &idx1, const unsigned long &idx2){

		info[2] = idx1;
		info[3] = idx2;

		
	}

	inline unsigned long OctreeEdge::operator[](unsigned const int &pos) const{
		return info.at(pos);
	}
	
	inline void OctreeEdge::setMidPoint(unsigned long &mid1, unsigned long &mid2){

		info[2] = mid1;
		info[3] = mid2;


	}
	
}
#endif
