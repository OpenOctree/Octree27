#ifndef EnhancedElement_h
#define EnhancedElement_h 1

#include <iostream>
#include <vector>
#include <list>
#include "MeshPoint.h"
#include "SurfTemplate1.h"
#include "SurfTemplate2.h"
#include "SurfTemplate3.h"
#include "SurfTemplate4.h"
#include "SurfTemplate5.h"
#include "SurfTemplate6.h"
#include "SurfTemplate7.h"


using Clobscode::MeshPoint;
using std::vector;
using std::list;

namespace Clobscode
{
	
	
	class EnhancedElement{
		
	public:
		
		EnhancedElement(vector<unsigned long> &epts);
		
		virtual ~EnhancedElement();
		
		//important methods 		
		virtual bool applySurfaceTemplates(vector<MeshPoint> &meshpoints,
										   list<MeshPoint> &newpts,
										   vector<vector<unsigned long> > &newsub);
				
		virtual void computeMaxDistance(vector<MeshPoint> &meshpoints);
		
		virtual void setMaxDistance(double md);
		
		virtual double getMaxDistance();
		
		//access methods
		virtual void setBorderState(bool state);
		
		virtual bool getBorderState();
		
		virtual vector<unsigned long> &getPoints();
		
		virtual bool isInside();
		
	protected:
		
		vector<unsigned long> pointindex;
		//this double is used decide if an inner node
		//of this element should be projected onto the
		//input domain in order to not produce a flat
		//element. This is done in method 
		//Clobscode::Mesher::projectCloseToBoundaryNodes.
		double maxdistance;
		//position flags
		bool border;
		
	};
	
	inline bool EnhancedElement::getBorderState(){
		return border;
	}
	
	inline void EnhancedElement::setMaxDistance(double md){
		maxdistance = md;
	}
	
	inline double EnhancedElement::getMaxDistance(){
		return maxdistance;
	}
	
	inline void EnhancedElement::setBorderState(bool state){
		border = state;
	}
	
	inline vector<unsigned long> &EnhancedElement::getPoints(){
		return pointindex;
	}
	
	inline bool EnhancedElement::isInside(){
		return border;
	}
	
	std::ostream& operator<<(ostream& o,EnhancedElement &e);
}
#endif
