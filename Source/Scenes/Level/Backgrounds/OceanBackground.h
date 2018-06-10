#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/UILayer.h"
#include "Resources.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class OceanBackground : public UILayer
{
public:
	static OceanBackground * create();

	void update(float) override;

private:
	OceanBackground();
	~OceanBackground();

	Sprite * background;
};

