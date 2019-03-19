#ifndef Prism_h
#define Prism_h 3

#include "FaceDiagonal.h"
#include <vector>
#include <list>
#include <iostream>

using std::vector;
using std::list;

namespace Clobscode
{
	class Prism {
		
	public:
		
		Prism(vector<unsigned long> &mypoints);
		
		virtual ~Prism();
		
		virtual vector<vector<unsigned long> > getSubElements(vector<bool> &inside_state);
        
    protected:
        
        virtual unsigned long opposite(unsigned long idx);
        
        virtual void oppositeFace(unsigned long idx, vector<unsigned long> &base);
        
        virtual bool oneRepeated(vector<unsigned long> &original, vector<unsigned long> &result);
        
        virtual vector<unsigned long> sortDiagonals(list<unsigned long> &original);
        
    protected:
        
        vector<unsigned long> points;
		
	};
}
#endif
