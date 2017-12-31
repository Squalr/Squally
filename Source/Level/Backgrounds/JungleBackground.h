#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Player/Player.h"
#include "GUI/Components/InfiniteParallaxNode.h"

using namespace cocos2d;

class JungleBackground : public Layer
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

