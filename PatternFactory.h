/*
 * PatternsDefault.h
 *
 *  Created on: May 18, 2012
 *      Author: jsepulve
 */

#include <iostream>
#include <vector>
#include <map>
#include <bitset>
#include "TransitionCube.h"


#ifndef PATTERN_FACTORY_H_
#define PATTERN_FACTORY_H_

using std::vector;
using std::map;
using std::bitset;
using std::cout;

namespace patterns {

typedef unsigned long Uint;
typedef vector< vector<Uint> > VTable;
typedef vector< vector<Uint> >::iterator VTableIter;

static const Uint TETRA_POINTS  =4;
static const Uint PYRAMID_POINTS=5;
static const Uint PRISM_POINTS  =6;
static const Uint HEXA_POINTS   =8;
static const Uint CORNER_POINTS =8;
static const Uint EDGE_POINTS   =24;
static const Uint FACE_POINTS   =24;
static const Uint TOTAL_POINTS  =64;
static const Uint PERMUTATIONS  =30;
//static const Uint MAX_ELEMENTS  =71;
static const Uint MAX_ELEMENTS  =82;
static const Uint NUM_PATTERNS  =26;


class PatternFactory {
public:
    
   /// Contains size (#points) & points that define one element.
   struct item {
      Uint size;
      Uint points[CORNER_POINTS];
   };

   /// Struct for a template definition (T2, T3, T4, T40, etc...)
   struct Template_st{
      Uint id; // unnecessary
      item items[MAX_ELEMENTS];
   };

   static PatternFactory *instance();
   static void deleteInstance();
   //virtual void createPattern(vector< vector<Uint> > & p);
   bool createPattern(Uint);
   void vectors(vector< vector<Uint> > & p ) { p = pattern; };
   
   void getTemplateEdges(Uint mask, vector<vector<Uint>>& edges);

private:
   PatternFactory() { };
   PatternFactory(const PatternFactory &) { };
   virtual ~PatternFactory() { };
   PatternFactory& operator=(PatternFactory const&){ return *this; };

   /// Array of templates (their definition)
   static const Template_st templates[];
   /// Maps pattern_mask --> template_ix (on templates array)
   static const map<Uint, Uint> pattern_template_map_newest;
   static const map<Uint, Uint> pattern_template_map_ito; // version Ito et al (2009) Efficient Hexa mesh...
   static const map<Uint, Uint> pattern_template_map_ito_A; // Ito et al. 2009 Octree-based reasonable-quality hexahedral mesh generation using a new set of refinement templates.
   static const map<Uint, Uint> pattern_template_map_ito_B;
   static const constexpr map<Uint, Uint>* pattern_template_map = &pattern_template_map_newest;
   /// Edges that must be split for each template.
   static const map<Uint, vector<vector<Uint>>> template_edges_map;
   /// Storages the elements of the template for the pattern found
   vector< vector<Uint> > pattern;

   static PatternFactory* m_Instance;
   static int m_NumInstances;
};
}

#endif /* PATTERN_FACTORY_H_ */
