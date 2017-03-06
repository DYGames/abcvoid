#pragma once

#include "stdafx.h"

class MenuScene : public Layer
{
private:
	Layer *bgLayer;
	Sprite *BackGround;
	Sprite *BackGround2;

	MoveBy *MoveAct1;
	Place *PlaceAct2;
	Sequence *Sequence3;
	RepeatForever *RepeatForeverAct4;

	Sprite *Title;

	MenuItemImage *Start;
	MenuItemImage *Opt;
	MenuItemImage *Exit;
	Menu *Buttons;

	Sprite *OptBack;
	MenuItemImage *Music;
	MenuItemImage *Music2;
	MenuItemToggle *MusicToggle;
	MenuItemImage *Sound;
	MenuItemImage *Sound2;
	MenuItemToggle *SoundToggle;
	MenuItemImage *OptExit;
	Menu *OptM;
	bool OptOn = false;
public:
	static Scene* createScene();

	virtual bool init();

	void Update(float dt);

	void StartMenu(Ref *Sender);
	void OptMenu(Ref *Sender);
	void ExitMenu(Ref *Sender);

	void setMusic(Ref *Sender);
	void setSound(Ref *Sender);

	CREATE_FUNC(MenuScene);
};