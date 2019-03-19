/*
 * TransitionPoint.cpp
 *
 *  Created on: May 30, 2012
 *      Author: jsepulve
 */

#include "TransitionPoint.h"


namespace patterns {
	
	const int TransitionPoint::TOTAL_TransitionPointS = 64;
	const int TransitionPoint::CoordinatesToTransitionPointConversionMatrix [3] = {1,4,16};
	const int TransitionPoint::TransitionPointToCoordinatesConversionMatrix [TOTAL_TransitionPointS][3] = {
		{0,0,0}, //0
		{1,0,0}, //1
		{2,0,0}, //2
		{3,0,0}, //3
		{0,1,0}, //4
		{1,1,0}, //5
		{2,1,0}, //6
		{3,1,0}, //7
		{0,2,0}, //8
		{1,2,0}, //9
		{2,2,0}, //10
		{3,2,0}, //11
		{0,3,0}, //12
		{1,3,0}, //13
		{2,3,0}, //14
		{3,3,0}, //15
		{0,0,1}, //16
		{1,0,1}, //17
		{2,0,1}, //18
		{3,0,1}, //19
		{0,1,1}, //20
		{1,1,1}, //21
		{2,1,1}, //22
		{3,1,1}, //23
		{0,2,1}, //24
		{1,2,1}, //25
		{2,2,1}, //26
		{3,2,1}, //27
		{0,3,1}, //28
		{1,3,1}, //29
		{2,3,1}, //30
		{3,3,1}, //31
		{0,0,2}, //32
		{1,0,2}, //33
		{2,0,2}, //34
		{3,0,2}, //35
		{0,1,2}, //36
		{1,1,2}, //37
		{2,1,2}, //38
		{3,1,2}, //39
		{0,2,2}, //40
		{1,2,2}, //41
		{2,2,2}, //42
		{3,2,2}, //43
		{0,3,2}, //44
		{1,3,2}, //45
		{2,3,2}, //46
		{3,3,2}, //47
		{0,0,3}, //48
		{1,0,3}, //49
		{2,0,3}, //50
		{3,0,3}, //51
		{0,1,3}, //52
		{1,1,3}, //53
		{2,1,3}, //54
		{3,1,3}, //55
		{0,2,3}, //56
		{1,2,3}, //57
		{2,2,3}, //58
		{3,2,3}, //59
		{0,3,3}, //60
		{1,3,3}, //61
		{2,3,3}, //62
		{3,3,3}  //63
	};
	
	const int TransitionPoint::RotationMatrix_X [4][4][4] = {
		{ /// 0 degree rotation
			{ 1, 0, 0, 0},
			{ 0, 1, 0, 0},
			{ 0, 0, 1, 0},
			{ 0, 0, 0, 0}
		},
		{ /// 90 degree rotation
			{1, 0, 0, 0},
			{0, 0,-1, 3},
			{0, 1, 0, 0},
			{0, 0, 0, 1}
		},
		{ /// 180 degree rotation
			{1, 0, 0, 0},
			{0,-1, 0, 3},
			{0, 0,-1, 3},
			{0, 0, 0, 1}
		},
		{ /// 270 degree rotation
			{1, 0, 0, 0},
			{0, 0, 1, 0},
			{0,-1, 0, 3},
			{0, 0, 0, 1}
		}
	};
	
	const int TransitionPoint::RotationMatrix_Y [4][4][4] =
	{
		{ /// 0 degree rotation
			{ 1, 0, 0, 0},
			{ 0, 1, 0, 0},
			{ 0, 0, 1, 0},
			{ 0, 0, 0, 0}
		},
		{ /// 90 degree rotation
			{ 0, 0, 1, 0},
			{ 0, 1, 0, 0},
			{-1, 0, 0, 3},
			{ 0, 0, 0, 1}
		},
		{ /// 180 degree rotation
			{-1, 0, 0, 3},
			{ 0, 1, 0, 0},
			{ 0, 0,-1, 3},
			{ 0, 0, 0, 1}
		},
		{ /// 270 degree rotation
			{ 0, 0,-1, 3},
			{ 0, 1, 0, 0},
			{ 1, 0, 0, 0},
			{ 0, 0, 0, 1}
		}
	};
	
	const int TransitionPoint::RotationMatrix_Z [4][4][4] =
	{
		{ /// 0 degree rotation
			{ 1, 0, 0, 0},
			{ 0, 1, 0, 0},
			{ 0, 0, 1, 0},
			{ 0, 0, 0, 0}
		},
		{ /// 90 degree rotation
			{ 0,-1, 0, 3}, // <--
			{ 1, 0, 0, 0},
			{ 0, 0, 1, 0},
			{ 0, 0, 0, 1}
		},
		{ /// 180 degree rotation
			{-1, 0, 0, 3},
			{ 0,-1, 0, 3},
			{ 0, 0, 1, 0},
			{ 0, 0, 0, 1}
		},
		{ /// 270 degree rotation
			{ 0, 1, 0, 0},
			{-1, 0, 0, 3},
			{ 0, 0, 1, 0},
			{ 0, 0, 0, 1}
		}
	};
	
	TransitionPoint::TransitionPoint(int id, int x, int y, int z)
    : m_id(id), m_X(x), m_Y(y), m_Z(z), m_T(1) { 
		m_TransitionPoint = CoordinatesToTransitionPoint(); 
	}
	
	TransitionPoint::TransitionPoint(int x, int y, int z): m_X(x), m_Y(y), m_Z(z), m_T(1) { 
		m_TransitionPoint = CoordinatesToTransitionPoint(); 
		m_id    = m_TransitionPoint;
	}
	
	
	
	int TransitionPoint::CoordinatesToTransitionPoint() {
		return (m_X*CoordinatesToTransitionPointConversionMatrix[0] +
				m_Y*CoordinatesToTransitionPointConversionMatrix[1] +
				m_Z*CoordinatesToTransitionPointConversionMatrix[2]);
	}
	
	void TransitionPoint::TransitionPointToCoordinates(int TransitionPoint) {
		if ( (TransitionPoint >= 0) && (TransitionPoint <TOTAL_TransitionPointS) ) {
			m_X = TransitionPointToCoordinatesConversionMatrix[TransitionPoint][0];
			m_Y = TransitionPointToCoordinatesConversionMatrix[TransitionPoint][1];
			m_Z = TransitionPointToCoordinatesConversionMatrix[TransitionPoint][2];
			m_TransitionPoint = TransitionPoint;
			m_id = m_TransitionPoint;
		}
		else {
			m_X=0;
			m_Y=0;
			m_Z=0;
			m_TransitionPoint = 0;
			m_id=0;
		}
	}
	
	int TransitionPoint::rotX(int input_step) {
		int step = this->getSteps(input_step);
		
		const int (*rot)[4]=RotationMatrix_X[step];
		
		int temp[4] = {0, 0, 0, 0};
		
		for (int i=0; i<4; i++)
		{
			temp[i] = rot[i][0]*m_X + rot[i][1]*m_Y + rot[i][2]*m_Z + rot[i][3]*m_T;
		}
		m_X = temp[0];
		m_Y = temp[1];
		m_Z = temp[2];
		m_TransitionPoint = this->CoordinatesToTransitionPoint();
		
		return (m_TransitionPoint);
	}
	
	int TransitionPoint::rotate(int axis, int number_steps) {
		/// Do nothing just return current position
		if ( (axis > -1) && (axis < 4) )
		{
			int step = this->getSteps(number_steps);
			const int (*rot)[4];
			if (axis == 0)
				rot=RotationMatrix_X[step];
			else if (axis == 1)
				rot=RotationMatrix_Y[step];
			else if (axis == 2)
				rot=RotationMatrix_Z[step];
			
			int temp[4] = {0, 0, 0, 0};
			//std::cout << "axis: " << axis << "\n";
			//std::cout << "mask: " << step << "\n"; 
			for (int i=0; i<4; i++)
			{
				temp[i] = rot[i][0]*m_X + rot[i][1]*m_Y + rot[i][2]*m_Z + rot[i][3]*m_T;
			}
			
			m_X = temp[0];
			m_Y = temp[1];
			m_Z = temp[2];
			m_TransitionPoint = this->CoordinatesToTransitionPoint();
		}
		
		return (m_TransitionPoint);
	}
	
	
	void TransitionPoint::setPosition(int _x, int _y, int _z) {
		m_X = _x;
		m_Y = _y;
		m_Z = _z;
		m_TransitionPoint = this->CoordinatesToTransitionPoint();
	}
	
	void TransitionPoint::setPosition(int TransitionPoint) {
		this->TransitionPointToCoordinates(TransitionPoint);
		m_TransitionPoint = this->CoordinatesToTransitionPoint();
	}
	
	
	int TransitionPoint::getSteps(int rotation) {
		if (rotation < 0)
		{
			int step = abs(rotation) % 4;
			if (step == 1)
				step = 3; // -90 degrees --> +270 degrees
			else if (step == 3)
				step = 1; // -270 degrees --> +90 degrees
			
			return step;
		}
		return (rotation % 4);
	}
	
	int TransitionPoint::coordinatesToID(int x, int y, int z) {
		for (int i=0; i< TOTAL_TransitionPointS; i++)
		{
			if ( (TransitionPointToCoordinatesConversionMatrix[i][0] == x) && 
                (TransitionPointToCoordinatesConversionMatrix[i][1] == y) && 
                (TransitionPointToCoordinatesConversionMatrix[i][2] == z) )
			{
				return i;
			}
		}
		return 0;
	}
	
	
}
