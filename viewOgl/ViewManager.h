#pragma once
#include "ViewInterfaces.h"

class ViewManager : public IViewManager
{
public:
	std::shared_ptr<IObject> CreateObject();
private:
};