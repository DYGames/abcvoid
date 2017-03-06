#pragma once

#include "stdafx.h"

class InGame : public Layer
{
private:
	Layer *bgLayer;

	Sprite *BackGround;
	Sprite *BackGround2;

	MoveBy *MoveAct1;
	Place *PlaceAct2;
	Sequence *Sequence3;
	RepeatForever *RepeatForeverAct4;

	Point PosStartTouch[2];
	Point PosStartChar;

	int i;

	bool TouchMode;
	bool TouchMode2;

	Sprite *Hurt;
	Sprite *Good;

	Sprite *Character;
	Sprite *Characterbound;
	Sprite *EnemySpr;

	list<Sprite*> enemy;
	MoveBy *act1;

	int EnemyX;
	int EnemyY;

	int EnemyEndX;
	int EnemyEndY;
	int EnemyEndX2;
	int EnemyEndY2;

	list<Sprite*> bullet;
	Sprite *BulletSpr;
	MoveBy *act2;

	int BulletEndX;
	int BulletEndY;

	Rect rect1;
	Rect rect2;
	Rect rect3;

	EventListenerTouchAllAtOnce *Listener;

	int nLife;
	int nScore;
	bool God;
	float temptime;

	String *Lifestr;
	Label *LifeLabel;

	String *Scorestr;
	Label *ScoreLabel;

	float SpawnTime;
	float CharSpeed;
public:
	static Scene* createScene();

	virtual bool init();

	void Update(float dt);

	void CreateEnemy(float fDt);

	CREATE_FUNC(InGame);

	void GameOver(Ref *Sender);

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
};