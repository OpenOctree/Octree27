#include <string>
#include <cctype>
#include "SurfPrism.h"
#include "SurfPyramid.h"


using std::cout;
using std::vector;
using std::string;

using Clobscode::SurfPrism;
using Clobscode::SurfPyramid;

//-------------------------------------------------------------------
//-------------------------------------------------------------------

int main(int argc,char** argv){
	
    vector<unsigned long> pri(6,0), pyr(5,0);
    
    for (unsigned long i=0; i<6; i++) {
        pri[i] = i+20;
    }
    
    for (unsigned long i=0; i<5; i++) {
        pyr[i] = i+20;
    }
    
    vector<bool> pri_in_nodes(6,false);
    pri_in_nodes[1] = true;
    pri_in_nodes[0] = true;
    
    SurfPrism prism(pri);
    vector<vector<unsigned long> > sub_eles = prism.getSubElements(pri_in_nodes);
    
    cout << "for the prism we got:\n";
    
    for (unsigned long i=0; i<sub_eles.size(); i++) {
        vector<unsigned long> elem = sub_eles[i];
        cout << "new element";
        for (unsigned long j=0; j<elem.size(); j++) {
            cout << " " << elem[j];
        }
        cout << "\n";
    }
    
    SurfPyramid pyramid(pyr);
    
    vector<bool> pyr_in_nodes(5,false);
    pyr_in_nodes[1] = true;
    pyr_in_nodes[4] = true;
    pyr_in_nodes[3] = true;
    pyr_in_nodes[2] = true;
    
    sub_eles = pyramid.getSubElements(pyr_in_nodes);
    
    cout << "for the pyramid we got:\n";
    
    for (unsigned long i=0; i<sub_eles.size(); i++) {
        vector<unsigned long> elem = sub_eles[i];
        cout << "new element";
        for (unsigned long j=0; j<elem.size(); j++) {
            cout << " " << elem[j];
        }
        cout << "\n";
    }
	
	return 0;
}

