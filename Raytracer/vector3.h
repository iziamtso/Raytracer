#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;

class Vector3
{

public:

	Vector3(){};
	Vector3(float, float, float);

	Vector3(const Vector3& v) { *this = v; }
	//----------------
	//Getters
	//----------------
	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }
	//----------------
	//Getters End
	//----------------
	const Vector3& operator+() const; //?
	Vector3 operator-() const; //?

	float operator[](int i) const { return e[i]; } //?
	float& operator[](int i) { return e[i]; } //?

	float length() const;
	float squaredLength() const;
	void makeUnitVector();
	//----------------
	//Setters 
	//----------------
	void SetX(float m_x) { e[0] = m_x; }
	void SetY(float m_y) { e[1] = m_y; }
	void SetZ(float m_z) { e[2] = m_z; }
	//----------------
	//Setters END
	//----------------
	float minComponent() const;
	float maxComponent() const;

	float maxAbsComponent() const;
	float minAbsComponent() const;

	int indexOfMinComponent() const;
	int indexOfMinAbsComponent() const;
	int indexOfMaxComponent() const;
	int indexOfAbsMaxComponent() const;

	//Friends
	friend bool operator==(const Vector3& v1, const Vector3& v2);
	friend bool operator!=(const Vector3& v1, const Vector3& v2);

	friend istream& operator>>(istream& is, Vector3& v1); //?
	friend ostream& operator<<(ostream& os, const Vector3& v1);

	friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator/(const Vector3& v1, float scalar);

	friend Vector3 operator*(const Vector3& v1, float scalar);
	friend Vector3 operator*( float scalar, const Vector3& v1);


	Vector3& operator=(const Vector3& v2);
	Vector3& operator+=(const Vector3& v2);
	Vector3& operator-=(const Vector3& v2);
	Vector3& operator*=(const float scalar);
	Vector3& operator/=(const float scalar);


	//More friends
	friend Vector3 unitVector(const Vector3& v1);
	friend Vector3 minVec(const Vector3& v1, const Vector3& v2);
	friend Vector3 maxVec(const Vector3& v1, const Vector3& v2);

	friend Vector3 cross(const Vector3& v1, const Vector3& v2);
	friend float dot(const Vector3& v1, const Vector3& v2);

	friend float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	float e[3];
}; 


inline Vector3::Vector3(float n0, float n1, float n2) {
	e[0] = n0;
	e[1] = n1;
	e[2] = n2;
}

inline const Vector3& Vector3::operator+() const {
	return *this; 
}

inline Vector3 Vector3::operator-() const {
	return Vector3( -e[0], -e[1], -e[2]);
}

inline float Vector3::length() const {
	return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}

inline float Vector3::squaredLength() const {
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

inline void Vector3::makeUnitVector() {
	*this = *this / (*this).length();
}

inline float Vector3::minComponent() const {
	float temp = e[0];

	if(e[1] < temp) { temp = e[1]; }
	if(e[2] < temp) { temp = e[2]; }
	return temp;
}


inline float Vector3::maxComponent() const {
	float temp = e[0];
	if(e[1] > temp) {
		temp = e[1];
	}

	if(e[2] > temp) {
		temp = e[2];
	}
	return temp;
}

inline float Vector3::maxAbsComponent() const {
	//fabs is absolute function of double
	float temp = fabs(e[0]);

	if(fabs(e[1]) > temp) {
		temp = fabs(e[1]);
	}

	if(fabs(e[2]) > temp) {
		temp = fabs(e[2]);
	}
	return temp;
}


inline float Vector3::minAbsComponent() const {
	//fabs is absolute function of double
	float temp = fabs(e[0]);

	if(fabs(e[1]) < temp) {
		temp = fabs(e[1]);
	}

	if(fabs(e[2]) < temp) {
		temp = fabs(e[2]);
	}
	return temp;
}


inline int Vector3::indexOfMinComponent() const {
	float temp = e[0];
	int index = 0;

	if(e[1] < temp) {
		temp = e[1];
		index = 1;
	}

	if(e[2] < temp) {
		index = 2;
	}
	return index;
}


inline int Vector3::indexOfMinAbsComponent() const {
	float temp = fabs(e[0]);
	int index = 0;

	if(fabs(e[1]) < temp) {
		temp = fabs(e[1]);
		index = 1;
	}

	if(fabs(e[2]) < temp) {
		index = 2;
	}
	return index;
}

inline bool operator==(const Vector3& v1, const Vector3& v2) {
	if(v1.e[0] != v2.e[0]) {
		return false;
	}

	if(v1.e[1] != v2.e[1]) {
		return false;
	}

	if(v1.e[2] != v2.e[2]) {
		return false;
	}
	return true;
}

inline bool operator!=(const Vector3& v1, const Vector3& v2) {
	return !(v1 == v2);
}


inline int Vector3::indexOfMaxComponent() const {
	float temp = e[0];
	int index = 0;

	if(e[1] > temp) {
		temp = e[1];
		index = 1;
	}

	if(e[2] > temp) {
		index = 2;
	}
	return index;
}


inline int Vector3::indexOfAbsMaxComponent() const {
	float temp = fabs(e[0]);
	int index = 0;

	if(fabs(e[1]) > temp) {
		temp = fabs(e[1]);
		index = 1;
	}

	if(fabs(e[2]) > temp) {
		index = 2;
	}
	return index;
}

//-------------------------------------------------------
//Multiplication of object on scalar and scalar on object
//-------------------------------------------------------
inline Vector3 operator*(float scalar, const Vector3& v1) {
	return Vector3(v1.x() * scalar, v1.y() * scalar, v1.z() * scalar);
}

inline Vector3 operator*(const Vector3& v1, float scalar) {
	return Vector3(v1.x() * scalar, v1.y() * scalar, v1.z() * scalar);
}

//------------------------------------------------------------
//Multiplication of object on scalar and scalar on object end
//-----------------------------------------------------------

inline Vector3 operator/(const Vector3& v1, float scalar) {
	return Vector3(v1.x() / scalar, v1.y() / scalar, v1.z() / scalar);
}

inline Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}


inline Vector3& Vector3::operator+=(const Vector3& v1) {
	*this = *this + v1;
	return *this;
}

//QUESTION 
//HOW THIS WORKS WITHOUT THE RETURN OR VOID RETURN

inline Vector3& Vector3::operator=(const Vector3& v1) {
	e[0] = v1.x();
	e[1] = v1.y();
	e[2] = v1.z();

	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& v1) {
	*this = *this - v1;
	return *this;
}


inline Vector3& Vector3::operator*=(float scalar) {
	*this = *this * scalar;
	return *this;
}

inline Vector3& Vector3::operator/=(float scalar) {
	*this = *this / scalar;
	return *this;
}

inline float dot(const Vector3& v1, const Vector3& v2) {
	float dot = v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
	return dot;
}

inline Vector3 cross(const Vector3& v1, const Vector3& v2) {
	Vector3 temp;

	temp.SetX(v1.y() * v2.z() - v1.z() * v2.y());
	temp.SetY(v1.z() * v2.x() - v1.x() * v2.z());
	temp.SetZ(v1.x() * v2.y() - v1.y() * v2.x());

	return temp;
}

inline Vector3 unitVector(const Vector3& v1) {
	float length = v1.length();
	return v1 / length;
}

inline Vector3 minVec(const Vector3& v1, const Vector3& v2) {
	Vector3 vec(v1);

	if(v1.x() > v2.x()) {
		vec.SetX(v2.x());
	}

	if(v1.y() > v2.y()) {
		vec.SetY(v2.y());
	}

	if(v1.z() > v2.z()){
		vec.SetZ(v2.z());
	}
	return vec;
}


inline Vector3 maxVec(const Vector3& v1, const Vector3& v2) {
	Vector3 vec(v1);

	if(v1.x() < v2.x()) {
		vec.SetX(v2.x());
	}

	if(v1.y() < v2.y()) {
		vec.SetY(v2.y());
	}

	if(v1.z() < v2.z()) {
		vec.SetZ(v2.z());
	}
	return vec;
}



#endif