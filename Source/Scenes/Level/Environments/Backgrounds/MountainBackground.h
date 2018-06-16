#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Resources.h"
#include "Scenes/Level/Environments/Backgrounds/BackgroundBase.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class MountainBackground : public BackgroundBase
{
public:
	static MountainBackground * create(std::string name, ValueMap properties);

	static const std::string KeyBackgroundMountains;

private:
	MountainBackground(std::string name, ValueMap properties);
	~MountainBackground();

	void update(float) override;

	Sprite * background;
	InfiniteParallaxNode * clouds;
	ParallaxNode * mountains;
	ParallaxNode * mountains2;
	ParallaxNode * trees1;
	ParallaxNode * trees2;
	ParallaxNode * trees3;
};

