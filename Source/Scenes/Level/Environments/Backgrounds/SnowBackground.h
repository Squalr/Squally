#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Resources.h"
#include "Scenes/Level/Environments/Backgrounds/BackgroundBase.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class SnowBackground : public BackgroundBase
{
public:
	static SnowBackground * create(std::string name, ValueMap properties);

	static const std::string KeyBackgroundSnow;

private:
	SnowBackground(std::string name, ValueMap properties);
	~SnowBackground();

	void update(float) override;

	Sprite * background;
	InfiniteParallaxNode * layer6;
	InfiniteParallaxNode * layer5;
};

