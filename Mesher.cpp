//#include "stdafx.h"
#include "Mesher.h"
#include <math.h>

/** /
//debug
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
/**/

namespace Clobscode
{
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	Mesher::Mesher(){
        
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	Mesher::~Mesher(){
		
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	//Create a grid mesh regarding the Bounding Box of input mesh.
	//This will produce several cubes as roots of an octree structure.
	//Then split each initial element 8^rl times (where rl stands
	//for Refinement Level).
	
	FEMesh Mesher::generateMesh(void * pClientData,TriMesh &input,
								const unsigned short &rl,
								const string &name,
								list<RefinementRegion *> &all_reg){

		GeometricTransform gt;
        
		//rotate
		bool rotated = rotateGridMesh(input, all_reg, gt);
        
		//generate root octants
		generateGridMesh(input);
		
		//split octants until the refinement level (rl) is achieved.
		//The output will be a one-irregular mesh.
		generateOctreeMesh(rl,input,all_reg,name);
		
		//link element and node info for code optimization.
		linkElementsToNodes();
		detectInsideNodes(input);
        
        //projectCloseToBoundaryNodes(input);
   		//removeOnSurface();
		
		//apply the surface Patterns
		//applySurfacePatterns(input);
        //removeOnSurface();
        
        /*{
            Clobscode::CoteMarek marek;
            //save pure octree mesh
            FEMesh surf;
            saveOutputMesh(surf);
            string tmp_name = name + "_surfPatt";
            marek.WriteOutputMesh(tmp_name,surf);
        }*/
        
        //projectCloseToBoundaryNodes(input);
		//removeOnSurface();
				
        //detectInsideNodes(input);
        
		//update element and node info.
		//linkElementsToNodes();
        
		//shrink outside nodes to the input domain boundary
		//shrinkToBoundary(input);
        
        /*{
            Clobscode::CoteMarek marek;
            //save pure octree mesh
            FEMesh rot;
            saveOutputMesh(rot);
            string tmp_name = name + "_finalRotated";
            marek.WriteOutputMesh(tmp_name,rot);
        }*/
        
		//the almighty output mesh
		FEMesh mesh;
        
        if (rotated) {
            for (unsigned long i=0; i<points.size(); i++) {
                //doing the translation and rotations back only if rotations were done before
                gt.applyInverse(points[i].getPoint());
            }
        }
		
		//save the data of the mesh
		saveOutputMesh(mesh);
		
		return mesh;
	}
    //--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	bool Mesher::rotateGridMesh(TriMesh &input, list<RefinementRegion *> &all_reg,
								GeometricTransform &gt){
        
        //return false;
        
        list<RefinementRegion *>::iterator it;
        bool inputHasbeenRotated = false;
        
        

        for (it = all_reg.begin(); it!=all_reg.end(); it++) {
            //in case of input roi
            if((*it)->needsInputRotation()){
                if(!inputHasbeenRotated){
                    gt = (*it)->rotateWithinYou(input);
                    inputHasbeenRotated = true;
                    continue;
                }
            }
            
            if ((*it)->needsLocalRotation() &&inputHasbeenRotated) {
                (*it)->rotate(gt);
            }
        }
        
        
        /*if (all_reg.size()>=1){
            for (it = all_reg.begin(); it!=all_reg.end(); it++) {
                //in case of input roi
                if ((*it)->needsInputRotation() && (*it)->needsLocalRotation()) {
                    if(!inputHasbeenRotated){
                        gt = (*it)->rotateWithinYou(input);
                        inputHasbeenRotated = true;
                    }
                }
                //in case of cube region
                else if (!((*it)->needsInputRotation()) && (*it)->needsLocalRotation()) {
                    if(!inputHasbeenRotated){
                        break;
                    }
                    else (*it)->rotate(gt);
                }
            }
		}
		//in case the entire input mesh is refined 
		else{
			if((*it)->needsInputRotation()){
				gt = (*it)->rotateWithinYou(input);
			}	
		}*/

        return inputHasbeenRotated;
	}
    
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
   void Mesher::generateOctreeMesh(const unsigned short &rl, TriMesh &input,
                                    list<RefinementRegion *> &all_reg,
                                    const string &name){

      //to save m3d files per stage
      Clobscode::CoteMarek marek;

      //list of temp octants
      list<Octant> tmp_octants, new_octants;
      //list of the points added at this refinement iteration:
      list<Point3D> new_pts;

      list<Octant>::iterator iter;

      for (unsigned long i=0; i<octants.size(); i++) {
         tmp_octants.push_back(octants[i]);
      }

      //create visitors and give them variables
      SplitVisitor sv;
      sv.setPoints(points);
      sv.setEdges(octreeEdges);
      sv.setNewPts(new_pts);

      //----------------------------------------------------------
      //refine each octant until the Refinement Level is reached
      //----------------------------------------------------------
      cout << "  > refining the mesh ...";
         cout.flush();

      for (unsigned short i=0; i<rl; i++) {
         //the new_pts is a list that holds the coordinates of
         //new points inserted at this iteration. At the end of
         //this bucle, they are inserted in the point vector
         new_pts.clear();
         list<RefinementRegion *>::iterator reg_iter;
         //split the octants as needed
         for (iter=tmp_octants.begin(); iter!=tmp_octants.end(); iter++) {
            bool to_refine = false;
            for (reg_iter=all_reg.begin(); reg_iter!=all_reg.end(); reg_iter++) {
               unsigned short this_rl = (*reg_iter)->getRefinementLevel();
               //If the region has lower RL than the curren step.
               if (this_rl<i) {
                  continue;
               }
               //If the octant has a greater RL than the region needs, continue
               if (this_rl<=(*iter).getRefinementLevel()) {
                  continue;
               }
               //Get the two extreme nodes of the octant to test intersection with
               //this RefinementRegion. If not, conserve it as it is.
               //unsigned long n_idx1 = (*iter).getPoints()[0];
               //unsigned long n_idx2 = (*iter).getPoints()[6];
               if ((*reg_iter)->intersectsOctant(points,*iter)) {
                  to_refine = true;
               }
            }
            //now if refinement is not needed, we add the octant as it was.
            if (!to_refine) {
               new_octants.push_back(*iter);
               continue;
            }
            else {
               list<unsigned long> inter_faces = iter->getIntersectedFaces();
               vector<vector<Point3D> > clipping_coords;
               sv.setClipping(clipping_coords);
               vector<vector<unsigned long> > split_elements;
               sv.setNewEles(split_elements);

               //iter->split(points,new_pts,octreeEdges,split_elements,clipping_coords);
               //cout << "Accept" << endl;
               iter->accept(&sv);

               if (inter_faces.empty()) {
                  for (unsigned long j=0; j<split_elements.size(); j++) {
                     Octant o (split_elements[j],i+1);
                     new_octants.push_back(o);
                  }
               }
               else {
                  for (unsigned long j=0; j<split_elements.size(); j++) {
                     Octant o (split_elements[j],i+1);
                     //the new points are inserted in bash at the end of this
                     //iteration. For this reason, the coordinates must be passed
                     //"manually" at this point (clipping_coords).

                     //select_faces = true
                     IntersectionsVisitor iv(true);
                     //if (o.checkIntersections(input,inter_faces,clipping_coords[j]))
                     iv.setTriMesh(input);
                     iv.setFaces(inter_faces);
                     iv.setCoords(clipping_coords[j]);

                     if (o.accept(&iv)) {
                        new_octants.push_back(o);
                     }
                     else {
                        //The element doesn't intersect any input face.
                        //It must be checked if it's inside or outside.
                        //Only in the first case add it to new_octants.
                        //Test this with parent octant faces only.

                        //Comment the following lines of this 'else' if
                        //only intersecting octants are meant to be
                        //displayed.

                           //note: inter_faces is quite enough to check if
                           //element is inside input, no octant needed,
                           //so i moved the method to mesher  --setriva

                        if (isItIn(input,inter_faces,clipping_coords[j])) {
                           new_octants.push_back(o);
                        }
/** /
                        //DEBUG Descomentar para que no elimine octante
                        else{
                           cout << "\nelimina octante [1]: {";
                           vector<unsigned long> pix = o.getPoints();
                           std::copy(pix.begin(), pix.end(), std::ostream_iterator<unsigned long>(std::cout, ", "));
                           cout << "}" << endl;
                           new_octants.push_back(o);
                        }
/**/
                     }
                  }
               }
            }
         }
         //remove the old octants
         tmp_octants.clear();
         tmp_octants = new_octants;
         new_octants.clear();
         //if no points were added at this iteration, it is no longer
         //necessary to continue the refinement.
         if (new_pts.empty()) {
            cout << "wtf!!!\n";
            break;
         }
         //add the new points to the vector
         list<Point3D>::iterator piter;
         points.reserve(points.size() + new_pts.size());
         for (piter=new_pts.begin(); piter!=new_pts.end(); piter++) {
            points.push_back(MeshPoint (*piter));
         }
      }
      cout << " done\n";

      //----------------------------------------------------------
      //produce a one-irregular mesh
      //----------------------------------------------------------
      cout << "  > producing one-irregular mesh ...";
      cout.flush();

      bool one_irregular = false;
      new_octants.clear();

      //visitante oneIrregular
      OneIrregularVisitor oiv;
      oiv.setEdges(octreeEdges);
      oiv.setMaxRefLevel(rl);

      //visitante TransitionPattern in check mode
      //(we'll reuse it in apply mode later)
      TransitionPatternVisitor tpv(false);
      tpv.setPoints(points);
      tpv.setEdges(octreeEdges);
      tpv.setMaxRefLevel(rl);
      tpv.setPuntosExtras(puntosVector, idxsVector, idxsRefinados); //Contadores de puntos extras agregados por los patrones
 
      while (!one_irregular) {
         one_irregular = true;
         new_pts.clear();
         //refine until the mesh is one-irregular
         for (iter=tmp_octants.begin(); iter!=tmp_octants.end(); iter++) {
            if (!(*iter).accept(&oiv) || !(*iter).accept(&tpv)) {
               //split this octant
               vector<vector<Point3D> > clipping_coords;
               sv.setClipping(clipping_coords);
               vector< vector <unsigned long> > split_elements;
               sv.setNewEles(split_elements);
               list<unsigned long> inter_faces = (*iter).getIntersectedFaces();
               //(*iter).split(points,new_pts,octreeEdges,split_elements,clipping_coords);
               //split the octant
               iter->accept(&sv);
               unsigned short prl = (*iter).getRefinementLevel();
               //cout << "Refinement level: " << prl << endl;
               //insert the new elements
               for (unsigned long j=0; j<split_elements.size(); j++) {
                  Octant o (split_elements[j],prl+1);
                  if (inter_faces.empty()) {
                     new_octants.push_back(o);
                     continue;
                  }
                  //select_faces = true
                  IntersectionsVisitor iv(true);
                  //if (o.checkIntersections(input,inter_faces,clipping_coords[j]))
                  iv.setTriMesh(input);
                  iv.setFaces(inter_faces);
                  iv.setCoords(clipping_coords[j]);
                  if (o.accept(&iv)) {
                     new_octants.push_back(o);
                  } else {
                     if (isItIn(input,inter_faces,clipping_coords[j])) {
                        new_octants.push_back(o);
                     }
                  }
               }
               one_irregular = false;
            }
            else {
               new_octants.push_back(*iter);
            }
         }

         if (one_irregular) {
            break;
         }
         //remove the old octants
         tmp_octants.clear();
         tmp_octants = new_octants;
         new_octants.clear();
         //if no points were added at this iteration, it is no longer
         //necessary to continue the refinement.
         if (new_pts.empty()) {
            break;
         }
         //add the new points to the vector
         list<Point3D>::iterator piter;
         points.reserve(points.size() + new_pts.size());
         for (piter=new_pts.begin(); piter!=new_pts.end(); piter++) {
            points.push_back(MeshPoint (*piter));
         }
      }

      //----------------------------------------------------------
      // apply transition patterns
      //----------------------------------------------------------
      cout << " done\n  > applying transition patterns ...";
      cout.flush();

      //clean tmp point list
      new_pts.clear();
      //new_octants.clear();

      //change TransitionPatternVisitor mode to apply pattern
      tpv.setApplyMode(true);
      tpv.setNewPoints(new_pts);
      for (iter = tmp_octants.begin(); iter!=tmp_octants.end(); iter++) {
         //vector<vector <unsigned long> > trs_ele;
         //if (!(*iter).applyTransitionPattern(points,new_pts,octreeEdges,rl)) {
         if (!(*iter).accept(&tpv)) {
            std::cerr << "Error at Mesher::generateOctreeMesh";
            std::cerr << " Transition Pattern not found\n";
         }
      }
      //
      if (!new_pts.empty()) {
         //add the new points to the vector
         list<Point3D>::iterator piter;
         points.reserve(points.size() + new_pts.size());
         for (piter=new_pts.begin(); piter!=new_pts.end(); piter++) {
            points.push_back(MeshPoint (*piter));
         }
      }
      //put the octants in a vector
      octants.clear();
      octants.reserve(tmp_octants.size());
      for (iter=tmp_octants.begin(); iter!=tmp_octants.end(); iter++) {
         octants.push_back(*iter);
      }
      cout << " done\n";
   }

   bool Mesher::isItIn(TriMesh &mesh, list<unsigned long> &faces, vector<Point3D> &coords) {
        //this method is meant to be used by octants that don't
        //intersect input domains. If they are inside of at least
        //one input mesh, then they must remain in the output mesh.
        bool first = mesh.pointIsInMesh(coords[0],faces);
        bool second = mesh.pointIsInMesh(coords[1],faces);
/**/
        if (first==second) {
            return first;
        }
/** /
        if (first || second){
           return true;
        }
/**/

        //cout << "one incosistency detected -> hard test\n";
        //return mesh.pointIsInMesh(coords[0],faces);
        return mesh.pointIsInMesh(coords[0]);
    }
    
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	void Mesher::saveOutputMesh(FEMesh &mesh){
        
        vector<Point3D> out_pts;
        vector<vector<unsigned long> > out_els;
        list<vector<unsigned long> >tmp_els;
        
        //new_idxs will hold the index of used nodes in the outside vector for points.
        //If the a node is not used by any element, its index will be 0 in this vector,
        //therefore the actual index is shiffted in 1. In other words, node 0 is node 1,
        //and node n is node n+1.
        vector<unsigned long> new_idxs (points.size(),0);
        unsigned long out_node_count = 0;
        list<Point3D> out_points_tmp;
        
        //recompute node indexes and update elements with them.
        for (unsigned long i=0; i<octants.size(); i++) {
            vector<vector<unsigned long> > sub_els= octants[i].getSubElements();
            for (unsigned long j=0; j<sub_els.size(); j++) {
                
                vector<unsigned long> sub_ele_new_idxs = sub_els[j];
                for (unsigned long k=0; k<sub_ele_new_idxs.size();k++) {
                    
                    unsigned long p_idx = sub_ele_new_idxs[k];
                    
                    if (new_idxs[p_idx]==0) {
                        sub_ele_new_idxs[k] = out_node_count++;
                        new_idxs[p_idx]=out_node_count;
                        out_points_tmp.push_back(points[p_idx].getPoint());
                    }
                    else {
                        sub_ele_new_idxs[k] = new_idxs[p_idx]-1;
                    }
                }
                tmp_els.push_back(sub_ele_new_idxs);
            }
        }
        
        //write output elements
        out_els.reserve(tmp_els.size());
        list<vector<unsigned long> >::iterator iter;
        for (iter=tmp_els.begin(); iter!=tmp_els.end(); iter++) {
            out_els.push_back(*iter);
        }
        
        //write output points
        list<Point3D>::iterator opi;
        out_pts.reserve(out_points_tmp.size());
        for (opi=out_points_tmp.begin(); opi!=out_points_tmp.end(); opi++) {
            out_pts.push_back(*opi);
        }
        
        mesh.setPoints(out_pts);
        mesh.setElements(out_els);
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	void Mesher::saveOutputMesh(FEMesh &mesh,vector<MeshPoint> &tmp_points,
								list<Octant> &tmp_octants){
		
		vector<Point3D> out_pts;
        list<vector<unsigned long> > tmp_elements;
		vector<vector<unsigned long> > out_els;
		
		unsigned long n = tmp_points.size();
		out_pts.reserve(n);
		for (unsigned long i=0; i<n; i++) {
			out_pts.push_back(points[i].getPoint());
		}
        
		list<Octant>::iterator o_iter;
		
		for (o_iter=tmp_octants.begin(); o_iter!=tmp_octants.end(); o_iter++) {
            
            vector<vector<unsigned long> > sub_els= o_iter->getSubElements();
            for (unsigned long j=0; j<sub_els.size(); j++) {
                tmp_elements.push_back(sub_els[j]);
            }
		}
        
        out_els.reserve(tmp_elements.size());
        list<vector<unsigned long> >::iterator e_iter;
		
        for (e_iter=tmp_elements.begin(); e_iter!=tmp_elements.end(); e_iter++) {
            out_els.push_back(*e_iter);
        }
        
		mesh.setPoints(out_pts);
		mesh.setElements(out_els);
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	void Mesher::generateGridMesh(TriMesh &input){
		//vectors with each coordinate per axis
		vector<double> all_x, all_y, all_z;
		vector<vector<unsigned long> > elements;
		
		GridMesher gm;
		gm.generatePoints(input.getBounds(),all_x,all_y,all_z);
		gm.generateMesh(all_x,all_y,all_z,points,elements);
		
		octants.reserve(elements.size());
		
		//create the root octants
		for (unsigned long i=0; i<elements.size(); i++) {
			Octant o (elements[i], 0);
			//Only when the octant intersects the input
			//add it to the list of current octants. As
			//This is the first time octants are checked
			//for intersections they must be made w.r.t.
			//all input faces.
            IntersectionsVisitor iv(false);
            //if (o.checkIntersections(input,points)) {
            iv.setTriMesh(input);
            iv.setPoints(points);
            if (o.accept(&iv)) {
                EdgeVisitor::insertEdges(&o, octreeEdges);
				octants.push_back(o);
			}
		}
		
		
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
    
	void Mesher::linkElementsToNodes(){
		//clear previous information
		for (unsigned long i=0; i<points.size(); i++) {
			points.at(i).clearElements();
		}
		
		//link element info to nodes
		for (unsigned long i=0; i<octants.size(); i++) {
			vector <unsigned long> o_pts = octants[i].getPoints();
			
			for (unsigned long j=0; j<o_pts.size(); j++) {
				points.at(o_pts[j]).addElement(i);
			}
		}
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	void Mesher::detectInsideNodes(TriMesh &input){
		for (unsigned long i=0; i<points.size(); i++) {
			if (points[i].wasOutsideChecked()) {
				continue;
			}
			
			list<unsigned long> p_eles = points[i].getElements(),p_faces;
			points[i].outsideChecked();
			if (p_eles.empty()) {
				continue;
			}
			list<unsigned long>::iterator iter;
			for (iter=p_eles.begin(); iter!=p_eles.end(); iter++) {
				list<unsigned long> o_faces= octants[*iter].getIntersectedFaces();
				list<unsigned long>::iterator of_iter;
				if (o_faces.empty()) {
					continue;
				}
				for (of_iter=o_faces.begin(); of_iter!=o_faces.end(); of_iter++) {
					p_faces.push_back(*of_iter);
				}
			}
			
			p_faces.sort();
			p_faces.unique();
			
			if (p_faces.empty() || input.pointIsInMesh(points[i].getPoint(),p_faces)) {
				points[i].setInside();
			}
		}
	}
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	void Mesher::removeOnSurface(){
		
		list<Octant> newele,removed;
		list<Octant>::iterator eiter;
        RemoveSubElementsVisitor rsv;
        rsv.setPoints(points);
		//remove elements without an inside node.
		for (unsigned long i=0; i<octants.size(); i++) {
			if (octants[i].isInside()) {
				newele.push_back(octants[i]);
				continue;
			}

            //if (octants[i].removeOutsideSubElements(points)) {
            if (octants[i].accept(&rsv)) {
                removed.push_back(octants[i]);
            }
            else {
                newele.push_back(octants[i]);
            }
            
			/*bool onein = false;
             vector<unsigned long> epts = octants[i].getPoints();
             
             for (unsigned long j=0; j< epts.size(); j++) {
             if (points.at(epts[j]).isInside()) {// &&
             //!points.at(epts[j]).wasProjected()) {
             onein = true;
             break;
             }
             }
             
             if (onein) {
             newele.push_back(octants[i]);
             }
             else {
             removed.push_back(octants[i]);
             }*/
		}
		
		if (removed.empty()) {
			return;
		}
		
		cout << "   > Elements removed: " << removed.size() << "\n";
		
		//clear removed elements
		removed.clear();
		//now element std::list from Vomule mesh can be cleared, as all remaining
		//elements are still in use and attached to newele std::list.
		octants.clear();
		for (eiter = newele.begin(); eiter!=newele.end(); eiter++) {
			octants.push_back(*eiter);
		}
	}
    
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	void Mesher::applySurfacePatterns(TriMesh &input){
		//apply patters to avoid flat, invalid and
		//poor quality elements.
		list<MeshPoint> tmppts;
		list<MeshPoint>::iterator piter;
		
		//cout << "  > applying surface patterns ...";
		//cout.flush();

        SurfaceTemplatesVisitor stv;
        stv.setPoints(points);
        stv.setInput(input);

		for (unsigned long i=0; i<octants.size(); i++) {
			
			/*if (octants[i].getPoints().size()>8) {
             continue;
             }*/
			
			if (octants[i].isSurface()) {
                stv.setNewPoints(tmppts);
                stv.setIdx(i);
                //if (!octants[i].applySurfaceTemplates(points,tmppts,input,i)) {
				if (!octants[i].accept(&stv)) {
					cout << "Error in Mesher::applySurfacePatterns: coultd't apply";
					cout << " a surface pattern\n";
					cout << octants[i] << "\n";
					continue;
				}
			}
		}
		
		//add new nodes to the vector meshPoints.
		if (!tmppts.empty()) {
			unsigned long npts = points.size()+tmppts.size();
			points.reserve(npts);
			for (piter=tmppts.begin(); piter!=tmppts.end(); piter++) {
				points.push_back(*piter);
			}
		}
		
		/*cout << " done (nodes added ";
         cout << tmppts.size() << ")\n";
         cout.flush();*/
	}
	
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	//shrink elements intersecting the envelope defined by all
	//input surfaces
	
	void Mesher::shrinkToBoundary(TriMesh &input){
		
		//Slow element removed (but works): from elements intersecting the
		//input domain, detect inner nodes. Project this nodes onto the
		//surface. If after all is done, if an element counts only with "on
		//surface" and "outside" nodes, remove it.
		list<unsigned long> out_nodes;
		list<Octant>::iterator oiter;
		
		//cout << "  > shrinking outside nodes:\n";
		//cout.flush();
        
		for (unsigned long i=0; i<octants.size(); i++) {
			if (octants[i].isInside()) {// || !octants[i].isSurface()) {
				continue;
			}
			
			//Put in a std::list inside nodes of boundary elements that
			//may be projected to the input domain.
			vector<unsigned long> epts = octants[i].getPoints();
			for (unsigned long j=0; j < epts.size(); j++) {
				
				if (!points[epts[j]].wasOutsideChecked()) {
					cout << "wtf!!! some nodes were not outside checked (";
					cout << epts.size() << "): " << epts[j] << " (" << j << ")\n";
					
					points[epts[j]].outsideChecked();
					Point3D oct_p = points.at(epts[j]).getPoint();
					if (input.pointIsInMesh(oct_p,octants[i].getIntersectedFaces())) {
						points[epts[j]].setInside();
					}
				}
				
				if (points[epts[j]].wasProjected()) {
					continue;
				}
				
				if (points[epts[j]].isOutside()) {
					out_nodes.push_back(epts[j]);
				}
			}
		}
		
		out_nodes.sort();
		out_nodes.unique();
		
		//project all outside points onto the surface
		std::list<unsigned long>::iterator piter;
		
		for (piter=out_nodes.begin(); piter!=out_nodes.end(); piter++) {
            
			//get the faces of octants sharing this node
			list<unsigned long> p_faces, p_eles = points.at(*piter).getElements();
			list<unsigned long>::iterator p_eiter;
			
			for (p_eiter=p_eles.begin(); p_eiter!=p_eles.end(); p_eiter++) {
				list<unsigned long> o_faces = octants[*p_eiter].getIntersectedFaces();
				list<unsigned long>::iterator oct_fcs;
				for (oct_fcs=o_faces.begin(); oct_fcs!=o_faces.end(); oct_fcs++) {
					p_faces.push_back(*oct_fcs);
				}
			}
			
			p_faces.sort();
			p_faces.unique();
			
			if (p_faces.empty()) {
				cout << "\nWarning at Mesher::shrinkToBoundary";
				cout << " no faces to project an outside node\n";
				cout << *piter << " n_els " << p_eles.size() << ":";
				for (p_eiter=p_eles.begin(); p_eiter!=p_eles.end(); p_eiter++) {
					cout << " " << *p_eiter;
				}
				cout << "\n";
				continue;
			}
			
			Point3D current = points.at(*piter).getPoint();
			Point3D projected = input.getProjection(current,p_faces);
			
			for (p_eiter=p_eles.begin(); p_eiter!=p_eles.end(); p_eiter++) {
				octants[*p_eiter].addProjectionInfluence(projected-current);
			}
			
			points.at(*piter).setPoint(projected);
			points.at(*piter).setProjected();
		}
		
		//Shrink inside nodes with respect to outside ones.
		/*double factor = 0.75;
         for (unsigned long i=0; i<3; i++) {
         
         //detect all internal nodes to be displaced in this iteration.
         list<unsigned long> to_move, to_reset;
         list<unsigned long>::iterator o_iter, p_iter;
         for (unsigned long j=0; j<octants.size(); j++) {
         if (octants[j].wasShrink()) {
         octants[j].noMoreProjectionInfluences();
         to_reset.push_back(j);
         vector<unsigned long> o_pts = octants[j].getPoints();
         for (unsigned long k=0; k<o_pts.size(); k++) {
         if (!points.at(o_pts[k]).wasProjected()) {
         to_move.push_back(o_pts[k]);
         }
         }
         }
         }
         
         if (to_move.empty()) {
         //cout << "   > no one else to move\n";
         break;
         }
         
         //move each node only once per iteration.
         to_move.sort();
         to_move.unique();
         
         //cout << "   > moving " << to_move.size() << " inside nodes\n";
         
         for (p_iter=to_move.begin(); p_iter!=to_move.end(); p_iter++) {
         list<unsigned long> p_eles = points[*p_iter].getElements();
         Point3D p_to_add;
         unsigned short qty = 0;
         for (o_iter=p_eles.begin(); o_iter!=p_eles.end(); o_iter++) {
         if (!octants[*o_iter].wasConsideredInProjection()) {
         continue;
         }
         p_to_add += octants[*o_iter].getProjectionInfluence();
         qty++;
         }
         
         p_to_add = p_to_add * (factor/(qty));
         //use this for less displacement of internal nodes.
         //p_to_add = p_to_add * (factor/(2*qty));
         
         for (o_iter=p_eles.begin(); o_iter!=p_eles.end(); o_iter++) {
         if (octants[*o_iter].wasConsideredInProjection()) {
         continue;
         }
         octants[*o_iter].addProjectionInfluence(p_to_add);
         }
         p_to_add += points[*p_iter].getPoint();
         points.at(*p_iter).setPoint(p_to_add);
         points.at(*p_iter).setProjected();
         }
         
         //clear information over already shrunk octants
         for (o_iter=to_reset.begin(); o_iter!=to_reset.end(); o_iter++) {
         octants[*o_iter].resetProjectionInfluence();
         }
         
         factor -= 0.25;
         }*/
        
		//cout.flush();
	}
	
	
	//--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
	void Mesher::projectCloseToBoundaryNodes(TriMesh &input){
        
        //Slow element removed (but works): from elements intersecting the
        //input domain, detect inner nodes. Project this nodes onto the
        //surface. If after all is done, if an element counts only with "on
        //surface" and "outside" nodes, remove it.
        list<unsigned long> in_nodes;
        list<Octant>::iterator oiter;
        
        for (unsigned long i=0; i<octants.size(); i++) {
            if (!octants[i].isSurface()) {
                continue;
            }
            octants[i].computeMaxDistance(points);
        }
        
        for (unsigned long i=0; i<octants.size(); i++) {
            if (octants[i].isInside()) {
                continue;
            }
            
            //Put in a std::list inside nodes of boundary elements that
            //may be projected to the input domain.
            vector<unsigned long> epts = octants[i].getPoints();
            for (unsigned long j=0; j < epts.size(); j++) {
                
                if (!points[epts[j]].wasOutsideChecked()) {
                    cout << "wtf!! point wasn't outside checked\n";
                    
                    points[epts[j]].outsideChecked();
                    
                    Point3D oct_p = points.at(epts[j]).getPoint();
                    
                    if (input.pointIsInMesh(oct_p,octants[i].getIntersectedFaces())) {
                        points[epts[j]].setInside();
                    }
                }
                if (points[epts[j]].isInside()) {
                    in_nodes.push_back(epts[j]);
                    double md = octants[i].getMaxDistance();
                    if (j>7) {
                        md*=0.5;
                    }
                    points[epts[j]].setMaxDistance(md);
                }
            }
            
        }
        
        in_nodes.sort();
        in_nodes.unique();
        
        //move (when possible) all inner points to surface
        std::list<unsigned long>::iterator piter;
        
        for (piter=in_nodes.begin(); piter!=in_nodes.end(); piter++) {
            
            //if this node is attached to an octant which was split in
            //mixed-elements due to transition patterns, avoid the
            //displacement.
            
            
            //get the faces of octants sharing this node
            list<unsigned long> o_faces,p_faces, p_eles = points.at(*piter).getElements();
            list<unsigned long>::iterator peiter,oct_fcs;
            
            //bool trans_pattern = false;
            
            for (peiter=p_eles.begin(); peiter!=p_eles.end(); peiter++) {
                //if (octants[*peiter].getPoints().size()>8) {
                //trans_pattern = true;
                //break;
                //}
                o_faces = octants[*peiter].getIntersectedFaces();
                for (oct_fcs=o_faces.begin(); oct_fcs!=o_faces.end(); oct_fcs++) {
                    p_faces.push_back(*oct_fcs);
                }
            }
            
            //if (trans_pattern) {
            //continue;
            //}
            
            p_faces.sort();
            p_faces.unique();
            
            Point3D current = points.at(*piter).getPoint();
            Point3D projected = input.getProjection(current,p_faces);
            double dis = (current - projected).Norm();
            
            if(dis<points[*piter].getMaxDistance()){
                //this node have been moved to boundary, thus every element
                //sharing this node must be set as a border element in order
                //to avoid topological problems.
                //points.at(*piter).setOutside();
                points.at(*piter).setProjected();
                points.at(*piter).setPoint(projected);
                for (peiter=p_eles.begin(); peiter!=p_eles.end(); peiter++) {
                    //if (octants[*peiter].isInside()) {
                    octants[*peiter].setSurface();
                    //}
                }
            }
        }
    }
	
    //--------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------
	
    /*	void Mesher::generateGridFromOctree(const unsigned short &rl,
     TriMesh &input,
     const string &name){
     
     //to save m3d files per stage
     Clobscode::CoteMarek marek;
     
     //list of temp octants
     list<Octant> tmp_octants, new_octants;
     //list of the points added at this refinement iteration:
     list<Point3D> new_pts;
     
     list<Octant>::iterator iter;
     
     for (unsigned long i=0; i<octants.size(); i++) {
     tmp_octants.push_back(octants[i]);
     }
     
     //----------------------------------------------------------
     //refine each octant until the Refinement Level is reached
     //----------------------------------------------------------
     
     cout << "  > refining the mesh ...";
     cout.flush();
     
     for (unsigned short i=0; i<rl; i++) {
     
     //the new_pts is a list that holds the coordinates of
     //new points inserted at this iteration. At the end of
     //this bucle, they are inserted in the point vector
     new_pts.clear();
     
     //split the octants as needed
     for (iter=tmp_octants.begin(); iter!=tmp_octants.end(); iter++) {
     
     list<unsigned long> inter_faces = (*iter).getIntersectedFaces();
     bool oct_inside = false;
     if (inter_faces.empty()) {
     oct_inside = true;
     }
     vector<vector<Point3D> > clipping_coords;
     
     vector< vector <unsigned long> > split_elements;
     (*iter).split(points,new_pts,octreeEdges,split_elements,clipping_coords);
     
     //cout << "\n";
     
     for (unsigned long j=0; j<split_elements.size(); j++) {
     Octant o (split_elements[j],i+1);
     
     //if parent octant was completely inside, directly add its sons.
     if (oct_inside) {
     new_octants.push_back(o);
     continue;
     }
     //the new points are inserted in bash at the end of this
     //iteration. For this reason, the coordinates must be passed
     //"manually" at this point (clipping_coords).
     if (o.checkIntersections(input,inter_faces,clipping_coords[j])) {
     new_octants.push_back(o);
     }
     else {
     //The element doesn't intersect any input face.
     //It must be checked if it's inside or outside.
     //Only in the first case add it to new_octants.
     //Test this with parent octant faces only.
     
     //Comment the following lines of this 'else' if
     //only intersecting octants are meant to be
     //displayed.
     if (o.isItIn(input,inter_faces,clipping_coords[j])) {
     new_octants.push_back(o);
     }
     }
     }
     }
     //remove the old octants
     tmp_octants.clear();
     tmp_octants = new_octants;
     new_octants.clear();
     
     //if no points were added at this iteration, it is no longer
     //necessary to continue the refinement.
     if (new_pts.empty()) {
     cout << "wtf!!!\n";
     break;
     }
     //add the new points to the vector
     list<Point3D>::iterator piter;
     points.reserve(points.size() + new_pts.size());
     for (piter=new_pts.begin(); piter!=new_pts.end(); piter++) {
     points.push_back(MeshPoint (*piter));
     }
     }
     
     //save current stage of the mesh in a file
     {
     //save pure octree mesh
     FEMesh pure_octree;
     saveOutputMesh(pure_octree,points,tmp_octants);
     string tmp_name = name + "_octree";
     marek.WriteOutputMesh(tmp_name,pure_octree);
     }
     
     //put the octants in a vector
     octants.clear();
     octants.reserve(tmp_octants.size());
     for (iter=tmp_octants.begin(); iter!=tmp_octants.end(); iter++) {
     octants.push_back(*iter);
     }
     
     cout << " done\n";
     cout.flush();
     }
     */
	
    
	
    /*
     //--------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------
     
     
     //shrink elements intersecting the envelope defined by all
     //input surfaces
     
     void Mesher::shrinkToBoundary(void * pClientData,
     PTRFUN_POINT_PROJECTOR pClientPointProjectorFunc){
     
     
     //From the list of elements intersecting any input mesh
     //select the nodes to be projected, i.e., the nodes that
     //are outside an input mesh
     list<unsigned long> out_nodes;
     for (unsigned long i=0; i<elements.size(); i++) {
     if (!elements[i].outsideBorder(points)) {
     continue;
     }
     vector<unsigned long> epts = elements[i].getPoints();
     for (unsigned long j=0; j<epts.size(); j++) {
     if (points[epts[j]].isOutside()) {
     out_nodes.push_back(epts[j]);
     }
     }
     }
     
     out_nodes.sort();
     out_nodes.unique();
     
     //project all outside nodes into the surface
     list<unsigned long>::iterator piter;
     
     for (piter=out_nodes.begin(); piter!=out_nodes.end(); piter++) {
     Point3D current = points.at(*piter).getPoint();
     
     double min_dis = std::numeric_limits<double>::max();
     
     //-----------------------------------------------------
     //-----------------------------------------------------
     for (unsigned long i=0; i<n_meshes; i++) {
     Point3D projected = pClientPointProjectorFunc( pClientData, current, i);
     double dis = (current - projected).Norm();
     
     //-----------------------------------------------------
     //-----------------------------------------------------
     
     
     if(min_dis>dis){
     //this node have been moved to boundary, thus every element
     //sharing this node must be set as a border element in order
     //to avoid topological problems.
     min_dis = dis;
     points.at(*piter).setOutside(i);
     points.at(*piter).setPoint(projected);
     vector<unsigned long> pele = points.at(*piter).getElements();
     for (unsigned long j=0; j<pele.size(); j++) {
     elements[pele[j]].setBorderState(i,true);
     }
     }
     }
     }
     }
     
     
     //--------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------
     
     //wirte outside nodes to project them with registration
     void Mesher::writeOutsideNodes(FEMesh &mesh, void * pClientData,
     PTRFUN_POINT_IN_MESH pClientPointTestFunc){
     
     list<unsigned long> outside;
     
     for (unsigned long i=0; i<elements.size(); i++) {
     //if the element does not intersect the domain,
     //then continue
     if (!elements.at(i).outsideBorder(points)) {
     continue;
     }
     
     vector<unsigned long> epts = elements[i].getPoints();
     for (unsigned long j=0; j<epts.size(); j++) {
     if (!points.at(epts[j]).wasOutsideChecked()) {
     Point3D p =points.at(epts[j]).getPoint();
     
     
     //-----------------------------------------------------
     //-----------------------------------------------------
     
     for (unsigned long k=0; k<n_meshes; k++) {
     if (pClientPointTestFunc( pClientData, p, k)) {
     points.at(epts[j]).setInside(k);
     }
     }
     //-----------------------------------------------------
     //-----------------------------------------------------
     
     points.at(epts[j]).outsideChecked();
     }
     if (points.at(epts[j]).isOutside()) {
     outside.push_back(epts[j]);
     }
     }
     }
     outside.sort();
     outside.unique();
     
     mesh.setOutsideNodes(outside);
     }
     
     //--------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------
     
     //wirte all inside nodes for testing
     void Mesher::writeInsideNodes(FEMesh &mesh, void * pClientData,
     PTRFUN_POINT_IN_MESH pClientPointTestFunc){
     
     list<unsigned long> inside_only;
     
     for (unsigned long i=0; i<points.size(); i++) {
     //if the element does not intersect the domain,
     //then continue
     if (!points.at(i).wasOutsideChecked()) {
     Point3D p =points.at(i).getPoint();
     
     //-----------------------------------------------------
     //-----------------------------------------------------
     for (unsigned long j=0; j<n_meshes; j++) {
     if (pClientPointTestFunc( pClientData, p,j)) {
     points.at(i).setInside(j);
     }
     }
     //-----------------------------------------------------
     //-----------------------------------------------------
     
     points.at(i).outsideChecked();
     }
     if (points.at(i).isInside()) {
     inside_only.push_back(i);
     }
     }
     inside_only.sort();
     inside_only.unique();
     
     mesh.setOutsideNodes(inside_only);
     }
     
     
     
     //--------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------
     // Start debugging
     //--------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------
     
     void Mesher::debugging(void * pClientData,
     PTRFUN_POINT_IN_MESH pClientPointTestFunc){
     vector<Point3D> deb_pts;
     deb_pts.reserve(4);
     Point3D p1(-4.2,0.8,4.3), p2(-3.7,0.8,3.8), p3(-3.7,0.8,4.3), p4(-3.7,1.3,4.3);
     deb_pts.push_back(p1);
     deb_pts.push_back(p2);
     deb_pts.push_back(p3);
     deb_pts.push_back(p4);
     
     unsigned long ele_idx;
     for (unsigned long i=0; i<elements.size(); i++) {
     bool e_found = true;
     for (unsigned long j=0; j<4; j++) {
     vector<unsigned long> epts = elements[i].getPoints();
     bool p_found = false;
     for (unsigned long k=0; k<epts.size(); k++) {
     Point3D ep = points[epts[k]].getPoint();
     if (ep == deb_pts[j]) {
     p_found = true;
     break;
     }
     }
     if (!p_found) {
     e_found = false;
     break;
     }
     }
     if (e_found) {
     ele_idx = i;
     break;
     }
     }
     
     std::cout << "Element found! Index: " << ele_idx << "\n";
     
     vector<unsigned long> bug_e_pts = elements[ele_idx].getPoints();
     for (unsigned long i=0; i<bug_e_pts.size(); i++) {
     Point3D p =points.at(bug_e_pts[i]).getPoint();
     std::cout << "point " << p << " is ";
     
     
     //-----------------------------------------------------
     //-----------------------------------------------------
     if (pClientPointTestFunc( pClientData, p, 0)) {
     std::cout << "in\n";
     }
     //-----------------------------------------------------
     //-----------------------------------------------------
     
     else {
     std::cout << "out\n";
     }
     
     }
     }
     
     //--------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------
     // End debugging
     //--------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------
     
     
     */

}
