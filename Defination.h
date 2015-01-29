#ifndef DEFINATION_H_
#define DEFINATION_H_

#include <cmath>
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const double EPS = 0.000001;
const double INF = 1000000000.0;
const double PI = 3.141592653;

const int SAMPLE_PER_PIXEL = 10;

// 定义向量
struct Vector
{
    double x, y, z;
    Vector(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}
    double operator* (const Vector &v) {return x * v.x + y * v.y + z * v.z;}
	Vector operator* (double s) {return Vector(x * s, y * s, z * s);}
	Vector operator^ (const Vector &v) {return Vector(x * v.x, y * v.y, z * v.z);} // for multiple of color
	Vector operator/ (double s) {return Vector(x / s, y / s, z / s);}
	Vector operator+ (const Vector &v) {return Vector(x + v.x, y + v.y, z + v.z);}
	Vector operator- (const Vector &v) {return Vector(x - v.x, y - v.y, z - v.z);}
    void operator*= (double s) {x *= s; y *= s; z *= s;}
	void operator/= (double s) {x /= s; y /= s; z /= s;}
    void operator+= (const Vector &v) {x += v.x; y += v.y; z += v.z;}
	void operator-= (const Vector &v) {x -= v.x; y -= v.y; z -= v.z;}
    Vector& normalize() {double m = module(); x /= m; y /= m; z /= m; return *this;}
    double module() {return sqrt(x * x + y * y + z * z);}

	friend istream& operator >> (istream &in, Vector &obj){
		in >> obj.x >> obj.y >> obj.z;
		return in;
	}
	friend ostream& operator << (ostream &out, const Vector &obj){
		out << obj.x << " " << obj.y << " " << obj.z;
		return out;
	}
};

// 定义顶点
typedef Vector Vertex;

// 定义颜色
typedef Vector Color;
const Color BLACK = Color(0.0, 0.0, 0.0);
const Color WHITE = Color(1.0, 1.0, 1.0);
const Color RED = Color(1.0, 0.0, 0.0);
const Color AMBIENT = Color(0.3, 0.3, 0.3);

// 角度转弧度
inline double DegToRad(double deg)
{
	return deg / 180.0 * PI;
}

// 弧度转角度
inline double RadToDeg(double rad)
{
	return rad / PI * 180.0;
}

// 求行列式
inline double Det(Vector v1, Vector v2, Vector v3)
{
	return v1.x * v2.y * v3.z + v2.x * v3.y * v1.z + v3.x * v1.y * v2.z - v3.x * v2.y * v1.z - v2.x * v1.y * v3.z - v1.x * v3.y * v2.z;
}

// 求叉积
inline Vector Cross(Vector v1, Vector v2)
{
	return Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

// 求三角形面积
inline double Area(Vector v1, Vector v2)
{
	return 0.5 * sqrt((v1.y * v2.z - v1.z * v2.y) * (v1.y * v2.z - v1.z * v2.y) + (v1.z * v2.x - v1.x * v2.z) * (v1.z * v2.x - v1.x * v2.z) + (v1.x * v2.y - v1.y * v2.x) * (v1.x * v2.y - v1.y * v2.x));
}

// 求夹角
inline double CosTheta(Vector v1, Vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / v1.module() / v2.module();
}

// 浮点数的相等
inline bool DoubleEqual(double a, double b)
{
	return b > a - EPS && b < a + EPS;
}

// 浮点数的SGN函数
inline int Sign(double a)
{
	if (a > EPS)
		return 1;
	else if (a < -EPS)
		return -1;
	return 0;
}

inline float max(float a, float b)
{
	return a > b ? a : b;
}

inline float min(float a, float b)
{
	return a > b ? b : a;
}

#endif