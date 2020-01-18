#include <stdio.h>
#include <math.h>
#include <stdexcept>
#include "weno5.h"

double weno5(Matrix<double>& f, double eps)
{
	double I0 = f(1)*(4.0*f(1) -19.0*f(2)+11.0*f(3)) + f(2)*(25.0*f(2) -31.0*f(3)) + f(3)*(10.0*f(3));
	I0 = I0/3.0;

	double p0 = 1/3.0*f(1) -7/6.0*f(2)+11/6.0*f(3);

	double I1 = f(2)*(4.0*f(2) -13.0*f(3)+5.0*f(4)) + f(3)*(13.0*f(3) -13.0*f(4)) + f(4)*(4.0*f(4));
	I1 = I1/3.0;

	double p1 = -1/6.0*f(2)+5/6.0*f(3)+1/3.0*f(4);

	double I2 = f(3)*(10.0*f(3) -31.0*f(4)+11.0*f(5)) + f(4)*(25.0*f(4) -19.0*f(5)) + f(5)*(4.0*f(5));
	I2 = I2/3.0;

	double p2 = 1/3.0*f(3)+5/6.0*f(4) -1/6.0*f(5);

	double a0 = (I0+eps)*(I0+eps);
	a0 = 1/10.0/a0;
	double a1 = (I1+eps)*(I1+eps);
	a1 = 3/5.0/a1;
	double a2 = (I2+eps)*(I2+eps);
	a2 = 3/10.0/a2;
	double sum_a = a0 + a1 + a2;
	double w0 = a0/sum_a;
	double w1 = a1/sum_a;
	double w2 = a2/sum_a;
	double w = w0*p0 + w1*p1 + w2*p2;

	if (isnan(w)) throw std::invalid_argument("\nisnan(w)!!\n");
	return w;
}