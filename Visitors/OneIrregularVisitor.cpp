#include "OneIrregularVisitor.h"

#include "../Octant.h"

namespace Clobscode
{

    OneIrregularVisitor::OneIrregularVisitor() {
        edges = NULL;
        max_ref_level = NULL;
    }

    void OneIrregularVisitor::setEdges(set<OctreeEdge> &edges) {
        this->edges = &edges;
    }

    void OneIrregularVisitor::setMaxRefLevel(const unsigned short &max_ref_level) {
        this->max_ref_level = &max_ref_level;
    }

    bool OneIrregularVisitor::visit(Octant *o) {
        //cout << "OneIrregular visit" << endl;
        if (*max_ref_level==o->ref_level) {
            return true;
        }

        //EdgeVisitor ev;
        for (unsigned long i=0; i<12; i++) {
            OctreeEdge ee;
            EdgeVisitor::getEdge(o,i,ee);
            set<OctreeEdge>::iterator my_edge, sub_edge;
            my_edge = edges->find(ee);
            if (my_edge==edges->end()) {
                cout << "Octant::isOneIrregular wtf!!!\n";
                return false;
            }

            unsigned long mid_idx = (*my_edge)[2];
            unsigned long mid_idx2 = (*my_edge)[3];

            //if the edge is not split, check the others
            if (mid_idx==0) {
                continue;
            }
            //At this point, the edge is split so both
            //"sub-edges" must be checked. If at least one of
            //them is also split, then this element is not
            //one-irregular

            OctreeEdge sub1(ee[0],mid_idx);
            sub_edge = edges->find(sub1);
            if ((*sub_edge)[2]!=0) {
                return false;
            }

            OctreeEdge sub2(mid_idx,mid_idx2);
            sub_edge = edges->find(sub2);
            if ((*sub_edge)[2]!=0) {
                return false;
            }

            OctreeEdge sub3(mid_idx2, ee[1]);
            sub_edge = edges->find(sub3);
            if ((*sub_edge)[2]!=0) {
                return false;
            }
        }
        return true;
    }
}
