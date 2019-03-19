#ifndef Visitor_h
#define Visitor_h 1

/*
 * Parent definition of visitors
 * Visitors shall extend this main class to get forward declarations,
 * and also for operations that extends to more than one class...
 */

namespace Clobscode {

    //forward declarations
    class Octant;

    class Visitor {

    public:
        Visitor() { }

        virtual bool visit(Octant *o) { return false; }
    };


}

#endif //Visitor_h
