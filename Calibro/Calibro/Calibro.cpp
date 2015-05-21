#include "Calibro.h"
#include <boost/format.hpp>
#include <irrlicht.h>
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
	)
{
	irr::IrrlichtDevice * device = createDevice(video::EDT_DIRECT3D9, dimension2d<u32>(640,480), 16, false, false, false, 0);
	if(device)
	{
		IVideoDriver *driver = device->getVideoDriver();
		ISceneManager* smgr = device->getSceneManager();
		IGUIEnvironment *guienv = device->getGUIEnvironment();

		IGUIStaticText* text = guienv->addStaticText(L"", rect<s32>(10,10,200,22), false);		
		IAnimatedMesh* mesh = smgr->getMesh("D:/projects/irrlicht-1.8.1/media/sydney.md2");
		if(!mesh)
		{
			device->drop();
			return 1;
		}		
		ISceneNode *node;
		//IAnimatedMeshSceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
		if(node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			//node->setMD2Animation(scene::EMAT_STAND);			
			//node->setMaterialTexture(0, driver->getTexture("D:/projects/irrlicht-1.8.1/media/sydney.bmp"));			
		}
		smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
		SMaterial mat;
		while(device->run())
		{
			std::wstring s = boost::str(boost::wformat(L"%d") % driver->getFPS());
			text->setText(s.c_str());
			driver->beginScene(true, true, SColor(255,100,101,140));
			
			driver->setMaterial(mat);
			driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);
			driver->draw3DBox(aabbox3d<f32>(0.0,0.0,0.0,10.0,10.0,10.0));
			smgr->drawAll();
			guienv->drawAll();			
			driver->endScene();
		}
		device->drop();
	}
	return 0;
}