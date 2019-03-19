#include "SplitVisitor.h"
#include "../Octant.h"

namespace Clobscode
{
    SplitVisitor::SplitVisitor() {
        points = NULL;
        new_pts = NULL;
        edges = NULL;
        new_eles = NULL;
        clipping = NULL;

    }

    void SplitVisitor::setPoints(vector<MeshPoint> &points) {
        this->points = &points;
    }
    
    void SplitVisitor::setNewPts(list<Point3D> &new_pts) {
        this->new_pts = &new_pts;
    }
    
    void SplitVisitor::setEdges(set<OctreeEdge> &edges) {
        this->edges = &edges;
    }
    
    void SplitVisitor::setNewEles(vector<vector<unsigned long> > &new_eles) {
        this->new_eles = &new_eles;
    }
    
    void SplitVisitor::setClipping(vector<vector<Point3D> > &clipping) {
        this->clipping = &clipping;
    }

    double SplitVisitor::getAxis(double min, double max, float val){
    	return min*(1.0-val) + max*(val);
    }

    bool SplitVisitor::visit(Octant *o)
    {
        //getting variables for modification
        //preferably by reference, to avoid unnecesary copying
        vector<unsigned long>&pi = o->pointindex;

        //from now on, it's all old code, verbatim

        //Reservar 27 elementos
        new_eles->reserve(27);

        unsigned long n_pts = points->size() + new_pts->size();
        //the vector containing all nodes of this octant (and sons)
        //Guardar 64 puntos
        vector<unsigned long> all_pts(64,0);


        //save the eight nodes of this cube first
        for (unsigned long i=0; i< pi.size(); i++) {
            all_pts[i] = pi[i];
        }


        // Nueva version structura de un octree de 27 
        //
        //                      4-----18-------19------7
        //                     /                      /
        //                    /                      /   
        //                   16     36       38     22
        //                  /                      /
        //                 /                      /
        //                17     37       39     23
        //               /                      /
        //              /                      /
        //             5-----20--------21-----6
        //                      25----45-------47------29
        //                     /                      /
        //                    /                      /   
        //                  41     60       62      53
        //                  /                      /
        //                 /                      /
        //               43     61       63     55
        //               /                      /
        //              /                      /
        //            27-----49-------51------31
        //                      24----44-------46------28
        //                     /                      /
        //                    /                      /   
        //                  40     56       58      52
        //                  /                      /
        //                 /                      /
        //               42     57       59      54
        //               /                      /
        //              /                      /            y   
        //            26-----48-------50------30            |  
        //                      0----10-------11-------3    0 ---x
        //                     /                      /    /
        //                    /                      /    z
        //                   8     32       34      14
        //                  /                      /
        //                 /                      /
        //                9     33       35     15
        //               /                      /
        //              /                      /
        //             1-----12--------13-----2



        const Point3D min = points->at(pi[0]).getPoint();
        const Point3D max = points->at(pi[6]).getPoint();

        //8 y 9 entre 0 y 1
        if (splitEdge(all_pts[0],all_pts[1],n_pts,all_pts[8],all_pts[9]) ) {
        	//pt8
            new_pts->push_back(Point3D (min[0],min[1], getAxis(min[2],max[2],1.0/3.0)));
            //pt9
            new_pts->push_back(Point3D (min[0],min[1], getAxis(min[2],max[2],2.0/3.0)));
        }
        //10 y 11
        if (splitEdge(all_pts[0],all_pts[3],n_pts,all_pts[10],all_pts[11])) {
            //pt10
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),min[1],min[2]));
            //pt11
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),min[1],min[2]));
        }
        //12 y 13
        if (splitEdge(all_pts[1],all_pts[2],n_pts,all_pts[12],all_pts[13])) {
            //pt12
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),min[1],max[2]));
            //pt13
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),min[1],max[2]));
        }
        //14 y 15
        if (splitEdge(all_pts[3],all_pts[2],n_pts,all_pts[14],all_pts[15])) {
            //pt14
            new_pts->push_back(Point3D (max[0],min[1],getAxis(min[2],max[2],1.0/3.0)));
            //pt15
            new_pts->push_back(Point3D (max[0],min[1],getAxis(min[2],max[2],2.0/3.0)));
        }

        //16 y 17
        if (splitEdge(all_pts[4],all_pts[5],n_pts,all_pts[16],all_pts[17])) {
            //pt16
            new_pts->push_back(Point3D (min[0],max[1],getAxis(min[2],max[2],1.0/3.0)));
            //pt17
            new_pts->push_back(Point3D (min[0],max[1],getAxis(min[2],max[2],2.0/3.0)));
        }
        //18 y 19
        if (splitEdge(all_pts[4],all_pts[7],n_pts,all_pts[18],all_pts[19])) {
            //pt18
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),max[1],min[2]));
            //pt19
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),max[1],min[2]));
        }
        //20 y 21
        if (splitEdge(all_pts[5],all_pts[6],n_pts,all_pts[20],all_pts[21])) {
            //pt20
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),max[1],max[2]));
            //pt21
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),max[1],max[2]));
        }
        //22 y 23
        if (splitEdge(all_pts[7],all_pts[6],n_pts,all_pts[22],all_pts[23])) {
            //pt22
            new_pts->push_back(Point3D (max[0],max[1],getAxis(min[2],max[2],1.0/3.0)));
            //pt23
            new_pts->push_back(Point3D (max[0],max[1],getAxis(min[2],max[2],2.0/3.0)));
        }
        

        //24 y 25
        if (splitEdge(all_pts[0],all_pts[4],n_pts,all_pts[24],all_pts[25])) {
        	//pt24
            new_pts->push_back(Point3D (min[0],getAxis(min[1],max[1],1.0/3.0),min[2]));
            //pt25
            new_pts->push_back(Point3D (min[0],getAxis(min[1],max[1],2.0/3.0),min[2]));
        }
        //26 y 27
        if (splitEdge(all_pts[1],all_pts[5],n_pts,all_pts[26],all_pts[27])) {
            ///pt26
            new_pts->push_back(Point3D (min[0],getAxis(min[1],max[1],1.0/3.0),max[2]));
            ///pt27
            new_pts->push_back(Point3D (min[0],getAxis(min[1],max[1],2.0/3.0),max[2]));
        }
        //28 y 29
        if (splitEdge(all_pts[3],all_pts[7],n_pts,all_pts[28],all_pts[29])) {
            //pt28
            new_pts->push_back(Point3D (max[0],getAxis(min[1],max[1],1.0/3.0),min[2]));
            //pt29
            new_pts->push_back(Point3D (max[0],getAxis(min[1],max[1],2.0/3.0),min[2]));
        }
        //30 y 31
        if (splitEdge(all_pts[2],all_pts[6],n_pts,all_pts[30],all_pts[31])) {
            //pt30
            new_pts->push_back(Point3D (max[0],getAxis(min[1],max[1],1.0/3.0),max[2]));
            //pt31
            new_pts->push_back(Point3D (max[0],getAxis(min[1],max[1],2.0/3.0),max[2]));
        }
        
        //cout << "Split Edges done!" << endl;

        //                      0----10-------11-------3
        //                     /                      /
        //                    /                      /
        //                   8     32       34      14
        //                  /                      /
        //                 /                      /
        //                9     33       35     15
        //               /                      /
        //              /                      /
        //             1-----12--------13-----2


        if (splitFace(all_pts[8],all_pts[9],all_pts[10],all_pts[11],
        	all_pts[12],all_pts[13],all_pts[14],all_pts[15],n_pts,
        	all_pts[32],all_pts[33],all_pts[34],all_pts[35])) {
            //pt32
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),min[1],getAxis(min[2],max[2],1.0/3.0)));
        	//pt33
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),min[1],getAxis(min[2],max[2],2.0/3.0))); 
            //pt34
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),min[1],getAxis(min[2],max[2],1.0/3.0)));
            //pt35
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),min[1],getAxis(min[2],max[2],2.0/3.0)));
        }


        if (splitFace(all_pts[8],all_pts[9],all_pts[24],all_pts[25],
        	all_pts[26],all_pts[27],all_pts[16],all_pts[17],n_pts,
        	all_pts[40],all_pts[42],all_pts[41],all_pts[43])) {
            //pt40
            new_pts->push_back(Point3D (min[0],getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0)));
            //pt42
            new_pts->push_back(Point3D (min[0],getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0)));
            //pt41
            new_pts->push_back(Point3D (min[0],getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0)));
            //pt43
            new_pts->push_back(Point3D (min[0],getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0)));
            
        }

        if (splitFace(all_pts[10],all_pts[11],all_pts[24],all_pts[25],
        all_pts[28],all_pts[29],all_pts[18],all_pts[19],n_pts,
            all_pts[44],all_pts[46],all_pts[45],all_pts[47])) {
            //pt44
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),min[2]));
            //pt46
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),min[2]));
            //pt45
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),min[2]));
            //pt47
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),min[2]));
        }

        if (splitFace(all_pts[12],all_pts[13],all_pts[26],all_pts[27],
            all_pts[30],all_pts[31],all_pts[20],all_pts[21],n_pts,
            all_pts[48],all_pts[50],all_pts[49],all_pts[51])) {
            //pt48
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),max[2]));
            //pt50
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),max[2]));
            //pt49
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),max[2]));
            //pt51
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),max[2]));    
        }


        if (splitFace(all_pts[14],all_pts[15],all_pts[28],all_pts[29],
        	all_pts[30],all_pts[31],all_pts[22],all_pts[23],n_pts,
        	all_pts[52],all_pts[54],all_pts[53],all_pts[55])) {
        	//pt52
            new_pts->push_back(Point3D (max[0],getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0)));
            //pt54
            new_pts->push_back(Point3D (max[0],getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0)));
            //pt53
            new_pts->push_back(Point3D (max[0],getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0)));
            //pt55
            new_pts->push_back(Point3D (max[0],getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0)));
        }
        
        if (splitFace(all_pts[16],all_pts[17],all_pts[18],all_pts[19],
            all_pts[20],all_pts[21],all_pts[22],all_pts[23],n_pts,
            all_pts[36],all_pts[37],all_pts[38],all_pts[39])) {
            //pt36
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),max[1],getAxis(min[2],max[2],1.0/3.0)));
            //pt37
            new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),max[1],getAxis(min[2],max[2],2.0/3.0)));
            //pt38
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),max[1],getAxis(min[2],max[2],1.0/3.0)));
            //pt39
            new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),max[1],getAxis(min[2],max[2],2.0/3.0)));
        }
        
        //inserting node (lower face)
        
        if (splitFace(all_pts[40],all_pts[42],all_pts[44],all_pts[46],
        	all_pts[48],all_pts[50],all_pts[52],all_pts[54],n_pts,
        	all_pts[56],all_pts[57],all_pts[58],all_pts[59])) {
            //pt56
	        new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0)));
	        //pt57
	        new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0)));
	        //pt58
	        new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0)));
	        //pt59
	        new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0)));
        }
        
        //inserting node second level
        
        if (splitFace(all_pts[41],all_pts[43],all_pts[45],all_pts[47],
        	all_pts[49],all_pts[51],all_pts[53],all_pts[55],n_pts,
        	all_pts[60],all_pts[61],all_pts[62],all_pts[63])) {
            //pt60
	        new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0)));
	        //pt61
			new_pts->push_back(Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0)));
	        //pt62
	        new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0)));
	        //pt63
			new_pts->push_back(Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0)));
        }

        //cout << "Split faces Done!" << endl;

        //intern edges

        OctreeEdge intern_edge1 (all_pts[32],all_pts[36]);
        intern_edge1.updateMidPoint(all_pts[56], all_pts[60]);

        OctreeEdge intern_edge2 (all_pts[33],all_pts[37]);
        intern_edge2.updateMidPoint(all_pts[57], all_pts[61]);

        OctreeEdge intern_edge3 (all_pts[34],all_pts[38]);
        intern_edge3.updateMidPoint(all_pts[58], all_pts[62]);

        OctreeEdge intern_edge4 (all_pts[35],all_pts[39]);
        intern_edge4.updateMidPoint(all_pts[59], all_pts[63]);


        edges->insert(intern_edge1);
        edges->insert(intern_edge2);
        edges->insert(intern_edge3);
        edges->insert(intern_edge4);

        edges->insert(OctreeEdge (all_pts[32],all_pts[56]));
        edges->insert(OctreeEdge (all_pts[56],all_pts[60]));
        edges->insert(OctreeEdge (all_pts[60],all_pts[36]));

        edges->insert(OctreeEdge (all_pts[33],all_pts[57]));
        edges->insert(OctreeEdge (all_pts[57],all_pts[61]));
        edges->insert(OctreeEdge (all_pts[61],all_pts[37]));

        edges->insert(OctreeEdge (all_pts[34],all_pts[58]));
        edges->insert(OctreeEdge (all_pts[58],all_pts[62]));
        edges->insert(OctreeEdge (all_pts[62],all_pts[38]));  

        edges->insert(OctreeEdge (all_pts[35],all_pts[59]));
        edges->insert(OctreeEdge (all_pts[59],all_pts[63]));
        edges->insert(OctreeEdge (all_pts[63],all_pts[39]));

        //cout << "Split internal down-up done" << endl;

        //now that all edges were inserted, the elements can be easily built
        vector<unsigned long> son_element (8,0);

        son_element[0]=all_pts[0];
        son_element[1]=all_pts[8];
        son_element[2]=all_pts[32];
        son_element[3]=all_pts[10];

        son_element[4]=all_pts[24];
        son_element[5]=all_pts[40];
        son_element[6]=all_pts[56];
        son_element[7]=all_pts[44];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[8];
        son_element[1]=all_pts[9];
        son_element[2]=all_pts[33];
        son_element[3]=all_pts[32];

        son_element[4]=all_pts[40];
        son_element[5]=all_pts[42];
        son_element[6]=all_pts[57];
        son_element[7]=all_pts[56];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[9];
        son_element[1]=all_pts[1];
        son_element[2]=all_pts[12];
        son_element[3]=all_pts[33];

        son_element[4]=all_pts[42];
        son_element[5]=all_pts[26];
        son_element[6]=all_pts[48];
        son_element[7]=all_pts[57];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[10];
        son_element[1]=all_pts[32];
        son_element[2]=all_pts[34];
        son_element[3]=all_pts[11];

        son_element[4]=all_pts[44];
        son_element[5]=all_pts[56];
        son_element[6]=all_pts[58];
        son_element[7]=all_pts[46];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[32];
        son_element[1]=all_pts[33];
        son_element[2]=all_pts[35];
        son_element[3]=all_pts[34];

        son_element[4]=all_pts[56];
        son_element[5]=all_pts[57];
        son_element[6]=all_pts[59];
        son_element[7]=all_pts[58];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[33];
        son_element[1]=all_pts[12];
        son_element[2]=all_pts[13];
        son_element[3]=all_pts[35];

        son_element[4]=all_pts[57];
        son_element[5]=all_pts[48];
        son_element[6]=all_pts[50];
        son_element[7]=all_pts[59];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[11];
        son_element[1]=all_pts[34];
        son_element[2]=all_pts[14];
        son_element[3]=all_pts[3];

        son_element[4]=all_pts[46];
        son_element[5]=all_pts[58];
        son_element[6]=all_pts[52];
        son_element[7]=all_pts[28];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[34];
        son_element[1]=all_pts[35];
        son_element[2]=all_pts[15];
        son_element[3]=all_pts[14];

        son_element[4]=all_pts[58];
        son_element[5]=all_pts[59];
        son_element[6]=all_pts[54];
        son_element[7]=all_pts[52];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[35];
        son_element[1]=all_pts[13];
        son_element[2]=all_pts[2];
        son_element[3]=all_pts[15];

        son_element[4]=all_pts[59];
        son_element[5]=all_pts[50];
        son_element[6]=all_pts[30];
        son_element[7]=all_pts[54];
        new_eles->push_back(son_element);

		son_element[0]=all_pts[24];
        son_element[1]=all_pts[40];
        son_element[2]=all_pts[56];
        son_element[3]=all_pts[44];

        son_element[4]=all_pts[25];
        son_element[5]=all_pts[41];
        son_element[6]=all_pts[60];
        son_element[7]=all_pts[45];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[40];
        son_element[1]=all_pts[42];
        son_element[2]=all_pts[57];
        son_element[3]=all_pts[56];

        son_element[4]=all_pts[41];
        son_element[5]=all_pts[43];
        son_element[6]=all_pts[61];
        son_element[7]=all_pts[60];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[42];
        son_element[1]=all_pts[26];
        son_element[2]=all_pts[48];
        son_element[3]=all_pts[57];

        son_element[4]=all_pts[43];
        son_element[5]=all_pts[27];
        son_element[6]=all_pts[49];
        son_element[7]=all_pts[61];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[44];
        son_element[1]=all_pts[56];
        son_element[2]=all_pts[58];
        son_element[3]=all_pts[46];

        son_element[4]=all_pts[45];
        son_element[5]=all_pts[60];
        son_element[6]=all_pts[62];
        son_element[7]=all_pts[47];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[56];
        son_element[1]=all_pts[57];
        son_element[2]=all_pts[59];
        son_element[3]=all_pts[58];

        son_element[4]=all_pts[60];
        son_element[5]=all_pts[61];
        son_element[6]=all_pts[63];
        son_element[7]=all_pts[62];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[57];
        son_element[1]=all_pts[48];
        son_element[2]=all_pts[50];
        son_element[3]=all_pts[59];

        son_element[4]=all_pts[61];
        son_element[5]=all_pts[49];
        son_element[6]=all_pts[51];
        son_element[7]=all_pts[63];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[46];
        son_element[1]=all_pts[58];
        son_element[2]=all_pts[52];
        son_element[3]=all_pts[28];

        son_element[4]=all_pts[47];
        son_element[5]=all_pts[62];
        son_element[6]=all_pts[53];
        son_element[7]=all_pts[29];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[58];
        son_element[1]=all_pts[59];
        son_element[2]=all_pts[54];
        son_element[3]=all_pts[52];

        son_element[4]=all_pts[62];
        son_element[5]=all_pts[63];
        son_element[6]=all_pts[55];
        son_element[7]=all_pts[53];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[59];
        son_element[1]=all_pts[50];
        son_element[2]=all_pts[30];
        son_element[3]=all_pts[54];

        son_element[4]=all_pts[63];
        son_element[5]=all_pts[51];
        son_element[6]=all_pts[31];
        son_element[7]=all_pts[55];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[25];
        son_element[1]=all_pts[41];
        son_element[2]=all_pts[60];
        son_element[3]=all_pts[45];

        son_element[4]=all_pts[4];
        son_element[5]=all_pts[16];
        son_element[6]=all_pts[36];
        son_element[7]=all_pts[18];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[41];
        son_element[1]=all_pts[43];
        son_element[2]=all_pts[61];
        son_element[3]=all_pts[60];

        son_element[4]=all_pts[16];
        son_element[5]=all_pts[17];
        son_element[6]=all_pts[37];
        son_element[7]=all_pts[36];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[43];
        son_element[1]=all_pts[27];
        son_element[2]=all_pts[49];
        son_element[3]=all_pts[61];

        son_element[4]=all_pts[17];
        son_element[5]=all_pts[5];
        son_element[6]=all_pts[20];
        son_element[7]=all_pts[37];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[45];
        son_element[1]=all_pts[60];
        son_element[2]=all_pts[62];
        son_element[3]=all_pts[47];

        son_element[4]=all_pts[18];
        son_element[5]=all_pts[36];
        son_element[6]=all_pts[38];
        son_element[7]=all_pts[19];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[60];
        son_element[1]=all_pts[61];
        son_element[2]=all_pts[63];
        son_element[3]=all_pts[62];

        son_element[4]=all_pts[36];
        son_element[5]=all_pts[37];
        son_element[6]=all_pts[39];
        son_element[7]=all_pts[38];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[61];
        son_element[1]=all_pts[49];
        son_element[2]=all_pts[51];
        son_element[3]=all_pts[63];

        son_element[4]=all_pts[37];
        son_element[5]=all_pts[20];
        son_element[6]=all_pts[21];
        son_element[7]=all_pts[39];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[47];
        son_element[1]=all_pts[62];
        son_element[2]=all_pts[53];
        son_element[3]=all_pts[29];

        son_element[4]=all_pts[19];
        son_element[5]=all_pts[38];
        son_element[6]=all_pts[22];
        son_element[7]=all_pts[7];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[62];
        son_element[1]=all_pts[63];
        son_element[2]=all_pts[55];
        son_element[3]=all_pts[53];

        son_element[4]=all_pts[38];
        son_element[5]=all_pts[39];
        son_element[6]=all_pts[23];
        son_element[7]=all_pts[22];
        new_eles->push_back(son_element);

        son_element[0]=all_pts[63];
        son_element[1]=all_pts[51];
        son_element[2]=all_pts[31];
        son_element[3]=all_pts[55];

        son_element[4]=all_pts[39];
        son_element[5]=all_pts[21];
        son_element[6]=all_pts[6];
        son_element[7]=all_pts[23];
        new_eles->push_back(son_element);

        //extreme nodes of each son to be used by clipping
        //method.
        clipping->reserve(27);
        vector<Point3D> extreme_nodes(2, Point3D ());

        // Nodos extremos de cada hijo
        // 0-36
        extreme_nodes[0] = Point3D (min[0],min[1],min[2]);
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0));
        clipping->push_back(extreme_nodes);

        // 8-37
        extreme_nodes[0] = Point3D (min[0],min[1], getAxis(min[2],max[2],1.0/3.0));
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0));
        clipping->push_back(extreme_nodes);

        // 9-30
        extreme_nodes[0] = Point3D (min[0],min[1], getAxis(min[2],max[2],2.0/3.0));
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),max[2]);
        clipping->push_back(extreme_nodes);

        // 15-39
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],1.0/3.0),min[1],min[2]);
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 16-38
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],1.0/3.0),min[1],getAxis(min[2],max[2],1.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 17-31
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],1.0/3.0),min[1],getAxis(min[2],max[2],2.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),max[2]);//
        clipping->push_back(extreme_nodes);


        // 14-33
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],2.0/3.0),min[1],min[2]);//
        extreme_nodes[1] = Point3D (max[0],getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 19-32
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],2.0/3.0),min[1],getAxis(min[2],max[2],1.0/3.0));//
        extreme_nodes[1] = Point3D (max[0],getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 18-24
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],2.0/3.0),min[1],getAxis(min[2],max[2],2.0/3.0));//
        extreme_nodes[1] = Point3D (max[0],getAxis(min[1],max[1],1.0/3.0),max[2]);//
        clipping->push_back(extreme_nodes);

        // 20-48
        extreme_nodes[0] = Point3D (min[0],getAxis(min[1],max[1],1.0/3.0),min[2]);//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 28-49
        extreme_nodes[0] = Point3D (min[0],getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        clipping->push_back(extreme_nodes);

		// 29-42
        extreme_nodes[0] = Point3D (min[0],getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),max[2]);//
        clipping->push_back(extreme_nodes);

		// 35-51
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),min[2]);//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        clipping->push_back(extreme_nodes);

		// 36-50
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        clipping->push_back(extreme_nodes);

		// 37-43
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),max[2]);//
        clipping->push_back(extreme_nodes);

        // 34-45
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),min[2]);//
        extreme_nodes[1] = Point3D (max[0],getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 39-44
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        extreme_nodes[1] = Point3D (max[0],getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 38-25
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],1.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        extreme_nodes[1] = Point3D (max[0],getAxis(min[1],max[1],2.0/3.0),max[2]);//
        clipping->push_back(extreme_nodes);

        // 21-60
        extreme_nodes[0] = Point3D (min[0],getAxis(min[1],max[1],2.0/3.0),min[2]);//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],1.0/3.0),max[1],getAxis(min[2],max[2],1.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 40-61
        extreme_nodes[0] = Point3D (min[0],getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],1.0/3.0),max[1],getAxis(min[2],max[2],2.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 41-54
        extreme_nodes[0] = Point3D (min[0],getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],1.0/3.0),max[1],max[2]);//
        clipping->push_back(extreme_nodes);

        // 47-63
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),min[2]);//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],2.0/3.0),max[1],getAxis(min[2],max[2],1.0/3.0));//
        clipping->push_back(extreme_nodes);

        // 48-62
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],2.0/3.0),max[1],getAxis(min[2],max[2],2.0/3.0));//
        clipping->push_back(extreme_nodes);

		// 49-55
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],1.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0));//
        extreme_nodes[1] = Point3D (getAxis(min[0],max[0],2.0/3.0),max[1],max[2]);//
        clipping->push_back(extreme_nodes);

		// 46-57
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),min[2]);//
        extreme_nodes[1] = Point3D (max[0],max[1],getAxis(min[2],max[2],1.0/3.0));//
        clipping->push_back(extreme_nodes);

		// 51-56
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],1.0/3.0));//
        extreme_nodes[1] = Point3D (max[0],max[1],getAxis(min[2],max[2],2.0/3.0));//
        clipping->push_back(extreme_nodes);

		// 50-6
        extreme_nodes[0] = Point3D (getAxis(min[0],max[0],2.0/3.0),getAxis(min[1],max[1],2.0/3.0),getAxis(min[2],max[2],2.0/3.0));
        extreme_nodes[1] = Point3D (max[0], max[1], max[2]);
        clipping->push_back(extreme_nodes);

        return true;
    }


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------


    bool SplitVisitor::splitEdge(const unsigned long &idx1, const unsigned long &idx2,
                                 unsigned long &c_n_pts, unsigned long &mid_idx1, unsigned long &mid_idx2){

        OctreeEdge this_edge (idx1,idx2);
        set<OctreeEdge>::iterator found = edges->find(this_edge);
        //cout << "Spliting Edges: "<<idx1 << " " << idx2 << endl;

        if ((*found)[2]!=0) {
            //cout << "Found" << endl;
            //cout <<idx1 << " " << (*found)[2] << " " << (*found)[3] << " " << idx2 << endl;
            //if the edge was already split, then save its mid_point and
            //return false (the current process didn't split the edge)
            mid_idx1 = (*found)[2];
            mid_idx2 = (*found)[3];
            ////cout << "c_n_pts: " << c_n_pts << endl;
            return false;
        }
        //cout << "Splitting" << endl;

        //this edge is about to be split. Note that no edge can have point index
        //0 as its mid_point. For this reason, we know that the edge was not
        //split by other octant before. The current edge must be replaced in the
        //set by the same one plus a mid_point equal to c_n_pts (current number
        //of points). The coordinates of this new point will be inserted by the
        //split method above. The splitEdge method will only compute the index
        //for this new point and will insert the two new edges (derived from the
        //splitting process of the current edge). Note that c_n_pts will be
        //increased for next splitting process of another edge.

        unsigned long count = c_n_pts;
        this_edge.updateMidPoint(count, count+1);
        //cout << "Updated" << endl;

        c_n_pts++;
        c_n_pts++;
        
        edges->erase(found);
        //cout << "erased" << endl;
        OctreeEdge e1(this_edge[0],this_edge[2]), e2(this_edge[2],this_edge[3]), e3(this_edge[3],this_edge[1]);
        edges->insert(this_edge);
        edges->insert(e1);
        edges->insert(e2);
        edges->insert(e3);
        //cout << "Inserted" << endl;
        mid_idx1 = this_edge[2];
        mid_idx2 = this_edge[3];

        //cout << "c_n_pts: " << c_n_pts << endl;

        return true;
    }

//--------------------------------------------------------------------------------


        //                      0----3--------4--------3    0 ---x
        //                     /                      /    /
        //                    /                      /    z
        //                   1     9        11      7
        //                  /                      /
        //                 /                      /
        //                2     10       12      8
        //               /                      /
        //              /                      /
        //             1-----5--------6-------2                                             

    bool SplitVisitor::splitFace(const unsigned long &idx1, const unsigned long &idx2,
    	const unsigned long &idx3, const unsigned long &idx4,
    	const unsigned long &idx5, const unsigned long &idx6,
    	const unsigned long &idx7, const unsigned long &idx8,
    	unsigned long &c_n_pts, unsigned long &mid_idx1, unsigned long &mid_idx2, unsigned long &mid_idx3, unsigned long &mid_idx4){
        //cout << "Spliting Face: " << idx1 << " " << idx2 << " "<< idx3 << " "<< idx4 << " "<< idx5 << " "<< idx6 << " "<< idx7 << " "<< idx8 << endl;

        OctreeEdge e1 (idx3,idx5);
        OctreeEdge e3 (idx4,idx6);

        set<OctreeEdge>::iterator found = edges->find(e1);
        set<OctreeEdge>::iterator found2 = edges->find(e3);

        if (found==edges->end() || found2==edges->end()) {
            //cout << "Spliting" << endl;
        	unsigned long count = c_n_pts;

            //this face wasn't split before->
        	e1.updateMidPoint(count, count+1);
            e3.updateMidPoint(count+2, count+3);

            OctreeEdge e2 (idx1,idx7);
            e2.updateMidPoint(count, count+2);
            

            OctreeEdge e4 (idx2,idx8);
            e4.updateMidPoint(count+1, count+3);

            edges->insert(e1);
            edges->insert(e3);
            edges->insert(e2);
            edges->insert(e4);

            //splitting edge e1
            edges->insert(OctreeEdge (idx3,e1[2]));
            edges->insert(OctreeEdge (e1[2],e1[3]));
            edges->insert(OctreeEdge (e1[3],idx5));
            //splitting edge e2
            edges->insert(OctreeEdge (idx1,e2[2]));
            edges->insert(OctreeEdge (e2[2],e2[3]));
            edges->insert(OctreeEdge (e2[3],idx7));
            //splitting edge e3
            edges->insert(OctreeEdge (idx4,e3[2]));
            edges->insert(OctreeEdge (e3[2],e3[3]));
            edges->insert(OctreeEdge (e3[3],idx6));
            //splitting edge e4
            edges->insert(OctreeEdge (idx2,e4[2]));
            edges->insert(OctreeEdge (e4[2],e4[3]));
            edges->insert(OctreeEdge (e4[3],idx8));

            //increase the number fo total points
            mid_idx1 = e1[2];
            mid_idx2 = e1[3];
            mid_idx3 = e3[2];
            mid_idx4 = e3[3];
            c_n_pts+=4;

            ////cout << "c_n_pts: " << c_n_pts << endl;

            return true;
        }
        //cout << "Splited" << endl;
        //at this point, the face was already split. Update the mid index

        
        mid_idx1 = (*found)[2];
        mid_idx2 = (*found)[3];

        mid_idx3 = (*found2)[2];
        mid_idx4 = (*found2)[3];
        return false;
    }

}


