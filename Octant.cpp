#include "stdafx.h"
#include "Octant.h"


namespace Clobscode
{
	
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	Octant::Octant(vector<unsigned long> &epts, 
				   const unsigned short &ref_level){
		
		pointindex = epts;
		//for optimization
		(*this).ref_level = ref_level;

		sub_elements.assign(1,epts);
		n_influences = 0;
		influence_commit = false;
		
		//surface = false;
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	Octant::~Octant(){
		
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------


    bool Octant::accept(Visitor *v)
    {
        return v->visit(this);
    }

	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	std::ostream& operator<<(std::ostream& o,Octant &e){
		std::vector<unsigned long> points = e.getPoints();
		for (unsigned long i=0; i<points.size(); i++)
			o << " " << points[i];
		return o;
	}

}
