cmake_minimum_required(VERSION 2.6)
project(mesher_roi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES Main MeshPoint Point3D TriMesh Octant OctreeEdge HexRotation
        SurfTemplate1 SurfTemplate2 SurfTemplate3 SurfTemplate4
        SurfTemplate5 SurfTemplate6 SurfTemplate7
        Mesher GridMesher TransitionPoint PatternFactory TransitionTemplate
        TransitionCube SurfPair SurfEdge SurfEdgeContainer SurfTriangle
        RefinementRegion RefinementCubeRegion RefinementSurfaceRegion
        RefinementInputSurfaceRegion RefinementAllRegion
        FaceDiagonal SurfPrism SurfPyramid SurfHexahedron SurfTetrahedron 
	SurfaceEdge GeometricTransform
        Visitors/Visitor Visitors/SplitVisitor Visitors/EdgeVisitor 
	Visitors/IntersectionsVisitor
        Visitors/OneIrregularVisitor Visitors/PointMovedVisitor
        Visitors/TransitionPatternVisitor Visitors/SurfaceTemplatesVisitor
        Visitors/RemoveSubElementsVisitor)


add_executable(mesher_roi_27 ${SOURCE_FILES})
