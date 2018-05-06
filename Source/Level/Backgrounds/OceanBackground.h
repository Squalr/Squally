#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/LevelCamera.h"
#include "GUI/Components/InfiniteParallaxNode.h"

using namespace cocos2d;

class OceanBackground : public Layer
{
public:
	static OceanBackground * create();

	void update(float) override;

private:
	OceanBackground();
	~OceanBackground();

	Sprite * background;
};

