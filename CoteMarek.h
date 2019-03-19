#ifndef CoteMarek_h
#define CoteMarek_h 1

#include <cstring>
#include "TriMesh.h"
#include "FEMesh.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

//using TxTriModel::Mesh;
//using TxGeom::VPoint3D;
using Clobscode::Point3D;
using Clobscode::TriMesh;
using std::vector;

namespace Clobscode
{
	
	
	//The TxTriModel are meshes used by mesher_services to detect 
	//in/outside nodes. The TriMesh ares meshes (with "almost" the 
	//same information) employed by the mesher class of this code.
	
	//static std::vector<TxTriModel::Mesh> input_meshes;
	
	class CoteMarek
	{
	public:
		
		/*
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		static void setNumberOfInputs(const unsigned long &n){
			input_meshes.reserve(n);
		}
		
		
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		static Point3D GetProjection( const void *, const Point3D & pPoint, 
									 const unsigned long &i){
				
			VPoint3D TxPoint (pPoint.X(),pPoint.Y(),pPoint.Z());
			VPoint3D TxResult = input_meshes[i].GetProjection(TxPoint);
			Point3D CPoint (TxResult.X(),TxResult.Y(),TxResult.Z());

			return CPoint;
		}
		
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		static bool CheckIfPointInMesh( const void *, const Point3D & pPoint, 
									   const unsigned long &i ){
			VPoint3D TxPoint (pPoint.X(),pPoint.Y(),pPoint.Z());
			return input_meshes[i].PointIsInMesh_slow(TxPoint);
		}*/
		
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		static bool ReadInputMesh(std::string name, 
								  vector<Clobscode::TriMesh> &clobs_inputs){

			char word [256];
			int cant;
			double x,y,z;
			vector<vector<unsigned long> > allfaces;
			vector<Point3D> tri_pts;
			
			FILE *file = fopen(name.c_str(),"r");
			
			if (file==NULL) {
				std::cout << "File " << name << " doesn't exist\n";
				return false;
			}
			
			//read number of nodes
			while(true){
				if(std::fscanf(file,"%s",word)==EOF){
					fclose(file);
					return false;
				}
				if(!strcmp(word,"ARRAY1<POINT3D>]\0"))
					break;
			}
			std::fscanf(file,"%i",&cant);
			
			if(cant<=0)
				return false;
			//read each node
			tri_pts.reserve(cant);
			
			for( int i=0;i<cant;i++){
				std::fscanf(file,"%s",word);
				x=atof(word);
				std::fscanf(file,"%s",word);
				y=atof(word);
				std::fscanf(file,"%s",word);
				z=atof(word);
				Point3D p (x,y,z);
				tri_pts.push_back(p);
			}
			
			//read number of "triangle faces"
			cant = 0;
			while(1){
				if(std::fscanf(file,"%s",word) == EOF){
					std::cout << "didn't find faces\n";
					fclose(file);
					return false;
				}
				
				if(!std::strcmp(word,"ARRAY1<STRING>]\0")){
					//std::fscanf(file,"%s",word);
					std::fscanf(file,"%i",&cant);
					break;
				}
			}
			
			allfaces.reserve(cant);
			//read each face (assuming they are triangles
			int dust;
			for( int i=0;i<cant;i++){
				std::vector<unsigned long> fpts(3,0);
				for(unsigned long j=0;j<3;j++){
					std::fscanf(file,"%lu",&fpts[j]);
				}
				//read some unnecessary integers
				for(unsigned long j=0;j<3;j++)
					std::fscanf(file,"%i",&dust);
				
				allfaces.push_back(fpts);
			}
			fclose(file);
						
			TriMesh tm (tri_pts, allfaces);
			clobs_inputs.push_back(tm);
			
			return true;
		}
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		static bool WriteOutputMesh(std::string name, FEMesh &output){
						
			vector<Point3D> points = output.getPoints();
			vector<vector<unsigned long> > elements = output.getElements();
			
			if (elements.empty()) {
				std::cout << "no output elements\n";
				return false;
			}
			
			string vol_name = name+".m3d";
			
			//write the volume mesh
			FILE *f = fopen(vol_name.c_str(),"wt");
			
			unsigned long n = points.size();
			
			fprintf(f,"%s\n","[Nodes, ARRAY1<STRING>]");
			fprintf(f,"%lu\n\n",n);
			
			//write points
			for(unsigned long i=0;i<n;i++){			
				fprintf(f,"1 %+1.8E",points[i][0]);
				fprintf(f," %+1.8E",points[i][1]);
				fprintf(f," %+1.8E\n",points[i][2]);
			}
			
			n = elements.size();
			
			fprintf(f,"\n%s\n","[Elements, ARRAY1<STRING>]");
			fprintf(f,"%lu\n\n",n);
			
			int idx = 0;
			//get all the elements in a std::vector
			for (unsigned long i=0; i<n; i++) {
				std::vector<unsigned long> epts = elements[i];
				unsigned long np = epts.size();
				if (np == 4) {
					fprintf(f,"T");
				}
				else if (np == 5){
					fprintf(f,"P");
				}
				else if (np == 6){
					fprintf(f,"R");
				}
				else if (np == 8){
					fprintf(f,"H");
				}
				
				for (unsigned long j= 0; j<np; j++) {
					fprintf(f," %lu", epts.at(j));
				}
				
				fprintf(f," 1000.0 0.45 1.0\n");
			}
			fclose(f);
			
			//write the surface nodes:
			/*string surf_name = name + ".mdl";
			list<unsigned long> out_pts = output.getOutsideNodes();
			list<unsigned long>::iterator o_iter;
			n = out_pts.size();
			
			FILE *sf = fopen(surf_name.c_str(),"wt");
			fprintf(sf,"%s\n", "[Points, ARRAY1<POINT3D>]");
			fprintf(sf,"%lu\n\n",n); 
			
			for (o_iter=out_pts.begin(); o_iter!=out_pts.end(); o_iter++) {
				
				fprintf(sf,"%+1.8E",points[*o_iter][0]);
				fprintf(sf," %+1.8E",points[*o_iter][1]);
				fprintf(sf," %+1.8E\n",points[*o_iter][2]);
			}
			
			fprintf(sf,"\n%s\n", "[Triangles, ARRAY1<STRING>]\n0");
			
			fclose(sf);*/
			
			return true;
		}
	};
}
#endif
