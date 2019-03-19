#ifndef OneIrregularVisitor_h
#define OneIrregularVisitor_h 1

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

namespace Clobscode
{
    class OneIrregularVisitor : public Visitor {
    public:
        OneIrregularVisitor();

        bool visit(Octant *o);

        void setEdges(set<OctreeEdge> &edges);
        void setMaxRefLevel(const unsigned short &max_ref_level);

    protected:
        set<OctreeEdge> *edges;
        const unsigned short *max_ref_level;
    };

}


#endif //MESHER_ROI_ONEIRREGULARVISITOR_H
