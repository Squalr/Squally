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
	static MountainBackground * create(ValueMap* properties, std::string name);

	static const std::string KeyBackgroundMountains;

private:
	MountainBackground(ValueMap* properties, std::string name);
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

