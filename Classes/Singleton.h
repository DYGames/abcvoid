#pragma once

#include "stdafx.h"

class Singleton{
private:
	static Singleton* m_uInstance;
public:
	Singleton()
	{

	}
	~Singleton()
	{
	}
	int sScore = 0;
	int sBScore = 0;
	bool sMusic = true;
	bool sSound = true;
	static Singleton* getInstance();

};
