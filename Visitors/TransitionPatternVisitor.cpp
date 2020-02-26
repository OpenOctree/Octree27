#include "TransitionPatternVisitor.h"
#include "../Octant.h"

namespace Clobscode {

   TransitionPatternVisitor::TransitionPatternVisitor() {
      points = NULL;
      new_pts = NULL;
      edges = NULL;
      max_ref_level = NULL;
      apply_pattern = false;
      v_nodes = NULL;

      idxsRefinados = NULL;
      idxsVector = NULL;
      puntosVector = NULL;
      edges_to_refine = NULL;
   }

   TransitionPatternVisitor::TransitionPatternVisitor(bool apply_pattern) {
      points = NULL;
      new_pts = NULL;
      edges = NULL;
      max_ref_level = NULL;
      this->apply_pattern = apply_pattern;
      v_nodes = NULL;

      idxsRefinados = NULL;
      idxsVector = NULL;
      puntosVector = NULL;
      edges_to_refine = NULL;
   }

   void TransitionPatternVisitor::setPoints(vector<MeshPoint> &points) {
      this->points = &points;
   }

   void TransitionPatternVisitor::setNewPoints(list<Point3D> &new_pts) {
      this->new_pts = &new_pts;
   }

   void TransitionPatternVisitor::setEdges(const set<OctreeEdge> &edges) {
      this->edges = &edges;
   }

   void TransitionPatternVisitor::setMaxRefLevel(const unsigned short &max_ref_level) {
      this->max_ref_level = &max_ref_level;
   }

   void TransitionPatternVisitor::setApplyMode(bool apply_pattern){
      this->apply_pattern = apply_pattern;
   }

   void TransitionPatternVisitor::setVNodes(set<unsigned long> &v_nodes){ 
      this->v_nodes = &v_nodes; 
   } 

   void TransitionPatternVisitor::setPuntosExtras(vector<Point3D> &puntosVector, vector<unsigned long> &idxsVector, set<unsigned long> &idxsRefinados){
      this->puntosVector = &puntosVector;
      this->idxsVector = &idxsVector;
      this->idxsRefinados = &idxsRefinados;
   }

   bool TransitionPatternVisitor::visit(Octant *o) {
      //cout << "TransitionPatternVisitor" << endl;
      //applyTransitionPattern
      if (apply_pattern) {
         if (new_pts == NULL)
            throw std::runtime_error(std::string("TransitionPatternVisitor: need new_pts (calling apply instead of check?)"));
         //if this octant is refined to the maximum level, return it immediately
         if (*max_ref_level == o->ref_level) {
            return true;
         }
         vector<unsigned long> &pointindex = o->pointindex;
         EdgeVisitor ev; // TODO not used?

         vector<unsigned long> nodes, mid_nodes, tmp_nodes(24,0);
         list<unsigned long> l_nodes, l_mid_nodes;
         set<unsigned long> l_mid_nodes_v; 
         //insert the 8 nodes of the cube.
         //cout << "checking element";
         for (unsigned long i=0; i<8; i++) {
            //cout << " " << pointindex[i];
            l_nodes.push_back(pointindex[i]);
            if(idxsRefinados->find(pointindex[i]) != idxsRefinados->end()) {
               l_mid_nodes_v.insert(i);
            }
         }
         //cout << "\nInserted edges:\n";
         //search for nodes inserted in edges
         for (unsigned long i=0; i<12; i++) {
            OctreeEdge e;
            EdgeVisitor::getEdge(o,i,e);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge==edges->end()) {
               cout << "  edge " << e << " not found at applyTransitionPattern\n";
               return false;
            }
            if ((*my_edge)[2]!=0) {
               //cout << (*my_edge)[2] << ", " <<  (*my_edge)[3] << "(" << i << ") [";
               //cout << *my_edge << "]\n";
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);

               l_mid_nodes.push_back((i*2)+8);
               l_mid_nodes.push_back((i*2+1)+8);
               tmp_nodes[i*2]=(*my_edge)[2];
               tmp_nodes[i*2+1]=(*my_edge)[3];

               switch (i) {
                  case 0:
                     l_mid_nodes_v.insert(0);
                     l_mid_nodes_v.insert(1);
                     break;
                  case 1:
                     l_mid_nodes_v.insert(0);
                     l_mid_nodes_v.insert(3);
                     break;
                  case 2:
                     l_mid_nodes_v.insert(1);
                     l_mid_nodes_v.insert(2);
                     break;
                  case 3:
                     l_mid_nodes_v.insert(3);
                     l_mid_nodes_v.insert(2);
                     break;
                  case 4:
                     l_mid_nodes_v.insert(4);
                     l_mid_nodes_v.insert(5);
                     break;
                  case 5:
                     l_mid_nodes_v.insert(4);
                     l_mid_nodes_v.insert(7);
                     break;
                  case 6:
                     l_mid_nodes_v.insert(5);
                     l_mid_nodes_v.insert(6);
                     break;
                  case 7:
                     l_mid_nodes_v.insert(7);
                     l_mid_nodes_v.insert(6);
                     break;
                  case 8:
                     l_mid_nodes_v.insert(0);
                     l_mid_nodes_v.insert(4);
                     break;
                  case 9:
                     l_mid_nodes_v.insert(1);
                     l_mid_nodes_v.insert(5);
                     break;
                  case 10:
                     l_mid_nodes_v.insert(3);
                     l_mid_nodes_v.insert(7);
                     break;
                  case 11:
                     l_mid_nodes_v.insert(2);
                     l_mid_nodes_v.insert(6);
                     break;
                  default:
                     break;
               }           
            }
         }
         //if this elements do not present nodes inserted in its edges
         //then return true (meaning this case is already considered in
         //the transition patterns) and add this element to the vector
         //of "new elements"

         if (l_mid_nodes.empty()) {
            //cout << "element without mid nodes\n";
            //new_eles.push_back(pointindex);
            return true;
         }
            
         //cout << "looking for nodes inserted in faces:\n";
         if (tmp_nodes[0]!=0 && tmp_nodes[6]!=0) {
            //search for node 32 y 34
            OctreeEdge e(tmp_nodes[0],tmp_nodes[6]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(32);
               l_mid_nodes.push_back(34);
               //cout << *my_edge << "\n";
               //cout << "32 -> " << (*my_edge)[2] << "\n";
               //cout << "34 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[1]!=0 && tmp_nodes[7]!=0) {
            //search for node 33 y 35
            OctreeEdge e(tmp_nodes[1],tmp_nodes[7]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(33);
               l_mid_nodes.push_back(35);
               //cout << *my_edge << "\n";
               //cout << "33 -> " << (*my_edge)[2] << "\n";
               //cout << "35 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[0]!=0 && tmp_nodes[8]!=0) {
            //search for node 40 y 41
            OctreeEdge e(tmp_nodes[0],tmp_nodes[8]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(40);
               l_mid_nodes.push_back(41);
               //cout << *my_edge << "\n";
               //cout << "40 -> " << (*my_edge)[2] << "\n";
               //cout << "41 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[1]!=0 && tmp_nodes[9]!=0) {
            //search for node 42 y 43
            OctreeEdge e(tmp_nodes[1],tmp_nodes[9]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(42);
               l_mid_nodes.push_back(43);
               //cout << *my_edge << "\n";
               //cout << "42 -> " << (*my_edge)[2] << "\n";
               //cout << "43 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[2]!=0 && tmp_nodes[10]!=0) {
            //search for node 44 y 45
            OctreeEdge e(tmp_nodes[2],tmp_nodes[10]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(44);
               l_mid_nodes.push_back(45);
               //cout << *my_edge << "\n";
               //cout << "44 -> " << (*my_edge)[2] << "\n";
               //cout << "45 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[3]!=0 && tmp_nodes[11]!=0) {
            //search for node 46 y 47
            OctreeEdge e(tmp_nodes[3],tmp_nodes[11]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(46);
               l_mid_nodes.push_back(47);
               //cout << *my_edge << "\n";
               //cout << "46 -> " << (*my_edge)[2] << "\n";
               //cout << "47 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[4]!=0 && tmp_nodes[12]!=0) {
            //search for node 48 y 49
            OctreeEdge e(tmp_nodes[4],tmp_nodes[12]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(48);
               l_mid_nodes.push_back(49);
               //cout << *my_edge << "\n";
               //cout << "48 -> " << (*my_edge)[2] << "\n";
               //cout << "49 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[5]!=0 && tmp_nodes[13]!=0) {
            //search for node 50 y 51
            OctreeEdge e(tmp_nodes[5],tmp_nodes[13]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(50);
               l_mid_nodes.push_back(51);
               //cout << *my_edge << "\n";
               //cout << "50 -> " << (*my_edge)[2] << "\n";
               //cout << "51 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[6]!=0 && tmp_nodes[14]!=0) {
            //search for node 52 y 53
            OctreeEdge e(tmp_nodes[6],tmp_nodes[14]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(52);
               l_mid_nodes.push_back(53);
               //cout << *my_edge << "\n";
               //cout << "52 -> " << (*my_edge)[2] << "\n";
               //cout << "53 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[7]!=0 && tmp_nodes[15]!=0) {
            //search for node 54 y 55
            OctreeEdge e(tmp_nodes[7],tmp_nodes[15]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(54);
               l_mid_nodes.push_back(55);
               //cout << *my_edge << "\n";
               //cout << "54 -> " << (*my_edge)[2] << "\n";
               //cout << "55 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[8]!=0 && tmp_nodes[14]!=0) {
            //search for node 36 y 38
            OctreeEdge e(tmp_nodes[8],tmp_nodes[14]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(36);
               l_mid_nodes.push_back(38);
               //cout << *my_edge << "\n";
               //cout << "36 -> " << (*my_edge)[2] << "\n";
               //cout << "38 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[9]!=0 && tmp_nodes[15]!=0) {
            //search for node 37 y 39
            OctreeEdge e(tmp_nodes[9],tmp_nodes[15]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(37);
               l_mid_nodes.push_back(39);
               //cout << *my_edge << "\n";
               //cout << "37 -> " << (*my_edge)[2] << "\n";
               //cout << "39 -> " << (*my_edge)[3] << "\n";
            }
         }
         //The middle node of the hexahedron can never be inserted
         //otherwise this octant was already removed from the list
         //of elements and replaced with the new 8 octants

         //------------------------------------------------------
         //Finally, apply the transition pattern
         //------------------------------------------------------

         //add the indexes to the vectors
         list<unsigned long>::iterator ui_iter;
         nodes.reserve(l_nodes.size());
         for (ui_iter = l_nodes.begin(); ui_iter!=l_nodes.end(); ui_iter++) {
            nodes.push_back(*ui_iter);
         }
         mid_nodes.reserve(l_mid_nodes.size());
         for (ui_iter=l_mid_nodes.begin(); ui_iter!=l_mid_nodes.end(); ui_iter++) {
            mid_nodes.push_back(*ui_iter);
         }

         // Create the pattern
         patterns::TransitionTemplate tt (nodes, mid_nodes, l_mid_nodes_v);
         tt.setAssociationTable(assoc_table_name);
         //new points goes to new_pts (if any new node is inserted) and
         //the new elements to new_eles

         //the subelements of this octant will no longer be the points
         //of the original cube. It will now contain mixed-elements.
         vector<vector<unsigned long>> &sub_elements = o->sub_elements;
         sub_elements.clear();

         unsigned long old_size = new_pts->size();

         unsigned long  succeed = tt.getNewElements(nodes,mid_nodes,*points,*new_pts,sub_elements,l_mid_nodes_v, *puntosVector, *idxsVector, false);

         if (succeed != 0) {
            pointindex.clear();
            pointindex.reserve(l_nodes.size());
            for (ui_iter = l_nodes.begin(); ui_iter!=l_nodes.end(); ui_iter++) {
               pointindex.push_back(*ui_iter);
            }

            if (new_pts->size()!=old_size) {
               pointindex.push_back(points->size() + old_size);
            }
            return true;
         }
         return false;
      }
      //checkTransitionPattern
      else {
         if (*max_ref_level==o->ref_level) {
            return true;
         }
         vector<unsigned long> &pointindex = o->pointindex;

         vector<unsigned long> nodes, mid_nodes, tmp_nodes(24,0);
         list<unsigned long> l_nodes, l_mid_nodes;
         set<unsigned long> l_mid_nodes_v; 
         //insert the 8 nodes of the cube.
         //cout << "checking element";

         for (unsigned long i=0; i<8; i++) {
            //cout << " " << pointindex[i];
            l_nodes.push_back(pointindex[i]);
            if(idxsRefinados->find(pointindex[i]) != idxsRefinados->end()) {
               l_mid_nodes_v.insert(i);
            }
         }
         //cout << "\nInserted edges:\n";
         //search for nodes inserted in edges
         for (unsigned long i=0; i<12; i++) {
            OctreeEdge e;
            EdgeVisitor::getEdge(o,i,e);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge==edges->end()) {
               cout << "  edge " << e << " not found at applyTransitionPattern\n";
               return false;
            }
            if ((*my_edge)[2]!=0) {
               //cout << (*my_edge)[2] << ", " <<  (*my_edge)[3] << "(" << i << ") [";
               //cout << *my_edge << "]\n";
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);

               l_mid_nodes.push_back((i*2)+8);
               l_mid_nodes.push_back((i*2+1)+8);
               tmp_nodes[i*2]=(*my_edge)[2];
               tmp_nodes[i*2+1]=(*my_edge)[3];

               switch (i) {
                  case 0:
                     l_mid_nodes_v.insert(0);
                     l_mid_nodes_v.insert(1);
                     break;
                  case 1:
                     l_mid_nodes_v.insert(0);
                     l_mid_nodes_v.insert(3);
                     break;
                  case 2:
                     l_mid_nodes_v.insert(1);
                     l_mid_nodes_v.insert(2);
                     break;
                  case 3:
                     l_mid_nodes_v.insert(3);
                     l_mid_nodes_v.insert(2);
                     break;
                  case 4:
                     l_mid_nodes_v.insert(4);
                     l_mid_nodes_v.insert(5);
                     break;
                  case 5:
                     l_mid_nodes_v.insert(4);
                     l_mid_nodes_v.insert(7);
                     break;
                  case 6:
                     l_mid_nodes_v.insert(5);
                     l_mid_nodes_v.insert(6);
                     break;
                  case 7:
                     l_mid_nodes_v.insert(7);
                     l_mid_nodes_v.insert(6);
                     break;
                  case 8:
                     l_mid_nodes_v.insert(0);
                     l_mid_nodes_v.insert(4);
                     break;
                  case 9:
                     l_mid_nodes_v.insert(1);
                     l_mid_nodes_v.insert(5);
                     break;
                  case 10:
                     l_mid_nodes_v.insert(3);
                     l_mid_nodes_v.insert(7);
                     break;
                  case 11:
                     l_mid_nodes_v.insert(2);
                     l_mid_nodes_v.insert(6);
                     break;
                  default:
                     break;
               }           
            }
         }
         //if this elements do not present nodes inserted in its edges
         //then return true (meaning this case is already considered in
         //the transition patterns) and add this element to the vector
         //of "new elements"

         if (l_mid_nodes.empty()) {
            //cout << "element without mid nodes\n";
            //new_eles.push_back(pointindex);
            return true;
         }
            

         //at this point the element has at least one node inserted in
         //an edge and we need to search for nodes inserted as middle
         //nodes of their faces
         //                       -----10-------11------ 
         //                     /                      /
         //                    /                      /   
         //                   8     36       38     14
         //                  /                      /
         //                 /                      /
         //                9     37       39     15
         //               /                      /
         //              /                      /
         //              -----12--------13----- 
         //                      17----45-------47------21
         //                     /                      /
         //                    /                      /   
         //                  41     60       62      53
         //                  /                      /
         //                 /                      /
         //               43     61       63     55
         //               /                      /
         //              /                      /
         //            19-----49-------51------23
         //                      16----44-------46------20
         //                     /                      /
         //                    /                      /   
         //                  40     56       58      52
         //                  /                      /
         //                 /                      /
         //               42     57       59      54
         //               /                      /
         //              /                      /            y   
         //            18-----48-------50------22            |  
         //                       ----2-------3-------     0 ---x
         //                     /                      /    /
         //                    /                      /    z
         //                   0     32       34      6
         //                  /                      /
         //                 /                      /
         //                1     33       35      7
         //               /                      /
         //              /                      /
         //              -----4--------5----- 
         //cout << "looking for nodes inserted in faces:\n";
         if (tmp_nodes[0]!=0 && tmp_nodes[6]!=0) {
            //search for node 32 y 34
            OctreeEdge e(tmp_nodes[0],tmp_nodes[6]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(32);
               l_mid_nodes.push_back(34);
               //cout << *my_edge << "\n";
               //cout << "32 -> " << (*my_edge)[2] << "\n";
               //cout << "34 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[1]!=0 && tmp_nodes[7]!=0) {
            //search for node 33 y 35
            OctreeEdge e(tmp_nodes[1],tmp_nodes[7]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(33);
               l_mid_nodes.push_back(35);
               //cout << *my_edge << "\n";
               //cout << "33 -> " << (*my_edge)[2] << "\n";
               //cout << "35 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[0]!=0 && tmp_nodes[8]!=0) {
            //search for node 40 y 41
            OctreeEdge e(tmp_nodes[0],tmp_nodes[8]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(40);
               l_mid_nodes.push_back(41);
               //cout << *my_edge << "\n";
               //cout << "40 -> " << (*my_edge)[2] << "\n";
               //cout << "41 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[1]!=0 && tmp_nodes[9]!=0) {
            //search for node 42 y 43
            OctreeEdge e(tmp_nodes[1],tmp_nodes[9]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(42);
               l_mid_nodes.push_back(43);
               //cout << *my_edge << "\n";
               //cout << "42 -> " << (*my_edge)[2] << "\n";
               //cout << "43 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[2]!=0 && tmp_nodes[10]!=0) {
            //search for node 44 y 45
            OctreeEdge e(tmp_nodes[2],tmp_nodes[10]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(44);
               l_mid_nodes.push_back(45);
               //cout << *my_edge << "\n";
               //cout << "44 -> " << (*my_edge)[2] << "\n";
               //cout << "45 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[3]!=0 && tmp_nodes[11]!=0) {
            //search for node 46 y 47
            OctreeEdge e(tmp_nodes[3],tmp_nodes[11]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(46);
               l_mid_nodes.push_back(47);
               //cout << *my_edge << "\n";
               //cout << "46 -> " << (*my_edge)[2] << "\n";
               //cout << "47 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[4]!=0 && tmp_nodes[12]!=0) {
            //search for node 48 y 49
            OctreeEdge e(tmp_nodes[4],tmp_nodes[12]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(48);
               l_mid_nodes.push_back(49);
               //cout << *my_edge << "\n";
               //cout << "48 -> " << (*my_edge)[2] << "\n";
               //cout << "49 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[5]!=0 && tmp_nodes[13]!=0) {
            //search for node 50 y 51
            OctreeEdge e(tmp_nodes[5],tmp_nodes[13]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(50);
               l_mid_nodes.push_back(51);
               //cout << *my_edge << "\n";
               //cout << "50 -> " << (*my_edge)[2] << "\n";
               //cout << "51 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[6]!=0 && tmp_nodes[14]!=0) {
            //search for node 52 y 53
            OctreeEdge e(tmp_nodes[6],tmp_nodes[14]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(52);
               l_mid_nodes.push_back(53);
               //cout << *my_edge << "\n";
               //cout << "52 -> " << (*my_edge)[2] << "\n";
               //cout << "53 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[7]!=0 && tmp_nodes[15]!=0) {
            //search for node 54 y 55
            OctreeEdge e(tmp_nodes[7],tmp_nodes[15]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(54);
               l_mid_nodes.push_back(55);
               //cout << *my_edge << "\n";
               //cout << "54 -> " << (*my_edge)[2] << "\n";
               //cout << "55 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[8]!=0 && tmp_nodes[14]!=0) {
            //search for node 36 y 38
            OctreeEdge e(tmp_nodes[8],tmp_nodes[14]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(36);
               l_mid_nodes.push_back(38);
               //cout << *my_edge << "\n";
               //cout << "36 -> " << (*my_edge)[2] << "\n";
               //cout << "38 -> " << (*my_edge)[3] << "\n";
            }
         }
         if (tmp_nodes[9]!=0 && tmp_nodes[15]!=0) {
            //search for node 37 y 39
            OctreeEdge e(tmp_nodes[9],tmp_nodes[15]);
            set<OctreeEdge>::iterator my_edge = edges->find(e);
            if (my_edge != edges->end() && (*my_edge)[2]!=0) {
               l_nodes.push_back((*my_edge)[2]);
               l_nodes.push_back((*my_edge)[3]);
               l_mid_nodes.push_back(37);
               l_mid_nodes.push_back(39);
               //cout << *my_edge << "\n";
               //cout << "37 -> " << (*my_edge)[2] << "\n";
               //cout << "39 -> " << (*my_edge)[3] << "\n";
            }
         }
         //The middle node of the hexahedron can never be inserted
         //otherwise this octant was already removed from the list
         //of elements and replaced with the new 8 octants

         //------------------------------------------------------
         //Finally, apply the transition pattern
         //------------------------------------------------------

         //add the indexes to the vectors
         list<unsigned long>::iterator ui_iter;
         nodes.reserve(l_nodes.size());
         for (ui_iter = l_nodes.begin(); ui_iter!=l_nodes.end(); ui_iter++) {
            nodes.push_back(*ui_iter);
         }
         mid_nodes.reserve(l_mid_nodes.size());
         for (ui_iter=l_mid_nodes.begin(); ui_iter!=l_mid_nodes.end(); ui_iter++) {
            mid_nodes.push_back(*ui_iter);
         }
         //temporal new points, but they won't be inserted. It's just
         //to see if the pattern for this configuration is already implemented
         list<Point3D> local_new_pts;

         vector<vector<unsigned long> > new_eles;
         list<MeshPoint> new_pts;

         patterns::TransitionTemplate tt (nodes,mid_nodes, l_mid_nodes_v);
         tt.setAssociationTable(assoc_table_name);
         //find out if the pattern is implemented
            
         unsigned long result = tt.getNewElements(nodes,mid_nodes,*points,local_new_pts,new_eles,l_mid_nodes_v, *puntosVector, *idxsVector, true);
            
         if(result == 0){ // <- Esto significa que no hay patron de transición
            // DEBUG
            //for(auto it : l_mid_nodes_v) {
            //   idxsRefinados->insert(pointindex[it]);
            //}
            return false;
         }
         else{
            //for(auto it : l_mid_nodes_v) {
            //   idxsRefinados->insert(pointindex[it]);
            //}
            
            tt.getEdgesToRefine(edges_to_refine);
            return true;
         }
      }
   }
}
