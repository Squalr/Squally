#pragma once

#include "Engine/SmartScene.h"

class GlobalScene : public SmartScene
{
public:
	static GlobalScene* create();

protected:
	GlobalScene();
	virtual ~GlobalScene();

private:
    typedef SmartScene super;
};
