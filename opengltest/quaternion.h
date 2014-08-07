#pragma once

class Quaternion
{
	public:
		void CreateFromAxisAngle(float x, float y, float z, float degrees);
		void CreateMatrix(float* pMatrix);
		Quaternion operator*(Quaternion &q);

private:
	float m_x;
	float m_y;
	float m_z;
	float m_w;
};