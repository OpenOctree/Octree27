#ifndef SplitVisitor_h
#define SplitVisitor_h 1

#include <list>
#include <set>
#include <vector>
#include <cmath>

#include "../MeshPoint.h"
#include "../Point3D.h"
#include "../OctreeEdge.h"

#include "Visitor.h"


using Clobscode::MeshPoint;
using Clobscode::OctreeEdge;
using Clobscode::Point3D;
using std::vector;
using std::list;
using std::set;


namespace Clobscode
{
    class SplitVisitor : public Visitor {

    public:
        SplitVisitor();
        /*void VisitOctant(Octant *o,
                         vector<MeshPoint> &points,
                         list<Point3D> &new_pts,
                         set<OctreeEdge> &edges,
                         vector< vector<unsigned long> > &new_eles,
                         vector<vector<Point3D> > &clipping);*/

        bool visit(Octant *o);

        void setPoints(vector<MeshPoint> &points);
        void setNewPts(list<Point3D> &new_pts);
        void setEdges(set<OctreeEdge> &edges);
        void setNewEles(vector<vector<unsigned long> > &new_eles);
        void setClipping(vector<vector<Point3D> > &clipping);

    protected:
        //references
        vector<MeshPoint> *points;
        list<Point3D> *new_pts;
        set<OctreeEdge> *edges;
        vector<vector<unsigned long> > *new_eles;
        vector<vector<Point3D> > *clipping;

        bool splitEdge(const unsigned long &idx1, const unsigned long &idx2,
                                  unsigned long &c_n_pts, unsigned long &mid_idx1, unsigned long &mid_idx2);

        bool splitFace(const unsigned long &idx1, const unsigned long &idx2,
                                  const unsigned long &idx3, const unsigned long &idx4,
                                  const unsigned long &idx5, const unsigned long &idx6,
                                  const unsigned long &idx7, const unsigned long &idx8,
                                  unsigned long &c_n_pts, unsigned long &mid_idx1, unsigned long &mid_idx2, unsigned long &mid_idx3, unsigned long &mid_idx4);
        
        double getAxis(double min, double max, float val);

    };
}



#endif //MESHER_ROI_SPLITVISITOR_H
