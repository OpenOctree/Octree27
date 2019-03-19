#ifndef PointMovedVisitor_h
#define PointMovedVisitor_h 1

#include "../MeshPoint.h"
#include "../OctreeEdge.h"
#include "../Point3D.h"
#include "../SurfTriangle.h"
#include "../TriMesh.h"

#include <list>
#include <set>
#include <vector>

#include "Visitor.h"
#include "EdgeVisitor.h"

using Clobscode::TriMesh;
using Clobscode::Point3D;
using Clobscode::MeshPoint;
using Clobscode::OctreeEdge;
using SurfMesh::SurfTriangle;
using std::list;
using std::vector;
using std::set;

namespace Clobscode
{
    class PointMovedVisitor : public Visitor {
    public:
        PointMovedVisitor();

        bool visit(Octant *o);

        void setPoints(vector<MeshPoint> &points);
        void setEdges(const set<OctreeEdge> &edges);
        void setMaxRefLevel(const unsigned short &max_ref_level);

    private:
        vector<MeshPoint> *points;
        const set<OctreeEdge> *edges;
        const unsigned short *max_ref_level;
    };
}


#endif //MESHER_ROI_POINTMOVEDVISITOR_H
