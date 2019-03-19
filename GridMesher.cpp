#include "stdafx.h"
#include "GridMesher.h"

namespace Clobscode
{
	
	/***********************************************
	 This class will compute the starting grid elements
	 that will be split following the octree technique.
	 The Octree works fine over domains that present a 
	 bounding box that is close to a cube, but it produces
	 several unnecessary elements in stick like domains or
	 3D domains that are close to be in 2D.
	 In order to do so, it will find the smallest edge
	 of the bounding box and will use it in other axis
	 to build cubes.
	***********************************************/
	GridMesher::GridMesher(){

	}
	
	GridMesher::~GridMesher(){
		
	}
	
	void GridMesher::generatePoints(vector<double> &bounds,
									vector<double> &all_x,
									vector<double> &all_y,
									vector<double> &all_z){
		
		list<double> deltas;
		list<double>::iterator iter;
		deltas.push_back(bounds[3]-bounds[0]);
		deltas.push_back(bounds[4]-bounds[1]);
		deltas.push_back(bounds[5]-bounds[2]);
		deltas.sort();
		
		double step = *(deltas.begin());
		step*=1.01; // <- why?
		
		generateVector(all_x,bounds[0],bounds[3],step);
		generateVector(all_y,bounds[1],bounds[4],step);
		generateVector(all_z,bounds[2],bounds[5],step);
	}
	
	void GridMesher::generateMesh(vector<double> &all_x,
								  vector<double> &all_y,
								  vector<double> &all_z,
								  vector<MeshPoint> &points,
								  vector<vector<unsigned long> > &elements){
	
		unsigned long nx = all_x.size();
		unsigned long ny = all_y.size();
		unsigned long nz = all_z.size();
		
		points.reserve(nx*ny*nz);
		points.clear();
		elements.reserve((nx-1)*(ny-1)*(nz-1));
		elements.clear();
		
		unsigned long one_col = nx*ny;
		
		for (unsigned long i=0; i<nz; i++) {
			for (unsigned long j=0; j<ny; j++) {
				for (unsigned long k=0; k<nx; k++) {
					
					//create the point
					Point3D p3d (all_x[k],all_y[j],all_z[i]);
					MeshPoint mp (p3d);
					points.push_back(mp);
					
					//create the element					
					if ((k+2)>nx || (j+2)>ny || (i+2)>nz) {
						continue;
					}

					vector<unsigned long> epts (8,0);
					epts[0] = k+j*nx+i*one_col;
					epts[1] = epts[0]+one_col;
					epts[2] = epts[1]+1;
					epts[3] = epts[0]+1;
					epts[4] = epts[0]+nx;
					epts[5] = epts[4]+one_col;
					epts[6] = epts[5]+1;
					epts[7] = epts[4]+1;
					
					elements.push_back(epts);
				}
			}
		}
	}
	
	void GridMesher::generateVector(vector<double> &coords, double min,
									double max, double step){
		
		list<double> tmp_pos_coords, tmp_neg_coords;
		
		double delta = max-min;
		double middle = min+delta/2;
		
		int exp;
		double mantissa = frexp(delta/step,&exp);
		
		double pos_start, neg_start;
		
		if (mantissa<0.55 || mantissa>0.97) {
			pos_start=middle+step/2;
			neg_start=middle-step/2;
			tmp_pos_coords.push_back(pos_start);
			tmp_neg_coords.push_back(neg_start);
		}
		else {
			pos_start = neg_start = middle;
			tmp_pos_coords.push_back(pos_start);
		}
		
		while (pos_start<max) {
			pos_start+=step;
			tmp_pos_coords.push_back(pos_start);
			neg_start-=step;
			tmp_neg_coords.push_back(neg_start);
		} 
		
		coords.reserve(tmp_pos_coords.size()+tmp_neg_coords.size());
		coords.clear();
		
		list<double>::reverse_iterator riter;
		for (riter=tmp_neg_coords.rbegin(); riter!=tmp_neg_coords.rend(); ++riter) {
			coords.push_back(*riter);
		}
		list<double>::iterator iter;
		for (iter=tmp_pos_coords.begin(); iter!=tmp_pos_coords.end(); iter++) {
			coords.push_back(*iter);
		}
	}
}
