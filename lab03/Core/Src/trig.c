#include "trig.h"
#include "math.h"


short custom_sin(short y)
{
	static short s1 = 0x6488;
	static short s3 = 0x2958;
	static short s5 = 0x51a;
	static short s7 = 0x4d;

	long z, prod, sum, result;

	z = ((long)y * y) >> 12;
	prod = (z * s7) >> 16;
	sum = s5 - prod;
	prod = (z * sum) >> 16;
	sum = s3 - prod;
	prod = (z * sum) >> 16;
	sum = s1 - prod;

	result = (short)((y * sum) >> 13);
	return result;
}

double regular_sin(double x)
{
	return sin(x);
}

short custom_cos(short y)
{
	static short c0 = 0x7fff;
	static short c2 = 0x4ef5;
	static short c4 = 0x103e;
	static short c6 = 0x156;
	long z, prod, sum;
	short result;

	z = ((long)y * y) >> 12;
	prod = (z * c6) >> 16;
	sum = c4 - prod;
	prod = (z * sum) >> 16;
	sum = c2 - prod;

	prod = (z * sum) >> 15;

	result = (short)(c0 - prod);
	return result;
}

double regular_cos(double x)
{
	return cos(x);
}
