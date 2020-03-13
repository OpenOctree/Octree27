/*
 * TransitionCube.cpp
 *
 *  Created on: May 30, 2012
 *      Author: jsepulve
 */

#include <math.h>
#include <algorithm>
#include "TransitionCube.h"


using namespace std;


namespace patterns {
	const Uint TransitionCube::ExternalToInternal[TOTAL_POINTS] = {
		0, 48, 51, 3, 
		12, 60, 63, 15,
		16, 32, 1, 2, 
		49, 50, 19, 35,
		28, 44, 13, 14, 
		61, 62, 31, 47,
		4, 8, 52, 56, 
		7, 11, 55, 59,
		17, 33, 18, 34, 
		29, 45, 30, 46,
		20, 24, 36, 40, 
		5, 9, 6, 10,
		53, 57, 54, 58, 
		23, 27, 39, 43,
		21, 37, 22, 38, 
		25, 41, 26, 42
		/*0,  18, 20, 2, 6, 24, 26, 8,
		9,  19, 11, 1, 3, 21, 23, 5,
		15, 25, 17, 7,10, 12, 22,14,
		4,  16, 13*/
	};

	const Uint TransitionCube::InternalToExternal[TOTAL_POINTS] = {
		0, 10, 11, 3, 
		24, 44, 46, 28,
		25, 45, 47, 29, 
		4, 18, 19, 7,
		8, 32, 34, 14, 
		40, 56, 58, 52, 
		41, 60, 62, 53, 
		16, 36, 38, 22,
		9, 33, 35, 15, 
		42, 57, 59, 54, 
		43, 61, 63, 55, 
		17, 37, 39, 23,
		1, 12, 13, 2, 
		26, 48, 50, 30, 
		27, 49, 51, 31, 
		5, 20, 21, 6
		/*0, 11, 3,  12, 24, 15,  4, 19, 7,
		8, 20, 10, 21, 26, 23, 16, 25,18,
		1,  9, 2,  13, 22, 14,  5, 17, 6*/
	};

	TransitionCube::TransitionCube(const set<unsigned long>& flag_hex_idxs): m_mask(0) { 
		//Default eight corner point.
		this->flag_hex_idxs = flag_hex_idxs;
		addCornerTransitionPointsMap(); 
	}

	TransitionCube::TransitionCube(const vector<Uint>& edges, const set<unsigned long>& flag_hex_idxs): m_mask(0) {
		this->flag_hex_idxs = flag_hex_idxs;
		if (edges.size() > 0) {        
			for (int i=0; i<edges.size(); i++){
				// Convert input edge points to local internal mapping.
				m_edges.push_back(ExternalToInternal[edges[i]]);
			}
			
			// Sort points ascending.
			sort (m_edges.begin(), m_edges.begin() + m_edges.size() );
			
			//Inserts input edge points into the same map of corner points.
			addEdgeTransitionPointsMap();
		}
		
		//Insert eight default corner points into the map.
		addCornerTransitionPointsMap();
	}

	void TransitionCube::resetTransitionCube() {
		m_MapVertices.clear();
		addCornerTransitionPointsMap();
		addEdgeTransitionPointsMap();
	}

	void TransitionCube::addNewTransitionPoint(int point) {
		TransitionPoint tmpPoint = TransitionPoint(point);
		
		if (m_MapVertices.find(tmpPoint.getInitTransitionPoint()) == m_MapVertices.end())
			m_MapVertices.insert(std::make_pair(tmpPoint.getInitTransitionPoint(), tmpPoint));
	}

	void TransitionCube::deleteTransitionPoint(int point)
	{
		m_MapVertices.erase (m_MapVertices.find(point));
	}

	void TransitionCube::rotate(int axis, int rot) {
		
		if ((axis > -1) && (axis < 3)) {
			
			//Mask of rotated edge points.
			Uint mask = 0;
			
			// Get edge points iterator already configured in the constructor.
			vector<Uint>::iterator Iter = m_edges.begin();
			
			// Clean up all previous rotation
			m_rotated_edges.clear();
			
			/// Gets a number of 90 degree steps.
			/// If negative rotation converts to similar positive rotation.
			int step = this->getRotationSteps(rot);
			
			/// This loop rotates toward axis direction.
			/// Rotates all points of the map (corner and edge points)
			for (PointMapIter it  = m_MapVertices.begin(); it != m_MapVertices.end(); 
				 ++it) {
				if      (axis == 0)
					(*it).second.rotX(step);
				
				else if (axis == 1)
					(*it).second.rotY(step);
				
				else if (axis == 2)
					(*it).second.rotZ(step);
				
				if (!m_edges.empty()) 
				{	
					if(this->flag_hex_idxs.find(InternalToExternal[(*it).first])!=this->flag_hex_idxs.end()) {
						// Shift a left value edge point times to build a mask.
						mask |=1UL<<InternalToExternal[(*it).second.getRotatedTransitionPoint()];
						//cout << InternalToExternal[(*it).second.getRotatedTransitionPoint()] << " ";
					}
					if ((Iter != m_edges.end()) && (*it).first == (*Iter)) {
						// Puts into local vector the point number the result 
						// of rotated edge points.
						m_rotated_edges.push_back((*it).second.getRotatedTransitionPoint());
						++Iter;
						
						//This display rotation of points.
						//cout << "ROTACION:";
						//cout << " " << (*it).first << "-->" << (*it).second.getRotatedTransitionPoint() << "\n";
					}
					
				}
				
			}
			/// Save obtained mask in public variable.
			if (mask)
				//cout << "Mask: " << mask << "\n";
				m_mask = mask;
		}
	}

	void TransitionCube::rotX(int rotation) {
		this->rotate(0,rotation);
	}

	void TransitionCube::rotY(int rotation) {
		this->rotate(1,rotation);
	}

	void TransitionCube::rotZ(int rotation) {
		this->rotate(2,rotation);
	}

	void TransitionCube::getInitTransitionPoints(vector<Uint> & nodes) {
		nodes.clear();
		
		for (PointMapIter it  = m_MapVertices.begin(); 
			 it != m_MapVertices.end(); 
			 ++it) {
			nodes.push_back( InternalToExternal[(*it).first] );
		}
	}

	void TransitionCube::getCurrentTransitionPoints(vector<Uint> & nodes) {
		nodes.clear();
		
		for (PointMapIter it  = m_MapVertices.begin(); 
			 it != m_MapVertices.end(); 
			 ++it) {
			nodes.push_back( InternalToExternal[(*it).second.getRotatedTransitionPoint()] );
		}
	}

	void TransitionCube::getCurrentTransitionPoints(map<Uint, Uint> & nodes) {
		nodes.clear();
		
		for (PointMapIter it  = m_MapVertices.begin(); 
			 it != m_MapVertices.end(); 
			 ++it) {
			nodes.insert( make_pair(InternalToExternal[(*it).second.getRotatedTransitionPoint()],
									InternalToExternal[(*it).second.getInitTransitionPoint()]));
		}
	}

	void TransitionCube::getEdgeTransitionPoints(vector<Uint> & edges) {
		
		if (m_rotated_edges.empty()) {
			for (Uint i=0; i<m_edges.size(); i++)
				edges.push_back( InternalToExternal[ m_edges[i] ] );
		}
		else {
			for (Uint i=0; i<m_rotated_edges.size(); i++)
				edges.push_back( InternalToExternal[ m_rotated_edges[i] ] );
		}
		
	}

	void TransitionCube::addCornerTransitionPointsMap() {
		
		// Map of defaultvertices.
		m_MapVertices.insert(std::make_pair(0, TransitionPoint(0,0,0)));/// 0
		m_MapVertices.insert(std::make_pair(48,TransitionPoint(0,0,3)));/// 18
		m_MapVertices.insert(std::make_pair(51,TransitionPoint(3,0,3)));/// 20
		m_MapVertices.insert(std::make_pair(3, TransitionPoint(3,0,0)));/// 2
		m_MapVertices.insert(std::make_pair(12, TransitionPoint(0,3,0)));/// 6
		m_MapVertices.insert(std::make_pair(60,TransitionPoint(0,3,3)));/// 24
		m_MapVertices.insert(std::make_pair(63,TransitionPoint(3,3,3)));/// 26
		m_MapVertices.insert(std::make_pair(15, TransitionPoint(3,3,0)));/// 8
		
	}

	void TransitionCube::addEdgeTransitionPointsMap() {
		if ( m_edges.size() > 0 ) {
			
			for (vector<Uint>::iterator it  = m_edges.begin(); 
				 it != m_edges.end(); 
				 ++it) 
				m_MapVertices.insert(std::make_pair( TransitionPoint(*it).getInitTransitionPoint(), TransitionPoint(*it)));
		}
		
	}

	int TransitionCube::getRotationSteps(int rotation) {
		int step = 0;
		
		/// Check positive or negative 90 degree steps.
		if (rotation < 0) {
			step = abs(rotation) % 4;
			if      (step == 3) step = 1;
			else if (step == 1) step = 3;
		}
		else
			step = rotation % 4;
		
		return step;
	}

	string TransitionCube::reportRotation() {
		stringstream report ;
		Uint mask = 0;
		
		report << "|SIZE: "<< m_edges.size() << " NODES:";
		
		for (vector<Uint>::iterator it = m_edges.begin(); it != m_edges.end(); ++it){
			report << " " << InternalToExternal[(*it)];
			mask |=1UL<<InternalToExternal[(*it)];

		}
		
		for (PointMapIter it  = m_MapVertices.begin(); 
			 it != m_MapVertices.end(); 
			 ++it) {
			report << "| " << InternalToExternal[(*it).second.getInitTransitionPoint()] << 
            "-->" << InternalToExternal[(*it).second.getRotatedTransitionPoint()] ;
		}

		report << " Mask:" << mask;
		return report.str();
	}
}
