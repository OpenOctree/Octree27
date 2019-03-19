#ifndef SurfTemplate6_h
#define SurfTemplate6_h 3

#include <vector>
#include <iostream>
#include "HexRotation.h"

using std::vector;

namespace Clobscode
{
	class SurfTemplate6 {
		
	public:
		SurfTemplate6();
		
		virtual ~SurfTemplate6();
		
		virtual bool getSubelements(vector<unsigned long> &all, 
									vector<unsigned long> &out,
									vector<vector<unsigned long> > &neweles);
		
	protected:
		
		virtual void PatternA(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void PatternB(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void PatternC(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
	};
}
#endif
