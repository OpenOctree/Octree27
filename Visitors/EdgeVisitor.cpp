#include "EdgeVisitor.h"
#include "../Octant.h"


namespace Clobscode
{

    void EdgeVisitor::insertEdges(Octant *o, set<OctreeEdge> &edges) {
        for (unsigned long i=0; i<12; i++) {
            OctreeEdge ee;
            getEdge(o,i,ee);
            edges.insert(ee);
        }
    }

    void EdgeVisitor::getEdge(Octant *o, const unsigned long &idx, OctreeEdge &e) {
        vector<unsigned long> pointindex = o->pointindex;
        unsigned long e0,e1;
        switch (idx) {
            case 0:
                e0 = pointindex[0];
                e1 = pointindex[1];
                break;
            case 1:
                e0 = pointindex[0];
                e1 = pointindex[3];
                break;
            case 2:
                e0 = pointindex[1];
                e1 = pointindex[2];
                break;
            case 3:
                e0 = pointindex[3];
                e1 = pointindex[2];
                break;
            case 4:
                e0 = pointindex[4];
                e1 = pointindex[5];
                break;
            case 5:
                e0 = pointindex[4];
                e1 = pointindex[7];
                break;
            case 6:
                e0 = pointindex[5];
                e1 = pointindex[6];
                break;
            case 7:
                e0 = pointindex[7];
                e1 = pointindex[6];
                break;
            case 8:
                e0 = pointindex[0];
                e1 = pointindex[4];
                break;
            case 9:
                e0 = pointindex[1];
                e1 = pointindex[5];
                break;
            case 10:
                e0 = pointindex[3];
                e1 = pointindex[7];
                break;
            case 11:
                e0 = pointindex[2];
                e1 = pointindex[6];
                break;
            default:
                break;
        }
        //cout << "EdgeVisitor found: " << e0 << " " << e1 << endl;
        e.assign(e0,e1);
    }
}