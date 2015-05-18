#include "Vector3.h"


istream& operator>>(istream& is, Vector3& v1) {
	float temp;
	is >> temp;
	v1.SetX(temp);
	
	is >> temp;
	v1.SetY(temp);

	is >> temp;
	v1.SetZ(temp);

	return is;
}

ostream& operator<<(ostream& os, const Vector3& v1) {
	os << '(' << v1.x() << ' ' << v1.y() << ' ' << v1.z() << ')';
	return os;
}

float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	return dot((cross(v1, v2)), v3);
}


