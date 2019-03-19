#ifndef SurfTetrahedron_h
#define SurfTetrahedron_h 3

#include "FaceDiagonal.h"
#include "MeshPoint.h"
#include <vector>
#include <list>
#include <iostream>
#include <math.h>

using std::vector;
using std::list;

namespace Clobscode
{
	class SurfTetrahedron {
		
	public:
		
		SurfTetrahedron(vector<unsigned long> &mypoints);
		
		virtual ~SurfTetrahedron();
		
		virtual vector<vector<unsigned long> > getSubElements(vector<bool> &inside_state);
        
        virtual vector<vector<unsigned long> > getTetras();
        
        virtual double getQuality(vector<MeshPoint> &allpoints);
                
    protected:
        
        vector<unsigned long> points;
        
        double scaled_jac_constant;
		
	};
}
#endif
