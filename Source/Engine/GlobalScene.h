#pragma once

#include "Engine/SmartScene.h"

class GlobalScene : public SmartScene
{
public:
	static GlobalScene* create();

	GlobalScene();
	virtual ~GlobalScene();

private:
    typedef SmartScene super;
};
