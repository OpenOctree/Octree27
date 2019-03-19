#include "stdafx.h"
#include "FaceDiagonal.h"

namespace Clobscode
{
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    
	FaceDiagonal::FaceDiagonal(vector<unsigned long> &mypoints){
        if (mypoints.size()!=4) {
            std::cerr << "warning at FaceDiagonal constructor: not square face\n";
        }
        
        points = mypoints;
	}
	
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    
	FaceDiagonal::~FaceDiagonal(){
	
    }
	
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    
    bool FaceDiagonal::getDiagonal(vector<bool> &inside_state,
                                   vector<unsigned long> &diag){
    
        //detect number of inside nodes for this face
        unsigned long n_in = 0;
        for (unsigned long i=0; i<points.size(); i++) {
            if (inside_state[points[i]]) {
                n_in++;
            }
        }
        
        //all or none of this face nodes are inside, there is no
        //diagonal in this face.
        if (n_in == 0 || n_in == 4) {
            return false;
        }
        
        if (n_in == 1) {
            //detect the one node that is insde and return previous
            //and next nodes as diagonal for this face.
            for (unsigned long i=0; i<points.size(); i++) {
                if (inside_state[points[i]]) {
                    diag[0] = points[(i+3)%4];
                    diag[1] = points[(i+1)%4];
                    return true;
                }
            }
        }
        
        if (n_in == 2) {
            //two possible cases
            unsigned long n_in1, n_in2;
            for (unsigned long i=0; i<points.size(); i++) {
                if (inside_state[points[i]]) {
                    if (inside_state[points[(i+1)%4]]) {
                        //the two nodes are consecutive.
                        return false;
                    }
                    else {
                        if (inside_state[points[(i+3)%4]]) {
                            return false;
                        }
                        else{
                            //return previous and next nodes as diagonal
                            //for this face.
                            diag[0] = points[(i+3)%4];
                            diag[1] = points[(i+1)%4];
                            return true;
                        }
                    }
                }
            }
        }
        
        if (n_in == 3) {
            //find the one node that is outside
            for (unsigned long i=0; i<points.size(); i++) {
                if (!inside_state[points[i]]) {
                    diag[0] = points[i];
                    diag[1] = points[(i+2)%4];
                    return true;
                }
            }
        }
        
        std::cerr << " warning: unexpected case at FaceDiagonal::getDiagonal\n";
        
        return false;
    }
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    
    

	
	/******************
	 * This class manage the different cases of 3 points inside patterns.
	 * Once the pattern is identified, the corresponding class will handle
	 * the elements to be returned (
	 *//// 
}

