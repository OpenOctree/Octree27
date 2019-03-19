#ifndef Point3D_h
#define Point3D_h 1

#include <iostream>
#include <sstream>
#include <math.h>
#include <list>
#include <vector>

namespace Clobscode
{
	using namespace std;
	
	class Point3D{
		
	public:
		Point3D();
		
		Point3D(double x, double y, double z);
		
		virtual ~Point3D();
		
		virtual double X() const;
		
		virtual double Y() const;
		
		virtual double Z() const;
		
		virtual double &X();
		
		virtual double &Y();
		
		virtual double &Z();
		
		virtual void normalize();
		
		virtual double Norm();
		
		virtual Point3D cross(Point3D p);
		
		//cross product operator
		virtual Point3D operator^(Point3D p);
		
		virtual Point3D operator^(const Point3D &p) const;
		
		virtual double dot(Point3D p);
		
		//dot product operator
		virtual double operator*(Point3D p);
		
		virtual double operator*(const Point3D &p) const;
		
		virtual double distance(Point3D p);
		
		virtual double DistanceTo(const Point3D &p);
		
		virtual double DistanceTo(const Point3D &p) const;
		
		virtual Point3D operator-(Point3D p2);
		
		virtual Point3D operator-(const Point3D &p) const;
		
		virtual Point3D operator-();
		
		virtual Point3D operator-() const;
		
		virtual Point3D operator+(Point3D p);
		
		virtual Point3D operator+(const Point3D &p) const;
		
		//virtual void operator+=(Point3D p2);
		
		virtual const Point3D &operator+=(const Point3D &p);
		
		virtual const Point3D &operator-=(const Point3D &p);
		
		virtual const Point3D &operator*=(double mul);
		
		virtual void operator/=(double div);
		
		virtual Point3D operator/(double div) const;
		
		virtual Point3D operator*(double mul) const;
		
		virtual double &operator[](int pos);
		
		virtual double operator[](int pos) const;
		
		virtual void operator=(Point3D p);
		
		virtual Point3D operator*(double escalar);
		
		virtual void update(Point3D *Point3D);
		
		virtual void update(Point3D Point3D);
		
		virtual string print();
		
		virtual void xAxisRotation(double angle);
		
		virtual void yAxisRotation(double angle);
		
		virtual void zAxisRotation(double angle);
		
		friend std::ostream& operator<<(std::ostream& o,Point3D &p);
		
		friend bool operator==(Point3D &p1,Point3D &p2);
		
		friend bool operator!=(Point3D &p1,Point3D &p2);
		
		friend Point3D operator/(double div, const Point3D &p);
		
		friend Point3D operator*(double mul, const Point3D &p);
		
	protected:
		
		double x,y,z;
		
	};
	
	inline double Point3D::X() const {
		return x;
	}
	
	inline double Point3D::Y() const {
		return y;
	}
	
	inline double Point3D::Z() const {
		return z;
	}
	
	inline double &Point3D::X() {
		return x;
	}
	
	inline double &Point3D::Y() {
		return y;
	}
	
	inline double &Point3D::Z() {
		return z;
	}
	
	inline Point3D Point3D::operator^(const Point3D &p) const {
		Point3D ret;
		ret[0]=y*p[2] - z*p[1];
		ret[1]=z*p[0] - x*p[2];
		ret[2]=x*p[1] - y*p[0];
		return ret;
	}
	
	inline double Point3D::operator*(const Point3D &p) const {
		return x*p[0]+y*p[1]+z*p[2];
	}
	
	inline Point3D Point3D::operator/(double div) const {
		return Point3D(x/div,y/div,z/div);
	}
	
	inline Point3D Point3D::operator-(const Point3D &p) const {
		return Point3D(x-p[0],y-p[1],z-p[2]);
	}
	
	inline Point3D Point3D::operator-() const {
		return Point3D(-x,-y,-z);
	}

	inline Point3D Point3D::operator+(const Point3D &p) const {
		return Point3D(x+p[0],y+p[1],z+p[2]);
	}
	
	inline Point3D operator/(double div, const Point3D &p) {
		return p/div;
	}
	
	inline const Point3D &Point3D::operator+=(const Point3D &p) {
		x+=p[0]; y+=p[1]; z+=p[2];
		return *this;
	}
	
	inline const Point3D &Point3D::operator-=(const Point3D &p) {
		x-=p[0]; y-=p[1]; z-=p[2];
		return *this;
	}
	
	inline const Point3D &Point3D::operator*=(double mul) {
		x*=mul; y*=mul; z*=mul;
		return *this;
	}
	
	inline Point3D Point3D::operator*(double mul) const {
		return Point3D (x*mul,y*mul,z*mul);
	}
	
	inline Point3D operator*(double mul, const Point3D&p){
		return Point3D(p.X()*mul,p.Y()*mul,p.Z()*mul);
	}
	
	inline void Point3D::update(Point3D *Point3D){
		x = (*Point3D)[0];
		y = (*Point3D)[1];
		z = (*Point3D)[2]; 
	}
	
	inline void Point3D::update(Point3D Point3D){
		x = Point3D[0];
		y = Point3D[1];
		z = Point3D[2]; 
	}
	
	inline double Point3D::operator[](int pos) const{
		if(pos==0)
			return x;
		if(pos==1)
			return y;
		return z;
	}
	
	inline void Point3D::xAxisRotation(double angle){
		Point3D pivot ( x, y, z);
		Y() = cos(angle)*pivot.Y() - sin(angle)*pivot.Z();
        Z() = sin(angle)*pivot.Y() + cos(angle)*pivot.Z();
     }
     
     inline void Point3D::yAxisRotation(double angle){

		Point3D pivot ( x, y, z);
        X() = cos(angle)*pivot.X() + sin(angle)*pivot.Z();
        Z() = -sin(angle)*pivot.X() + cos(angle)*pivot.Z();
     } 
     
     inline void Point3D::zAxisRotation(double angle){

		Point3D pivot ( x, y, z);
		X() = cos(angle)*pivot.X() - sin(angle)*pivot.Y();
        Y() = sin(angle)*pivot.X() + cos(angle)*pivot.Y();
     }
}    
#endif
