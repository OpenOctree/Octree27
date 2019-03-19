/*
 * Cube.h
 *
 *  Created on: May 30, 2012
 *      Author: jsepulve
 */

#ifndef TransitionPoint_H_
#define TransitionPoint_H_

#include <vector>
#include <math.h>
#include <iostream>

/**
 * Defines a basic cube vertex unit.
 */

namespace patterns {
	
	typedef unsigned long Uint;
	
	class TransitionPoint 
	{
	public:
		
		
		/// Default constructor.
		TransitionPoint() : m_id(0), m_X(0), m_Y(0), m_Z(0), m_T(1), m_TransitionPoint(0) { };
		
		/** 
		 * Parametric constructor
		 * Initializes x,y,z vertex position, calculates vertex number.
		 */
		TransitionPoint(int , int , int , int );
		
		/** 
		 * Parametric constructor
		 * Initializes x,y,z vertex position, calculates vertex number.
		 */
		TransitionPoint(int , int , int );
		/**
		 * Initializes TransitionPoint vertex number, determines x,y,z position
		 */
		TransitionPoint(int p): m_T(1) { this->TransitionPointToCoordinates(p); };
		
		virtual ~TransitionPoint() {};
		
		/// Copy constructor
		TransitionPoint(const TransitionPoint & TransitionPoint) { *this = TransitionPoint; };
		
		/// Assignment operator
		TransitionPoint &operator =(const TransitionPoint &TransitionPoint) {
			if (*this != TransitionPoint)
			{
				m_id= TransitionPoint.m_id;
				m_X = TransitionPoint.m_X;
				m_Y = TransitionPoint.m_Y;
				m_Z = TransitionPoint.m_Z;
				m_TransitionPoint = TransitionPoint.m_TransitionPoint;
				m_T = TransitionPoint.m_T;
			}
			return *this;
		};
		
		/// Equals operator
		bool operator ==(const TransitionPoint &TransitionPoint) const {
			return ((m_id == TransitionPoint.m_id) &&
					(m_X == TransitionPoint.m_X) &&
					(m_Y == TransitionPoint.m_Y) &&
					(m_Z == TransitionPoint.m_Z) &&
					(m_T == TransitionPoint.m_T) &&
					(m_TransitionPoint == TransitionPoint.m_TransitionPoint));
		};
		
		/// Not Equals operator
		bool operator !=(const TransitionPoint &TransitionPoint) const {
			return ((m_id    != TransitionPoint.m_id) ||
					(m_X     != TransitionPoint.m_X ) ||
					(m_Y     != TransitionPoint.m_Y ) ||
					(m_Z     != TransitionPoint.m_Z ) ||
					(m_T     != TransitionPoint.m_T ) ||
					(m_TransitionPoint != TransitionPoint.m_TransitionPoint));
		};
		
		/// X rotate operator
		TransitionPoint &operator >>(const int step) {
			this->rotX(step);
			return *this;
		};
		
		/// Z rotate operator
		TransitionPoint &operator <<(const int step) {
			this->rotZ(step);
			return *this;
		};
		
		/// Y rotate operator
		TransitionPoint &operator ^(const int step) {
			this->rotY(step);
			return *this;
		};
		
		
		TransitionPoint &operator +(const TransitionPoint &TransitionPoint) {
			m_X += TransitionPoint.m_X;
			m_Y += TransitionPoint.m_Y;
			m_Z += TransitionPoint.m_Z;
			m_TransitionPoint = this->CoordinatesToTransitionPoint();
			return *this;
		};
		
		TransitionPoint &operator -(const TransitionPoint &TransitionPoint) {
			m_X -= TransitionPoint.m_X;
			m_Y -= TransitionPoint.m_Y;
			m_Z -= TransitionPoint.m_Z;
			m_TransitionPoint = this->CoordinatesToTransitionPoint();
			return *this;
		};
		
		/**
		 * Rotates set new vertex position.
		 * @param x position
		 * @param y position
		 * @param z position
		 */
		void setPosition(int, int, int);
		
		/**
		 * Sets up new vertex position
		 * @param TransitionPoint position
		 */ 
		void setPosition(int);
		
		/**
		 * Rotate X axis in steps of 90 degrees.
		 */
		int rotX(int);
		
		/**
		 * Rotate Y axis in steps of 90 degrees.
		 */
		int rotY(int step) { return this->rotate(1,step); };
		
		/**
		 * Rotate Z axis in steps of 90 degrees.
		 */
		int rotZ(int step) { return this->rotate(2,step); };
		
		/**
		 * Returns TransitionPoint rotated.
		 */
		Uint getRotatedTransitionPoint() { return (Uint)m_TransitionPoint; }
		
		int getX() { return m_X; };
		int getY() { return m_Y; };
		int getZ() { return m_Z; };
		
		/**
		 * Returns initial TransitionPoint values, it has not changed despite of rotations.
		 */
		Uint getInitTransitionPoint() { return (Uint)m_id; };
		
		void setX(int _x) { m_X = _x; };
		void setY(int _y) { m_Y = _y; };
		void setZ(int _z) { m_Z = _z; };
		
	private:
		int rotate(int, int);
		int CoordinatesToTransitionPoint();
		void TransitionPointToCoordinates(int);
		int coordinatesToID(int, int, int);
		
		/**
		 * Check 90 degrees step be into 0..3.
		 */
		int getSteps(int);
		
		int m_id;
		int m_X;
		int m_Y;
		int m_Z;
		int m_T;
		int m_TransitionPoint;
		
		static const int TOTAL_TransitionPointS;
		/**
		 * Matrix to determine vertex number
		 */ 
		static const int CoordinatesToTransitionPointConversionMatrix [];
		
		/**
		 * Matrix to return x,y,z according vertex number.
		 */
		static const int TransitionPointToCoordinatesConversionMatrix [][3];
		
		/**
		 *
		 */
		static const int RotationMatrix_X[4][4][4];
		static const int RotationMatrix_Y[4][4][4];
		static const int RotationMatrix_Z[4][4][4];
	};
	
}

#endif /* TransitionPoint_H_ */
