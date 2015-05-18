//#include "stdafx.h"
#include "Triangle.h"


Triangle::Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, const Rgb& _color)
	: p0(_p0), p1(_p1), p2(_p2), color(_color) {}


bool Triangle::hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const {
	// formula: o + td = a + beta(b-a) + gamma(c-a)

	//a-b
	float A = p0.x() - p1.x();
	float B = p0.y() - p1.y();
	float C = p0.z() - p1.z();

	//a-c
	float D = p0.x() - p2.x();
	float E = p0.y() - p2.y();
	float F = p0.z() - p2.z();

	//d (direction of ray)
	float G = r.direction().x();
	float H = r.direction().y();
	float I = r.direction().z();

	//a-o
	float J = p0.x() - r.origin().x();
	float K = p0.y() - r.origin().y();
	float L = p0.z() - r.origin().z();

	//Finding the determinant of A or |A|
	float EIHF = E*I - F*H;
	float GFDI = G*F - D*I; //Note the reverse order it is done to change the sign
	float DHEG = D*H - E*G;
	//Determinant of A or |A|
	float denom = (A*EIHF + B*GFDI + C*DHEG); //|A|

	//Finding BETA
	float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
	if(beta <= 0.0f || beta >= 1.0f) {
		return false;		//From barycentric coordinates alpha + beta + gamma = 1.0
	}

	//Finding GAMMA
	float AKBJ = A*K - B*J;
	float JCAL = J*C - A*L;
	float BLCK = B*K - C*K;

	float gamma = (I*AKBJ + H*JCAL + G*BLCK) / denom;
	if(gamma <= 0.0f || (beta + gamma) >= 1.0f) {
		return false;		//From barycentric coordinates alpha + beta + gamma = 1.0
	}

	//Finding t
	float tval = -(F*AKBJ + E*JCAL + D*BLCK) / denom;
	if(tval >= tmin && tval <= tmax) {
		record.t = tval;
		record.normal = unitVector(cross((p1 - p0), (p2 - p0)));
		record.color = color;
		return true;
	}
	return false;
}

bool Triangle::shadowHit(const Ray& r, float tmin, float tmax, float time) const {
	// formula: o + td = a + beta(b-a) + gamma(c-a)

	//a-b
	float A = p0.x() - p1.x();
	float B = p0.y() - p1.y();
	float C = p0.z() - p1.z();

	//a-c
	float D = p0.x() - p2.x();
	float E = p0.y() - p2.y();
	float F = p0.z() - p2.z();

	//d (direction of ray)
	float G = r.direction().x();
	float H = r.direction().y();
	float I = r.direction().z();

	//a-o
	float J = p0.x() - r.origin().x();
	float K = p0.y() - r.origin().y();
	float L = p0.z() - r.origin().z();

	//Finding the determinant of A or |A|
	float EIHF = E*I - F*H;
	float GFDI = G*F - D*I; //Note the reverse order it is done to change the sign
	float DHEG = D*H - E*G;
	//Determinant of A or |A|
	float denom = (A*EIHF + B*GFDI + C*DHEG); //|A|

	//Finding BETA
	float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
	if(beta <= 0.0f || beta >= 1.0f) {
		return false;		//From barycentric coordinates alpha + beta + gamma = 1.0
	}

	//Finding GAMMA
	float AKBJ = A*K - B*J;
	float JCAL = J*C - A*L;
	float BLCK = B*K - C*K;

	float gamma = (I*AKBJ + H*JCAL + G*BLCK) / denom;
	if(gamma <= 0.0f || (beta + gamma) >= 1.0f) {
		return false;		//From barycentric coordinates alpha + beta + gamma = 1.0
	}

	//Finding t
	float tval = -(F*AKBJ + E*JCAL + D*BLCK) / denom;

	return (tval >= tmin && tval <= tmax);
}



Triangle::~Triangle(void)
{
}
