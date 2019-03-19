#ifndef SurfTemplate3_h
#define SurfTemplate3_h 3

#include <vector>
#include <iostream>
#include "HexRotation.h"

using std::vector;

namespace Clobscode
{
    class SurfTemplate3 {
        
    public:
        
        SurfTemplate3();
        
        virtual ~SurfTemplate3();
        
        virtual bool getSubelements(vector<unsigned long> &all,
                                    vector<unsigned long> &in,
                                    vector<vector<unsigned long> > &neweles);
        
        virtual bool getSubelements(vector<unsigned long> &all,
                                    vector<unsigned long> &in,
                                    vector<vector<unsigned long> > &neweles,
                                    vector<vector<unsigned long> > &possibles);
        
    protected:
        
        virtual void PatternA(vector<unsigned long> &all,
                              vector<vector<unsigned long> > &neweles);
        
        virtual void PatternA(vector<unsigned long> &all,
                              vector<vector<unsigned long> > &neweles,
                              vector<vector<unsigned long> > &possibles);
        
        virtual void PatternB(vector<unsigned long> &all,
                              vector<vector<unsigned long> > &neweles);
        
        virtual void PatternB(vector<unsigned long> &all,
                              vector<vector<unsigned long> > &neweles,
                              vector<vector<unsigned long> > &possibles);
        
        virtual void PatternC(vector<unsigned long> &all,
                              vector<vector<unsigned long> > &neweles);
        
        virtual void PatternC(vector<unsigned long> &all,
                              vector<vector<unsigned long> > &neweles,
                              vector<vector<unsigned long> > &possibles);
        
        virtual void PatternD(vector<unsigned long> &all, 
                              vector<vector<unsigned long> > &neweles);
        
        virtual void swap(vector<unsigned long> &vec,int pos1, int pos2);
        
    };
}
#endif
