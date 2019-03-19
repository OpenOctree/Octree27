#ifndef SurfTemplate1_h
#define SurfTemplate1_h 1

#include <vector>
#include "HexRotation.h"

using std::vector;

namespace Clobscode
{
class SurfTemplate1 {
	
  public:
      SurfTemplate1();

      virtual ~SurfTemplate1();

      virtual bool getSubelements(vector<unsigned long> &all, 
								  vector<unsigned long> &in,
								  vector<vector<unsigned long> > &newsubs);

};
}
#endif
