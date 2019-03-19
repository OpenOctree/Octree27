#include "stdafx.h"
#include "HexRotation.h"

namespace Clobscode
{
HexRotation::HexRotation(){
}

HexRotation::~HexRotation(){
}

//class idea:
//The original points will be rearrenged as if index were now 
//point 0 in the hexa node cofiguration.
vector<unsigned long> HexRotation::rotate(vector<unsigned long> original, 
										 int index){
  vector<unsigned long> rotated(8,0);
  switch(index){
    case 0:
      return original;		  
	/*node 1 is now node 0*/
    case 1:
      rotated[0] = original[1];
      rotated[1] = original[2];
      rotated[2] = original[3];
      rotated[3] = original[0];
      rotated[4] = original[5];
      rotated[5] = original[6];
      rotated[6] = original[7];
      rotated[7] = original[4];
      return rotated;
    case 2:
	/*node 2 is now node 0*/
      rotated[0] = original[2];
      rotated[1] = original[3];
      rotated[2] = original[0];
      rotated[3] = original[1];
      rotated[4] = original[6];
      rotated[5] = original[7];
      rotated[6] = original[4];
      rotated[7] = original[5];
      return rotated;
	/*node 3 is now node 0*/
	case 3:
      rotated[0] = original[3];
      rotated[1] = original[0];
      rotated[2] = original[1];
      rotated[3] = original[2];
      rotated[4] = original[7];
      rotated[5] = original[4];
      rotated[6] = original[5];
      rotated[7] = original[6];
      return rotated;
	/*node 4 is now node 0*/
    case 4:
      rotated[0] = original[4];
      rotated[1] = original[5];
      rotated[2] = original[1];
      rotated[3] = original[0];
      rotated[4] = original[7];
      rotated[5] = original[6];
      rotated[6] = original[2];
      rotated[7] = original[3];
      return rotated;
	/*node 5 is now node 0*/
    case 5:
      rotated[0] = original[5];
      rotated[1] = original[1];
      rotated[2] = original[0];
      rotated[3] = original[4];
      rotated[4] = original[6];
      rotated[5] = original[2];
      rotated[6] = original[3];
      rotated[7] = original[7];
      return rotated;
	/*node 6 is now node 0*/
	case 6:
      rotated[0] = original[6];
      rotated[1] = original[5];
      rotated[2] = original[4];
      rotated[3] = original[7];
      rotated[4] = original[2];
      rotated[5] = original[1];
      rotated[6] = original[0];
      rotated[7] = original[3];
      return rotated;
	/*node 7 is now node 0*/
    case 7:
      rotated[0] = original[7];
      rotated[1] = original[6];
      rotated[2] = original[5];
      rotated[3] = original[4];
      rotated[4] = original[3];
      rotated[5] = original[2];
      rotated[6] = original[1];
      rotated[7] = original[0];
      return rotated;
    default:
      return rotated;
  }
}

vector<unsigned long> HexRotation::rotatePosX(vector<unsigned long> original){
  vector<unsigned long> rotated(8,0);
  rotated[0] = original[1];
  rotated[1] = original[5];
  rotated[2] = original[6];
  rotated[3] = original[2];
  rotated[4] = original[0];
  rotated[5] = original[4];
  rotated[6] = original[7];
  rotated[7] = original[3];
  return rotated;
}

vector<unsigned long> HexRotation::rotateNegX(vector<unsigned long> original){
  vector<unsigned long> rotated(8,0);
  rotated[0] = original[4];
  rotated[1] = original[0];
  rotated[2] = original[3];
  rotated[3] = original[7];
  rotated[4] = original[5];
  rotated[5] = original[1];
  rotated[6] = original[2];
  rotated[7] = original[6];
  return rotated;
}

vector<unsigned long> HexRotation::rotatePosY(vector<unsigned long> original){
  vector<unsigned long> rotated(8,0);
  rotated[0] = original[3];
  rotated[1] = original[0];
  rotated[2] = original[1];
  rotated[3] = original[2];
  rotated[4] = original[7];
  rotated[5] = original[4];
  rotated[6] = original[5];
  rotated[7] = original[6];
  return rotated;
}

vector<unsigned long> HexRotation::rotateNegY(vector<unsigned long> original){
  vector<unsigned long> rotated(8,0);
  rotated[0] = original[1];
  rotated[1] = original[2];
  rotated[2] = original[3];
  rotated[3] = original[0];
  rotated[4] = original[5];
  rotated[5] = original[6];
  rotated[6] = original[7];
  rotated[7] = original[4];
  return rotated;
}

vector<unsigned long> HexRotation::rotatePosZ(vector<unsigned long> original){
  vector<unsigned long> rotated(8,0);
  rotated[0] = original[4];
  rotated[1] = original[5];
  rotated[2] = original[1];
  rotated[3] = original[0];
  rotated[4] = original[7];
  rotated[5] = original[6];
  rotated[6] = original[2];
  rotated[7] = original[3];
  return rotated;
}

vector<unsigned long> HexRotation::rotateNegZ(vector<unsigned long> original){
  vector<unsigned long> rotated(8,0);
  rotated[0] = original[3];
  rotated[1] = original[2];
  rotated[2] = original[6];
  rotated[3] = original[7];
  rotated[4] = original[0];
  rotated[5] = original[1];
  rotated[6] = original[5];
  rotated[7] = original[4];
  return rotated;
}
}
