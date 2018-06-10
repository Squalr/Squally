#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/UILayer.h"
#include "Resources.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class MountainBackground : public UILayer
{
public:
	static MountainBackground * create();

	void update(float) override;

protected:
	MountainBackground();
	~MountainBackground();

	Sprite * background;

private:
	InfiniteParallaxNode * clouds;
	ParallaxNode * mountains;
	ParallaxNode * mountains2;
	ParallaxNode * trees1;
	ParallaxNode * trees2;
	ParallaxNode * trees3;
};

