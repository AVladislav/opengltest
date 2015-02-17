#pragma once
#include <vector>
#include "Common.h"
#include "ViewInterfaces.h"

class Object: public IObject
{
public:
	Object();
	virtual ~Object();
	void Draw();

protected:
	std::vector<Triangle> m_Triangles;
};