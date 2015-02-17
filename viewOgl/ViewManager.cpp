#include "stdafx.h"
#include "ViewManager.h"
#include "Object.h"
#include <memory>

std::shared_ptr<IObject> ViewManager::CreateObject()
{
	return std::shared_ptr<IObject>(new Object());
}
