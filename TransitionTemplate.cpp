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
    //cout << "\n**No-Pattern report: " << m_cube->reportRotation(); //DEBUG
    //cout << "\nPattern no encontrado: " << m_cube->getEdgeTransitionPointsMask(); //DEBUG
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

// tt.getNewElements(nodes,mid_nodes,*points,local_new_pts,new_eles,l_mid_nodes_v, *puntosVector, *idxsVector, true);
// tt.getNewElements(nodes,mid_nodes,*points,*new_pts,sub_elements,l_mid_nodes_v, *puntosVector, *idxsVector, false);
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

        vector<Point3D> pt(232); //12 ptos nuevos por T40 y 66 ptos por T7
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
        pt[56] = pt[44]+((pt[48]-pt[44])*(1.0/3.0));
        pt[57] = pt[44]+((pt[48]-pt[44])*(2.0/3.0));
        pt[58] = pt[46]+((pt[50]-pt[46])*(1.0/3.0));
        pt[59] = pt[46]+((pt[50]-pt[46])*(2.0/3.0));
        pt[60] = pt[45]+((pt[49]-pt[45])*(1.0/3.0));
        pt[61] = pt[45]+((pt[49]-pt[45])*(2.0/3.0));
        pt[62] = pt[47]+((pt[51]-pt[47])*(1.0/3.0));
        pt[63] = pt[47]+((pt[51]-pt[47])*(2.0/3.0));
 
        //Extra Pt
        Point3D aux1, aux2;
        Point3D tmp64, tmp65, tmp66, tmp67, tmp68, tmp69, tmp70, tmp71, tmp72, tmp73;
        Point3D tmp74, tmp75, tmp76, tmp77, tmp78, tmp79, tmp80, tmp81, tmp82, tmp83;
        Point3D tmp84, tmp85, tmp86, tmp87, tmp88, tmp89, tmp90, tmp91, tmp92, tmp93;
        Point3D tmp94, tmp95, tmp96, tmp97, tmp98, tmp99, tmp100, tmp101, tmp102, tmp103;
        Point3D tmp104, tmp105, tmp106, tmp107, tmp108, tmp109, tmp110, tmp111, tmp112, tmp113;
        Point3D tmp114, tmp115, tmp116, tmp117, tmp118, tmp119, tmp120, tmp121, tmp122, tmp123;
        Point3D tmp124, tmp125, tmp126, tmp127, tmp128, tmp129, tmp130, tmp131, tmp132, tmp133;
        Point3D tmp134, tmp135, tmp136, tmp137, tmp138, tmp139, tmp140, tmp141, tmp142, tmp143;
        Point3D tmp144, tmp145, tmp146, tmp147, tmp148, tmp149, tmp150, tmp151, tmp152, tmp153;
        Point3D tmp154, tmp155;
        
        //Face {0 1 2 3}
        //--------------
        aux1 = pt[32] + ((pt[33]-pt[32])*(1.0/3.0));
        aux2 = pt[32] + ((pt[33]-pt[32])*(2.0/3.0));
        pt[64] = pt[8] + ((aux1-pt[8])*(2.0/3.0));
        pt[65] = pt[9] + ((aux2-pt[9])*(2.0/3.0));
        tmp64 = pt[8] + ((aux1-pt[8])*(1.0/3.0));
        tmp65 = pt[9] + ((aux2-pt[9])*(1.0/3.0));

        aux1 = pt[32] + ((pt[34]-pt[32])*(1.0/3.0));
        aux2 = pt[32] + ((pt[34]-pt[32])*(2.0/3.0));
        pt[66] = pt[10] + ((aux1-pt[10])*(2.0/3.0));
        pt[67] = pt[11] + ((aux2-pt[11])*(2.0/3.0));
        tmp66 = pt[10] + ((aux1-pt[10])*(1.0/3.0));
        tmp67 = pt[11] + ((aux2-pt[11])*(1.0/3.0));

        aux1 = pt[33] + ((pt[35]-pt[33])*(1.0/3.0));
        aux2 = pt[33] + ((pt[35]-pt[33])*(2.0/3.0));
        pt[68] = pt[12] + ((aux1-pt[12])*(2.0/3.0));
        pt[69] = pt[13] + ((aux2-pt[13])*(2.0/3.0));
        tmp68 = pt[12] + ((aux1-pt[12])*(1.0/3.0));
        tmp69 = pt[13] + ((aux2-pt[13])*(1.0/3.0));

        aux1 = pt[34] + ((pt[35]-pt[34])*(1.0/3.0));
        aux2 = pt[34] + ((pt[35]-pt[34])*(2.0/3.0));
        pt[70] = pt[14] + ((aux1-pt[14])*(2.0/3.0));
        pt[71] = pt[15] + ((aux2-pt[15])*(2.0/3.0));
        tmp70 = pt[14] + ((aux1-pt[14])*(1.0/3.0));
        tmp71 = pt[15] + ((aux2-pt[15])*(1.0/3.0));

        //Face {4 5 6 7}
        //--------------
        aux1 = pt[36] + ((pt[37]-pt[36])*(1.0/3.0));
        aux2 = pt[36] + ((pt[37]-pt[36])*(2.0/3.0));
        pt[72] = pt[16] + ((aux1-pt[16])*(2.0/3.0));
        pt[73] = pt[17] + ((aux2-pt[17])*(2.0/3.0));
        tmp72 = pt[16] + ((aux1-pt[16])*(1.0/3.0));
        tmp73 = pt[17] + ((aux2-pt[17])*(1.0/3.0));

        aux1 = pt[36] + ((pt[38]-pt[36])*(1.0/3.0));
        aux2 = pt[36] + ((pt[38]-pt[36])*(2.0/3.0));
        pt[74] = pt[18] + ((aux1-pt[18])*(2.0/3.0));
        pt[75] = pt[19] + ((aux2-pt[19])*(2.0/3.0));
        tmp74 = pt[18] + ((aux1-pt[18])*(1.0/3.0));
        tmp75 = pt[19] + ((aux2-pt[19])*(1.0/3.0));

        aux1 = pt[37] + ((pt[39]-pt[37])*(1.0/3.0));
        aux2 = pt[37] + ((pt[39]-pt[37])*(2.0/3.0));
        pt[76] = pt[20] + ((aux1-pt[20])*(2.0/3.0));
        pt[77] = pt[21] + ((aux2-pt[21])*(2.0/3.0));
        tmp76 = pt[20] + ((aux1-pt[20])*(1.0/3.0));
        tmp77 = pt[21] + ((aux2-pt[21])*(1.0/3.0));

        aux1 = pt[38] + ((pt[39]-pt[38])*(1.0/3.0));
        aux2 = pt[38] + ((pt[39]-pt[38])*(2.0/3.0));
        pt[78] = pt[22] + ((aux1-pt[22])*(2.0/3.0));
        pt[79] = pt[23] + ((aux2-pt[23])*(2.0/3.0));
        tmp78 = pt[22] + ((aux1-pt[22])*(1.0/3.0));
        tmp79 = pt[23] + ((aux2-pt[23])*(1.0/3.0));

        //Face {0 4 5 1}
        //--------------
        aux1 = pt[40] + ((pt[42]-pt[40])*(1.0/3.0));
        aux2 = pt[40] + ((pt[42]-pt[40])*(2.0/3.0));
        pt[80] = pt[8] + ((aux1-pt[8])*(2.0/3.0));
        pt[81] = pt[9] + ((aux2-pt[9])*(2.0/3.0));
        tmp80 = pt[8] + ((aux1-pt[8])*(1.0/3.0));
        tmp81 = pt[9] + ((aux2-pt[9])*(1.0/3.0));

        aux1 = pt[41] + ((pt[43]-pt[41])*(1.0/3.0));
        aux2 = pt[41] + ((pt[43]-pt[41])*(2.0/3.0));
        pt[82] = pt[16] + ((aux1-pt[16])*(2.0/3.0));
        pt[83] = pt[17] + ((aux2-pt[17])*(2.0/3.0));
        tmp82 = pt[16] + ((aux1-pt[16])*(1.0/3.0));
        tmp83 = pt[17] + ((aux2-pt[17])*(1.0/3.0));

        aux1 = pt[40] + ((pt[41]-pt[40])*(1.0/3.0));
        aux2 = pt[40] + ((pt[41]-pt[40])*(2.0/3.0));
        pt[84] = pt[24] + ((aux1-pt[24])*(2.0/3.0));
        pt[85] = pt[25] + ((aux2-pt[25])*(2.0/3.0));
        tmp84 = pt[24] + ((aux1-pt[24])*(1.0/3.0));
        tmp85 = pt[25] + ((aux2-pt[25])*(1.0/3.0));

        aux1 = pt[42] + ((pt[43]-pt[42])*(1.0/3.0));
        aux2 = pt[42] + ((pt[43]-pt[42])*(2.0/3.0));
        pt[86] = pt[26] + ((aux1-pt[26])*(2.0/3.0));
        pt[87] = pt[27] + ((aux2-pt[27])*(2.0/3.0));
        tmp86 = pt[26] + ((aux1-pt[26])*(1.0/3.0));
        tmp87 = pt[27] + ((aux2-pt[27])*(1.0/3.0));

        //Face {0 3 7 4}
        //--------------
        aux1 = pt[44] + ((pt[46]-pt[44])*(1.0/3.0));
        aux2 = pt[44] + ((pt[46]-pt[44])*(2.0/3.0));
        pt[88] = pt[10] + ((aux1-pt[10])*(2.0/3.0));
        pt[89] = pt[11] + ((aux2-pt[11])*(2.0/3.0));
        tmp88 = pt[10] + ((aux1-pt[10])*(1.0/3.0));
        tmp89 = pt[11] + ((aux2-pt[11])*(1.0/3.0));

        aux1 = pt[45] + ((pt[47]-pt[45])*(1.0/3.0));
        aux2 = pt[45] + ((pt[47]-pt[45])*(2.0/3.0));
        pt[90] = pt[18] + ((aux1-pt[18])*(2.0/3.0));
        pt[91] = pt[19] + ((aux2-pt[19])*(2.0/3.0));
        tmp90 = pt[18] + ((aux1-pt[18])*(1.0/3.0));
        tmp91 = pt[19] + ((aux2-pt[19])*(1.0/3.0));

        aux1 = pt[44] + ((pt[45]-pt[44])*(1.0/3.0));
        aux2 = pt[44] + ((pt[45]-pt[44])*(2.0/3.0));
        pt[92] = pt[24] + ((aux1-pt[24])*(2.0/3.0));
        pt[93] = pt[25] + ((aux2-pt[25])*(2.0/3.0));
        tmp92 = pt[24] + ((aux1-pt[24])*(1.0/3.0));
        tmp93 = pt[25] + ((aux2-pt[25])*(1.0/3.0));

        aux1 = pt[46] + ((pt[47]-pt[46])*(1.0/3.0));
        aux2 = pt[46] + ((pt[47]-pt[46])*(2.0/3.0));
        pt[94] = pt[28] + ((aux1-pt[28])*(2.0/3.0));
        pt[95] = pt[29] + ((aux2-pt[29])*(2.0/3.0));
        tmp94 = pt[28] + ((aux1-pt[28])*(1.0/3.0));
        tmp95 = pt[29] + ((aux2-pt[29])*(1.0/3.0));

        //Face {1 2 6 5}
        //--------------
        aux1 = pt[48] + ((pt[50]-pt[48])*(1.0/3.0));
        aux2 = pt[48] + ((pt[50]-pt[48])*(2.0/3.0));
        pt[96] = pt[12] + ((aux1-pt[12])*(2.0/3.0));
        pt[97] = pt[13] + ((aux2-pt[13])*(2.0/3.0));
        tmp96 = pt[12] + ((aux1-pt[12])*(1.0/3.0));
        tmp97 = pt[13] + ((aux2-pt[13])*(1.0/3.0));

        aux1 = pt[49] + ((pt[51]-pt[49])*(1.0/3.0));
        aux2 = pt[49] + ((pt[51]-pt[49])*(2.0/3.0));
        pt[98] = pt[20] + ((aux1-pt[20])*(2.0/3.0));
        pt[99] = pt[21] + ((aux2-pt[21])*(2.0/3.0));
        tmp98 = pt[20] + ((aux1-pt[20])*(1.0/3.0));
        tmp99 = pt[21] + ((aux2-pt[21])*(1.0/3.0));

        aux1 = pt[48] + ((pt[49]-pt[48])*(1.0/3.0));
        aux2 = pt[48] + ((pt[49]-pt[48])*(2.0/3.0));
        pt[100] = pt[26] + ((aux1-pt[26])*(2.0/3.0));
        pt[101] = pt[27] + ((aux2-pt[27])*(2.0/3.0));
        tmp100 = pt[26] + ((aux1-pt[26])*(1.0/3.0));
        tmp101 = pt[27] + ((aux2-pt[27])*(1.0/3.0));

        aux1 = pt[50] + ((pt[51]-pt[50])*(1.0/3.0));
        aux2 = pt[50] + ((pt[51]-pt[50])*(2.0/3.0));
        pt[102] = pt[30] + ((aux1-pt[30])*(2.0/3.0));
        pt[103] = pt[31] + ((aux2-pt[31])*(2.0/3.0));
        tmp102 = pt[30] + ((aux1-pt[30])*(1.0/3.0));
        tmp103 = pt[31] + ((aux2-pt[31])*(1.0/3.0));

        //Face {2 3 7 6}
        //--------------
        aux1 = pt[52] + ((pt[54]-pt[52])*(1.0/3.0));
        aux2 = pt[52] + ((pt[54]-pt[52])*(2.0/3.0));
        pt[104] = pt[14] + ((aux1-pt[14])*(2.0/3.0));
        pt[105] = pt[15] + ((aux2-pt[15])*(2.0/3.0));
        tmp104 = pt[14] + ((aux1-pt[14])*(1.0/3.0));
        tmp105 = pt[15] + ((aux2-pt[15])*(1.0/3.0));

        aux1 = pt[53] + ((pt[55]-pt[53])*(1.0/3.0));
        aux2 = pt[53] + ((pt[55]-pt[53])*(2.0/3.0));
        pt[106] = pt[22] + ((aux1-pt[22])*(2.0/3.0));
        pt[107] = pt[23] + ((aux2-pt[23])*(2.0/3.0));
        tmp106 = pt[22] + ((aux1-pt[22])*(1.0/3.0));
        tmp107 = pt[23] + ((aux2-pt[23])*(1.0/3.0));

        aux1 = pt[52] + ((pt[53]-pt[52])*(1.0/3.0));
        aux2 = pt[52] + ((pt[53]-pt[52])*(2.0/3.0));
        pt[108] = pt[28] + ((aux1-pt[28])*(2.0/3.0));
        pt[109] = pt[29] + ((aux2-pt[29])*(2.0/3.0));
        tmp108 = pt[28] + ((aux1-pt[28])*(1.0/3.0));
        tmp109 = pt[29] + ((aux2-pt[29])*(1.0/3.0));

        aux1 = pt[54] + ((pt[55]-pt[54])*(1.0/3.0));
        aux2 = pt[54] + ((pt[55]-pt[54])*(2.0/3.0));
        pt[110] = pt[30] + ((aux1-pt[30])*(2.0/3.0));
        pt[111] = pt[31] + ((aux2-pt[31])*(2.0/3.0));
        tmp110 = pt[30] + ((aux1-pt[30])*(1.0/3.0));
        tmp111 = pt[31] + ((aux2-pt[31])*(1.0/3.0));

        //Face {57 56 0 1}
        //----------------
        aux1 = pt[56] + ((pt[57]-pt[56])*(1.0/3.0));
        aux2 = pt[56] + ((pt[57]-pt[56])*(2.0/3.0));
        pt[112] = pt[8] + ((aux1-pt[8])*(2.0/3.0));
        pt[113] = pt[9] + ((aux2-pt[9])*(2.0/3.0));
        tmp112 = pt[8] + ((aux1-pt[8])*(1.0/3.0));
        tmp113 = pt[9] + ((aux2-pt[9])*(1.0/3.0));

        //Face {3 0 56 58}
        //----------------
        aux1 = pt[56] + ((pt[58]-pt[56])*(1.0/3.0));
        aux2 = pt[56] + ((pt[58]-pt[56])*(2.0/3.0));
        pt[114] = pt[10] + ((aux1-pt[10])*(2.0/3.0));
        pt[115] = pt[11] + ((aux2-pt[11])*(2.0/3.0));
        tmp114 = pt[10] + ((aux1-pt[10])*(1.0/3.0));
        tmp115 = pt[11] + ((aux2-pt[11])*(1.0/3.0));

        //Face {59 57 1 2}
        //----------------
        aux1 = pt[57] + ((pt[59]-pt[57])*(1.0/3.0));
        aux2 = pt[57] + ((pt[59]-pt[57])*(2.0/3.0));
        pt[116] = pt[12] + ((aux1-pt[12])*(2.0/3.0));
        pt[117] = pt[13] + ((aux2-pt[13])*(2.0/3.0));
        tmp116 = pt[12] + ((aux1-pt[12])*(1.0/3.0));
        tmp117 = pt[13] + ((aux2-pt[13])*(1.0/3.0));

        //Face {2 3 58 59}
        //----------------
        aux1 = pt[58] + ((pt[59]-pt[58])*(1.0/3.0));
        aux2 = pt[58] + ((pt[59]-pt[58])*(2.0/3.0));
        pt[118] = pt[14] + ((aux1-pt[14])*(2.0/3.0));
        pt[119] = pt[15] + ((aux2-pt[15])*(2.0/3.0));
        tmp118 = pt[14] + ((aux1-pt[14])*(1.0/3.0));
        tmp119 = pt[15] + ((aux2-pt[15])*(1.0/3.0));

        //Face {61 60 4 5}
        //----------------
        aux1 = pt[60] + ((pt[61]-pt[60])*(1.0/3.0));
        aux2 = pt[60] + ((pt[61]-pt[60])*(2.0/3.0));
        pt[120] = pt[16] + ((aux1-pt[16])*(2.0/3.0));
        pt[121] = pt[17] + ((aux2-pt[17])*(2.0/3.0));
        tmp120 = pt[16] + ((aux1-pt[16])*(1.0/3.0));
        tmp121 = pt[17] + ((aux2-pt[17])*(1.0/3.0));

        //Face {7 4 60 62}
        //----------------
        aux1 = pt[60] + ((pt[62]-pt[60])*(1.0/3.0));
        aux2 = pt[60] + ((pt[62]-pt[60])*(2.0/3.0));
        pt[122] = pt[18] + ((aux1-pt[18])*(2.0/3.0));
        pt[123] = pt[19] + ((aux2-pt[19])*(2.0/3.0));
        tmp122 = pt[18] + ((aux1-pt[18])*(1.0/3.0));
        tmp123 = pt[19] + ((aux2-pt[19])*(1.0/3.0));

        //Face {63 61 5 6}
        //----------------
        aux1 = pt[61] + ((pt[63]-pt[61])*(1.0/3.0));
        aux2 = pt[61] + ((pt[63]-pt[61])*(2.0/3.0));
        pt[124] = pt[20] + ((aux1-pt[20])*(2.0/3.0));
        pt[125] = pt[21] + ((aux2-pt[21])*(2.0/3.0));
        tmp124 = pt[20] + ((aux1-pt[20])*(1.0/3.0));
        tmp125 = pt[21] + ((aux2-pt[21])*(1.0/3.0));

        //Face {6 7 62 63}
        //----------------
        aux1 = pt[62] + ((pt[63]-pt[62])*(1.0/3.0));
        aux2 = pt[62] + ((pt[63]-pt[62])*(2.0/3.0));
        pt[126] = pt[22] + ((aux1-pt[22])*(2.0/3.0));
        pt[127] = pt[23] + ((aux2-pt[23])*(2.0/3.0));
        tmp126 = pt[22] + ((aux1-pt[22])*(1.0/3.0));
        tmp127 = pt[23] + ((aux2-pt[23])*(1.0/3.0));

        //Face {56 60 4 0}
        //----------------
        aux1 = pt[56] + ((pt[60]-pt[56])*(1.0/3.0));
        aux2 = pt[56] + ((pt[60]-pt[56])*(2.0/3.0));
        pt[128] = pt[24] + ((aux1-pt[24])*(2.0/3.0));
        pt[129] = pt[25] + ((aux2-pt[25])*(2.0/3.0));
        tmp128 = pt[24] + ((aux1-pt[24])*(1.0/3.0));
        tmp129 = pt[25] + ((aux2-pt[25])*(1.0/3.0));

        //Face {57 61 5 1}
        //----------------
        aux1 = pt[57] + ((pt[61]-pt[57])*(1.0/3.0));
        aux2 = pt[57] + ((pt[61]-pt[57])*(2.0/3.0));
        pt[130] = pt[26] + ((aux1-pt[26])*(2.0/3.0));
        pt[131] = pt[27] + ((aux2-pt[27])*(2.0/3.0));
        tmp130 = pt[26] + ((aux1-pt[26])*(1.0/3.0));
        tmp131 = pt[27] + ((aux2-pt[27])*(1.0/3.0));

        //Face {58 62 7 3}
        //----------------
        aux1 = pt[58] + ((pt[62]-pt[58])*(1.0/3.0));
        aux2 = pt[58] + ((pt[62]-pt[58])*(2.0/3.0));
        pt[132] = pt[28] + ((aux1-pt[28])*(2.0/3.0));
        pt[133] = pt[29] + ((aux2-pt[29])*(2.0/3.0));
        tmp132 = pt[28] + ((aux1-pt[28])*(1.0/3.0));
        tmp133 = pt[29] + ((aux2-pt[29])*(1.0/3.0));

        //Face {59 63 6 2}
        //----------------
        aux1 = pt[59] + ((pt[63]-pt[59])*(1.0/3.0));
        aux2 = pt[59] + ((pt[63]-pt[59])*(2.0/3.0));
        pt[134] = pt[30] + ((aux1-pt[30])*(2.0/3.0));
        pt[135] = pt[31] + ((aux2-pt[31])*(2.0/3.0));
        tmp134 = pt[30] + ((aux1-pt[30])*(1.0/3.0));
        tmp135 = pt[31] + ((aux2-pt[31])*(1.0/3.0));

        // INTERNAL
        //Hexa {0 1 2 3 56 57 59 58}
        //--------------------------
        pt[136] = tmp114 + ((tmp116-tmp114)*(1.0/3.0));
        pt[137] = tmp114 + ((tmp116-tmp114)*(2.0/3.0));
        pt[138] = tmp115 + ((tmp117-tmp115)*(1.0/3.0));
        pt[139] = tmp115 + ((tmp117-tmp115)*(2.0/3.0));
        pt[140] = pt[114] + ((pt[116]-pt[114])*(1.0/3.0));
        pt[141] = pt[114] + ((pt[116]-pt[114])*(2.0/3.0));
        pt[142] = pt[115] + ((pt[117]-pt[115])*(1.0/3.0));
        pt[143] = pt[115] + ((pt[117]-pt[115])*(2.0/3.0));

        aux1 = pt[136] + ((pt[137]-pt[136])*(1.0/3.0));
        aux2 = pt[136] + ((pt[137]-pt[136])*(2.0/3.0));
        pt[144] = tmp112 + ((aux1-tmp112)*(2.0/3.0));
        pt[145] = tmp113 + ((aux2-tmp113)*(2.0/3.0));
        aux1 = pt[136] + ((pt[138]-pt[136])*(1.0/3.0));
        aux2 = pt[136] + ((pt[138]-pt[136])*(2.0/3.0));
        pt[146] = tmp114 + ((aux1-tmp114)*(2.0/3.0));
        pt[147] = tmp115 + ((aux2-tmp115)*(2.0/3.0));
        aux1 = pt[137] + ((pt[139]-pt[137])*(1.0/3.0));
        aux2 = pt[137] + ((pt[139]-pt[137])*(2.0/3.0));
        pt[148] = tmp116 + ((aux1-tmp116)*(2.0/3.0));
        pt[149] = tmp117 + ((aux2-tmp117)*(2.0/3.0));
        aux1 = pt[138] + ((pt[139]-pt[138])*(1.0/3.0));
        aux2 = pt[138] + ((pt[139]-pt[138])*(2.0/3.0));
        pt[150] = tmp118 + ((aux1-tmp118)*(2.0/3.0));
        pt[151] = tmp119 + ((aux2-tmp119)*(2.0/3.0));

        //Hexa {60 61 63 62 4 5 6 7}
        //--------------------------
        pt[152] = tmp122 + ((tmp124-tmp122)*(1.0/3.0));
        pt[153] = tmp122 + ((tmp124-tmp122)*(2.0/3.0));
        pt[154] = tmp123 + ((tmp125-tmp123)*(1.0/3.0));
        pt[155] = tmp123 + ((tmp125-tmp123)*(2.0/3.0));
        pt[156] = pt[122] + ((pt[124]-pt[122])*(1.0/3.0));
        pt[157] = pt[122] + ((pt[124]-pt[122])*(2.0/3.0));
        pt[158] = pt[123] + ((pt[125]-pt[123])*(1.0/3.0));
        pt[159] = pt[123] + ((pt[125]-pt[123])*(2.0/3.0));

        aux1 = pt[152] + ((pt[153]-pt[152])*(1.0/3.0));
        aux2 = pt[152] + ((pt[153]-pt[152])*(2.0/3.0));
        pt[160] = tmp120 + ((aux1-tmp120)*(2.0/3.0));
        pt[161] = tmp121 + ((aux2-tmp121)*(2.0/3.0));
        aux1 = pt[152] + ((pt[154]-pt[152])*(1.0/3.0));
        aux2 = pt[152] + ((pt[154]-pt[152])*(2.0/3.0));
        pt[162] = tmp122 + ((aux1-tmp122)*(2.0/3.0));
        pt[163] = tmp123 + ((aux2-tmp123)*(2.0/3.0));
        aux1 = pt[153] + ((pt[155]-pt[153])*(1.0/3.0));
        aux2 = pt[153] + ((pt[155]-pt[153])*(2.0/3.0));
        pt[164] = tmp124 + ((aux1-tmp124)*(2.0/3.0));
        pt[165] = tmp125 + ((aux2-tmp125)*(2.0/3.0));
        aux1 = pt[154] + ((pt[155]-pt[154])*(1.0/3.0));
        aux2 = pt[154] + ((pt[155]-pt[154])*(2.0/3.0));
        pt[166] = tmp126 + ((aux1-tmp126)*(2.0/3.0));
        pt[167] = tmp127 + ((aux2-tmp127)*(2.0/3.0));

        //Hexa {57 56 0 1 61 60 4 5}
        //--------------------------
        pt[168] = tmp112 + ((tmp120-tmp112)*(1.0/3.0));
        pt[169] = tmp112 + ((tmp120-tmp112)*(2.0/3.0));
        pt[170] = tmp113 + ((tmp121-tmp113)*(1.0/3.0));
        pt[171] = tmp113 + ((tmp121-tmp113)*(2.0/3.0));
        pt[172] = pt[112] + ((pt[120]-pt[112])*(1.0/3.0));
        pt[173] = pt[112] + ((pt[120]-pt[112])*(2.0/3.0));
        pt[174] = pt[113] + ((pt[121]-pt[113])*(1.0/3.0));
        pt[175] = pt[113] + ((pt[121]-pt[113])*(2.0/3.0));

        aux1 = pt[168] + ((pt[170]-pt[168])*(1.0/3.0));
        aux2 = pt[168] + ((pt[170]-pt[168])*(2.0/3.0));
        pt[176] = tmp112 + ((aux1-tmp112)*(2.0/3.0));
        pt[177] = tmp113 + ((aux2-tmp113)*(2.0/3.0));
        aux1 = pt[169] + ((pt[171]-pt[169])*(1.0/3.0));
        aux2 = pt[169] + ((pt[171]-pt[169])*(2.0/3.0));
        pt[178] = tmp120 + ((aux1-tmp120)*(2.0/3.0));
        pt[179] = tmp121 + ((aux2-tmp121)*(2.0/3.0));
        aux1 = pt[168] + ((pt[169]-pt[168])*(1.0/3.0));
        aux2 = pt[168] + ((pt[169]-pt[168])*(2.0/3.0));
        pt[180] = tmp128 + ((aux1-tmp128)*(2.0/3.0));
        pt[181] = tmp129 + ((aux2-tmp129)*(2.0/3.0));
        aux1 = pt[170] + ((pt[171]-pt[170])*(1.0/3.0));
        aux2 = pt[170] + ((pt[171]-pt[170])*(2.0/3.0));
        pt[182] = tmp130 + ((aux1-tmp130)*(2.0/3.0));
        pt[183] = tmp131 + ((aux2-tmp131)*(2.0/3.0));

        //Hexa {3 0 56 58 7 4 60 62}
        //--------------------------
        pt[184] = tmp114 + ((tmp122-tmp114)*(1.0/3.0));
        pt[185] = tmp114 + ((tmp122-tmp114)*(2.0/3.0));
        pt[186] = tmp115 + ((tmp123-tmp115)*(1.0/3.0));
        pt[187] = tmp115 + ((tmp123-tmp115)*(2.0/3.0));
        pt[188] = pt[114] + ((pt[122]-pt[114])*(1.0/3.0));
        pt[189] = pt[114] + ((pt[122]-pt[114])*(2.0/3.0));
        pt[190] = pt[115] + ((pt[123]-pt[115])*(1.0/3.0));
        pt[191] = pt[115] + ((pt[123]-pt[115])*(2.0/3.0));

        aux1 = pt[184] + ((pt[186]-pt[184])*(1.0/3.0));
        aux2 = pt[184] + ((pt[186]-pt[184])*(2.0/3.0));
        pt[192] = tmp114 + ((aux1-tmp114)*(2.0/3.0));
        pt[193] = tmp115 + ((aux2-tmp115)*(2.0/3.0));
        aux1 = pt[185] + ((pt[187]-pt[185])*(1.0/3.0));
        aux2 = pt[185] + ((pt[187]-pt[185])*(2.0/3.0));
        pt[194] = tmp122 + ((aux1-tmp122)*(2.0/3.0));
        pt[195] = tmp123 + ((aux2-tmp123)*(2.0/3.0));
        aux1 = pt[184] + ((pt[185]-pt[184])*(1.0/3.0));
        aux2 = pt[184] + ((pt[185]-pt[184])*(2.0/3.0));
        pt[196] = tmp128 + ((aux1-tmp128)*(2.0/3.0));
        pt[197] = tmp129 + ((aux2-tmp129)*(2.0/3.0));
        aux1 = pt[186] + ((pt[187]-pt[186])*(1.0/3.0));
        aux2 = pt[186] + ((pt[187]-pt[186])*(2.0/3.0));
        pt[198] = tmp132 + ((aux1-tmp132)*(2.0/3.0));
        pt[199] = tmp133 + ((aux2-tmp133)*(2.0/3.0));

        //Hexa {59 57 1 2 63 61 5 6}
        //--------------------------
        pt[200] = tmp116 + ((tmp124-tmp116)*(1.0/3.0));
        pt[201] = tmp116 + ((tmp124-tmp116)*(2.0/3.0));
        pt[202] = tmp117 + ((tmp125-tmp117)*(1.0/3.0));
        pt[203] = tmp117 + ((tmp125-tmp117)*(2.0/3.0));
        pt[204] = pt[116] + ((pt[124]-pt[116])*(1.0/3.0));
        pt[205] = pt[116] + ((pt[124]-pt[116])*(2.0/3.0));
        pt[206] = pt[117] + ((pt[125]-pt[117])*(1.0/3.0));
        pt[207] = pt[117] + ((pt[125]-pt[117])*(2.0/3.0));

        aux1 = pt[200] + ((pt[202]-pt[200])*(1.0/3.0));
        aux2 = pt[200] + ((pt[202]-pt[200])*(2.0/3.0));
        pt[208] = tmp116 + ((aux1-tmp116)*(2.0/3.0));
        pt[209] = tmp117 + ((aux2-tmp117)*(2.0/3.0));
        aux1 = pt[201] + ((pt[203]-pt[201])*(1.0/3.0));
        aux2 = pt[201] + ((pt[203]-pt[201])*(2.0/3.0));
        pt[210] = tmp124 + ((aux1-tmp124)*(2.0/3.0));
        pt[211] = tmp125 + ((aux2-tmp125)*(2.0/3.0));
        aux1 = pt[200] + ((pt[201]-pt[200])*(1.0/3.0));
        aux2 = pt[200] + ((pt[201]-pt[200])*(2.0/3.0));
        pt[212] = tmp130 + ((aux1-tmp130)*(2.0/3.0));
        pt[213] = tmp131 + ((aux2-tmp131)*(2.0/3.0));
        aux1 = pt[202] + ((pt[203]-pt[202])*(1.0/3.0));
        aux2 = pt[202] + ((pt[203]-pt[202])*(2.0/3.0));
        pt[214] = tmp134 + ((aux1-tmp134)*(2.0/3.0));
        pt[215] = tmp135 + ((aux2-tmp135)*(2.0/3.0));

        //Hexa {2 3 58 59 6 7 62 63}
        //--------------------------
        pt[216] = tmp118 + ((tmp126-tmp118)*(1.0/3.0));
        pt[217] = tmp118 + ((tmp126-tmp118)*(2.0/3.0));
        pt[218] = tmp119 + ((tmp127-tmp119)*(1.0/3.0));
        pt[219] = tmp119 + ((tmp127-tmp119)*(2.0/3.0));
        pt[220] = pt[118] + ((pt[126]-pt[118])*(1.0/3.0));
        pt[221] = pt[118] + ((pt[126]-pt[118])*(2.0/3.0));
        pt[222] = pt[119] + ((pt[127]-pt[119])*(1.0/3.0));
        pt[223] = pt[119] + ((pt[127]-pt[119])*(2.0/3.0));

        aux1 = pt[216] + ((pt[218]-pt[216])*(1.0/3.0));
        aux2 = pt[216] + ((pt[218]-pt[216])*(2.0/3.0));
        pt[224] = tmp118 + ((aux1-tmp118)*(2.0/3.0));
        pt[225] = tmp119 + ((aux2-tmp119)*(2.0/3.0));
        aux1 = pt[217] + ((pt[219]-pt[217])*(1.0/3.0));
        aux2 = pt[217] + ((pt[219]-pt[217])*(2.0/3.0));
        pt[226] = tmp126 + ((aux1-tmp126)*(2.0/3.0));
        pt[227] = tmp127 + ((aux2-tmp127)*(2.0/3.0));
        aux1 = pt[216] + ((pt[217]-pt[216])*(1.0/3.0));
        aux2 = pt[216] + ((pt[217]-pt[216])*(2.0/3.0));
        pt[228] = tmp132 + ((aux1-tmp132)*(2.0/3.0));
        pt[229] = tmp133 + ((aux2-tmp133)*(2.0/3.0));
        aux1 = pt[218] + ((pt[219]-pt[218])*(1.0/3.0));
        aux2 = pt[218] + ((pt[219]-pt[218])*(2.0/3.0));
        pt[230] = tmp134 + ((aux1-tmp134)*(2.0/3.0));
        pt[231] = tmp135 + ((aux2-tmp135)*(2.0/3.0));

        vector<Uint> idxs(232,-1);

        for (int i = 0; i < 64; i++) {
            if(points.find(i) != points.end()){
                idxs[i] = m_NodesMap.find(points.find(i)->second)->second.External; // Rellena todos los Ids del mapa de puntos
            }
        }


        // The found pattern is returned in m_result
        for (VectorTableIt it=m_result.begin(); it != m_result.end(); ++it) {
            // Temporary vector
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

                        idxsVector.push_back(idxs[*it1]); // Agrega idx al Vector Global
                        puntosVector.push_back(pt[*it1]); // Agrega el punto al Vector Global
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

