#ifndef TriMesh_h
#define TriMesh_h 1

#include "Point3D.h"
#include "SurfTriangle.h"
#include "SurfEdgeContainer.h"
#include "SurfaceEdge.h"
#include <limits>
#include <set>

using std::vector;
using std::set;
using Clobscode::Point3D;
using SurfMesh::SurfTriangle;
using SurfMesh::SurfEdgeContainer;

namespace Clobscode
{
	class TriMesh{
		
	public:
        
        TriMesh();
        
		TriMesh(vector<Point3D> &pts, 
				vector<vector<unsigned long> > &fv);
		
		virtual ~TriMesh();
		
		virtual vector<Point3D> &getPoints();
		
		virtual vector<SurfTriangle> &getFaces();

		virtual vector<Point3D> &getVerticePseudoNormals();		
        
        virtual set<SurfaceEdge> &getEdges();
		
		virtual vector<double> &getBounds();
		
		virtual bool pointIsInMesh(const Point3D &pPoint);
		
		virtual bool pointIsInMesh(const Point3D & pPoint, 
								   list<unsigned long> &lFaces);
		
		virtual Point3D getProjection(const Point3D &pPoint);
		
		virtual Point3D getProjection(const Point3D & pPoint, 
								   list<unsigned long> &lFaces);
								 
		virtual Point3D getCentroid();
		
		virtual vector<Point3D> getNormals();						   
									
		
	protected:
		
		virtual void toCube(double per);
		
		// compute the pseudo normal at each surface node
		virtual void computeNodePseudoNormal();
		
		// compute the pseudo normal at each surface edge
		virtual void computeEdgePseudoNormal();
		
		virtual bool SignedDistToTriangle(const Point3D & pP, 
										  const unsigned long &iT, 
										  const double &current_min_dist, 
										  double & pDist, 
										  Point3D & pProjP, bool & pIsIn, 
										  int & faceEdgeNode);
		
		
	protected:
		
		vector<Point3D> mVertices;
		vector<SurfTriangle> mTriangles;
		
		//one pseudo normal per vertices (same size)
		vector<Point3D> mVerticePseudoNormals; 
		
		//one pseudo normal per edge, so 3 pseudo normals per 
		//triangle (3*size)
		vector<Point3D> mEdgePseudoNormals;
		
		//bounding box of this surface mesh
		vector<double> bounds;	
		
		//Point used by Ray Tracing Method (unstable)
		Point3D outside;
        
        //the set of edges
        set<SurfaceEdge> edges;
        
        
        
        
	};
	
	inline vector<Point3D> &TriMesh::getPoints(){
		return mVertices;
	}
	
	inline vector<double> &TriMesh::getBounds(){
		return bounds;
	}
	
	inline vector<SurfTriangle> &TriMesh::getFaces(){
		return mTriangles;
	}
    
    inline set<SurfaceEdge> &TriMesh::getEdges(){
        return edges;
    }
    
    inline vector<Point3D> &TriMesh::getVerticePseudoNormals(){
        return mVerticePseudoNormals;
    }
    
    inline Point3D TriMesh::getCentroid(){
		Point3D mCentroid;
		mCentroid.X() = (bounds[0]+bounds[3])/2;
        mCentroid.Y() = (bounds[1]+bounds[4])/2;
        mCentroid.Z() = (bounds[2]+bounds[5])/2;
		return mCentroid;
	}
	   
}
#endif
