#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Resources.h"
#include "Scenes/Maps/Platformer/Backgrounds/BackgroundBase.h"

using namespace cocos2d;

class SnowBackground : public BackgroundBase
{
public:
	static SnowBackground * create(ValueMap* properties, std::string name);

	static const std::string KeyBackgroundSnow;

private:
	SnowBackground(ValueMap* properties, std::string name);
	~SnowBackground();

	void update(float) override;

	Sprite * background;
	InfiniteParallaxNode * layer6;
	InfiniteParallaxNode * layer5;
};

