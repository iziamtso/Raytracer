#ifndef _SPHERE_H_
#define _SPHERE_H_ 1

#include "Shape.h"
#include "vector3.h"
#include "Ray.h"
#include "rgb.h"

class Sphere : public Shape
{
public:
	Sphere(const Vector3& _center, float _radius, const Rgb& _color);
	//BBox boundingBox() const; //WTF is this?
	bool hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const Ray& r, float tmin, float tmax, float time) const;

	~Sphere(void);

	Vector3 center;
	float radius;
	Rgb color;
};

#endif
