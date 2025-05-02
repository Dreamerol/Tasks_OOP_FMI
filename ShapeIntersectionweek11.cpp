#pragma once
struct Point{
    int x;
    int y;
    
   
};
class Shape{
    public:
virtual double getPerimeter() const = 0;
virtual double getArea() const = 0;
virtual bool isPointInside(const Point& p) const = 0; 
virtual ~Shape();
virtual bool intersectionWith(Shape* shape) const = 0;
virtual bool intersectionWithCircle(Shape* shape) const = 0;
};

#pragma once
#include "Shape.h"
class Triangle : public Shape{
  Point A;
  Point B;
  Point C;
  
  public:
  const Point& getA() const;
  const Point& getB() const;
  const Point& getC() const;
  
  Triangle(const Point& A,const Point& B,const Point& C);
    double getPerimeter() const override;
    double getArea() const override;
    bool isPointInside(const Point& P) const override;
    virtual bool intersectionWith(Shape* shape) const override;
    virtual bool intersectionWithCircle(Shape* shape) const override;
  
};

#pragma once
#include "Shape.h"
class Circle : public Shape{
  double radius;
  Point center;
  public:
  Circle(const Circle& other);
  const Point& getCenter() const;
  double getRadius() const;
  Circle(double radius,const Point& center);
  double getPerimeter() const override;
    double getArea() const override;
    bool isPointInside(const Point& P) const override;
    virtual bool intersectionWith(Shape* shape) const override;
    virtual bool intersectionWithCircle(Shape* shape) const override;
};

#pragma once
#include "Shape.h"
class Rectangle : public Shape{
  Point A;
  Point B;
  Point C;
  Point D;
  
  int height;
  int width;
  
  public:
   const Point& getA() const;
  const Point& getB() const;
  const Point& getC() const;
  const Point& getD() const;
   Rectangle(const Point& A,int w, int h);
    double getPerimeter() const override;
    double getArea() const override;
    bool isPointInside(const Point& P) const override;
    virtual bool intersectionWith(Shape* shape) const override;
    virtual bool intersectionWithCircle(Shape* shape) const override;
    
  
};


#include <iostream>
#include <cmath>
#include "Shape.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
const double EPSILON = 1e-10;
Shape::~Shape() = default;
Triangle::Triangle(const Point& A,const Point& B,const Point& C) {
	this->A = A;
	this->B = B;
	this->C = C;
}
double getDistance(const Point& A,const Point& B) {
	return sqrt((A.x - B.x)*(A.x-B.x) + (A.y - B.y)*(A.y-B.y));
}
double Triangle::getPerimeter() const {
	double p = getDistance(A, B) + getDistance(B, C) + getDistance(A, C);
	return p;

}
double Triangle::getArea() const {

	double p = getPerimeter() / 2;

	double a = getDistance(B, C);
	double b = getDistance(A, C);
	double c = getDistance(B, A);
	double s = sqrt(p*(p-a)*(p-b)*(p-c));
	return s;
}

bool Triangle::isPointInside(const Point& P) const {
	double S = getArea();
	Triangle t1(A, B, P);
	Triangle t2(A, C, P);
	Triangle t3(B, C, P);

	double S1 = t1.getArea();
	double S2 = t2.getArea();
	double S3 = t3.getArea();
	return (abs(S1+S2+S3 - S)< EPSILON);
}
Rectangle::Rectangle(const Point& A,int w, int h) {
	height = h;
	width = w;
	this->A = A;
	this->B = {A.x + width, A.y};
	this->C = {this->B.x, this->B.y+height};
	this->D = {A.x, A.y+height};
}
double Rectangle::getPerimeter() const {
	// double p = getDistance(A, B) + getDistance(A, D);
	double p = width+height;
	return 2*p;
}
double Rectangle::getArea() const {
	// double s = getDistance(A, D) * getDistance(A, B);
	double s = width*height;
	return s;
}
bool Rectangle::isPointInside(const Point& P) const {
	double S = getArea();
	Triangle t1(A, B, P);
	Triangle t2(B, C, P);
	Triangle t3(D, C, P);
	Triangle t4(A, D, P);

	double S1 = t1.getArea();
	double S2 = t2.getArea();
	double S3 = t3.getArea();
	double S4 = t4.getArea();
	//std::cout<<S<<' '<<S1<<' '<<S2<<' '<<S3<<' '<<S4<<'\n';
	return (abs(S1+S2+S3+S4 - S)< EPSILON);
}
Circle::Circle(double radius,const Point& center) {
	this->radius = radius;
	this->center = center;
}
double Circle::getPerimeter() const {
	return 2*3.14*radius;
}
double Circle::getArea() const {
	return 3.14*radius*radius;
}
bool Circle::isPointInside(const Point& P) const {
	double dist = getDistance(center, P);
	return(dist <= radius);
}
const Point& Triangle::getA() const {
	return A;
}
const Point& Triangle::getB() const {
	return B;
}
const Point& Triangle::getC() const {
	return C;
}

const Point& Rectangle::getA() const {
	return A;
}
const Point& Rectangle::getB() const {
	return B;
}
const Point& Rectangle::getC() const {
	return C;
}

const Point& Rectangle::getD() const {
	return D;
}
const Point& Circle::getCenter() const {
	return center;
}
double Circle::getRadius() const {
	return radius;
}
bool Triangle::intersectionWith(Shape* shape) const {
	return (shape->isPointInside(getA()) ||
	        shape->isPointInside(getB()) ||
	        shape->isPointInside(getC()));
}
bool Rectangle::intersectionWith(Shape* shape) const {
	return(shape->isPointInside(getA()) ||
	       shape->isPointInside(getB()) ||
	       shape->isPointInside(getC()) ||
	       shape->isPointInside(getD()));
}
 bool Triangle::intersectionWithCircle(Shape* shape) const{
     Circle* c = dynamic_cast<Circle*>(shape);
      return((getDistance(c->getCenter(), getA()) <= c->getRadius()) ||
               (getDistance(c->getCenter(), getB()) <= c->getRadius())||
               (getDistance(c->getCenter(), getC()) <= c->getRadius()));
 }
 bool Rectangle::intersectionWithCircle(Shape* shape) const{
        Circle* c = dynamic_cast<Circle*>(shape);
     return((getDistance(c->getCenter(), getA()) <= c->getRadius()) ||
               (getDistance(c->getCenter(), getB()) <= c->getRadius())||
               (getDistance(c->getCenter(), getC()) <= c->getRadius())||
               (getDistance(c->getCenter(), getD()) <= c->getRadius()));
 }
 bool Circle::intersectionWithCircle(Shape* shape) const{
        Circle* c = dynamic_cast<Circle*>(shape);
     return (c->getRadius() + getRadius() > getDistance(c->getCenter(), getCenter()));
 }
 Circle::Circle(const Circle& other){
     this->center = other.center;
     this->radius = other.radius;
 }
bool Circle::intersectionWith(Shape* shape) const {
    Circle* ci = new Circle(*this);
    return shape->intersectionWithCircle(ci);
    
}
     
bool intersect(Shape* shape1, Shape* shape2) {
    
    return shape1->intersectionWith(shape2);
    
}



// bool Circle::intersectionWith(Shape* shape) const {

        //   if(Triangle* t = dynamic_cast<Triangle*>(shape)){
        //       return t->intersectionWithCircle(this);
        //   }
        //   else if(Rectangle* t = dynamic_cast<Rectangle*>(shape)){
        //       return r->intersectionWithCircle(this);
        //   }
        //   else{
        //       Circle* c1 = dynamic_cast<Circle*>(shape);
        //       return c1->intersectionWithCircle(this);
        //   }
//}
// bool intersect(Shape* shape1, Shape* shape2) {
    
//     return shape1->intersectionWith(shape2);
// 	if (Triangle* t = dynamic_cast<Triangle*>(shape2)) {
// 		
		// return (shape1->isPointInside(t->getA()) ||
		//         shape1->isPointInside(t->getB()) ||
		//         shape1->isPointInside(t->getC()));
	//}
// 	else if(Rectangle* r = dynamic_cast<Rectangle*>(shape2)) {
// 	
		//   return(shape1->isPointInside(r->getA()) ||
		//   shape1->isPointInside(r->getB()) ||
		//   shape1->isPointInside(r->getC()) ||
		//   shape1->isPointInside(r->getD()));
// 	}
// 	else {
// 	    Circle* c = dynamic_cast<Rectangle*>(shape2);
		//     Circle* c = dynamic_cast<Circle*>(shape2);
		//   if(Triangle* t = dynamic_cast<Triangle*>(shape1)){
		//       return((getDistance(c->getCenter(), t->getA()) <= c->getRadius()) ||
		//       (getDistance(c->getCenter(), t->getB()) <= c->getRadius())||
		//       (getDistance(c->getCenter(), t->getC()) <= c->getRadius()));
		//   }
		//   else if(Rectangle* t = dynamic_cast<Rectangle*>(shape1)){
		//       return((getDistance(c->getCenter(), t->getA()) <= c->getRadius()) ||
		//       (getDistance(c->getCenter(), t->getB()) <= c->getRadius())||
		//       (getDistance(c->getCenter(), t->getC()) <= c->getRadius())||
		//       (getDistance(c->getCenter(), t->getD()) <= c->getRadius()));
		//   }
		//   else{
		//       Circle* c1 = dynamic_cast<Circle*>(shape1);
		//       return (c->getRadius() + c1->getRadius() > getDistance(c->getCenter(), c1->getCenter()));
		//   }
//	}
//}
int main()
{
	Point A = {0, 0};
	Point B = {4, 0};
	Point C = {4, 3};
	Point D = {0, 3};
	Point X = {11111, 1};
	Triangle t(A, B, C);
	Triangle r(A, B, D);
	 Rectangle f(X, 20, 10);
	Circle d(2, A);
	Circle d1(3, A);
	std::cout<<intersect(&d, &d1);
	//std::cout<<r.isPointInside(X);
	// std::cout<<r.getArea();
	Circle c(10, A);
	//  std::cout<<c.getPerimeter();
	//std::cout<<c.isPointInside(X);
//   std::cout<<t.getArea();
//  std::cout<< t.isPointInside(D);
	return 0;
}
