#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/UILayer.h"
#include "Resources.h"
#include "Scenes/Level/LevelCamera.h"

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

