#include "PcHeader.h"

#include "Trace.h"
#include "TraceMath.h"
#include "SystemTrace.h"

#include "Quaternion.h"
#include "QuaternionTool.h"

namespace math
{

Quaternion::Quaternion()
{
	Clear();
}

Quaternion::Quaternion(double p_E, double p_I, double p_J, double p_K)
{
	Set(p_E,p_I,p_J,p_K);
}

Quaternion::Quaternion(const Quaternion& p_gr)
{
	(*this) = p_gr;
}

void Quaternion::Clear()
{
	Set(0,0,0,0);
}

void Quaternion::Set(double p_E, double p_I, double p_J, double p_K)
{
	E = p_E;
	I = p_I;
	J = p_J;
	K = p_K;
}

Quaternion& Quaternion::operator=(const Quaternion& p_gr)
{
	Set(p_gr.E,p_gr.I,p_gr.J,p_gr.K);
	return (*this);
}

Quaternion Quaternion::operator+(Quaternion& p_gr)
{
	Quaternion qRes;
	qRes.Set(E+p_gr.E,I+p_gr.I,J+p_gr.J,K+p_gr.K);
	return qRes;
}

Quaternion Quaternion::operator-(Quaternion& p_gr)
{
	Quaternion qRes;
	qRes.Set(E-p_gr.E,I-p_gr.I,J-p_gr.J,K-p_gr.K);
	return qRes;
}

Quaternion Quaternion::operator*(Quaternion& p_gr)
{
	Quaternion qRes;

	qRes.E	= E*p_gr.E - I*p_gr.I - J*p_gr.J - K*p_gr.K;
	qRes.I	= E*p_gr.I + I*p_gr.E + J*p_gr.K - K*p_gr.J;
	qRes.J	= E*p_gr.J - I*p_gr.K + J*p_gr.E + K*p_gr.I;
	qRes.K	= E*p_gr.K + I*p_gr.J - J*p_gr.I + K*p_gr.E;

	return qRes;
}

Quaternion Quaternion::operator/(Quaternion& p_gr)
{
	Quaternion qRes;

	qRes = (*this) * Inverse(p_gr);

	return qRes;
}

Quaternion Quaternion::operator+(double p_d)
{
	Quaternion qRes;

	qRes	= (*this);
	qRes.E	+= p_d;

	return qRes;
}

Quaternion Quaternion::operator-(double p_d)
{
	Quaternion qRes;

	qRes	= (*this);
	qRes.E	-= p_d;

	return qRes;
}

Quaternion Quaternion::operator*(double p_d)
{
	Quaternion qRes;

	qRes.Set(E*p_d,I*p_d,J*p_d,K*p_d);

	return qRes;
}

Quaternion Quaternion::operator/(double p_d)
{
	Quaternion qRes;

	double d = 1.0/p_d;
	qRes.Set(E*d,I*d,J*d,K*d);

	return qRes;
}

}// namespace