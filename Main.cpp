#include <iostream>
#include <math.h>
using namespace std;
#define SQRT_2 1.4142135623731
#define HALFPI 1.5707963267949

typedef union{
	double fp;
	unsigned long long ll; //32+32
} hack_structure;

double getSquareRoot(double);
double getSquareRoot(unsigned long);
double getSine(double);
double getCosine(double);
double getDifferentiation(double);
double getIntegration(double, double);
double menuDifferentiation();
double menuIntegration();

double(*fp)(double) = NULL;

double s1 = 1.0 / (2.0*3.0);
double s2 = 1.0 / (4.0*5.0);
double s3 = 1.0 / (6.0*7.0);
double s4 = 1.0 / (8.0*9.0);
double c1 = 1.0 / (1.0*2.0);
double c2 = 1.0 / (3.0*4.0);
double c3 = 1.0 / (5.0*6.0);
double c4 = 1.0 / (7.0*8.0);

int main()
{
	int op;
	double number=0;

	do
	{
		cout << "1: square root (double type)" << endl
			<< "2: square root (unsigned long type)" << endl
			<< "3: sine (double type)" << endl
			<< "4: cosine (double type)" << endl
			<< "5: differentiation (of double type function)" << endl
			<< "6: integration (of double type function)" << endl
			<< "0: quit" << endl;

		cin >> op;

		if (op != 0 && op != 5 && op != 6)
		{
			cout << "input a number: " << endl;
			cin >> number;
		}

		switch (op)
		{
		case 1: cout << getSquareRoot(number) << endl;
			break;
		case 2: cout << getSquareRoot((unsigned long)number) << endl;
			break;
		case 3: cout << getSine(number) << endl;
			break;
		case 4: cout << getCosine(number) << endl;
			break;
		case 5: cout << menuDifferentiation() << endl;
			break;
		case 6: cout << menuIntegration() << endl;
			break;
		case 0: cout << "프로그램을 종료합니다." << endl;
		default: break;
		}
		cout << endl;
	} while (op!=0);

	return 0;
}

double getSquareRoot(double num)
{
	hack_structure xx;
	short expo;	//num의 지수부분
	char odd = 0; //flag
	double tmp;
	xx.fp = num;
	expo = (short)(xx.ll >> 52);
	expo -= 0x3ff;

	xx.ll &= 0x000fffffffffffff;
	xx.ll += 0x3ff0000000000000;

	if (num <= 0.0)
		return num;
	tmp = xx.fp;
	//The initial guess is y=0.4x+0.6
	xx.fp = (0.4*xx.fp) + 0.6;

	for (size_t i = 0; i < 10; i++)
		xx.fp = 0.5*((tmp / xx.fp) + xx.fp);

	if (expo & 1)
	{
		++expo;
		odd = 1;
	}

	expo /= 2;
	expo += 0x3ff;
	xx.ll &= 0x000fffffffffffff;
	xx.ll += ((unsigned long long)expo << 52);

	if (odd)
		return xx.fp / SQRT_2;
	else
		return xx.fp;
}
double getSquareRoot(unsigned long num)
{
	if ((num == 0) || (num==1))
		return num;

	unsigned long aa = num;
	unsigned long high = 1;
	unsigned long low = 1;
	unsigned long mid;
	short shift = 31;

	while (!((aa >> shift)&1))
		shift--;

	high <<= shift;
	while (high - low > 1)
	{
		mid = (high + low) / 2;
		if (mid*mid <= aa)
			low = mid;
		else
			high = mid;
	}

	return low;
}
double getSine(double num)
{
	long n = (long)(num / HALFPI + 0.5);
	double x;
	
	x = num - n*HALFPI;
	n &= 0x3;
	double z = x*x;

	switch (n)
	{
	case 0:
		return ((((s4*z-1.0)*s3*z+1.0)*s2*z-1.0)*s1*z+1.0)*x;
	case 1:
		return (((c4*z-1.0)*c3*z+1.0)*c2*z-1.0)*c1*z+1.0;
	case 2:
		return -((((s4*z - 1.0)*s3*z + 1.0)*s2*z - 1.0)*s1*z + 1.0)*x;
	case 3:
		return -(((c4*z - 1.0)*c3*z + 1.0)*c2*z - 1.0)*c1*z + 1.0;;
		break;
	}
}
double getCosine(double num)
{
	long n = (long)(num / HALFPI + 0.5);
	double x;

	x = num - n*HALFPI;
	n &= 0x3;
	double z = x*x;

	switch (n+1)
	{
	case 4:
		return ((((s4*z - 1.0)*s3*z + 1.0)*s2*z - 1.0)*s1*z + 1.0)*x;
	case 1:
		return (((c4*z - 1.0)*c3*z + 1.0)*c2*z - 1.0)*c1*z + 1.0;
	case 2:
		return -((((s4*z - 1.0)*s3*z + 1.0)*s2*z - 1.0)*s1*z + 1.0)*x;
	case 3:
		return -(((c4*z - 1.0)*c3*z + 1.0)*c2*z - 1.0)*c1*z + 1.0;;
		break;
	}
}
double menuDifferentiation()
{
	int op1;
	double number;
	do
	{
		cout << "1: differentiate sine (double type)" << endl
			<< "2: differentiate cosine (double type)" << endl
			<< "3: differentiate tangent (double type)" << endl;

		cin >> op1;

		if (op1 == 1 || op1 == 2 || op1 == 3)
		{
			cout << "input a number: " << endl;
			cin >> number;
		}

		switch (op1)
		{
		case 1: fp = sin;	//math.h sin
			break;
		case 2: fp = cos;	//math.h cos
			break;
		case 3: fp = tan;	//math.h tan
			break;
		default: break;
		}

	} while ((op1 != 1) && (op1 != 2) && (op1 != 3));
	return getDifferentiation(number);
	
}
double menuIntegration()
{
	int op2;
	double number1, number2;
	do
	{
		cout << "1: intergrate sine (double type)" << endl
			<< "2: intergrate cosine (double type)" << endl
			<< "3: intergrate tangent (double type)" << endl;

		cin >> op2;
		
		if (op2 == 1 || op2 == 2 || op2 == 3)
		{
			cout << "input a number: A to B" << endl;
			cout << "A: ";
			cin >> number1;
			cout << "B: ";
			cin >> number2;
		}

		switch (op2)
		{
		case 1: fp = sin;	//math.h sin
			break;
		case 2: fp = cos;	//math.h cos;
			break;
		case 3: fp = tan;	//math.h tan
			break;
		default: break;
		}
	} while ((op2 != 1) && (op2 != 2) && (op2 != 3));
	return getIntegration(number1, number2);
}

double getDifferentiation(double num)
{
	//set interval 0.001
	double h = 0.001;
	double f0, f1, f2;
	f0 = fp(num);
	f1 = fp(num + h);
	f2 = fp(num + 2*h);

	return (-f2 + 4 * f1 - 3 * f0) / (2 * h);
}

double getIntegration(double num1, double num2)
{
	double h = (num2 - num1) / 2;
	double f0, f1, f2;
	f0 = fp(num1);
	f1 = fp(num1 + h);
	f2 = fp(num2);

	return (h/3) * (f0 + 4 * f1 + f2);
}