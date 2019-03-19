#include "stdafx.h"
#include "SurfHexahedron.h"

namespace Clobscode
{
 
    /*
     NOTA IMPORTANTE:
     mejorar esta clase y Octant para que la segunda no tenga estos mismos métodos,
     Además se pueden mejorar varias cosas en esta clase: imitar el tratamiento de 
     puntos in/out en un solo vector, como se hace para prismas, etc.
     
     */
    
    
    
    
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    
	SurfHexahedron::SurfHexahedron(vector<unsigned long> &mypoints){
        if (mypoints.size()!=8) {
            std::cerr << "warning at SurfHexahedron constructor: not 6 node element\n";
        }
        
        points = mypoints;
	}
	
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    
	SurfHexahedron::~SurfHexahedron(){
	
    }
	
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    vector<vector<unsigned long> > SurfHexahedron::getSubElements(vector<MeshPoint> &meshpoints, list<MeshPoint> &newpts,
                                                                 TriMesh &input, unsigned long &e_idx,
                                                                 vector<vector<unsigned long> > &possibles,
                                                                 vector<vector<unsigned long> > &continuity,
                                                                 list<unsigned long> &intersected_faces){
    
        vector<vector<unsigned long> > newsubs;
        
        
        vector<unsigned long> inpts, outpts;
        list<unsigned long> tmpin,tmpout;
        list<unsigned long>::iterator piter;
        
        for (unsigned long i=0; i<points.size(); i++) {
            
            if (meshpoints.at(points[i]).isOutside()) {
                tmpout.push_back(i);
            }
            else {
                tmpin.push_back(i);
            }
        }
        
        //save the points in a std::vector for quick acces
        inpts.reserve(tmpin.size());
        for(piter=tmpin.begin();piter!=tmpin.end();piter++)
            inpts.push_back(*piter);
        outpts.reserve(tmpout.size());
        for(piter=tmpout.begin();piter!=tmpout.end();piter++)
            outpts.push_back(*piter);
        
        
        //select the patter to apply
        switch (inpts.size()) {
            case 0:{
                /*If at this point, the element has 0 node inside,
                 it might be tangencial to input mesh, in which case
                 it should be removed, or represent a feature of
                 the domain (e.g. all nodes outside, but there is
                 something like a pipeline crossing it). This algorithm
                 isn't yet "future sensitive", therefore the element
                 is simply removed.
                 */
                cerr << "warning at SurfHexahedron::getSubElements 0 inside nodes\n";
                break;
            }
            case 1: {
                SurfTemplate1 surf_t1;
                surf_t1.getSubelements(points,inpts,newsubs);
                break;
            }
            case 2: {
                //erase last argument ("possibles") to maximum avoid eventual quality issues.
                SurfTemplate2 surf_t2;
                surf_t2.getSubelements(points,inpts,newsubs,possibles,continuity);
                break;
            }
            case 3: {
                //erase last argument ("possibles") to maximum avoid eventual quality issues.
                SurfTemplate3 surf_t3;
                surf_t3.getSubelements(points,inpts,newsubs,possibles);
                break;
            }
            case 4: {
                SurfTemplate4 surf_t4;
                surf_t4.getSubelements(points,inpts,newsubs);
                break;
            }
            case 5: {
                SurfTemplate5 surf_t5;
                unsigned long old_size = newpts.size();
                surf_t5.getSubelements(points,inpts,meshpoints,newpts,newsubs,input,intersected_faces,e_idx);
                break;
            }
            case 6: {
                SurfTemplate6 surf_t6;
                surf_t6.getSubelements(points,outpts,newsubs);
                break;
            }
            case 7: {
                SurfTemplate7 surf_t7;
                surf_t7.getSubelements(points,outpts,newsubs);
                break;
            }
            case 8: {
                //If this happens the element is inside the overall
                //geometry, but intersects inner features.
                newsubs.push_back(points);
                break;
            }
            default: {
                cerr << " Error at EnhancedElement::applySurfacePatterns\n";
                cerr << " Number of inside nodes: " << inpts.size() << "\n";
                cerr << " Surface Patterns must be applied over elements";
                cerr << " with 1 to 7 inside nodes.\n";
                break;
            }
        }
        
        return newsubs;
    }
}

