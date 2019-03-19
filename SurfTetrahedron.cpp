#include "stdafx.h"
#include "SurfTetrahedron.h"

namespace Clobscode
{
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    
	SurfTetrahedron::SurfTetrahedron(vector<unsigned long> &mypoints){
        if (mypoints.size()!=4) {
            std::cerr << "warning at SurfTetrahedron constructor: not a 4 node element\n";
        }
        
        points = mypoints;
        scaled_jac_constant = 1/sqrt(2);
	}
	
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    
	SurfTetrahedron::~SurfTetrahedron(){
	
    }
	
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    vector<vector<unsigned long> > SurfTetrahedron::getSubElements(vector<bool> &inside_state){
    
        vector<vector<unsigned long> > sub_ele;
        sub_ele.push_back(points);
        return sub_ele;
    }
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    double SurfTetrahedron::getQuality(vector<MeshPoint> &allpoints) {
        
        vector<vector<unsigned long> > allt = getTetras();
        double quality = 2, value = 2;
        bool one_neg = false;
        
        //we should optimize this computation: compute only once
        //all the vectors normalized and then multiply them by -1
        //if needed in the other direction. ToDo list.
        
        for (unsigned long i=0; i<allt.size(); i++) {
            
            Point3D n0 = allpoints[allt[i][0]].getPoint();
            Point3D n1 = allpoints[allt[i][1]].getPoint();
            Point3D n2 = allpoints[allt[i][2]].getPoint();
            Point3D n3 = allpoints[allt[i][3]].getPoint();
            
            //this is due to tetra definition
            Point3D d1 = (n1 - n0);
            Point3D d2 = (n2 - n0);
            Point3D d3 = (n3 - n0);
            
            d1.normalize();
            d2.normalize();
            d3.normalize();
            
            value = d1.dot(d2.cross(d3));
            
            if (one_neg) {
                if (value>0) {
                    continue;
                }
                
                if (value < -scaled_jac_constant) {
                    quality = -1 - scaled_jac_constant - value;
                }

                else {
                    quality = value/scaled_jac_constant;
                }
            }
            
            else {
                if (value > scaled_jac_constant) {
                    quality = 1 + scaled_jac_constant - value;
                }
                else {
                    quality = value/scaled_jac_constant;
                }
            }
        }
        
        return quality;
    }
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    vector<vector<unsigned long> > SurfTetrahedron::getTetras(){
        vector<vector<unsigned long> > tetras;
        tetras.reserve(8);

        vector<unsigned long> t0(4,0);
        t0[0]= points[0];
        t0[1]= points[1];
        t0[2]= points[2];
        t0[3]= points[3];
        tetras.push_back(t0);
        
        vector<unsigned long> t1(4,0);
        t1[0]= points[1];
        t1[1]= points[0];
        t1[2]= points[3];
        t1[3]= points[2];
        tetras.push_back(t1);
        
        vector<unsigned long> t2(4,0);
        t2[0]= points[2];
        t2[1]= points[0];
        t2[2]= points[1];
        t2[3]= points[3];
        tetras.push_back(t2);
        
        vector<unsigned long> t3(4,0);
        t3[0]= points[3];
        t3[1]= points[0];
        t3[2]= points[2];
        t3[3]= points[1];
        tetras.push_back(t3);
        
        return tetras;
    }
}

