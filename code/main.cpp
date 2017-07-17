#include <iostream>
#include <cmath>
using namespace std;

#include "Bitmap.h"

//#define IM_HEIGHT 400
//#define IM_WIDTH 365	//height / 1.097177

typedef struct LabColor {
	double L;
	double a;
	double b;
};

typedef struct RGBColor {
	BYTE R;
	BYTE G;
	BYTE B;
};

void lab2RGB(LabColor &lab,RGBColor &rgb);
//lab转rgb
//L = [0,8.99144]
//a = [-13.1977,13.1989]
//b = [-12.471,12.4584]

void rgb2lab(RGBColor &rgb, LabColor &lab);
//rgb转lab

int main()
{	
	double Lvalue = 0;								//范围0-100,仅为指标，实际L范围[0,8.99144]
	int i, j;
	int height = 480;								//标记为-60,100
	int width = 420;								//标记为-60,80
	double dA = (13.1989 + 13.1977) / width;		//横轴变化量
	double dB = (12.4584 + 12.471) / height;		//纵轴变化量

	RGBColor rgb;
	LabColor lab;
	int size = height * width * 3;
	
	//设置图像基本信息
	Bitmap pic;
	pic.fileHeader.bfSize = sizeof(MYBITMAPFILEHEADER) + sizeof(MYBITMAPINFOHEADER) + size;
	pic.infoHeader.biHeight = height;
	pic.infoHeader.biWidth = width;
	if (pic.buffer != NULL) delete[]pic.buffer;
	pic.buffer = new BYTE[size];

	//导入图像数据
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			lab.L = Lvalue / 100.0 * 8.99144;
			lab.a = -13.1977 + j * dA;
			lab.b = -12.4710 + i * dB;
			lab2RGB(lab, rgb);
			pic.buffer[i * width * 3 + j * 3 + 0] = rgb.B;
			pic.buffer[i * width * 3 + j * 3 + 1] = rgb.G;
			pic.buffer[i * width * 3 + j * 3 + 2] = rgb.R;
		}
	}

	//写入文件
	FILE *output = fopen("output.bmp", "wb");
	if (!output)
	{
		cout << "Cannot open file!\n";
		exit(0);
	}

	fwrite(&pic.fileHeader, sizeof(MYBITMAPFILEHEADER), 1, output);
	fwrite(&pic.infoHeader, sizeof(MYBITMAPINFOHEADER), 1, output);
	fwrite(pic.buffer, size, 1, output);
	fclose(output);

	return 0;
}

void lab2RGB(LabColor & lab, RGBColor & rgb)
{
	double fY, fX, fZ;
	fY = (lab.L + 16) / 116.0;
	fX = lab.a / 500.0 + fY;
	fZ = fY - lab.b / 200.0;

	double Xn = 95.047, Yn = 100.0, Zn = 108.883;
	double X, Y, Z;
	if (fX > 6 / 29.0)
		X = Xn * fX * fX * fX;
	else
		X = Xn * (fX - 4 / 29.0) * 3 * 6 * 6 / 29.0 / 29.0;
	if (fY > 6 / 29.0)
		Y = Yn * fY * fY * fY;
	else
		Y = Yn * (fY - 4 / 29.0) * 3 * 6 * 6 / 29.0 / 29.0;
	if (fZ > 6 / 29.0)
		Z = Zn * fZ * fZ * fZ;
	else
		Z = Zn * (fZ - 4 / 29.0) * 3 * 6 * 6 / 29.0 / 29.0;

	double r = 3.2406 * X - 1.5372 * Y - 0.4986 * Z;
	double g = -0.9689 * X + 1.8758 * Y + 0.0415 * Z;
	double b = 0.0557 * X - 0.2040 * Y + 1.0570 * Z;

	if (r > 1) r = 1.0;
	if (r < 0) r = 0.0;
	if (g > 1) g = 1.0;
	if (g < 0) g = 0.0;
	if (b > 1) b = 1.0;
	if (b < 0) b = 0.0;

	rgb.R = (int)(r * 255 + 0.5);
	rgb.G = (int)(g * 255 + 0.5);
	rgb.B = (int)(b * 255 + 0.5);
}

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

	lab.L = 116 * (fY)-16;
	lab.a = 500 * (fX - fY);
	lab.b = 200 * (fY - fZ);
}