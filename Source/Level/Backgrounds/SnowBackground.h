#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/LevelCamera.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/UILayer.h"

using namespace cocos2d;

class SnowBackground : public UILayer
{
public:
	static SnowBackground * create();

	void update(float) override;

private:
	SnowBackground();
	~SnowBackground();
	Sprite * background;
	InfiniteParallaxNode * layer6;
	InfiniteParallaxNode * layer5;
};

