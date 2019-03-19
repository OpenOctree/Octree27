#ifndef SurfaceEdge_h
#define SurfaceEdge_h 1

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
	
	class SurfaceEdge{
		
	public:
        
		SurfaceEdge();
		
		SurfaceEdge(const unsigned long &idx1, const unsigned long &idx2);
		
		virtual ~SurfaceEdge();
		
		virtual void assign(const unsigned long &idx1, const unsigned long &idx2);
		
		virtual unsigned long operator[](unsigned const int &pos) const;
		
		virtual void operator=(const SurfaceEdge &e);
		
		friend ostream& operator<<(ostream& o, const SurfaceEdge &e);
		
		friend bool operator==(const SurfaceEdge &e1, const SurfaceEdge &e2);
		
		friend bool operator!=(const SurfaceEdge &e1, const SurfaceEdge &e2);
		
		friend bool operator<(const SurfaceEdge &e1, const SurfaceEdge &e2);
		
		
	protected:
		
		vector<unsigned long> info;

	};
		
	inline unsigned long SurfaceEdge::operator[](unsigned const int &pos) const{
		return info.at(pos);
	}
	
}
#endif
