#pragma once

namespace math
{

class Quaternion
{
public:
	Quaternion();
	Quaternion(double,double,double,double);
	Quaternion(const Quaternion&);
	void Clear();

public:
	double E;
	double I;
	double J;
	double K;

public:
	void Set(double,double,double,double);

public:
	Quaternion& operator=(const Quaternion&);
	Quaternion operator+(Quaternion&);
	Quaternion operator-(Quaternion&);
	Quaternion operator*(Quaternion&);
	Quaternion operator/(Quaternion&);
	Quaternion operator+(double);
	Quaternion operator-(double);
	Quaternion operator*(double);
	Quaternion operator/(double);

};

} // namespace

typedef math::Quaternion QUATERNION;