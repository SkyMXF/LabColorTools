#include <iostream>
#include <math.h>
using namespace std;

#include "Bitmap.h"

typedef struct LabColor {
	double L;
	double a;
	double b;
};

typedef struct RGBColor {
	int R;
	int G;
	int B;
};

/*
void rgb2lab(RGBColor &rgb, LabColor &lab)
{
	double r = rgb.R / 255.0;
	double g = rgb.G / 255.0;
	double b = rgb.B / 255.0;

	double X = r * 0.4124 + g * 0.3576 + b * 0.1805;
	double Y = r * 0.2126 + g * 0.7152 + b * 0.0722;
	double Z = r * 0.0193 + g * 0.1192 + b * 0.9505;

	double Xn = 95.047, Yn = 100.0, Zn = 108.883;

	double fX, fY, fZ;

	if (X / Xn > pow(6 / 29.0, 3))
		fX = pow(X / Xn, 1 / 3.0);
	else
		fX = 1 / 3.0 * 29 * 29 / 6.0 / 6.0*X / Xn + 4 / 29.0;
	if (Y / Yn > pow(6 / 29.0, 3))
		fY = pow(Y / Yn, 1 / 3.0);
	else
		fY = 1 / 3.0 * 29 * 29 / 6.0 / 6.0*Y / Yn + 4 / 29.0;
	if (Z / Zn > pow(6 / 29.0, 3))
		fZ = pow(Z / Zn, 1 / 3.0);
	else
		fZ = 1 / 3.0 * 29 * 29 / 6.0 / 6.0*Z / Zn + 4 / 29.0;

	lab.L = 116 * (fY) - 16;
	lab.a = 500 * (fX - fY);
	lab.b = 200 * (fY - fZ);
}


int main()
{
	double minL = 1000, mina = 1000, minb = 1000;
	double maxL = -1000, maxa = -1000, maxb = -1000;
	RGBColor testRGB;
	LabColor testLab;
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 256; k++)
			{
				testRGB.R = i;
				testRGB.G = j;
				testRGB.B = k;
				rgb2lab(testRGB, testLab);
				if (minL > testLab.L) minL = testLab.L;
				if (mina > testLab.a) mina = testLab.a;
				if (minb > testLab.b) minb = testLab.b;
				if (maxL < testLab.L) maxL = testLab.L;
				if (maxa < testLab.a) maxa = testLab.a;
				if (maxb < testLab.b) maxb = testLab.b;
			}
		}
	}

	cout << minL << "\t" << mina << "\t" << minb << endl;
	cout << maxL << "\t" << maxa << "\t" << maxb << endl;

	system("pause");
	return 0;
}*/