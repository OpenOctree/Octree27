#ifndef HexRotation_h
#define HexRotation_h 1

#include <vector>

using std::vector;

namespace Clobscode
{
	class HexRotation {
		
	public:
		HexRotation();
		
		virtual ~HexRotation();
		
		virtual vector<unsigned long> rotate(vector<unsigned long> original,
											int index);
		
		virtual vector<unsigned long> rotatePosX(vector<unsigned long> original);
		
		virtual vector<unsigned long> rotateNegX(vector<unsigned long> original);
		
		virtual vector<unsigned long> rotatePosY(vector<unsigned long> original);
		
		virtual vector<unsigned long> rotateNegY(vector<unsigned long> original);
		
		virtual vector<unsigned long> rotatePosZ(vector<unsigned long> original);
		
		virtual vector<unsigned long> rotateNegZ(vector<unsigned long> original);
		
	};
}
#endif
