#include "stdafx.h"
#include "GLEngine.h"
#include "boost/thread.hpp"

GLEngine::GLEngine() :
	m_hglrc(NULL),
	m_hdc(NULL)
{

}

GLEngine::~GLEngine()
{

}

void GLEngine::Init(HDC hdc)
{
	logging::add_file_log("log.txt");
	m_hdc = hdc;

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

	m_hglrc = wglCreateContext(hdc);
	if(!m_hglrc)
	{
		BOOST_LOG_TRIVIAL(error) << "Error wglCreateContext: " << __LINE__;
		DWORD error = GetLastError();
	}

	if(!wglMakeCurrent(hdc, m_hglrc))
		BOOST_LOG_TRIVIAL(error) << "Error wglMakeCurrent: " << __LINE__;

	ResizeScene(800, 600);
	InitGL();
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

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void GLEngine::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
	glColor3f(1,0,0);
	glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
	glColor3f(0,1,0);
	glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle
	glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
	glBegin(GL_QUADS);									// Draw A Quad
	glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
	glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
	glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glEnd();											// Done Drawing The Quad
	SwapBuffers(m_hdc);
	DWORD err = GetLastError();
}

void GLEngine::InitGL()
{
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
	while(true)
	{
		wglMakeCurrent(m_hdc, m_hglrc);
		Draw();
		Sleep(100);
	}
}