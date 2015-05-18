#ifndef _SHAPE_H_
#define _SHAPE_H_ 1

#include "Ray.h"
#include "vector3.h"
#include "rgb.h"

//Forward declarations
class Ray;
class Rgb;

struct HitRecord{
	float t;
	Vector3 normal;
	Rgb color;
};

class Shape {
public:
	virtual bool hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const=0;
	virtual bool shadowHit(const Ray& r, float tmin, float tmax, float time) const=0;
};

#endif

//virtual void funcFoo() const = 0;
//- You can't change the state of the object
//	- You can call this function via const objects
//	- You can only call another const member functions on this object
//
//	virtual void funcFoo() = 0;
//- You can change the state of the object
//	- You can't call this function via const objects
