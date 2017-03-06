#include "stdafx.h"

Scene* InGame::createScene()
{
	auto scene = Scene::create();

	auto layer = InGame::create();

	scene->addChild(layer);

	return scene;
}

bool InGame::init()
{
	if (!Layer::init())
		return false;

	srand(time(NULL));

	nLife = 5;
	nScore = 0;

	TouchMode = false;
	TouchMode2 = false;
	God = false;
	temptime = 0.0f;

	SpawnTime = 0.5f;
	CharSpeed = 0.7f;

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

	Listener = EventListenerTouchAllAtOnce::create();
	Listener->onTouchesBegan = CC_CALLBACK_2(InGame::onTouchesBegan, this);
	Listener->onTouchesMoved = CC_CALLBACK_2(InGame::onTouchesMoved, this);
	Listener->onTouchesEnded = CC_CALLBACK_2(InGame::onTouchesEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(Listener, 1);


	Characterbound = Sprite::create("charbound.png");
	Characterbound->setScale(0.8f);
	Characterbound->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);
	this->addChild(Characterbound, 98);

	Character = Sprite::create("char.png");
	Character->setScale(0.8f);
	Character->setPosition(Character->getPosition());
	this->addChild(Character, 99, TAG_SPRITE_CHAR);

	Lifestr = String::createWithFormat("Life : %d", nLife);

	LifeLabel = Label::create("", "Consolas", 25);
	LifeLabel->setAnchorPoint(Point(0.0f, 1.0f));
	LifeLabel->setPosition(Point(0.0f, 480));
	LifeLabel->setColor(Color3B::GREEN);
	LifeLabel->setString(Lifestr->getCString());
	this->addChild(LifeLabel);

	Scorestr = String::createWithFormat("Score : %d", nScore);

	ScoreLabel = Label::create("", "Consolas", 25);
	ScoreLabel->setAnchorPoint(Point(1.0f, 1.0f));
	ScoreLabel->setPosition(Point(800, 480));
	ScoreLabel->setColor(Color3B::GREEN);
	ScoreLabel->setString(Scorestr->getCString());
	this->addChild(ScoreLabel);

	schedule(schedule_selector(InGame::CreateEnemy), SpawnTime);
	schedule(schedule_selector(InGame::Update));

	return true;
}

void InGame::CreateEnemy(float fDt)
{
	int check = rand() % 4 + 0;
	EnemyEndX = Characterbound->getPositionX();
	EnemyEndY = Characterbound->getPositionY();
	switch (check)
	{
	case 0:
		EnemyX = rand() % 800;
		EnemyY = 480;
		break;
	case 1:
		EnemyX = 800;
		EnemyY = rand() % 480;
		break;
	case 2:
		EnemyX = rand() % 800;
		EnemyY = 0;
		break;
	case 3:
		EnemyX = 0;
		EnemyY = rand() % 480;
		break;
	}

	EnemySpr = Sprite::create("enemy.png");
	EnemySpr->setPosition(EnemyX, EnemyY);

	EnemyEndX2 = EnemyEndX - EnemyX;

	EnemyEndY2 = EnemyEndY - EnemyY;

	act1 = MoveBy::create(rand() % 2 + 1, Point(EnemyEndX2, EnemyEndY2));

	EnemySpr->runAction(RepeatForever::create(act1));

	enemy.push_back(EnemySpr);

	this->addChild(EnemySpr);
}

void InGame::Update(float dt)
{
	Character->setPosition(Characterbound->getPosition());

	if (nScore == 5 && !(SpawnTime = 0.45f))	{
		SpawnTime = 0.45f, CharSpeed = 0.55f;
		unschedule(schedule_selector(InGame::CreateEnemy));
		schedule(schedule_selector(InGame::CreateEnemy), SpawnTime);
	}
	if (nScore == 10 && !(SpawnTime = 0.425f))	{
		SpawnTime = 0.425f, CharSpeed = 0.525f;
		unschedule(schedule_selector(InGame::CreateEnemy));
		schedule(schedule_selector(InGame::CreateEnemy), SpawnTime);
	}
	if (nScore == 15 && !(SpawnTime = 0.4f))	{
		SpawnTime = 0.4f, CharSpeed = 0.5f;
		unschedule(schedule_selector(InGame::CreateEnemy));
		schedule(schedule_selector(InGame::CreateEnemy), SpawnTime);
	}
	if (nScore == 20 && !(SpawnTime = 0.375f))	{
		SpawnTime = 0.375f, CharSpeed = 0.475f;
		unschedule(schedule_selector(InGame::CreateEnemy));
		schedule(schedule_selector(InGame::CreateEnemy), SpawnTime);
	}
	if (nScore == 25 && !(SpawnTime = 0.35f))	{
		SpawnTime = 0.35f, CharSpeed = 0.45f;
		unschedule(schedule_selector(InGame::CreateEnemy));
		schedule(schedule_selector(InGame::CreateEnemy), SpawnTime);
	}

	if (God == true)
	{
		temptime += dt;
		if (temptime >= 1.5f)
		{
			God = false;
			temptime = 0.f;
		}
	}
	for (auto ene : enemy)
	{
		if (ene->getPositionX() < 0 || ene->getPositionX() > 800 || ene->getPositionY() < 0 || ene->getPositionY() > 480)
		{
			log("Deleted");
			enemy.remove(ene);
			this->removeChild(ene, true);
			return;
		}
		rect1 = ene->getBoundingBox();
		rect2 = Character->getBoundingBox();

		if (rect2.intersectsRect(rect1) && God == false && nLife > 0)
		{
			log("Deleted");
			enemy.remove(ene);
			this->removeChild(ene, true);
			God = true;
			nLife--;
			Hurt = Sprite::create("hurt.png");
			Hurt->setPosition(Point(400, 240));
			this->addChild(Hurt);
			Hurt->runAction(FadeOut::create(0.65f));
			Character->runAction(Blink::create(1.5, 4));
			Characterbound->runAction(Blink::create(1.5, 4));
			Lifestr = String::createWithFormat("Life : %d", nLife);
			LifeLabel->setString(Lifestr->getCString());
			return;
		}
		for (auto bul : bullet)
		{
			rect3 = bul->getBoundingBox();
			if (rect3.intersectsRect(rect1))
			{

				log("Deleted by Bullet");
				enemy.remove(ene);
				this->removeChild(ene, true);

				bullet.remove(bul);
				this->removeChild(bul, true);

				nScore++;

				Good = Sprite::create("earn.png");
				Good->setPosition(Point(400, 240));
				this->addChild(Good);
				Good->runAction(FadeOut::create(0.65f));

				Scorestr = String::createWithFormat("Score : %d", nScore);
				ScoreLabel->setString(Scorestr->getCString());

				return;
			}
		}
	}
	if (nLife <= 0)
	{
		InGame::GameOver(this);
	}
}

void InGame::GameOver(Ref *Sender)
{
	if (nScore > Singleton::getInstance()->sBScore)
		Singleton::getInstance()->sBScore = nScore;

	Singleton::getInstance()->sScore = nScore;
	enemy.clear();
	bullet.clear();
	Director::getInstance()->getEventDispatcher()->removeEventListener(Listener);
	unschedule(schedule_selector(InGame::Update));
	unschedule(schedule_selector(InGame::CreateEnemy));
	auto scene = TransitionFade::create(0.5f, GameOver::createScene());
	Director::getInstance()->replaceScene(scene);
}

void InGame::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	vector<Touch*>::const_iterator it = touches.begin();
	Touch* touch;

	for (i = 0; i < touches.size(); i++){
		touch = (Touch*)(*it);

		PosStartTouch[i] = touch->getLocation();

		Rect rectspr = Characterbound->getBoundingBox();

		if (rectspr.containsPoint(PosStartTouch[i]))
		{
			if (TouchMode2 == false)
			{
				TouchMode = true;
				TouchMode2 = true;
			}
		}
		else
		{
			if (nLife > 0){
				TouchMode = false;
				PosStartChar = Characterbound->getPosition();
			}
		}
	}
}

void InGame::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	vector<Touch*>::const_iterator it = touches.begin();

	Touch* touch;

	Point Location[2];
	for (int j = 0; j < touches.size(); j++)
	{
		touch = (Touch*)(*it);
		if (TouchMode == false && nLife > 0)
		{
			Location[j] = touch->getLocation();

			Point PosChange = Location[j] - PosStartTouch[j];

			Characterbound->setPosition(PosStartChar + (PosChange * CharSpeed));

			if (Characterbound->getPositionX() < 20)
				Characterbound->setPositionX(20);
			if (Characterbound->getPositionX() > 780)
				Characterbound->setPositionX(780);
			if (Characterbound->getPositionY() < 20)
				Characterbound->setPositionY(20);
			if (Characterbound->getPositionY() > 460)
				Characterbound->setPositionY(460);

			//if (Character->getPositionX() < 20 || Character->getPositionX() > 780 || Character->getPositionY() < 20 || Character->getPositionY() > 460)
			//	Character->setPosition(PosStartChar - (PosChange * 0.85f));
		}
		else if (TouchMode == true && TouchMode2 == true)
		{
			log("create");
			Location[j] = touch->getLocation();

			if (Characterbound->getBoundingBox().containsPoint(Location[j])){
				//TouchMode2 = true;
				return;
			}
			BulletEndX = Location[j].x;
			BulletEndY = Location[j].y;

			BulletSpr = Sprite::create("bullet.png");

			BulletSpr->setPosition(Characterbound->getPosition());

			BulletEndX -= Characterbound->getPositionX();

			BulletEndY -= Characterbound->getPositionY();

			act2 = MoveBy::create(0.01f, Point(BulletEndX, BulletEndY));

			BulletSpr->runAction(RepeatForever::create(act2));

			bullet.push_back(BulletSpr);

			this->addChild(BulletSpr);

			TouchMode2 = false;
		}
	}
}

void InGame::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	vector<Touch*>::const_iterator it = touches.begin();

	Touch* touch;
	
	touch = (Touch*)(*it);

	Rect rect = Characterbound->getBoundingBox();

	if (rect.containsPoint(touch->getLocation()))
	{
		TouchMode = false;
		TouchMode2 = false;
	}
}