#ifndef Mesher_h
#define Mesher_h 1

#include "TriMesh.h"
#include "FEMesh.h"
#include "GridMesher.h"
#include "Octant.h"
#include "OctreeEdge.h"
#include "CoteMarek.h"
#include "RefinementRegion.h"
#include "RefinementCubeRegion.h"

#include "Visitors/SplitVisitor.h"
#include "Visitors/IntersectionsVisitor.h"
#include "Visitors/OneIrregularVisitor.h"
#include "Visitors/PointMovedVisitor.h"
#include "Visitors/TransitionPatternVisitor.h"
#include "Visitors/SurfaceTemplatesVisitor.h"
#include "Visitors/RemoveSubElementsVisitor.h"

#include <list>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <string.h>

using std::vector;
using std::list;
using std::set;
using Clobscode::OctreeEdge;
using Clobscode::TriMesh;
using Clobscode::RefinementRegion;

namespace Clobscode
{
	
	class Mesher{
		
	public:
		
		Mesher();
		
		virtual ~Mesher();
				
		virtual FEMesh generateMesh(void * pClientData, TriMesh &input,
                                    const unsigned short &rl, const string &name,
									list<RefinementRegion *> &all_reg);
		
	protected:
		
		virtual void generateOctreeMesh(const unsigned short &rl, TriMesh &input,
                                        list<RefinementRegion *> &all_reg, const string &name);

		virtual bool isItIn(TriMesh &mesh, list<unsigned long> &faces, vector<Point3D> &coords);

		virtual bool rotateGridMesh(TriMesh &input,
									list<RefinementRegion *> &all_reg,
									GeometricTransform &gt);                                        
		
		/*virtual void generateGridFromOctree(const unsigned short &rl, 
										TriMesh &input,
										const string &name);*/
		
		virtual void generateGridMesh(TriMesh &input);
		
		virtual void linkElementsToNodes();

		virtual void detectInsideNodes(TriMesh &input);

		virtual void removeOnSurface();
		
		virtual void applySurfacePatterns(TriMesh &input);

		virtual void shrinkToBoundary(TriMesh &input);

		virtual void saveOutputMesh(FEMesh &mesh);
		
		virtual void saveOutputMesh(FEMesh &mesh,
									vector<MeshPoint> &points, 
									list<Octant> &elements);
        
        virtual void projectCloseToBoundaryNodes(TriMesh &input);


		
	protected:
		
		vector<MeshPoint> points;
		vector<Octant> octants;
		set<OctreeEdge> octreeEdges;
		list<RefinementRegion *> regions;

		vector<Point3D> puntosVector;
		vector<unsigned long> idxsVector;
		set<unsigned long> idxsRefinados;
	};
	
	
}
#endif
