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
	void InitTextures();
	void Shutdown();	
	void Draw();
	void StartThread();
	void Run();

protected:
	void ResizeScene(UINT width, UINT height);
	void InitGL();

private:
	HGLRC m_hglrc;
	HDC m_hdc;
	GLuint      texture[1]; 
};