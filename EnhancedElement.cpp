#include "stdafx.h"
#include "EnhancedElement.h"

namespace Clobscode
{
	EnhancedElement::EnhancedElement(vector<unsigned long> &epts){
		border = true;
		pointindex = epts;
		maxdistance = 0;
	}
	
	EnhancedElement::~EnhancedElement(){
		
	}
	
	//return true if SurfacePatterns succeded in replacing the hex element.
	bool EnhancedElement::applySurfaceTemplates(vector<MeshPoint> &meshpoints,
												list<MeshPoint> &newpts,
												vector<vector<unsigned long> > &newsub){	 
		
		//A surface template should be applyed only over elements
		//that intersect one surface or all of them. In both cases
		//at least one element node should be outside the sum of
		//input surfaces
		
		std::vector<unsigned long> inpts, outpts;
		std::list<unsigned long> tmpin;
		std::list<unsigned long> tmpout;
		std::list<unsigned long>::iterator piter;
		
		
		for (unsigned long i=0; i<pointindex.size(); i++){
			if(meshpoints.at(pointindex[i]).isOutside())
				tmpout.push_back(i);
			else
				tmpin.push_back(i);
		}
		
		//save the points in a std::vector for quick acces
		inpts.reserve(tmpin.size());
		for(piter=tmpin.begin();piter!=tmpin.end();piter++)
			inpts.push_back(*piter);
		outpts.reserve(tmpout.size());
		for(piter=tmpout.begin();piter!=tmpout.end();piter++)
			outpts.push_back(*piter);
				
		
		//select the patter to apply
		switch ((int)inpts.size()) {
			case 0:{
				/*If at this point, the element has 0 node inside,
				 it might be tangencial to input mesh, in which case
				 it should be removed, or represent a feature of
				 the domain (e.g. all nodes outside, but there is
				 something like a pipeline crossing it). This algorithm
				 isn't yet "future sensitive", therefore the element
				 is simply removed.
				 */
				return false;
			}
			case 1: {
				SurfTemplate1 surf_t1;
				return surf_t1.getSubelements(pointindex,inpts,newsub);
			}
			case 2: {
				SurfTemplate2 surf_t2;
				return surf_t2.getSubelements(pointindex,inpts,newsub);
			}
			case 3: {
				SurfTemplate3 surf_t3;
				return surf_t3.getSubelements(pointindex,inpts,newsub);
			}
			case 4: {
				SurfTemplate4 surf_t4;
				return surf_t4.getSubelements(pointindex,inpts,newsub);
			}
			case 5: {
				SurfTemplate5 surf_t5;
				return surf_t5.getSubelements(pointindex,inpts,meshpoints,
											  newpts,newsub);
			}
			case 6: {
				SurfTemplate6 surf_t6;
				return surf_t6.getSubelements(pointindex,outpts,newsub);
			}
			case 7: {
				SurfTemplate7 surf_t7;
				return surf_t7.getSubelements(pointindex,outpts,newsub);
			}
			case 8: {
				//If this happens the element is inside the overall
				//geometry, but intersects inner features.
				newsub.push_back(pointindex);
				break;
			}
			default: {
				cerr << " Error at EnhancedElement::applySurfacePatterns\n";
				cerr << " Number of inside nodes: " << inpts.size() << "\n";
				cerr << " Surface Patterns must be applied over elements";
				cerr << " with 1 to 7 inside nodes.\n";
				return false;
			}
		}
		
		return false;
	}
	
	void EnhancedElement::computeMaxDistance(vector<MeshPoint> &meshpoints){
		Point3D p0 = meshpoints[pointindex[0]].getPoint();
		Point3D p1 = meshpoints[pointindex[1]].getPoint();
		Point3D p3 = meshpoints[pointindex[3]].getPoint();
		Point3D p4 = meshpoints[pointindex[4]].getPoint();
		double dx = (p3-p0).Norm();
		double dy = (p4-p0).Norm();
		double dz = (p1-p0).Norm();

		double min;
		if (dx>dy && dx>dz) {
			min = dx;
		}
		else {
			if (dy>dz && dy>dx) {
				min = dy;
			}
			else {
				min = dz;
			}
		}
		maxdistance = min*0.3;
	}
	
	std::ostream& operator<<(std::ostream& o,EnhancedElement &e){
		std::vector<unsigned long> points = e.getPoints();
		for (unsigned long i=0; i<points.size(); i++)
			o << " " << points[i];
		return o;
	}
}
