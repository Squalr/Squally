#pragma once
#include "cocos2d.h"

#include "Scenes/Level/LevelCamera.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Resources.h"

using namespace cocos2d;

class SnowEnvironment : public Layer
{
public:
	static SnowEnvironment * create();

	void update(float) override;

private:
	SnowEnvironment();
	~SnowEnvironment();

	ParticleSystem * snow;
};

