#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/LevelCamera.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/UILayer.h"

using namespace cocos2d;

class JungleBackground : public UILayer
{
public:
	static JungleBackground * create();

	void update(float) override;

private:
	JungleBackground();
	~JungleBackground();
	Sprite * background;
	InfiniteParallaxNode * layer6;
	InfiniteParallaxNode * layer5;
	InfiniteParallaxNode * layer4;
	InfiniteParallaxNode * layer2;
};

