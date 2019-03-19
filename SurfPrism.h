#ifndef SurfPrism_h
#define SurfPrism_h 3

#include "FaceDiagonal.h"
#include "MeshPoint.h"
#include <vector>
#include <list>
#include <iostream>

using std::vector;
using std::list;

namespace Clobscode
{
	class SurfPrism {
		
	public:
		
		SurfPrism(vector<unsigned long> &mypoints);
		
		virtual ~SurfPrism();
		
		virtual vector<vector<unsigned long> > getSubElements(vector<bool> &inside_state);
        
        virtual double getQuality(vector<MeshPoint> &allpoints);
        
        virtual vector<vector<unsigned long> > getTetras();
        
    protected:
        
        virtual unsigned long opposite(unsigned long idx);
        
        virtual void oppositeFace(unsigned long idx, vector<unsigned long> &base);
        
        virtual bool oneRepeated(vector<unsigned long> &original, vector<unsigned long> &result);
        
        virtual vector<unsigned long> sortDiagonals(list<unsigned long> &original);
        
    protected:
        
        vector<unsigned long> points;
        
        double scaled_jac_constant;
		
	};
}
#endif
