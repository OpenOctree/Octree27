#include "PointMovedVisitor.h"
#include "../Octant.h"

namespace Clobscode
{
    
    PointMovedVisitor::PointMovedVisitor() {
        points = NULL;
        edges = NULL;
        max_ref_level = NULL;
    }

    
    void PointMovedVisitor::setPoints(vector<MeshPoint> &points) {      
        this->points = &points;
    }


    void PointMovedVisitor::setEdges(const set<OctreeEdge> &edges) {
        this->edges = &edges;
    }

    void PointMovedVisitor::setMaxRefLevel(const unsigned short &max_ref_level) {
        this->max_ref_level = &max_ref_level;
    }

    bool PointMovedVisitor::visit(Octant *o) {
        unsigned short ref_level = o->ref_level;
        vector<unsigned long> pointindex = o->pointindex;

        //when the octant has at least one point that has been
        //projected into the input surface, the transition
        //patterns may cause some topology and quality problems.
        //For these reasons, an octant under these conditions
        //should be refined one more level.

        if (*max_ref_level==ref_level) {
            return false;
        }

        //check if any of the cube nodes been moved.
        for (unsigned long i=0; i<pointindex.size(); i++) {
            if (points->at(pointindex[i]).isOutside()) {
                return true;
            }
        }

        vector<unsigned long> mid_nodes, tmp_nodes(12,0);

        //check if any of the mid edge nodes been moved.
        EdgeVisitor ev;
        for (unsigned long i=0; i<12; i++) {
            OctreeEdge ee;
            ev.getEdge(o,i,ee);
            set<OctreeEdge>::iterator my_edge = edges->find(ee);
            //if the edge doesn't exist return false,
            //but this should be considered as an error.
            if (my_edge==edges->end()) {
                cout << "Octant::isOneIrregular wtf!!!\n";
                cout.flush();
                return false;
            }

            unsigned long mid_idx = (*my_edge)[2];
            tmp_nodes[i]=(*my_edge)[2];

            //if the edge is not split or under this iteration
            //of the refinement was split, check the others
            if (mid_idx==0 || mid_idx>=points->size()) {
                continue;
            }

            if (points->at(mid_idx).isOutside()) {
                return true;
            }
        }

        //check if any of the mid face nodes been moved.
        if (tmp_nodes[0]!=0 && tmp_nodes[2]!=0) {
            //search for node 20
            OctreeEdge e(tmp_nodes[0],tmp_nodes[2]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
                if ((*my_edge)[2]<points->size()) {
                    if (points->at((*my_edge)[2]).isOutside()) {
                        return true;
                    }
                }
            }
        }
        if (tmp_nodes[0]!=0 && tmp_nodes[8]!=0) {
            //search for node 21
            OctreeEdge e(tmp_nodes[0],tmp_nodes[8]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
                if ((*my_edge)[2]<points->size()) {
                    if (points->at((*my_edge)[2]).isOutside()) {
                        return true;
                    }
                }
            }
        }
        if (tmp_nodes[1]!=0 && tmp_nodes[9]!=0) {
            //search for node 22
            OctreeEdge e(tmp_nodes[1],tmp_nodes[9]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
                if ((*my_edge)[2]<points->size()) {
                    if (points->at((*my_edge)[2]).isOutside()) {
                        return true;
                    }
                }
            }
        }
        if (tmp_nodes[2]!=0 && tmp_nodes[10]!=0) {
            //search for node 23
            OctreeEdge e(tmp_nodes[2],tmp_nodes[10]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
                if ((*my_edge)[2]<points->size()) {
                    if (points->at((*my_edge)[2]).isOutside()) {
                        return true;
                    }
                }
            }
        }
        if (tmp_nodes[3]!=0 && tmp_nodes[11]!=0) {
            //search for node 24
            OctreeEdge e(tmp_nodes[3],tmp_nodes[11]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
                if ((*my_edge)[2]<points->size()) {
                    if (points->at((*my_edge)[2]).isOutside()) {
                        return true;
                    }
                }
            }
        }
        if (tmp_nodes[9]!=0 && tmp_nodes[11]!=0) {
            //search for node 25
            OctreeEdge e(tmp_nodes[9],tmp_nodes[11]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
                if ((*my_edge)[2]<points->size()) {
                    if (points->at((*my_edge)[2]).isOutside()) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}
