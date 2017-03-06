#include "stdafx.h"

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
		return false;

	bgLayer = Layer::create();
	this->addChild(bgLayer);

	BackGround = Sprite::create("background.png");
	BackGround->setAnchorPoint(Point::ZERO);
	bgLayer->addChild(BackGround);

	BackGround2 = Sprite::create("background.png", Rect(0, 0, 800, 480));
	BackGround2->setAnchorPoint(Point::ZERO);
	BackGround2->setPosition(Point(800, 0));
	bgLayer->addChild(BackGround2);

	MoveAct1 = MoveBy::create(10.0, Point(-800, 0));
	PlaceAct2 = Place::create(Point::ZERO);
	Sequence3 = Sequence::create(MoveAct1, PlaceAct2, NULL);
	RepeatForeverAct4 = RepeatForever::create(Sequence3);

	bgLayer->runAction(RepeatForeverAct4);

	Title = Sprite::create("title.png");
	Title->setPosition(Point(400, 400));
	this->addChild(Title);

	Start = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(MenuScene::StartMenu, this));
	Start->setPosition(Point(400, 260));
	Opt = MenuItemImage::create("opt.png", "opt.png", CC_CALLBACK_1(MenuScene::OptMenu, this));
	Opt->setPosition(Point(400, 180));
	Exit = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(MenuScene::ExitMenu, this));
	Exit->setPosition(Point(400, 100));

	Buttons = Menu::create(Start, Opt, Exit, NULL);
	Buttons->setPosition(Point(0, 0));
	this->addChild(Buttons);

	scheduleUpdate();

	return true;
}

void MenuScene::Update(float dt)
{

}

void MenuScene::StartMenu(Ref *Sender)
{
	if (OptOn == false){
		auto scene = TransitionFade::create(0.5f, InGame::createScene());
		Director::getInstance()->replaceScene(scene);
	}
}

void MenuScene::OptMenu(Ref *Sender)
{
	if (OptOn == false){
		OptOn = true;
		OptBack = Sprite::create("optback.png");
		OptBack->setPosition(Point(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));

		Music = MenuItemImage::create("music.png", "musicx.png");
		Music2 = MenuItemImage::create("musicx.png", "music.png");
		if (Singleton::getInstance()->sMusic == true)
			MusicToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::setMusic, this), Music, Music2, NULL);
		else
			MusicToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::setMusic, this), Music2, Music, NULL);

		Sound = MenuItemImage::create("sound.png", "soundx.png");
		Sound2 = MenuItemImage::create("soundx.png", "sound.png");
		if (Singleton::getInstance()->sSound == true)
			SoundToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::setSound, this), Sound, Sound2, NULL);
		else
			SoundToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::setSound, this), Sound2, Sound, NULL);

		OptExit = MenuItemImage::create("optexit.png", "optexit.png", CC_CALLBACK_1(MenuScene::OptMenu, this));

		MusicToggle->setPosition(Point(400,290));
		SoundToggle->setPosition(Point(400,170));
		OptExit->setPosition(Point(570,410));

		OptM = Menu::create(MusicToggle, SoundToggle, OptExit, NULL);
		OptM->setPosition(Point(0, 0));

		OptBack->setScale(0.1f);
		OptM->setScale(0.1f);

		this->addChild(OptBack);
		this->addChild(OptM);

		OptBack->runAction(ScaleTo::create(0.25f, 1.0f));
		OptM->runAction(ScaleTo::create(0.25f, 1.0f));
	}
	else if (OptOn == true){
		OptBack->runAction(ScaleTo::create(0.25f, 0.0f));
		OptM->runAction(ScaleTo::create(0.25f, 0.0f));
		//this->removeChild(OptBack, true);
		//this->removeChild(OptM, true);
		OptOn = false;
		return;
	}
}

void MenuScene::ExitMenu(Ref *Sender)
{
	if(OptOn == false){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
		return;
#endif
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
}
}

void MenuScene::setMusic(Ref *Sender)
{
	if (Singleton::getInstance()->sMusic == true)
		Singleton::getInstance()->sMusic = false;
	else if (Singleton::getInstance()->sMusic == false)
		Singleton::getInstance()->sMusic = true;
}

void MenuScene::setSound(Ref *Sender)
{
	if (Singleton::getInstance()->sSound == true)
		Singleton::getInstance()->sSound = false;
	else if (Singleton::getInstance()->sSound == false)
		Singleton::getInstance()->sSound = true;

}