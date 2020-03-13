#include "Mesher.h"
#include "TriMesh.h"
#include "FEMesh.h"
#include "CoteMarek.h"
#include "RefinementCubeRegion.h"
#include "RefinementSurfaceRegion.h"
#include "RefinementInputSurfaceRegion.h"
#include "RefinementAllRegion.h"
#include "Point3D.h"
#include <string>
#include <cctype>
#include <time.h>
#include <chrono>

using std::atoi;
using std::cout;
using std::cerr;
using std::vector;
using std::string;
using Clobscode::RefinementRegion;
using Clobscode::RefinementCubeRegion;
using Clobscode::RefinementSurfaceRegion;
using Clobscode::Point3D;

//-------------------------------------------------------------------
//-------------------------------------------------------------------

void endMsg(){
	cout << "use: ./mesher [-i] input.mdl [-o] output [-s] ref_level [-a] ref_level [-r] file.reg [-u] input_surface rl [-t table_name]\n";
	cout << "where:\n";
	cout << "  input.mdl is the surface input mesh in mdl format\n";
	cout << "  output is the output mesh to be saved in output.m3d\n";
    cout << "  the use one of the following options:\n";
	cout << "    -s (refine surface elements) ref_level is the refinement level\n";
    cout << "    -a (refine all elements) ref_level is the refinement level\n";
	cout << "    -r (refine regions) and file.reg is a text file specifying ";
    cout << "       regions of refinement with a particular level\n";
    cout << "    -u (refine surface region) will refine all the elements in the input_surface at level rl\n";
    cout << "    -t table_all|table_t7t5|ito2009_a|ito2009_b|ito_2009_c|table_t7|table_t6b|table_t5|table_t4c|table_t4b\n";
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

void printTime(double nseconds){
	int th,tm,ts;
	th = (int)nseconds/3600;
	tm = ((int)nseconds%3600)/60;
	ts = ((int)nseconds%3600)%60;
	if(th<10) 
		cout << "0";
	cout << th << ":";
	if(tm<10)
		cout << "0";
	cout << tm << ":";
	if(ts<10)
		cout << "0";
	cout << ts << std::endl;
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

void readSurfaceRefinementRegion(string name, list<RefinementRegion *> &regions, const unsigned short &rrl){
	
	char word [256];
	int cant,point;
	double x,y,z;
    
	vector<Point3D> pts;
    vector<vector<unsigned long> > fv;
	
	FILE *file = fopen(name.c_str(),"r");
	
	if (file==NULL) {
		std::cout << "File " << name << " doesn't exist\n";
		return;
	}
	
	//read number of nodes
	while(true){
		if(std::fscanf(file,"%s",word)==EOF){
			fclose(file);
            return;
		}
		if(!strcmp(word,"ARRAY1<POINT3D>]\0"))
			break;
	}
	std::fscanf(file,"%i",&cant);
	
	//read each node
	pts.reserve(cant);
	
	for(int i=0; i<cant; i++){
		
		//Read region's first point
		std::fscanf(file,"%s",word);
		x = atof(word);
		std::fscanf(file,"%s",word);
		y = atof(word);
		std::fscanf(file,"%s",word);
		z = atof(word);
		Point3D p (x,y,z);
        pts.push_back(p);
	}
    
    while(fscanf(file,"%s",word) != EOF){
        
        if(!strcmp(word,"[Triangles,\0")){
            
            fscanf(file,"%s",word);
            fscanf(file,"%i",&cant);
            
            fv.reserve(cant);
            
            for(int i=0;i<cant;i++){
                vector<unsigned long> fpts;
                unsigned long point=0;
                
                for(int j=0;j<3;j++){
                    fscanf(file,"%lu",&point);
                    fpts.push_back(point);
                }
                for(int j=0;j<3;j++)
                    fscanf(file,"%lu",&point);
                fv.push_back(fpts);
            }

        }
        
        if(!strcmp(word,"[Squares,\0")){
            std::cerr << "Main::readSurfaceRefinementRegion not prepeared to read square faces in a mdl file\n";
            fscanf(file,"%s",word);
            fscanf(file,"%i",&cant);
            for(int i=0;i<cant;i++){
                for(int j=0;j<7;j++)
                    fscanf(file,"%i",&point);
            }
        }
        
    }
    
    TriMesh tm (pts,fv);
    RefinementRegion *rr = new RefinementSurfaceRegion(tm,rrl);
    
    regions.push_back(rr);
	fclose(file);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

unsigned short readRefinementRegions(string name, list<RefinementRegion *> &regions){
	
	char word [256];
	int cant;
	double x,y,z;
	unsigned short max_refinement = 0;

	vector<Point3D> cube_pts;
	
	FILE *file = fopen(name.c_str(),"r");
	
	if (file==NULL) {
		std::cout << "File " << name << " doesn't exist\n";
		return max_refinement;
	}
	
	//read number of nodes
	while(true){
		if(std::fscanf(file,"%s",word)==EOF){
			fclose(file);
			return max_refinement;
		}
		if(!strcmp(word,"n_regions\0"))
			break;
	}
	std::fscanf(file,"%i",&cant);
	
	//read each node
	cube_pts.reserve(cant*2);
	
	for( int i=0;i<cant;i++){
		
		//Read region's first point
		std::fscanf(file,"%s",word);
		x = atof(word);
		std::fscanf(file,"%s",word);
		y = atof(word);
		std::fscanf(file,"%s",word);
		z = atof(word);
		Point3D p1 (x,y,z);
		
		//Read region's second point
		std::fscanf(file,"%s",word);
		x = atof(word);
		std::fscanf(file,"%s",word);
		y = atof(word);
		std::fscanf(file,"%s",word);
		z = atof(word);
		Point3D p2 (x,y,z);
		
		//Read Refinement Level
		unsigned short rrl = 0;
		std::fscanf(file,"%s",word);
		rrl = atoi(word);
		
		if (rrl>max_refinement) {
			max_refinement = rrl;
		}
		
		RefinementRegion *rr = new RefinementCubeRegion(p1,p2,rrl);
		
		regions.push_back(rr);
	}
	
	fclose(file);
		
	return max_refinement;
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

int main(int argc,char** argv){
   if (argc<4) {
      endMsg();
      return 0;
   }

   const int n_meshes = 1;
   string in_name, out_name = "";
   string table_name = "table_all";
   bool out_name_given = false, in_name_given = false;
   bool edge_projection = false;

   unsigned short ref_level = 0, rl = 0;
   list<RefinementRegion *> all_regions;
   RefinementRegion *rr;

   vector<double> bounds;
   Point3D pmin,pmax;

   vector<Clobscode::TriMesh> inputs;
   inputs.reserve(1);
   Clobscode::CoteMarek marek;

   //the firs parameter must be the input domain to mesh
   //there must be an input mesh
   if (argv[1][0]=='-' && argv[1][1]=='i') {
      in_name = argv[2];
      for (unsigned long i=1; i<(n_meshes+1); i++) {
         if (!marek.ReadInputMesh(in_name,inputs)) {
            std::cerr << "couldn't read file " << argv[i] << std::endl;
            return 1;
         }
      }
   }
   else {
      cout << "Error: first parameter must be the input domain to mesh\n";
      endMsg();
      return 0;
   }

   for (unsigned long i=3; i<argc; i++) {
      if (argv[i][0]!='-') {
         cout << "Error: expected option -X and got " << argv[i] << "\n";
         endMsg();
         return 0;
      }
      if (argc==i+1) {
         cout << "Error: expected argument for option " << argv[i] << "\n";
         endMsg();
         return 0;
      }

      switch (argv[i][1]) {
         case 'o':
            out_name = argv[i+1];
            out_name_given = true;
            i++;
            break;
         case 'a':
            rl = atoi(argv[i+1]);
            if (ref_level<rl) {
               ref_level = rl;
            }
            //+-10 is an arbitrary number to ensure the Bbox contains
            //the entire input mesh
            rr = new RefinementAllRegion(rl);
            //see if force rotation enable
            if (argv[i][2]=='r') {
               rr->forceInputRotation();
            }
            all_regions.push_back(rr);
            i++;
            break;
         case 's':
            rl = atoi(argv[i+1]);
            if (ref_level<rl) {
               ref_level = rl;
            }
            rr = new RefinementInputSurfaceRegion(rl);
            //see if force rotation enable
            if (argv[i][2]=='r') {
               rr->forceInputRotation();
            }
            all_regions.push_back(rr);
            i++;
            break;
         case 'r':
            unsigned short max_reg;
            max_reg= readRefinementRegions(argv[i+1],all_regions);
            if (ref_level<max_reg) {
               ref_level = max_reg;
            }
            i++;
            break;
         case 'u':
            rl = atoi(argv[i+2]);
            readSurfaceRefinementRegion(argv[i+1],all_regions,rl);
            if (ref_level<rl) {
               ref_level = rl;
            }
            i+=2;
            break;
         case 't':
            table_name = argv[i+1];
            i++;
            break;
         default:
            cerr << "Warning: unknown option " << argv[i] << " skipping\n";
            break;
      }
   }
   //give default output name if non is provided
   if (!out_name_given) {
      unsigned long last_point = in_name.find_last_of(".");
      out_name = in_name.substr(0,last_point);
   }
   auto start_time = chrono::high_resolution_clock::now();
   //Generate the mesh following the above constraints.
   Clobscode::Mesher mesher;
   Clobscode::FEMesh output = mesher.generateMesh(&marek,inputs[0],ref_level,out_name,all_regions,table_name);
   marek.WriteOutputMesh(out_name,output);

   auto end_time = chrono::high_resolution_clock::now();
   cout << "  All done in " << chrono::duration_cast<chrono::milliseconds>(end_time-start_time).count();
   cout << " ms"<< endl;

   list<RefinementRegion *>::iterator rriter;
   for (rriter = all_regions.begin(); rriter!=all_regions.end(); rriter++) {
      delete *rriter;
   }
   return 0;
}
