#ifndef FaceDiagonal_h
#define FaceDiagonal_h 3

#include <vector>
#include <iostream>

using std::vector;

namespace Clobscode
{
	class FaceDiagonal {
		
	public:
		
		FaceDiagonal(vector<unsigned long> &mypoints);
		
		virtual ~FaceDiagonal();
		
		virtual bool getDiagonal(vector<bool> &inside_state,
                                 vector<unsigned long> &diag);
        
    protected:
        
        vector<unsigned long> points;
		
	};
}
#endif
