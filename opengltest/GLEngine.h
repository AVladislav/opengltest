#pragma once

#include <gl/GL.h>
#include <gl/GLU.h>
#include <boost/log/trivial.hpp>
#include "camera.h"
#include "../viewOgl/ViewInterfaces.h"
class GLEngine
{
public:
	GLEngine();
	~GLEngine();

	void Init(HWND hWnd);
	void InitTextures();
	void Shutdown();	
	void Draw();
	void StartThread();
	void Run();
	void SetPerpective();
	void ProcessMsg(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
protected:
	void ResizeScene(UINT width, UINT height);
	void InitGL();

private:
	HGLRC m_hglrc;
	HDC m_hdc;
	HWND m_hWnd;
	GLuint      texture[1]; 
	Camera m_camera;
	IViewManager *m_viewManager;
	std::shared_ptr<IObject> m_Object;
};