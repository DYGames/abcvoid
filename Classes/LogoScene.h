#pragma once

#include "stdafx.h"

class Logo : public Layer
{
private:
	float fDt = 0.0f;

public:
    static Scene* createScene();

    virtual bool init();  

	void ChangeScene(Ref *Sender);

	CREATE_FUNC(Logo);
};