#pragma once
#include "ViewInterfaces.h"

#ifdef VIEWOGL_EXPORTS
#define _DECLSPEC  __declspec(dllexport)
#else
#define _DECLSPEC  __declspec(dllimport)
#endif

extern "C" _DECLSPEC 
	IViewManager* CreateManager();
