#pragma once

struct Point3D
{
	Point3D(float X, float Y, float Z):x(X), y(Y), z(Z){}
	float x, y, z;
};

struct Triangle
{
	Triangle(Point3D P1, Point3D P2, Point3D P3):p1(P1),p2(P2),p3(P3){}
	Point3D p1, p2, p3;
};
