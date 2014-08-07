#include "stdafx.h"
#include "quaternion.h"
#include <math.h>

#define PI 3.14159265358979323846

void Quaternion::CreateFromAxisAngle( float x, float y, float z, float degrees )
{
	float angle = float((degrees / 180.0f) * PI);
	
	float result = (float)sin( angle / 2.0f );
	
	m_w = (float)cos( angle / 2.0f );

	m_x = float(x * result);
	m_y = float(y * result);
	m_z = float(z * result);
}

void Quaternion::CreateMatrix( float* pMatrix )
{
	if(!pMatrix) return;

	pMatrix[ 0] = 1.0f - 2.0f * ( m_y * m_y + m_z * m_z );
	pMatrix[ 1] = 2.0f * (m_x * m_y + m_z * m_w);
	pMatrix[ 2] = 2.0f * (m_x * m_z - m_y * m_w);
	pMatrix[ 3] = 0.0f;

	pMatrix[ 4] = 2.0f * ( m_x * m_y - m_z * m_w );
	pMatrix[ 5] = 1.0f - 2.0f * ( m_x * m_x + m_z * m_z );
	pMatrix[ 6] = 2.0f * (m_z * m_y + m_x * m_w );
	pMatrix[ 7] = 0.0f;

	pMatrix[ 8] = 2.0f * ( m_x * m_z + m_y * m_w );
	pMatrix[ 9] = 2.0f * ( m_y * m_z - m_x * m_w );
	pMatrix[10] = 1.0f - 2.0f * ( m_x * m_x + m_y * m_y );
	pMatrix[11] = 0.0f;

	pMatrix[12] = 0;
	pMatrix[13] = 0;
	pMatrix[14] = 0;
	pMatrix[15] = 1.0f;
}

Quaternion Quaternion::operator*( Quaternion &q )
{
	Quaternion r;

	r.m_w = m_w*q.m_w - m_x*q.m_x - m_y*q.m_y - m_z*q.m_z;
	r.m_x = m_w*q.m_x + m_x*q.m_w + m_y*q.m_z - m_z*q.m_y;
	r.m_y = m_w*q.m_y + m_y*q.m_w + m_z*q.m_x - m_x*q.m_z;
	r.m_z = m_w*q.m_z + m_z*q.m_w + m_x*q.m_y - m_y*q.m_x;
	return(r);
}
