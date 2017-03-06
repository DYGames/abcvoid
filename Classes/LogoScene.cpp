#include "stdafx.h"

Scene* Logo::createScene()
{
    auto scene = Scene::create();
    
	auto layer = Logo::create();

    scene->addChild(layer);

    return scene;
}

bool Logo::init()
{
	if ( !Layer::init() )
		return false;
	
	MenuItemImage* sLogo = MenuItemImage::create("dygames.png","dygames.png",CC_CALLBACK_1(Logo::ChangeScene,this));
	sLogo->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);

	Menu* mMenu = Menu::create(sLogo, NULL);
	mMenu->setPosition(0, 0);
	this->addChild(mMenu);
	
    return true;
}

void Logo::ChangeScene(Ref *Sender)
{
	auto scene = TransitionFade::create(1.5f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

