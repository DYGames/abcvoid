#include "stdafx.h"

Scene* GameOver::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOver::create();

	scene->addChild(layer);

	return scene;
}

bool GameOver::init()
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

	gameoverSpr = Sprite::create("gameover.png");

	gameoverSpr->setPosition(Point(400, 400));

	this->addChild(gameoverSpr);

	String *str = String::createWithFormat("Score : %d", Singleton::getInstance()->sScore);
	String *str2 = String::createWithFormat("Best Score : %d", Singleton::getInstance()->sBScore);

	score = Label::create("", "Consolas", 30);
	score->setString(str->getCString());
	score->setColor(Color3B::GREEN);
	score->setPosition(Point(275, 250));
	this->addChild(score);

	bscore = Label::create("", "Consolas", 30);
	bscore->setString(str2->getCString());
	bscore->setColor(Color3B::GREEN);
	bscore->setPosition(Point(550, 250));
	this->addChild(bscore);

	Retry = MenuItemImage::create("retry.png", "retry.png", CC_CALLBACK_1(GameOver::retryScene, this));
	Retry->setPosition(Point(275, 150));

	Exit = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(GameOver::exitScene, this));
	Exit->setPosition(Point(550, 150));

	menub = Menu::create(Retry, Exit, NULL);
	menub->setPosition(Point(0, 0));
	this->addChild(menub);

	return true;
}

void GameOver::retryScene(Ref *Sender)
{ 
	auto scene = TransitionFade::create(1.5f, InGame::createScene());
	Director::getInstance()->replaceScene(scene);
}

void GameOver::exitScene(Ref *Sender)
{
	auto scene = TransitionFade::create(1.5f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}