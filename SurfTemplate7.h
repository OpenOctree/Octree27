#ifndef SurfTemplate7_h
#define SurfTemplate7_h 1

#include <vector>
#include <iostream>
#include "HexRotation.h"

using std::vector;

namespace Clobscode
{
	class SurfTemplate7 {
		
	public:
		SurfTemplate7();
		
		virtual ~SurfTemplate7();
		
		virtual bool getSubelements(vector<unsigned long> &all, 
									vector<unsigned long> &in,
									vector<vector<unsigned long> > &neweles);
		
	};
}
#endif
