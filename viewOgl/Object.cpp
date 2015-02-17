#include "stdafx.h"
#include "Object.h"
#include <gl\GL.h>

Object::Object()
{
	for(int i = 1; i< 10; ++i)
		for(int j = 1; j< 10; ++j)
		m_Triangles.emplace_back(Triangle(Point3D(0.0f+i, 0.5f, 0.0f+j),Point3D(-0.5f+i,-0.5f, 0.5f+j),Point3D(0.5f+i,-.5f, 0.5f+j)));
	//m_Triangles.emplace_back(Triangle(Point3D(0.0f, 1.0f, 0.0f),Point3D(-1.0f,-1.0f, 1.0f),Point3D(1.0f,-1.0f, 1.0f)));

}

Object::~Object()
{

}

void Object::Draw()
{
// 	for(auto t: m_Triangles)
// 	{
// 		glVertex3f(t.p1.x, t.p1.y, t.p1.z);
// 		glVertex3f(t.p2.x, t.p2.y, t.p2.z);
// 		glVertex3f(t.p3.x, t.p3.y, t.p3.z);
// 	}
	static GLfloat pVerts[]= {-0.5f, -0.5f, 0.0f,
		0.5f,  0.0f, 0.0f,
		-0.5f , 0.5f, 0.0f};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0, &m_Triangles[0].p1);
	glColor3ub(0,255,0); 
	glDrawArrays(GL_TRIANGLES,0,m_Triangles.size()*3);
}
