#include "stdafx.h"
#include "GLEngine.h"
#include "boost/thread.hpp"
#include "quaternion.h"

GLEngine *g_Engine(NULL);

GLEngine::GLEngine() :
	m_hglrc(NULL),
	m_hdc(NULL),
	m_hWnd(NULL)
{
	g_Engine = this;
}

GLEngine::~GLEngine()
{
	g_Engine = NULL;
	ReleaseDC(m_hWnd,m_hdc);
}

void GLEngine::Init(HWND hWnd)
{
	logging::add_file_log("log.txt");
	m_hdc = GetDC(hWnd);
	RECT rc;
	GetWindowRect(hWnd, &rc);
	m_camera.SetCenter(rc.left+(rc.right-rc.left)/2,rc.top+(rc.bottom-rc.top)/2);

	GLuint		PixelFormat;
	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		16,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	PixelFormat=ChoosePixelFormat(m_hdc, &pfd);	// Did Windows Find A Matching Pixel Format?

	BOOL res = SetPixelFormat(m_hdc, PixelFormat, &pfd);		// Are We Able To Set The Pixel Format?	

	m_hglrc = wglCreateContext(m_hdc);
	if(!m_hglrc)
	{
		BOOST_LOG_TRIVIAL(error) << "Error wglCreateContext: " << __LINE__;
		DWORD error = GetLastError();
	}

	if(!wglMakeCurrent(m_hdc, m_hglrc))
		BOOST_LOG_TRIVIAL(error) << "Error wglMakeCurrent: " << __LINE__;

	ResizeScene(800, 600);	
	InitGL();
	InitTextures();
}

void GLEngine::Shutdown()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hglrc);
	m_hglrc = NULL;
	m_hdc = NULL;
}

void GLEngine::ResizeScene( UINT width, UINT height )
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	//glOrtho(0,2,2,0,-1,1);
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void GLEngine::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matsrix

	m_camera.CheckMouse();	
	SetPerpective();
	
	glTranslatef(m_camera.x, 0, m_camera.z);
	//gluLookAt(m_camera.x, 0, m_camera.z, eyeCX, eyeCY, eyeCZ, 0, 1, 0);

	//glTranslatef(-1.f,0.0f,-6.f);						// Move Left 1.5 Units And Into The Screen 6.0	
	
	static GLfloat angle = 0.0;
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	angle+=1.0f;
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, texture[0]);	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,1.0f,1.0f); //white
	glTexCoord2f(0.0f,0.0f);
	glVertex3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(-1.0f,-1.0f, 1.0f);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f( 1.0f,-1.0f, 1.0f);

	glTexCoord2f(1.0f,0.0f);
	glVertex3f( 0.0f, 1.0f, 0.0f); 
	glTexCoord2f(1.0f,1.0f);
	glVertex3f( 1.0f,-1.0f, 1.0f); 
	glTexCoord2f(0.0f,0.0f);
	glVertex3f( 1.0f,-1.0f, -1.0f);

	glTexCoord2f(0.0f,1.0f);
	glVertex3f( 0.0f, 1.0f, 0.0f); 
	glTexCoord2f(0.0f,0.0f);
	glVertex3f( 1.0f,-1.0f, -1.0f);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f, -1.0f);

	glTexCoord2f(1.0f,1.0f);
	glVertex3f( 0.0f, 1.0f, 0.0f); 
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f); 
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-1.0f,-1.0f, 1.0f); 
	glEnd();											// Done Drawing The Quad
	glDisable(GL_TEXTURE_2D);

	glRotatef(-angle, 1.0f, 1.0f, 1.0f);	 	
	glBegin(GL_QUADS);		
	glColor3f(255, 0, 0);
	glVertex3f( -2.0f, 2.0f, -2.0f);
	glVertex3f( 2.0f, 2.0f, -2.0f);
	glVertex3f( 2.0f, -2.0f, -2.0f);
	glVertex3f( -2.0f, -2.0f, -2.0f);
	glEnd();

	SwapBuffers(m_hdc);
	DWORD err = GetLastError();
}

void GLEngine::InitGL()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

void GLEngine::StartThread()
{
	static bool started(false);
	wglMakeCurrent(0, 0);
	if(!started)
	{
		new boost::thread(boost::bind(&GLEngine::Run, this));
		started = true;
	}
}

void GLEngine::Run()
{
	//while(true)
	{
		wglMakeCurrent(m_hdc, m_hglrc);
		Draw();
		Sleep(20);
	}
}

void GLEngine::InitTextures()
{	
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	unsigned char texturePixels[]={255,0,0,255,   0,255,0,255,   255,255,0,255,   0,0,255,255};
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturePixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


LRESULT CALLBACK GLEngine::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	switch (message)
	{
	
	case WM_CLOSE:
		PostQuitMessage(0);
		break;	
	case WM_PAINT:
		break;
	}
	g_Engine->ProcessMsg(hWnd, message,wParam,lParam);

	return DefWindowProc(hWnd, message, wParam, lParam);

}

void GLEngine::ProcessMsg( HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam )
{
	switch(mes)
	{		
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_DOWN:
				m_camera.z -= m_camera.dirz;
				m_camera.x += m_camera.dirx;
				break;
			case VK_UP:
				m_camera.z += m_camera.dirz;
				m_camera.x -= m_camera.dirx;
				break;
			case VK_LEFT:
				m_camera.z += m_camera.dirLz;
				m_camera.x -= m_camera.dirLx;
				break;
			case VK_RIGHT:
				m_camera.z -= m_camera.dirLz;
				m_camera.x += m_camera.dirLx;
				break;
			}
		}
		break;		
	}
}

void GLEngine::SetPerpective()
{
	Quaternion m_qPitch, m_qHeading;
	m_qPitch.CreateFromAxisAngle(1.0f, 0.0f, 0.0f, m_camera.pitch);
	m_qHeading.CreateFromAxisAngle(0.0f, 1.0f, 0.0f, m_camera.heading);

	Quaternion q;
	q = m_qPitch * m_qHeading;
	float Matrix[16];
	q.CreateMatrix(Matrix);
	glMultMatrixf(Matrix);

	m_qPitch.CreateMatrix(Matrix);
	m_camera.diry = Matrix[9];

	q = m_qHeading*m_qPitch;
	q.CreateMatrix(Matrix);
	m_camera.dirx = Matrix[8];
	m_camera.dirz = Matrix[10];

	m_camera.dirLx = -m_camera.dirz;
	m_camera.dirLz = m_camera.dirx;
}
