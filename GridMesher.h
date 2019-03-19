#ifndef GridMesher_h
#define GridMesher_h 1

#include "MeshPoint.h"
#include <math.h>

using std::vector;
using std::list;
using Clobscode::MeshPoint;

namespace Clobscode
{
	class GridMesher{
		
	public:
		
		GridMesher();
		
		virtual ~GridMesher();
		
		virtual void generatePoints(vector<double> &bounds,
									vector<double> &all_x,
									vector<double> &all_y,
									vector<double> &all_z);
		
		virtual void generateMesh(vector<double> &all_x,
						vector<double> &all_y,
						vector<double> &all_z,
						vector<MeshPoint> &points,
						vector<vector<unsigned long> > &elements);
		
	protected:
		
		virtual void generateVector(vector<double> &coords, 
									double min, double max, 
									double step);
		
	};
	
}
#endif
