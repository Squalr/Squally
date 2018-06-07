#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Level/LevelCamera.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"

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

