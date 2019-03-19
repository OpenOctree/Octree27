#ifndef SurfPair_h
#define SurfPair_h 1

#include <iostream>

using std::ostream;

namespace SurfMesh {

	class SurfPair{
		
	public:
		
		SurfPair();
		
		SurfPair(unsigned long key, unsigned long val);
		
		virtual ~SurfPair();
		
		virtual unsigned long &operator[](unsigned long pos);
		
		virtual void operator=(SurfPair p2);
		
	protected:
		
		unsigned long key,val;
		
	};
	
	ostream& operator<<(ostream& o,SurfPair &p);
	
	bool operator==(SurfPair &p1,SurfPair &p2);
	
	bool operator!=(SurfPair &p1,SurfPair &p2);
}

#endif
