#pragma once

#include "stdafx.h"

class GameOver : public Layer
{
private:
	Layer *bgLayer;

	Sprite *BackGround;
	Sprite *BackGround2;

	MoveBy *MoveAct1;
	Place *PlaceAct2;
	Sequence *Sequence3;
	RepeatForever *RepeatForeverAct4;

	Sprite* gameoverSpr;

	Label* score;
	Label* bscore;

	MenuItemImage *Retry;
	MenuItemImage *Exit;

	Menu *menub;
public:
	static Scene* createScene();

	virtual bool init();

	void retryScene(Ref *Sender);
	void exitScene(Ref *Sender);

	CREATE_FUNC(GameOver);
};