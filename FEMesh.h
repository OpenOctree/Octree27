#ifndef FEMesh_h
#define FEMesh_h 1

#include <vector>
#include "Point3D.h"

using std::vector;

namespace Clobscode
{
	class FEMesh{
		
	public:
		
		FEMesh(){};
		
		virtual void setPoints(vector<Point3D> &pts);
		
		virtual void setElements(vector<vector<unsigned long> > &els);
		
		virtual void setOutsideNodes(list<unsigned long> &outpts);
		
		virtual vector<Point3D> &getPoints();
		
		virtual vector<vector<unsigned long> > &getElements();
		
		virtual list<unsigned long> &getOutsideNodes();
		
	protected:
		
		vector<Point3D> points;
		vector<vector<unsigned long> > elements;
		list<unsigned long> outpts;
		
	};
	
	inline void FEMesh::setOutsideNodes(list<unsigned long> &outpts){
		list<unsigned long>::iterator iter;
		for (iter=outpts.begin(); iter!=outpts.end(); iter++) {
			this->outpts.push_back(*iter);
		}
	}
	
	inline void FEMesh::setElements(vector<vector<unsigned long> > &els){
		unsigned long n = els.size();
		elements.reserve(n);
		for (unsigned long i=0; i<n; i++) {
			elements.push_back(els[i]);
		}
	}
	
	inline void FEMesh::setPoints(vector<Point3D> &pts){
		unsigned long n = pts.size();
		points.reserve(n);
		for (unsigned long i=0; i<n; i++) {
			points.push_back(pts[i]);
		}
	}
	
	inline vector<Point3D> &FEMesh::getPoints(){
		return points;
	}
	
	inline vector<vector<unsigned long> > &FEMesh::getElements(){
		return elements;
	}
	
	inline list<unsigned long> &FEMesh::getOutsideNodes(){
		return outpts;
	}
}
#endif
