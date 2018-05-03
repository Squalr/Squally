#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/LevelCamera.h"
#include "GUI/Components/InfiniteParallaxNode.h"

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

