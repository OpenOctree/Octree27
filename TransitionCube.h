/*
 * TransitionCube.h
 *
 *  Created on: May 30, 2012
 *      Author: jsepulve
 */

#ifndef TransitionCube_H_
#define TransitionCube_H_

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include "TransitionPoint.h"

using namespace std;

namespace patterns {
	
	/**
	 * Creates a basic TransitionCube
	 *         External                           Internal
	 *       4--------19-------7              6--------7--------8
	 *      /|                /|             /|                /|
	 *     / |               / |            / |               / |
	 *   16  |     24       18 |          15  |     16       17 |
	 *   /   12       4    /   15         /   3        4    /   5
	 *  5----+--17--------6   3|        24----+--25--------26   |
	 *  | 21 |        13  |  2 |  <-->   | 12 |        13  |  14|
	 *  |    0--------11--|----3         |    0--------1---|- --2
	 *  |   /             |   /          |   /             |   /
	 *  |  8        20    |  10          |  9        10    |  11
	 * 13 /       22      14/           21 /       22      23/
	 *  |/                |/             |/                |/
	 *  1--------9--------2             18--------19-------20
	 *
	 */

	/*
	* 			External 27							Internal 27
    *         4-----18-------19------7			    12-----13------14------15
    *        /                      /              /
    *       /                      /              /
    *      16     36       38     22             28     29      30       31
    *     /                      /
    *    /                      /
    *   17     37       39     23              44     45     46     47
    *  /                      /
    * /                      /
    *5-----20--------21-----6			   60     61     62     63
    *          25----45-------47------29            8------9------10-------11
    *         /                      /			   /
    *        /                      /   		  /
    *      41     60       62      53		     24     25      26      27
    *      /                      /
    *     /                      /
    *   43     61       63     55             40     41     42     43
    *   /                      /
    *  /                      /
    *27-----49-------51------31            56     57     58     59
    *          24----44-------46------28           4------5------6-------7
    *         /                      /            /                     /
    *        /                      /            /                     /
    *      40     56       58      52	        20     21     22     23
    *      /                      /
    *     /                      /
    *   42     57       59      54			 36     37     38     39
    *   /                      /
    *  /                      /  
    *26-----48-------50------30  	      52     53     54     55
    *         0----10-------11-------3           0------1------2-------3
    *        /                      /           /                     /
    *       /                      /           /                     /
    *      8     32       34      14		  16     17     18     19
    *     /                      /
    *    /                      /
    *   9     33       35     15		   32     33     34     35
    *  /                      /
    * /                      /
    *1-----12--------13-----2           48     49     50     51

	*/
	class TransitionCube {
	public:
		//typedef unsigned long Uint;
		/**
		 * Default constructor.
		 */
		TransitionCube(const set<unsigned long>&);
		
		virtual ~TransitionCube() { };
		
		/**
		 * Creates a TransitionCube assigning edge and mid points.
		 */
		TransitionCube(const vector<Uint>& edges);
		TransitionCube(const vector<Uint>& edges, const set<unsigned long>& flag_hex_idxs);
		
		/**
		 * Copy constructor
		 */
		TransitionCube(const TransitionCube & c) { *this = c; };
		
		/**
		 * Assignment operator
		 */
		TransitionCube &operator =(const TransitionCube &c)  
		{
			if (*this != c) { m_MapVertices = c.m_MapVertices; m_edges = c.m_edges; }
			return *this;
		};
		
		/**
		 * Equals operator
		 */ 
		bool operator ==(const TransitionCube &c) const {
			return ( (m_MapVertices == c.m_MapVertices) || (m_edges==c.m_edges) );
		};
		
		bool operator !=(const TransitionCube &c) const {
			return ( (m_MapVertices != c.m_MapVertices) || (m_edges!=c.m_edges) );
		};
		
		
		/**
		 * TransitionCube start over
		 * Sets all hexahedron points to init condition, all rotations will lost.
		 */
		void resetTransitionCube(); 
		
		/**
		 * Adds on a new edge or face vertices to hexahedron.
		 * Vertices already present in the TransitionCube are not appended.
		 */
		void addNewTransitionPoint(int);
		
		/**
		 * Removes a edge or face point currently in the hexahedron
		 */
		void deleteTransitionPoint(int);
		
		/**
		 * Rotates TransitionCube in 90 degree steps.
		 * Positive step is right hand direction rotation.
		 * Rotation step of +1 unit is a 90 degree clockwise.
		 */
		void rotX(int);
		
		/**
		 * Rotates Y TransitionCube in 90 degree steps.
		 * Positive step is right hand direction rotation.
		 * Rotation step of +1 unit is a 90 degree clockwise.
		 */
		void rotY(int);
		
		/**
		 * Rotates Z TransitionCube in 90 degree steps.
		 * Positive step is right hand direction rotation.
		 * Rotation step of +1 unit is a 90 degree clockwise.
		 */
		void rotZ(int);
		
		/**
		 * Return init points
		 */
		void getInitTransitionPoints(vector<Uint> & );
		
		/**
		 * Return vector of points
		 */
		void getCurrentTransitionPoints(vector<Uint> & );
		
		/**
		 * Return map of init and rotated value of each point.
		 */
		void getCurrentTransitionPoints(map<Uint, Uint>& );
		
		/**
		 * Return vector of points
		 */
		void getEdgeTransitionPoints(vector<Uint> & );
		
		/**
		 * Return mask of edge points
		 */
		Uint getEdgeTransitionPointsMask() { return m_mask; };
		
		/**
		 * Return a string with node rotations performed.
		 */
		string reportRotation();
		
	private:
		/**
		 * Creates a default eight corner points.
		 * Populates internal map with a vertice and object point.
		 * Each point is defined by a vector of three dimensions (x,y,z).
		 */
		void addCornerTransitionPointsMap();
		
		/**
		 * Inserts edge vectors into the internal map
		 */
		void addEdgeTransitionPointsMap();
		
		/**
		 * Calculates number of step repetions
		 */
		int getRotationSteps(int);
		
		void rotate (int, int);
		
		typedef vector<TransitionPoint> TransitionPointVector;
		typedef vector<TransitionPoint>::iterator TransitionPointVectorIter;
		
		/**
		 * Map of a vertice and object point (x,y,z)
		 */
		typedef map<Uint,TransitionPoint> PointMap_t;
		typedef PointMap_t::iterator PointMapIter;
		
		PointMap_t  m_MapVertices;
		
		vector<Uint> m_edges;
		vector<Uint> m_rotated_edges;
		set<unsigned long> flag_hex_idxs;
		
		// total number of TransitionCube points
		static const Uint TOTAL_POINTS = 64;
		
		/**
		 * Public points defined in the patterns.
		 */
		static const Uint ExternalToInternal[];
		
		/**
		 * Container of internal points defined in TransitionCube class
		 */
		static const Uint InternalToExternal[];
		
		Uint m_mask;
		
		
		
	};
	
}

#endif /* TransitionCube_H_ */
