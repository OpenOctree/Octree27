#ifndef Octant_h
#define Octant_h 1

#include <iostream>
#include <vector>
#include <list>
#include <set>

#include "Visitors/Visitor.h"

#include "MeshPoint.h"
#include "Point3D.h"
#include "OctreeEdge.h"
//#include "TransitionTemplate.h"
#include "TriMesh.h"
//#include "SurfTemplate1.h"
//#include "SurfTemplate2.h"
//#include "SurfTemplate3.h"
//#include "SurfTemplate4.h"
//#include "SurfTemplate5.h"
//#include "SurfTemplate6.h"
//#include "SurfTemplate7.h"
//#include "SurfTetrahedron.h"
//#include "SurfPrism.h"
//#include "SurfPyramid.h"
//#include "SurfHexahedron.h"

using Clobscode::MeshPoint;
using Clobscode::OctreeEdge;
using Clobscode::Point3D;
using Clobscode::TriMesh;
//using Clobscode::SurfPrism;
//using Clobscode::SurfPyramid;
using SurfMesh::SurfTriangle;
using std::vector;
using std::list;
using std::set;
using std::pair;

namespace Clobscode
{
	
	class Octant{
        friend class IntersectionsVisitor;
        friend class OneIrregularVisitor;
        friend class PointMovedVisitor;
        friend class SplitVisitor;
        friend class EdgeVisitor;
        friend class TransitionPatternVisitor;
        friend class SurfaceTemplatesVisitor;
        friend class RemoveSubElementsVisitor;

	public:
		
		Octant(vector<unsigned long> &epts, 
			   const unsigned short &ref_level);
		
		virtual ~Octant();

        bool accept(Visitor *v);

		//virtual void insertEdges(set<OctreeEdge> &edges);

        /*virtual void split(vector<MeshPoint> &points,
                           list<Point3D> &new_pts,
                           set<OctreeEdge> &edges,
                           vector<vector <unsigned long> > &new_eles,
                           vector<vector<Point3D> > &clipping);*/

		//note: max_ref_level is an important optimization due to it
		//avoids expensive checking functions for the octants refined 
		//to the maximum level (generally: the most common case in 
		//the output mesh).
		
//		virtual bool checkTransitionPattern(vector<MeshPoint> &points,
//							const set<OctreeEdge> &edges,
//							const unsigned short &max_ref_level);
//
//		virtual bool applyTransitionPattern(vector<MeshPoint> &points,
//							list<Point3D> &new_pts,
//							const set<OctreeEdge> &edges,
//							const unsigned short &max_ref_level);
		
		//virtual bool applySurfaceTemplates(vector<MeshPoint> &meshpoints,
		//					list<MeshPoint> &newpts,TriMesh &input,
		//					unsigned long &e_idx);
		
		//virtual bool isOneIrregular(const set<OctreeEdge> &edges,
        //                            const unsigned short &max_ref_level);

		//virtual bool pointMoved(vector<MeshPoint> &points,
		//					const set<OctreeEdge> &edges,
		//					const unsigned short &max_ref_level);

		//todo: again, isItIn must go
		//virtual bool isItIn(TriMesh &mesh,
		//					list<unsigned long> &faces,
		//					vector<Point3D> &coords);
		
		
		virtual void addProjectionInfluence(const Point3D &dir);
		
		virtual const Point3D &getProjectionInfluence();
		
		virtual void noMoreProjectionInfluences();
        
        //virtual bool removeOutsideSubElements(vector<MeshPoint> &points);
				
		//access methods
		virtual vector<unsigned long> &getPoints();
		
		virtual bool isInside();
		
		virtual bool intersectsSurface();
		
		virtual unsigned short &getRefinementLevel();
		
		virtual bool wasShrink();
		
		virtual bool wasConsideredInProjection();
		
		virtual void resetProjectionInfluence();
		
		//check intersections with all input faces
		//virtual bool checkIntersections(TriMesh &mesh,
		//								vector<MeshPoint> &pts);

        //check intersections with selected input faces
		//virtual bool checkIntersections(TriMesh &mesh,
		//								list<unsigned long> &faces,
		//								vector<Point3D> &coords);

		virtual list<unsigned long> &getIntersectedFaces();
		
		virtual vector<vector<unsigned long> > &getSubElements();
		
		virtual void computeMaxDistance(vector<MeshPoint> &mp);
		
        virtual double getMaxDistance();
		
		//flag for inside octants that due to "inside node" moved
		//to the input domain, it must be treated as a surface
		//element by the surfacePatterns
		virtual void setSurface();
		
		virtual bool isSurface();
		
		virtual void setIntersectedFaces(list<unsigned long> &ifcs);

    protected:
        
        //virtual bool applyHexSurfaceTemplates(vector<MeshPoint> &meshpoints,
        //                                     list<MeshPoint> &newpts,TriMesh &input,
        //                                      unsigned long &e_idx,
        //                                      vector<unsigned long> &inpts,
        //                                      vector<unsigned long> &outpts);
		
		//virtual void getEdge(const unsigned long &idx, OctreeEdge &e);

		
		//Clipping methods to detect intersection between input faces
		//and this octant.
		/*virtual bool intersectsTrianlge(SurfTriangle &st,
										vector<Point3D> &input_pts,
										const Point3D &pmin, 
										const Point3D &pmax);
		
		virtual unsigned long computePosition(const Point3D &p,
											 const Point3D &pmin,
											 const Point3D &pmax);
		
		virtual bool clipGeneralCase(const Point3D &p1, 
									 const Point3D &p2,
									 const Point3D &pmin,
									 const Point3D &pmax);
		
		virtual bool edgeTriangleIntersection(
									SurfTriangle &st,
									vector<Point3D> &input_pts,
									const Point3D &pmin,
									const Point3D &pmax);
		
		virtual vector<vector<Point3D> > getEdges(const Point3D &pmin,
									const Point3D &pmax);
		*/
		//protected:
		
		vector<unsigned long> pointindex;
		vector<vector<unsigned long> > sub_elements, possibles, continuity;
		list<unsigned long> intersected_faces;
		//the level at which this octant is found in the
		//the tree structure (octree). Used for optimization
		unsigned short ref_level;
		
		Point3D projection_influence;
		unsigned short n_influences;
		bool influence_commit;
		bool surface;
		
		double max_dis;
	};
	
	
	inline vector<unsigned long> &Octant::getPoints(){
		return pointindex;
	}
	
	inline bool Octant::isInside(){
		return intersected_faces.empty();
	}
	
	inline bool Octant::intersectsSurface(){
		return !intersected_faces.empty();
	}
	
	inline list<unsigned long> &Octant::getIntersectedFaces(){
		return intersected_faces;
	}
	
	inline unsigned short &Octant::getRefinementLevel() {
		return ref_level;
	}
	
	inline vector<vector<unsigned long> > &Octant::getSubElements() {
		return sub_elements;
	}
	
	inline void Octant::addProjectionInfluence(const Point3D &dir) {
		projection_influence += dir;
		n_influences++;
	}
	
	inline bool Octant::wasShrink() {
		return n_influences!=0;
	}
	
	inline const Point3D &Octant::getProjectionInfluence(){
		return projection_influence;
	}
	
	inline void Octant::noMoreProjectionInfluences(){
		if (n_influences==0) {
			return;
		}
		influence_commit = true;
		projection_influence = projection_influence / n_influences;
	}
	
	inline void Octant::resetProjectionInfluence() {
		projection_influence = projection_influence * 0;
		n_influences = 0;
	}
	
	inline bool Octant::wasConsideredInProjection(){
		return influence_commit;
	}
	
	inline void Octant::computeMaxDistance(vector<MeshPoint> &mp){
		Point3D p0 = mp[pointindex[0]].getPoint();
		Point3D p1 = mp[pointindex[6]].getPoint();
		max_dis = 0.3 * (p0 - p1).Norm();
	}
	
	inline double Octant::getMaxDistance(){
		return max_dis;
	}
	
	inline void Octant::setSurface(){
		surface = true;
	}
	
	inline bool Octant::isSurface(){
		return surface || !intersected_faces.empty();
	}
	
	inline void Octant::setIntersectedFaces(list<unsigned long> &ifcs){
		intersected_faces = ifcs;
	}
	
	std::ostream& operator<<(ostream& o,Octant &e);
}
#endif
