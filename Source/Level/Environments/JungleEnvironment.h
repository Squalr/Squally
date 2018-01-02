#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/LevelCamera.h"
#include "GUI/Components/InfiniteParallaxNode.h"

using namespace cocos2d;

class JungleEnvironment : public Layer
{
public:
	static JungleEnvironment * create();

	void update(float) override;

private:
	JungleEnvironment();
	~JungleEnvironment();

	ParticleSystem * fireflies;
	ParticleSystem * rain;
};

