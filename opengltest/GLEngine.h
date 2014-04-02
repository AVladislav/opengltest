#pragma once

#include <gl/GL.h>
#include <gl/GLU.h>
#include <boost/log/trivial.hpp>
class GLEngine
{
public:
	GLEngine();
	~GLEngine();

	void Init(HDC hdc);
	void Shutdown();	
private:
	HGLRC m_hglrc;
	HDC m_hdc;
};