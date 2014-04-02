#include "stdafx.h"
#include "GLEngine.h"

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
	m_hglrc = wglCreateContext(hdc);
	if(!m_hglrc)
		BOOST_LOG_TRIVIAL(error) << "Error wglCreateContext: " << __LINE__;

	if(!wglMakeCurrent(hdc, m_hglrc))
		BOOST_LOG_TRIVIAL(error) << "Error wglMakeCurrent: " << __LINE__;
}

void GLEngine::Shutdown()
{

}
