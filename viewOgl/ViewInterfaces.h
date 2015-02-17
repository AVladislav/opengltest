#pragma once

#include <memory>

struct IObject
{
	virtual void Draw() = 0;
};

struct IViewManager
{
	virtual std::shared_ptr<IObject> CreateObject() = 0;
};