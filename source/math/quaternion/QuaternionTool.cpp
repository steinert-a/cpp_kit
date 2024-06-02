#include "PcHeader.h"
#include "Trace.h"
#include "TraceMath.h"
#include "SystemTrace.h"

#include "Quaternion.h"
#include "QuaternionTool.h"

namespace math
{

double Norm(Quaternion& p_gr)
{
	double d = 0;

	d += p_gr.E*p_gr.E;
	d += p_gr.I*p_gr.I;
	d += p_gr.J*p_gr.J;
	d += p_gr.K*p_gr.K;

	return d;
}

double Abs(Quaternion& p_gr)
{
	return sqrt(Norm(p_gr));
}


Quaternion Konjugate(Quaternion& p_gr)
{
	Quaternion qRes;
	qRes.Set(p_gr.E,-p_gr.I,-p_gr.J,-p_gr.K);
	return qRes;
}

Quaternion Inverse(Quaternion& p_gr)
{ // both side inverse
	Quaternion qRes;

	double dNorm = Norm(p_gr);
	if(dNorm > MATH_ERROR)
	{
		qRes = Konjugate(p_gr) * (1.0/dNorm);
	}

	return qRes;
}

} // namespace