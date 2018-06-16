#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Resources.h"
#include "Scenes/Level/Environments/Backgrounds/BackgroundBase.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class OceanBackground : public BackgroundBase
{
public:
	static OceanBackground * create(std::string name, ValueMap properties);

	static const std::string KeyBackgroundOcean;

private:
	OceanBackground(std::string name, ValueMap properties);
	~OceanBackground();

	void update(float) override;

	Sprite * background;
};

