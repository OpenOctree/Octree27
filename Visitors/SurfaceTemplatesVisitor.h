#ifndef SurfaceTemplatesVisitor_h
#define SurfaceTemplatesVisitor_h 1

#include "../OctreeEdge.h"
#include "../MeshPoint.h"
#include "../TriMesh.h"

//#include "../TransitionTemplate.h"

#include "../SurfTemplate1.h"
#include "../SurfTemplate2.h"
#include "../SurfTemplate3.h"
#include "../SurfTemplate4.h"
#include "../SurfTemplate5.h"
#include "../SurfTemplate6.h"
#include "../SurfTemplate7.h"
#include "../SurfPrism.h"
#include "../SurfPyramid.h"
#include "../SurfTetrahedron.h"
#include "../SurfHexahedron.h"

#include "Visitor.h"
#include "EdgeVisitor.h"

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
    class SurfaceTemplatesVisitor : public Visitor {
    public:
        SurfaceTemplatesVisitor();

        bool visit(Octant *o);

        void setPoints(vector<MeshPoint> &meshpts);
        void setNewPoints(list<MeshPoint> &newpts);
        void setInput(TriMesh &input);
        void setIdx(unsigned long &e_idx);

    private:
        vector<MeshPoint> *meshpts;
        list<MeshPoint> *newpts;
        TriMesh *input;
        unsigned long *e_idx;

        bool applyHexSurfaceTemplates(Octant *o,
                                      vector<unsigned long> &inpts,
                                      vector<unsigned long> &outpts);
    };
}

#endif //MESHER_ROI_SURFACETEMPLATESVISITOR_H
