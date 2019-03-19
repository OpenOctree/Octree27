#ifndef RemoveSubElementsVisitor_h
#define RemoveSubElementsVisitor_h 1

#include "../OctreeEdge.h"
#include "../MeshPoint.h"
#include "../TriMesh.h"

#include "Visitor.h"

#include <list>
#include <set>
#include <vector>

using Clobscode::MeshPoint;
using Clobscode::OctreeEdge;
using Clobscode::TriMesh;
using std::list;
using std::set;
using std::vector;


namespace Clobscode
{
    class RemoveSubElementsVisitor : public Visitor{
    public:
        RemoveSubElementsVisitor();

        bool visit(Octant *o);

        void setPoints(vector<MeshPoint> &points);

    private:
        vector<MeshPoint> *points;
    };
}



#endif //MESHER_ROI_REMOVESUBELEMENTSVISITOR_H
