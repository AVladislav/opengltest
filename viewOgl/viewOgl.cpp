// viewOgl.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <memory>
#include "ViewOgl.h"
#include "ViewManager.h"

ViewManager *_viewManager; 

IViewManager* CreateManager()
{
	_viewManager = new ViewManager();
	return _viewManager;
}