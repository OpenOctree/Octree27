#ifndef SurfTemplate2_h
#define SurfTemplate2_h 3

#include <vector>
#include "HexRotation.h"
#include <iostream>

using std::vector;

namespace Clobscode
{
class SurfTemplate2 {
	
  public:
	
	SurfTemplate2();
	
	virtual ~SurfTemplate2();
	
	virtual bool getSubelements(vector<unsigned long> &all, 
								vector<unsigned long> &in,
								vector<vector<unsigned long> > &neweles);

    virtual bool getSubelements(vector<unsigned long> &all,
								vector<unsigned long> &in,
								vector<vector<unsigned long> > &neweles,
                                vector<vector<unsigned long> > &possibles,
                                vector<vector<unsigned long> > &continuity);
    
  protected:
	
	virtual void PatternA(vector<unsigned long> &all, 
						  vector<vector<unsigned long> > &neweles,
                          vector<vector<unsigned long> > &continuity);
    
    virtual void PatternA(vector<unsigned long> &all,
                          vector<vector<unsigned long> > &neweles);
	
	virtual void PatternB(vector<unsigned long> &all, 
						  vector<vector<unsigned long> > &neweles);
	
    virtual void PatternB(vector<unsigned long> &all,
						  vector<vector<unsigned long> > &neweles,
                          vector<vector<unsigned long> > &possibles);
    
	virtual void PatternC(vector<unsigned long> &all, 
						  vector<vector<unsigned long> > &neweles);
	
};
}
#endif
