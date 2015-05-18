#pragma once

#include "Shape.h"
#include "vector3.h"
#include "Ray.h"
#include "rgb.h"


class Triangle : public Shape {
public:

	Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, const Rgb& _color);
	bool hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const Ray& r, float tmin, float tmax, float time) const;
	~Triangle(void);

	Vector3 p0;
	Vector3 p1;
	Vector3 p2;

	Rgb color;
};

