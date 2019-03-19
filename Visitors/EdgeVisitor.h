#ifndef EdgeVisitor_h
#define EdgeVisitor_h 1

#include "../OctreeEdge.h"
#include "../Point3D.h"

#include <set>
#include <vector>

#include "Visitor.h"

using Clobscode::OctreeEdge;
using Clobscode::Point3D;
using std::set;
using std::vector;

namespace Clobscode
{
    class EdgeVisitor : public Visitor{
    public:
        static void insertEdges(Octant *o, set<OctreeEdge> &edges);
        static void getEdge(Octant *o, const unsigned long &idx, OctreeEdge &e);
    };

}


#endif //EdgeVisitor_h
