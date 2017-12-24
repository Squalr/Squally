#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class FadeScene : public Scene
{
protected:
	FadeScene();
	~FadeScene();

	void onEnter() override;

	LayerColor* layerColor;
};

