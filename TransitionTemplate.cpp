/*
 * PatternsDefault.cpp
 *
 *  Created on: May 18, 2012
 *      Author: jsepulve
 */

#include "TransitionTemplate.h"

using namespace std;

namespace patterns {

const TransitionTemplate::Permutations_t TransitionTemplate::RotationMatrix[PERMUTATIONS] = {

    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360 --> 0

    Permutations_t(Y,1), /// Y --> 90  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360 --> 0

    Permutations_t(Y,1), /// Y --> 180  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360 --> 0

    Permutations_t(Y,1), /// Y --> 270  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360 --> 0

    Permutations_t(Y,1), /// Y --> 360 --> 0  
    Permutations_t(X,1), /// X --> 90  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1), /// Z --> 360

    Permutations_t(X,2), /// X --> 270 X-->180 is the same Y-->180  
    Permutations_t(Z,1), /// Z --> 90  
    Permutations_t(Z,1), /// Z --> 180 
    Permutations_t(Z,1), /// Z --> 270
    Permutations_t(Z,1)  /// Z --> 360
};


TransitionTemplate::TransitionTemplate(const set<unsigned long> &flag_hex_idxs)  { 

    m_cube = new TransitionCube(flag_hex_idxs);

    // builds a map with default values of corner points (0,1,..7)
    createDefaultMapping(); 

    factory = PatternFactory::instance();
}

TransitionTemplate::TransitionTemplate(const UintVec& nodes,const set<unsigned long> &flag_hex_idxs) {

    m_cube = new TransitionCube(flag_hex_idxs);
    // makes map with values of input vector
    createNodesMapping(nodes);

    factory = PatternFactory::instance();
}

TransitionTemplate::TransitionTemplate(const UintVec& nodes, const UintVec& edges,const set<unsigned long> &flag_hex_idxs) {

    if (edges.size() > 0 ) {
        // Creates a map with nodes and edge values.
        createEdgesMapping(nodes, edges);

        // Create an instance of cube containing edge nodes
        m_cube = new TransitionCube(m_localVector,flag_hex_idxs);
    }
    else {
        createNodesMapping(nodes);
        m_cube = new TransitionCube(flag_hex_idxs);
    }

    factory = PatternFactory::instance();
}

void TransitionTemplate::createDefaultMapping() {

    for (Uint i=0; i<CORNER_POINTS; i++) 
        m_NodesMap.insert( make_pair( i, CubeMapping_t(i , i)) );

}

/// Insert input vector into internal map.
void TransitionTemplate::createNodesMapping(const UintVec& nodes) {
    Uint SIZE = CORNER_POINTS;
    if (nodes.size() < SIZE)
        SIZE = nodes.size();

    /// This map creates a link of first 8 internal number and external points
    // 0 --> (0, 23)
    UintVecIt it = nodes.begin();
    for (Uint i=0; i< SIZE; i++){
        m_NodesMap.insert( make_pair( i, CubeMapping_t(i,*it++)) );
    }

        
}

/// Insert the input vector of edge point into local vector.
void TransitionTemplate::createEdgesMapping(const UintVec& nodes, const UintVec& edges) {

    // insert first eight input nodes into an internal map.
    createNodesMapping(nodes);

    m_localVector.clear();

    UintVecIt itn = nodes.begin() + CORNER_POINTS;
    UintVecIt ite = edges.begin();

    int SIZE;
    if ( nodes.size() > CORNER_POINTS) {

        SIZE = nodes.size() - CORNER_POINTS;

        if ( edges.size() < SIZE )
            SIZE = edges.size();

        //for ( ;itn != nodes.end(); ++itn) {
        for ( int i=0; i<SIZE; i++) {

            // This map is a link of internal and external points
            // The constructor was created with point 123 which is linked to 11
            // Example: 11 --> (11,123)
            m_NodesMap.insert( make_pair( *ite, CubeMapping_t( *ite, *(itn++) ) ) );

            //Keep a local copy of edge nodes.
            m_localVector.push_back( *(ite++) );

        }
    }
}

// Rotate cube until find a pattern
bool TransitionTemplate::findPattern() {

    Coordinate axis;
    int step;

    // Max cube rotation defined in PERMUTATIONS
    for (int i=0; i<PERMUTATIONS; i++) {

        axis = RotationMatrix[i].Axis;
        step = RotationMatrix[i].Step;
        if (axis == X)
            m_cube->rotX(step);
        else if (axis == Y)
            m_cube->rotY(step);
        else if (axis ==Z) 
            m_cube->rotZ(step);

        //Check if rotated cube mask matchs to one the masks in factory.
        if( factory->createPattern( m_cube->getEdgeTransitionPointsMask() ) ){

            factory->vectors(m_result);
            //cout << "ENCONTRADO " << m_cube->getEdgeTransitionPointsMask()  << endl;
            return true;
            
        }
    }

    // Just for debugging
    //cout << "PATRON NO ENCONTRADO " << m_cube->reportRotation() << endl;

    return false;
}


void TransitionTemplate::reset()
{

    if (m_NodesMap.size() > 0)
        m_NodesMap.clear();

    initialize();
}


void TransitionTemplate::initialize()
{
    if (m_localVector.size() > 0)
        m_localVector.clear();

    for(Uint i=0; i<TOTAL_POINTS; i++)
    {
        m_localVector.push_back(i);
    }
}
double TransitionTemplate::getAxis(double min, double max, float val){
    return min*(1.0-val) + max*(val);
}

Uint TransitionTemplate::getNewElements(const UintVec &hex_idxs,
										const UintVec & edge_idxs,
										MeshPointVec & mesh_point,
										Point3DList & tmp_pts,
										VectorTable & new_element,
                                        set<unsigned long> &flag_hex_idxs,
                                        vector<Point3D> &puntosVector,
                                        vector<unsigned long> &idxsVector,
                                        bool check){
    TransitionCube *cube;
    m_NodesMap.clear();
    
    if (edge_idxs.size() > 0 ) {
        // Creates a map with nodes and edge values.
        createEdgesMapping(hex_idxs, edge_idxs);

        // Create an instance of cube containing edge nodes
        cube = new TransitionCube(m_localVector,flag_hex_idxs);
    }
    else {
        createNodesMapping(hex_idxs);
        cube = new TransitionCube(flag_hex_idxs);
    }

    m_cube= cube;

    if (findPattern()) {
        if(check == true){
            //Aca retorno el mask para el caso exploratorio
            Uint ma = m_cube->getEdgeTransitionPointsMask();

            return ma;
        }
        
        
        UintMap points;
        // Returns a map of (rotated,init point)
        m_cube->getCurrentTransitionPoints(points);

        // Determine 8 mid point of this hexahedron
        Point3D p0 = mesh_point[hex_idxs[points.find(0)->second]].getPoint();
        Point3D p1 = mesh_point[hex_idxs[points.find(1)->second]].getPoint();
        Point3D p2 = mesh_point[hex_idxs[points.find(2)->second]].getPoint();
        Point3D p3 = mesh_point[hex_idxs[points.find(3)->second]].getPoint();
        Point3D p4 = mesh_point[hex_idxs[points.find(4)->second]].getPoint();
        Point3D p5 = mesh_point[hex_idxs[points.find(5)->second]].getPoint();
        Point3D p6 = mesh_point[hex_idxs[points.find(6)->second]].getPoint();
        Point3D p7 = mesh_point[hex_idxs[points.find(7)->second]].getPoint();

        vector<Point3D> pt(250); //12 ptos nuevos por T40 y 66 ptos por T7
        pt.clear();

        pt[0] = p0;
        pt[1] = p1;
        pt[2] = p2;
        pt[3] = p3;
        pt[4] = p4;
        pt[5] = p5;
        pt[6] = p6;
        pt[7] = p7;
        pt[8] = p0+((p1-p0)*(1.0/3.0));
        pt[9] = p0+((p1-p0)*(2.0/3.0));
        pt[10] = p0+((p3-p0)*(1.0/3.0));
        pt[11] = p0+((p3-p0)*(2.0/3.0));
        pt[12] = p1+((p2-p1)*(1.0/3.0));
        pt[13] = p1+((p2-p1)*(2.0/3.0));
        pt[14] = p3+((p2-p3)*(1.0/3.0));
        pt[15] = p3+((p2-p3)*(2.0/3.0));
        pt[16] = p4+((p5-p4)*(1.0/3.0));
        pt[17] = p4+((p5-p4)*(2.0/3.0));
        pt[18] = p4+((p7-p4)*(1.0/3.0));
        pt[19] = p4+((p7-p4)*(2.0/3.0));
        pt[20] = p5+((p6-p5)*(1.0/3.0)); 
        pt[21] = p5+((p6-p5)*(2.0/3.0)); 
        pt[22] = p7+((p6-p7)*(1.0/3.0)); 
        pt[23] = p7+((p6-p7)*(2.0/3.0));
        pt[24] = p0+((p4-p0)*(1.0/3.0));
        pt[25] = p0+((p4-p0)*(2.0/3.0)); 
        pt[26] = p1+((p5-p1)*(1.0/3.0));
        pt[27] = p1+((p5-p1)*(2.0/3.0)); 
        pt[28] = p3+((p7-p3)*(1.0/3.0));
        pt[29] = p3+((p7-p3)*(2.0/3.0));
        pt[30] = p2+((p6-p2)*(1.0/3.0));
        pt[31] = p2+((p6-p2)*(2.0/3.0));

        pt[32] = pt[10]+((pt[12]-pt[10])*(1.0/3.0));
        pt[33] = pt[10]+((pt[12]-pt[10])*(2.0/3.0)); 
        pt[34] = pt[11]+((pt[13]-pt[11])*(1.0/3.0));
        pt[35] = pt[11]+((pt[13]-pt[11])*(2.0/3.0)); 
        pt[36] = pt[18]+((pt[20]-pt[18])*(1.0/3.0));
        pt[37] = pt[18]+((pt[20]-pt[18])*(2.0/3.0));
        pt[38] = pt[19]+((pt[21]-pt[19])*(1.0/3.0)); 
        pt[39] = pt[19]+((pt[21]-pt[19])*(2.0/3.0)); 
        pt[40] = pt[8]+((pt[16]-pt[8])*(1.0/3.0)); 
        pt[41] = pt[8]+((pt[16]-pt[8])*(2.0/3.0));
        pt[42] = pt[9]+((pt[17]-pt[9])*(1.0/3.0)); 
        pt[43] = pt[9]+((pt[17]-pt[9])*(2.0/3.0));  
        pt[44] = pt[10]+((pt[18]-pt[10])*(1.0/3.0)); 
        pt[45] = pt[10]+((pt[18]-pt[10])*(2.0/3.0)); 
        pt[46] = pt[11]+((pt[19]-pt[11])*(1.0/3.0)); 
        pt[47] = pt[11]+((pt[19]-pt[11])*(2.0/3.0)); 
        pt[48] = pt[12]+((pt[20]-pt[12])*(1.0/3.0));
        pt[49] = pt[12]+((pt[20]-pt[12])*(2.0/3.0)); 
        pt[50] = pt[13]+((pt[21]-pt[13])*(1.0/3.0)); 
        pt[51] = pt[13]+((pt[21]-pt[13])*(2.0/3.0)); 
        pt[52] = pt[14]+((pt[22]-pt[14])*(1.0/3.0));
        pt[53] = pt[14]+((pt[22]-pt[14])*(2.0/3.0));
        pt[54] = pt[15]+((pt[23]-pt[15])*(1.0/3.0));
        pt[55] = pt[15]+((pt[23]-pt[15])*(2.0/3.0)); 
        pt[56] = pt[44]+((pt[48]-pt[44])*(1.0/3.0));//TODO equiv pto 116
        pt[57] = pt[44]+((pt[48]-pt[44])*(2.0/3.0));
        pt[58] = pt[46]+((pt[50]-pt[46])*(1.0/3.0));//TODO equiv pto 120 y 151
        pt[59] = pt[46]+((pt[50]-pt[46])*(2.0/3.0));//TODO equiv pto 146
        pt[60] = pt[45]+((pt[49]-pt[45])*(1.0/3.0));//TODO equiv pto 117
        pt[61] = pt[45]+((pt[49]-pt[45])*(2.0/3.0));
        pt[62] = pt[47]+((pt[51]-pt[47])*(1.0/3.0));//TODO equiv pto 121 y 150
        pt[63] = pt[47]+((pt[51]-pt[47])*(2.0/3.0));//TODO equiv pto 147
 
        //Puntos Extras! Puntos Patron 2 Edge 0-3
        pt[64] = pt[32]+((pt[34]-pt[32])*(1.0/3.0));//TODO equiv pto 118
        pt[65] = pt[32]+((pt[34]-pt[32])*(2.0/3.0));//TODO equiv pto 119
        pt[66] = pt[10]+((pt[64]-pt[10])*(2.0/3.0));//TODO equiv pto 129
        pt[67] = pt[11]+((pt[65]-pt[11])*(2.0/3.0));//TODO equiv pto 131
        pt[68] = pt[60]+((pt[62]-pt[60])*(1.0/3.0));
        pt[69] = pt[60]+((pt[62]-pt[60])*(2.0/3.0));
        pt[70] = pt[18]+((pt[68]-pt[18])*(2.0/3.0));//TODO equiv pto 206
        pt[71] = pt[19]+((pt[69]-pt[19])*(2.0/3.0));//TODO equiv pto 207
        pt[72] = pt[66]+((pt[70]-pt[66])*(2.0/3.0));//
        pt[73] = pt[67]+((pt[71]-pt[67])*(2.0/3.0));//

        //Puntos Patron 2 Edge 0-1
        pt[74] = pt[32]+((pt[33]-pt[32])*(1.0/3.0));
        pt[75] = pt[32]+((pt[33]-pt[32])*(2.0/3.0));
        pt[76] = pt[8]+((pt[74]-pt[8])*(2.0/3.0));//
        pt[77] = pt[9]+((pt[75]-pt[9])*(2.0/3.0));//
        pt[78] = pt[60]+((pt[61]-pt[60])*(1.0/3.0));
        pt[79] = pt[60]+((pt[61]-pt[60])*(2.0/3.0));//TODO equiv pto 107
        pt[80] = pt[16]+((pt[78]-pt[16])*(2.0/3.0));//TODO equiv pto 204
        pt[81] = pt[17]+((pt[79]-pt[17])*(2.0/3.0));//TODO equiv pto 205
        pt[82] = pt[76]+((pt[80]-pt[76])*(2.0/3.0));//
        pt[83] = pt[77]+((pt[81]-pt[77])*(2.0/3.0));//

        //Puntos Patron 2 Edge 1-2
        pt[84] = pt[33]+((pt[35]-pt[33])*(1.0/3.0));
        pt[85] = pt[33]+((pt[35]-pt[33])*(2.0/3.0));
        pt[86] = pt[84]+((pt[12]-pt[84])*(1.0/3.0));//
        pt[87] = pt[85]+((pt[13]-pt[85])*(1.0/3.0));//
        pt[88] = pt[61]+((pt[63]-pt[61])*(1.0/3.0));//TODO equiv pto 113
        pt[89] = pt[61]+((pt[63]-pt[61])*(2.0/3.0));
        pt[90] = pt[88]+((pt[20]-pt[88])*(2.0/3.0));
        pt[91] = pt[89]+((pt[21]-pt[89])*(2.0/3.0));
        pt[92] = pt[86]+((pt[90]-pt[86])*(1.0/3.0));//
        pt[93] = pt[87]+((pt[91]-pt[87])*(1.0/3.0));//

        //Puntos Patron 2 Edge 2-3
        pt[94] = pt[34]+((pt[35]-pt[34])*(1.0/3.0));//TODO equiv pto 144
        pt[95] = pt[34]+((pt[35]-pt[34])*(2.0/3.0));//TODO equiv pto 145
        pt[96] = pt[94]+((pt[14]-pt[94])*(1.0/3.0));//TODO equiv pto 153
        pt[97] = pt[95]+((pt[15]-pt[95])*(1.0/3.0));//TODO equiv pto 155
        pt[98] = pt[62]+((pt[63]-pt[62])*(1.0/3.0));
        pt[99] = pt[62]+((pt[63]-pt[62])*(2.0/3.0));
        pt[100] = pt[98]+((pt[22]-pt[98])*(2.0/3.0));
        pt[101] = pt[99]+((pt[23]-pt[99])*(2.0/3.0));
        pt[102] = pt[96]+((pt[100]-pt[96])*(1.0/3.0));//
        pt[103] = pt[97]+((pt[101]-pt[97])*(1.0/3.0));//

        
        //Puntos Patron 3 Edge 0-1
        pt[104] = pt[24]+((pt[56]-pt[24])*(2.0/3.0));//TODO equiv pto 127
        pt[105] = pt[25]+((pt[60]-pt[25])*(2.0/3.0));//TODO equiv pto 125
        
        pt[106] = pt[56]+((pt[57]-pt[56])*(2.0/3.0));
        pt[107] = pt[60]+((pt[61]-pt[60])*(2.0/3.0));//TODO equiv pto 79

        pt[108] = pt[42]+((pt[106]-pt[42])*(2.0/3.0));//
        pt[109] = pt[43]+((pt[107]-pt[43])*(2.0/3.0));//

        //Puntos Patron 3 Edge 1-2
        pt[110] = pt[59]+((pt[30]-pt[59])*(1.0/3.0));//TODO equiv pto 157
        pt[111] = pt[63]+((pt[31]-pt[63])*(1.0/3.0));//TODO equiv pto 159

        pt[112] = pt[57]+((pt[59]-pt[57])*(1.0/3.0));
        pt[113] = pt[61]+((pt[63]-pt[61])*(1.0/3.0));//TODO equiv pto 88

        pt[114] = pt[112]+((pt[48]-pt[112])*(1.0/3.0));//
        pt[115] = pt[113]+((pt[49]-pt[113])*(1.0/3.0));//

        //Puntos Patron 3 Edge 0-3

        pt[116] = pt[32]+((pt[36]-pt[32])*(1.0/3.0));//TODO equiv pto 56
        pt[117] = pt[32]+((pt[36]-pt[32])*(2.0/3.0));//TODO equiv pto 60

        pt[118] = pt[32]+((pt[34]-pt[32])*(1.0/3.0));//TODO equiv pto 64
        pt[119] = pt[32]+((pt[34]-pt[32])*(2.0/3.0));//TODO equiv pto 65

        pt[120] = pt[34]+((pt[38]-pt[34])*(1.0/3.0));//TODO equiv pto 58
        pt[121] = pt[34]+((pt[38]-pt[34])*(2.0/3.0));//TODO equiv pto 62

        pt[122] = pt[36]+((pt[38]-pt[36])*(1.0/3.0));
        pt[123] = pt[36]+((pt[38]-pt[36])*(2.0/3.0));
        //-----
        pt[124] = pt[25]+((pt[117]-pt[25])*(1.0/3.0));
        pt[125] = pt[25]+((pt[117]-pt[25])*(2.0/3.0));//TODO equiv pto 105

        pt[126] = pt[24]+((pt[116]-pt[24])*(1.0/3.0));
        pt[127] = pt[24]+((pt[116]-pt[24])*(2.0/3.0));//TODO equiv pto 104

        pt[128] = pt[10]+((pt[118]-pt[10])*(1.0/3.0));
        pt[129] = pt[10]+((pt[118]-pt[10])*(2.0/3.0));//TODO equiv pto 66

        pt[130] = pt[11]+((pt[119]-pt[11])*(1.0/3.0));
        pt[131] = pt[11]+((pt[119]-pt[11])*(2.0/3.0));//TODO equiv pto 67

        pt[132] = pt[28]+((pt[120]-pt[28])*(1.0/3.0));//TODO equiv pto 166
        pt[133] = pt[28]+((pt[120]-pt[28])*(2.0/3.0));//TODO equiv pto 167

        pt[134] = pt[29]+((pt[121]-pt[29])*(1.0/3.0));//TODO equiv pto 164
        pt[135] = pt[29]+((pt[121]-pt[29])*(2.0/3.0));//TODO equiv pto 165

        pt[136] = pt[19]+((pt[123]-pt[19])*(1.0/3.0));
        pt[137] = pt[19]+((pt[123]-pt[19])*(2.0/3.0));//TODO equiv pto 187

        pt[138] = pt[18]+((pt[122]-pt[18])*(1.0/3.0));
        pt[139] = pt[18]+((pt[122]-pt[18])*(2.0/3.0));//TODO equiv pto 186
        //------
        pt[140] = pt[124]+((pt[134]-pt[124])*(1.0/3.0));//
        pt[141] = pt[124]+((pt[134]-pt[124])*(2.0/3.0));//

        pt[142] = pt[126]+((pt[132]-pt[126])*(1.0/3.0));//
        pt[143] = pt[126]+((pt[132]-pt[126])*(2.0/3.0));//

        //Puntos Patron 3 Edge 2-3

        pt[144] = pt[34]+((pt[35]-pt[34])*(1.0/3.0));//TODO equiv pto 94
        pt[145] = pt[34]+((pt[35]-pt[34])*(2.0/3.0));//TODO equiv pto 95
        pt[146] = pt[35]+((pt[39]-pt[35])*(1.0/3.0));//TODO equiv pto 59
        pt[147] = pt[35]+((pt[39]-pt[35])*(2.0/3.0));//TODO equiv pto 63
        pt[148] = pt[38]+((pt[39]-pt[38])*(2.0/3.0));
        pt[149] = pt[38]+((pt[39]-pt[38])*(1.0/3.0));
        pt[150] = pt[34]+((pt[38]-pt[34])*(2.0/3.0));//TODO equiv pto 62
        pt[151] = pt[34]+((pt[38]-pt[34])*(1.0/3.0));//TODO equiv pto 58
        //--------
        pt[152] = pt[14]+((pt[144]-pt[14])*(1.0/3.0));
        pt[153] = pt[14]+((pt[144]-pt[14])*(2.0/3.0));//TODO equiv pto 96

        pt[154] = pt[15]+((pt[145]-pt[15])*(1.0/3.0));
        pt[155] = pt[15]+((pt[145]-pt[15])*(2.0/3.0));//TODO equiv pto 97

        pt[156] = pt[30]+((pt[146]-pt[30])*(1.0/3.0));
        pt[157] = pt[30]+((pt[146]-pt[30])*(2.0/3.0));//TODO equiv pto 110

        pt[158] = pt[31]+((pt[147]-pt[31])*(1.0/3.0));
        pt[159] = pt[31]+((pt[147]-pt[31])*(2.0/3.0));//TODO equiv pto 111

        pt[160] = pt[23]+((pt[148]-pt[23])*(1.0/3.0));
        pt[161] = pt[23]+((pt[148]-pt[23])*(2.0/3.0));

        pt[162] = pt[22]+((pt[149]-pt[22])*(1.0/3.0));
        pt[163] = pt[22]+((pt[149]-pt[22])*(2.0/3.0));

        pt[164] = pt[29]+((pt[150]-pt[29])*(1.0/3.0));//TODO equiv pto 134
        pt[165] = pt[29]+((pt[150]-pt[29])*(2.0/3.0));//TODO equiv pto 135

        pt[166] = pt[28]+((pt[151]-pt[28])*(1.0/3.0));//TODO equiv pto 132
        pt[167] = pt[28]+((pt[151]-pt[28])*(2.0/3.0));//TODO equiv pto 133
        //---
        pt[168] = pt[152]+((pt[162]-pt[152])*(1.0/3.0));
        pt[169] = pt[152]+((pt[162]-pt[152])*(2.0/3.0));
        
        pt[170] = pt[154]+((pt[160]-pt[154])*(1.0/3.0));
        pt[171] = pt[154]+((pt[160]-pt[154])*(2.0/3.0));

        // Puntos patron T40
        Point3D pt106_aux;
        pt106_aux = pt[56] + ((pt[57]-pt[56])*(1.0/3.0));
        pt[172] = pt[8] + ((pt106_aux-pt[8])*(2.0/3.0));//TODO equiv pto 196
        pt[173] = pt[9] + ((pt[106]-pt[9])*(2.0/3.0));//TODO equiv pto 197
        pt[174] = pt[3] + ((pt[57]-pt[3])*(2.0/3.0));
        pt[175] = pt[2] + ((pt[56]-pt[2])*(2.0/3.0));
        pt[176] = pt[4] + ((pt[57]-pt[4])*(2.0/3.0));
        pt[177] = pt[5] + ((pt[56]-pt[5])*(2.0/3.0));
        pt[178] = pt[22] + ((pt[98]-pt[22])*(2.0/3.0));
        pt[179] = pt[23] + ((pt[99]-pt[23])*(2.0/3.0));
        pt[180] = pt[4] + ((pt[63]-pt[4])*(2.0/3.0));
        pt[181] = pt[5] + ((pt[62]-pt[5])*(2.0/3.0));
        pt[182] = pt[3] + ((pt[63]-pt[3])*(2.0/3.0));//TODO equiv pto 242
        pt[183] = pt[2] + ((pt[62]-pt[2])*(2.0/3.0));//TODO equiv pto 243

        //Puntos patron T7
        // Ptos auxiliares para el calculo de otros ptos.
        Point3D aux1, aux2;
        Point3D aux05, aux06;
        Point3D aux07, aux08;
        Point3D aux09, aux10;
        Point3D aux11, aux12;
        Point3D aux15, aux16;
        Point3D aux17, aux18;

        //--- SUPERFICIE (exterior) ---
        //Cara 1: {4 5 6 7}
        aux1 = pt[36] + ((pt[37]-pt[36])*(1.0/3.0));
        aux2 = pt[36] + ((pt[37]-pt[36])*(2.0/3.0));
        pt[184] = pt[16] + ((aux1-pt[16])*(2.0/3.0));
        pt[185] = pt[17] + ((aux2-pt[17])*(2.0/3.0));
        aux1 = pt[36] + ((pt[38]-pt[36])*(1.0/3.0));
        aux2 = pt[36] + ((pt[38]-pt[36])*(2.0/3.0));
        pt[186] = pt[18] + ((aux1-pt[18])*(2.0/3.0));//TODO equiv pto 139
        pt[187] = pt[19] + ((aux2-pt[19])*(2.0/3.0));//TODO equiv pto 137
        //Cara 2: {1 2 6 5}
        aux1 = pt[48] + ((pt[50]-pt[48])*(1.0/3.0));
        aux2 = pt[48] + ((pt[50]-pt[48])*(2.0/3.0));
        pt[188] = pt[12] + ((aux1-pt[12])*(2.0/3.0));
        pt[189] = pt[13] + ((aux2-pt[13])*(2.0/3.0));
        aux1 = pt[48] + ((pt[49]-pt[48])*(1.0/3.0));
        aux2 = pt[48] + ((pt[49]-pt[48])*(2.0/3.0));
        pt[190] = pt[26] + ((aux1-pt[26])*(2.0/3.0));
        pt[191] = pt[27] + ((aux2-pt[27])*(2.0/3.0));
        //Cara 3: {2 3 7 6}
        aux1 = pt[52] + ((pt[54]-pt[52])*(1.0/3.0));
        aux2 = pt[52] + ((pt[54]-pt[52])*(2.0/3.0));
        pt[192] = pt[14] + ((aux1-pt[14])*(2.0/3.0));
        pt[193] = pt[15] + ((aux2-pt[15])*(2.0/3.0));
        aux1 = pt[52] + ((pt[53]-pt[52])*(1.0/3.0));
        aux2 = pt[52] + ((pt[53]-pt[52])*(2.0/3.0));
        pt[194] = pt[28] + ((aux1-pt[28])*(2.0/3.0));
        pt[195] = pt[29] + ((aux2-pt[29])*(2.0/3.0));
        //--- INTERIOR ---
        //Cara 1: {0 1 57 56}
        aux1 = pt[56] + ((pt[57]-pt[56])*(1.0/3.0));
        aux2 = pt[56] + ((pt[57]-pt[56])*(2.0/3.0));
        pt[196] = pt[8] + ((aux1-pt[8])*(2.0/3.0));//TODO equiv pto 172
        pt[197] = pt[9] + ((aux2-pt[9])*(2.0/3.0));//TODO equiv pto 173
        //Cara 2: {0 56 58 3}
        aux1 = pt[56] + ((pt[58]-pt[56])*(1.0/3.0));
        aux2 = pt[56] + ((pt[58]-pt[56])*(2.0/3.0));
        pt[198] = pt[10] + ((aux1-pt[10])*(2.0/3.0));
        pt[199] = pt[11] + ((aux2-pt[11])*(2.0/3.0));
        //Cara 3: {1 2 59 57}
        aux1 = pt[57] + ((pt[59]-pt[57])*(1.0/3.0));
        aux2 = pt[57] + ((pt[59]-pt[57])*(2.0/3.0));
        pt[200] = pt[12] + ((aux1-pt[12])*(2.0/3.0));
        pt[201] = pt[13] + ((aux2-pt[13])*(2.0/3.0));
        aux05 = pt[12] + ((aux1-pt[12])*(1.0/3.0));
        aux06 = pt[13] + ((aux2-pt[13])*(1.0/3.0));
        //Cara 4: {58 59 2 3}
        aux1 = pt[58] + ((pt[59]-pt[58])*(1.0/3.0));
        aux2 = pt[58] + ((pt[59]-pt[58])*(2.0/3.0));
        pt[202] = pt[14] + ((aux1-pt[14])*(2.0/3.0));
        pt[203] = pt[15] + ((aux2-pt[15])*(2.0/3.0));
        aux07 = pt[14] + ((aux1-pt[14])*(1.0/3.0));
        aux08 = pt[15] + ((aux2-pt[15])*(1.0/3.0));
        //Cara 5: {4 5 61 60}
        aux1 = pt[60] + ((pt[61]-pt[60])*(1.0/3.0));
        aux2 = pt[60] + ((pt[61]-pt[60])*(2.0/3.0));
        pt[204] = pt[16] + ((aux1-pt[16])*(2.0/3.0));//TODO equiv pto 80
        pt[205] = pt[17] + ((aux2-pt[17])*(2.0/3.0));//TODO equiv pto 81
        aux09 = pt[16] + ((aux1-pt[16])*(1.0/3.0));
        aux10 = pt[17] + ((aux2-pt[17])*(1.0/3.0));
        //Cara 6: {4 60 62 7}
        aux1 = pt[60] + ((pt[62]-pt[60])*(1.0/3.0));
        aux2 = pt[60] + ((pt[62]-pt[60])*(2.0/3.0));
        pt[206] = pt[18] + ((aux1-pt[18])*(2.0/3.0));//TODO equiv pto 70
        pt[207] = pt[19] + ((aux2-pt[19])*(2.0/3.0));//TODO equiv pto 71
        aux11 = pt[18] + ((aux1-pt[18])*(1.0/3.0));
        aux12 = pt[19] + ((aux2-pt[19])*(1.0/3.0));
        //Cara 5: {0 56 60 4} (vertical)
        aux1 = pt[56] + ((pt[60]-pt[56])*(1.0/3.0));
        aux2 = pt[56] + ((pt[60]-pt[56])*(2.0/3.0));
        pt[208] = pt[24] + ((aux1-pt[24])*(2.0/3.0));
        pt[209] = pt[25] + ((aux2-pt[25])*(2.0/3.0));
        //Cara 6: {1 57 61 5}
        aux1 = pt[57] + ((pt[61]-pt[57])*(1.0/3.0));
        aux2 = pt[57] + ((pt[61]-pt[57])*(2.0/3.0));
        pt[210] = pt[26] + ((aux1-pt[26])*(2.0/3.0));
        pt[211] = pt[27] + ((aux2-pt[27])*(2.0/3.0));
        aux15 = pt[26] + ((aux1-pt[26])*(1.0/3.0));
        aux16 = pt[27] + ((aux2-pt[27])*(1.0/3.0));
        //Cara 7: {58 3 7 62}
        aux1 = pt[58] + ((pt[62]-pt[58])*(1.0/3.0));
        aux2 = pt[58] + ((pt[62]-pt[58])*(2.0/3.0));
        pt[212] = pt[28] + ((aux1-pt[28])*(2.0/3.0));
        pt[213] = pt[29] + ((aux2-pt[29])*(2.0/3.0));
        aux17 = pt[28] + ((aux1-pt[28])*(1.0/3.0));
        aux18 = pt[29] + ((aux2-pt[29])*(1.0/3.0));
        //Hexa 1: {0 1 2 3 56 57 59 58}
        pt[214] = pt[32] + ((pt[56]-pt[32])*(1.0/3.0));
        pt[215] = pt[33] + ((pt[57]-pt[33])*(1.0/3.0));
        pt[216] = pt[34] + ((pt[58]-pt[34])*(1.0/3.0));
        pt[217] = pt[35] + ((pt[59]-pt[35])*(1.0/3.0));
        //Hexa 2: {4 5 6 7 60 61 63 62}
        pt[218] = pt[36] + ((pt[60]-pt[36])*(1.0/3.0));//centro
        pt[219] = pt[37] + ((pt[61]-pt[37])*(1.0/3.0));
        pt[220] = pt[38] + ((pt[62]-pt[38])*(1.0/3.0));
        pt[221] = pt[39] + ((pt[63]-pt[39])*(1.0/3.0));
        aux1 = pt[218] + ((pt[219]-pt[218])*(1.0/3.0));//otros
        aux2 = pt[218] + ((pt[219]-pt[218])*(2.0/3.0));
        pt[222] = aux09 + ((aux1-aux09)*(2.0/3.0));
        pt[223] = aux10 + ((aux2-aux10)*(2.0/3.0));
        aux1 = pt[218] + ((pt[220]-pt[218])*(1.0/3.0));
        aux2 = pt[218] + ((pt[220]-pt[218])*(2.0/3.0));
        pt[224] = aux11 + ((aux1-aux11)*(2.0/3.0));
        pt[225] = aux12 + ((aux2-aux12)*(2.0/3.0));
        //Hexa 3: {0 1 57 56 4 5 61 60} (vertical)
        pt[226] = pt[40] + ((pt[56]-pt[40])*(1.0/3.0));
        pt[227] = pt[41] + ((pt[60]-pt[41])*(1.0/3.0));
        pt[228] = pt[42] + ((pt[57]-pt[42])*(1.0/3.0));
        pt[229] = pt[43] + ((pt[61]-pt[43])*(1.0/3.0));
        //Hexa 4: {0 56 58 3 4 60 62 7}
        pt[230] = pt[44] + ((pt[56]-pt[44])*(1.0/3.0));
        pt[231] = pt[45] + ((pt[60]-pt[45])*(1.0/3.0));
        pt[232] = pt[46] + ((pt[58]-pt[46])*(1.0/3.0));
        pt[233] = pt[47] + ((pt[62]-pt[47])*(1.0/3.0));
        //Hexa 5: {57 1 2 59 61 5 6 63}
        pt[234] = pt[1] + ((pt[63]-pt[1])*(2.0/3.0));//centro
        pt[235] = pt[2] + ((pt[61]-pt[2])*(2.0/3.0));
        pt[236] = pt[5] + ((pt[59]-pt[5])*(2.0/3.0));
        pt[237] = pt[6] + ((pt[57]-pt[6])*(2.0/3.0));
        aux1 = pt[234] + ((pt[235]-pt[234])*(1.0/3.0));//otro
        aux2 = pt[234] + ((pt[235]-pt[234])*(1.0/3.0));
        pt[238] = aux05 + ((aux1-aux05)*(2.0/3.0));
        pt[239] = aux06 + ((aux2-aux06)*(2.0/3.0));
        aux1 = pt[234] + ((pt[236]-pt[234])*(1.0/3.0));
        aux2 = pt[234] + ((pt[236]-pt[234])*(1.0/3.0));
        pt[240] = aux15 + ((aux1-aux15)*(2.0/3.0));
        pt[241] = aux16 + ((aux2-aux16)*(2.0/3.0));
        //Hexa 6: {58 59 2 3 62 63 6 7}
        pt[242] = pt[3] + ((pt[63]-pt[3])*(2.0/3.0));//centro //TODO equiv pto 182
        pt[243] = pt[2] + ((pt[62]-pt[2])*(2.0/3.0));//TODO equiv pto 183
        pt[244] = pt[7] + ((pt[59]-pt[7])*(2.0/3.0));
        pt[245] = pt[6] + ((pt[58]-pt[6])*(2.0/3.0));
        aux1 = pt[242] + ((pt[243]-pt[242])*(1.0/3.0));//otro
        aux2 = pt[242] + ((pt[243]-pt[242])*(2.0/3.0));
        pt[246] = aux07 + ((aux1-aux07)*(2.0/3.0));
        pt[247] = aux08 + ((aux2-aux08)*(2.0/3.0));
        aux1 = pt[242] + ((pt[244]-pt[242])*(1.0/3.0));
        aux2 = pt[242] + ((pt[244]-pt[242])*(2.0/3.0));
        pt[248] = aux17 + ((aux1-aux17)*(2.0/3.0));
        pt[249] = aux18 + ((aux2-aux18)*(2.0/3.0));



        vector<Uint> idxs(172+12,-1);

        for (int i = 0; i < 64; i++) {
            if(points.find(i) != points.end()){
                idxs[i] = m_NodesMap.find(points.find(i)->second)->second.External; // Rellena todos los Ids del mapa de puntos
            }
        }

        // The found pattern is returned in m_result
        for (VectorTableIt it=m_result.begin(); it != m_result.end(); ++it) {
            // Temporay vector
            UintVec temp_vector;
            for (UintVecIt it1=(*it).begin() ; it1 != (*it).end(); ++it1) {
                if(idxs[*it1] == -1){ // Se busca el Id en el vector
                    int i = 0;
                    bool flag = false;
                    for(i;i<puntosVector.size();i++){
                        if(puntosVector[i] == pt[*it1]){ // Se encuentra en el vector global
                            flag = true;
                            break;
                        }
                    }
                    if(flag){
                        idxs[*it1] = idxsVector[i]; //Encuentra el Id en el vector global
                        tmp_pts.push_back(pt[*it1]); 
                    }
                    else{
                        idxs[*it1] = mesh_point.size() + tmp_pts.size(); //Crea el Id
                        tmp_pts.push_back(pt[*it1]);

                        idxsVector.push_back(idxs[*it1]); // Agrega al Idx al Vector Global
                        puntosVector.push_back(pt[*it1]); // Agrega los puntos al Vector Global
                    }
                }
                temp_vector.push_back(idxs[*it1]); 
            }
            new_element.push_back(temp_vector);
        }
        return m_cube->getEdgeTransitionPointsMask();
    }
    return 0;
}


void TransitionTemplate::vectors(VectorTable &v) {

    UintMap points;

    // Returns a map of (rotated,init point)
    m_cube->getCurrentTransitionPoints(points);

    if(!m_result.empty()) {
       for (VectorTableIt it=m_result.begin(); it != m_result.end(); ++it) {
   
           UintVec p;
   
           for (UintVecIt it1=(*it).begin(); it1!=(*it).end(); ++it1) {
               Uint internal = points.find(*it1)->second;
               p.push_back( m_NodesMap.find(internal)->second.External );
           }
            
           v.push_back(p);
       }
    }
}

void TransitionTemplate::normal_vectors(VectorTable &v) {

    UintMap points;

    // Returns: rotated --> init point
    m_cube->getCurrentTransitionPoints(points);


    for (VectorTableIt it=m_result.begin(); it != m_result.end(); ++it) {

        UintVec p;

        for (UintVecIt it1=(*it).begin(); it1!=(*it).end(); ++it1) 
            p.push_back(points.find(*it1)->second);

        v.push_back(p);
    }
}
}

