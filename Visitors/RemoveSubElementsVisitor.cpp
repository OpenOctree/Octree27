#include "RemoveSubElementsVisitor.h"
#include "../Octant.h"

namespace Clobscode
{

    RemoveSubElementsVisitor::RemoveSubElementsVisitor() {
        points = NULL;
    }

    void RemoveSubElementsVisitor::setPoints(vector<MeshPoint> &points) {
        this->points = &points;
    }

    bool RemoveSubElementsVisitor::visit(Octant *o) {
        //cout << "RemoveElements" << endl;
        vector<vector<unsigned long>> &sub_elements = o->sub_elements;

        list<vector<unsigned long> > still_in;
        list<vector<unsigned long> >::iterator iter;

        for (unsigned long i=0; i<sub_elements.size(); i++) {

            bool onein = false;
            vector<unsigned long> e_pts = sub_elements[i];
            for (unsigned long j=0; j<e_pts.size(); j++) {
                if (points->at(e_pts[j]).isInside()) {
                    onein = true;
                    break;
                }
            }
            if (onein) {
                still_in.push_back(sub_elements[i]);
            }
        }

        if (still_in.size()==sub_elements.size()) {
            return false;
        }
        if (still_in.empty()) {
            return true;
        }

        sub_elements.clear();
        sub_elements.reserve(still_in.size());
        for (iter=still_in.begin(); iter!=still_in.end(); iter++) {
            sub_elements.push_back(*iter);
        }
        return false;
    }
}