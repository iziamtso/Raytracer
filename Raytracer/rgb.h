//rgb.h

#ifndef _RGB_H_
#define _RGB_H_ 1

#include <iostream>

class Rgb
{
public:
	//------------
	//constructors
	//------------
	Rgb() { m_red = m_green = m_blue = 0.0; }
	Rgb(float red, float green, float blue);
	Rgb(const Rgb& original) { *this = original; } 
	Rgb(float gray) { 
		m_red = gray;
		m_green = gray;
		m_blue = gray;
	}
	//~Rgb();
	
	//-------
	//setters
	//-------
	void setRed(float red) { m_red = red; }
	void setGreen(float green) { m_green = green; }
	void setBlue(float blue) { m_blue = blue; }

	//--------------------
	//operator overloading
	//--------------------

	//Rgb with Rgb

	//----------------------------------------------------------------------------------------------------
	//Note that the argument is a reference! The reason for making the argument a reference is efficiency.
	//The code would produce the same results if the Rgb object were passed by value, but it's usually 
	//faster and more memory-efficient to just pass a reference.
	//
	//CAUTION
	//If I was to create a local variable which the sum would be assigned I will not be able to return Rgb&
	//because sum variable will be a local variable and will get destroyed right after the function terminates
	//and the address will point to nothing or non existing data.
	//----------------------------------------------------------------------------------------------------

	Rgb& operator=(const Rgb& right_op);  
	Rgb& operator+=(const Rgb& right_op);
	Rgb& operator*=(const Rgb& right_op);
	Rgb& operator/=(const Rgb& right_op);


	//Rgb with Scalars
	Rgb& operator*=(float right_op);
	Rgb& operator/=(float right_op);

	Rgb operator+()const { return *this; }  
	Rgb operator-()const { return Rgb(-m_red, -m_green, -m_blue); }

	//-------
	//Getters
	//-------
	//const there to signify that the function does not change any data (does not change any class variables)
	float r()const { return m_red; }
	float g()const { return m_green; }
	float b()const { return m_blue; }

	void clamp();

	//---------------
	//friend function
	//---------------

	//NOTE
	//There are there different categories of friend functions
	//
	// 1. Friend functions
	// 2. Friend classes
	// 3. Friend member functions
	// What essentially friend function is a function that is not a member (for case one at least) but it can access private members 

	//This is a very common friend function because when you call this object the first object of the two will be count then object I 
	//want to print but cannot do nicely vice versa object and then count
	friend std::ostream& operator<<(std::ostream& out, const Rgb& the_rgb);

	//Multiply on Rgb on scalar
	friend Rgb operator*(const Rgb& c, float f);
	friend Rgb operator*(float f, const Rgb& c);

	//Divide by scalar
	friend Rgb operator/(const Rgb& c , float f);

	//Multiply, Add, Divide Rgb vs Rgb
	friend Rgb operator*(const Rgb& c1, const Rgb& c2);
	friend Rgb operator/(const Rgb& c1, const Rgb& c2);
	friend Rgb operator+(const Rgb& c1, const Rgb& c2);

	float m_red;
	float m_green;
	float m_blue;
};

//inline qualifier in front of the function attempts to optimize the
// the function call. It may be more efficient to simply insert 
// the code of the function where it is called


// Def of the constructor
inline Rgb::Rgb(float red, float green, float blue): m_red(red), m_green(green), m_blue(blue) {}

//Shortcut operator definitions object on object
inline Rgb& Rgb::operator+=(const Rgb& right_op){
	*this = *this + right_op;
	return *this;
}

inline Rgb& Rgb::operator*=(const Rgb& right_op){
	*this = *this * right_op;
	return *this;
}

inline Rgb& Rgb::operator/=(const Rgb& right_op){
	*this = *this / right_op;
	return *this;
}

//Operator definitions object on scalar
//NOTE
//This is a good case when the friend function would be very handy
//because I can do object * scalar with the function below but I cannot do 
//scalar * object because scalar cannot call functions so to solution is FRIEND functions

inline Rgb& Rgb::operator*=(float right_op) {
	*this = *this * right_op;
	return *this;
}

inline Rgb& Rgb::operator/=(float right_op) {
	*this = *this / right_op;
	return *this;
}

//Equal operator def.
//Can only be a member function to overload the operator including others (), [], -> ONLY member functions can overload them
inline Rgb& Rgb::operator=(const Rgb& right_op) {
	m_red = right_op.m_red;
	m_green = right_op.m_green;
	m_blue = right_op.m_blue;
	return *this;
}

//Clamp function
inline void Rgb::clamp() {
	if(m_red > 1.0f) { m_red = 1.0f; }
	if(m_green > 1.0f) { m_green = 1.0f; }
	if(m_blue > 1.0f) { m_blue = 1.0f; }

	if(m_red < 0.0f) { m_red = 0.0f; }
	if(m_green < 0.0f) { m_green = 0.0f; }
	if(m_blue < 0.0f) { m_blue = 0.0f; }
}

//Print method

//The same function easier coded less functionality
//void operator<<(ostream& os, const Rgb& object)
//{
//	os<<objet.GetRed() << ' ' << object.GetGreen() << ' ' << object.GetBlue();
//}

//NOTE
//The call cout << Rgb shoud use the cout object itself, not a copy, so the function passes the object as a reference instead of by value.
//For the Rgb object it really does not matter if passed by value or by reference but passing by reference is faster
//
//The return type has to be reference to the ostream& so you stack multiple cout on top of each other
//Ex. cout<< "This is my class: " << Rgb ; 

inline std::ostream& operator<< ( std::ostream& out, const Rgb& rgb_object ) {
	out << rgb_object.r() << ' ' << rgb_object.g() << ' ' << rgb_object.b() << ' ' << std::endl;
	return out;
}


inline Rgb operator*(const Rgb& color, float value) {
	return Rgb(color.r() * value, color.g() * value, color.b() * value);
}

inline Rgb operator*(float value, const Rgb& color ) {
	return Rgb(color.r() * value, color.g() * value, color.b() * value);
}

inline Rgb operator/(const Rgb& color, float value) {
	return Rgb(color.r() / value, color.g() / value, color.b() / value);
}

inline Rgb operator*(const Rgb& color, const Rgb& color2) {
	return Rgb(color.r() * color2.r(),  color.g() * color2.g(), color.b() * color2.b());
}

inline Rgb operator/(const Rgb& color, const Rgb& color2) {
	return Rgb(color.r() / color2.r(),  color.g() / color2.g(), color.b() / color2.b());
}

inline Rgb operator+(const Rgb& color, const Rgb& color2) {
	return Rgb(color.r() + color2.r(),  color.g() + color2.g(), color.b() + color2.b());
}

#endif

