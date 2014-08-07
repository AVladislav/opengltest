#include "stdafx.h"
#include "camera.h"

Camera::Camera() : x(0), z(0), m_cx(0), m_cy(0), pitch(0), heading(0)
{
//	SetCursorPos();
}

void Camera::SetCenter( int x, int y )
{
	m_cx = x;
	m_cy = y;
	SetCursorPos(m_cx, m_cy);
}

void Camera::CheckMouse()
{
	POINT point;
	GetCursorPos(&point);
	float diffX, diffY;

	diffX = m_cx - point.x;
	heading -= 0.1*diffX;

	diffY = m_cy - point.y;
	pitch -= 0.1*diffY;


	if(point.x != m_cx || point.y != m_cy)
		SetCursorPos(m_cx, m_cy);
}
