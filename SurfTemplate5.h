#ifndef SurfTemplate5_h
#define SurfTemplate5_h 3

#include <vector>
#include <list>
#include <iostream>
#include "HexRotation.h"
#include "MeshPoint.h"
#include "TriMesh.h"

using std::vector;
using std::list;
using Clobscode::MeshPoint;
using Clobscode::TriMesh;

namespace Clobscode
{
	class VolumePointContainer;
	
	class SurfTemplate5 {
		
	public:
		
		SurfTemplate5();
		
		virtual ~SurfTemplate5();
		
		//eventually, this pattern will add new MeshPoints. If 
		//this is the case they will be included in the list newpts.
		virtual bool getSubelements(vector<unsigned long> &all, 
									vector<unsigned long> &in,
									vector<MeshPoint> &pts,
									list<MeshPoint> &newpts,
									vector<vector<unsigned long> > &neweles,
									TriMesh &input,
									list<unsigned long> &intersectedfaces,
									unsigned long &e_idx);
		
	protected:
		
		virtual void PatternA(vector<unsigned long> &all, 
							  vector<MeshPoint> &pts,
							  list<MeshPoint> &newpts,
							  vector<vector<unsigned long> > &neweles,
							  TriMesh &inputs,
							  list<unsigned long> &intersectedfaces,
							  unsigned long &e_idx);
		
		virtual void PatternB(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual void PatternC(vector<unsigned long> &all, 
							  vector<vector<unsigned long> > &neweles);
		
		virtual vector<unsigned long> searchPivote(vector<unsigned long> &doubles);
		
		virtual vector<unsigned long> getEdges(int p);
		
	};
}
#endif
