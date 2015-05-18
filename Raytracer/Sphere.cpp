//#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere(const Vector3& _center, float _radius, const Rgb& _color) 
	: center(_center), radius(_radius), color(_color) {}

bool Sphere::hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const {
	Vector3 temp = r.origin() - center;

	double a = dot(r.direction(), r.direction());
	double b = 2 * dot(r.direction(), temp);
	double c = dot(temp, temp) - radius * radius;

	double discriminant = b*b - 4*a*c;

	//First check to see if the ray intersect sphere
	//Discriminant has to be positive because we need to take a sqrt of it
	if(discriminant > 0) {
		discriminant = sqrt(discriminant);
		double t = (-b - discriminant) / (2 * a);

		//now check if the t is in the valid interval
		if(t < tmin) {
			t = (-b + discriminant) / (2 * a);
		}

		if(t < tmin || t > tmax) {
			return false;
		}

		//Record the valid hit
		record.t = float(t);
		record.normal = unitVector(r.origin() + float(t) * r.direction() - center);
		record.color = color;
		return true;
	}
	return false;
}

bool Sphere::shadowHit(const Ray& r, float tmin, float tmax, float time) const {
	Vector3 temp = r.origin() - center;

	double a = dot(r.direction(), r.direction());
	double b = 2 * dot(r.direction(), temp);
	double c = dot(temp, temp) - radius * radius;

	double discriminant = b*b - 4*a*c;

	//First check to see if the ray intersect sphere
	//Discriminant has to be positive because we need to take a sqrt of it
	if(discriminant > 0) {
		discriminant = sqrt(discriminant);
		double t = (-b - discriminant) / (2 * a);

		//now check if the t is in the valid interval
		if(t < tmin) {
			t = (-b + discriminant) / (2 * a);
		}

		if(t < tmin || t > tmax) {
			return false;
		}
		//The hit is valid
		return true;
	}
	return false;
}
