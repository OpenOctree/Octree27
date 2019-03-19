#ifndef SurfTemplate4_h
#define SurfTemplate4_h 3

#include <vector>
#include <iostream>
#include "HexRotation.h"

using std::vector;

namespace Clobscode
{
	class SurfTemplate4 {
		
	public:
		
		SurfTemplate4();
		
		virtual ~SurfTemplate4();
		
		virtual bool getSubelements(vector<unsigned long> &all, 
									vector<unsigned long> &in,
									vector<vector<unsigned long> > &neweles);
		
	protected:
		
		virtual void PatternA(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void PatternB(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void PatternC(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void PatternD(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void PatternE(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void PatternF(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void PatternG(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void swap(vector<unsigned long> &vec,int pos1, int pos2);
		
		virtual vector<unsigned long> getEdges(int p);
		
	};
}
#endif
