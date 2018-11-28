#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Resources/BackgroundResources.h"
#include "Scenes/Maps/Platformer/Backgrounds/BackgroundBase.h"

using namespace cocos2d;

class OceanBackground : public BackgroundBase
{
public:
	static OceanBackground* create(ValueMap* properties, std::string name);

	static const std::string MapKeyBackgroundLayerOcean;

private:
	OceanBackground(ValueMap* properties, std::string name);
	~OceanBackground();

	void update(float) override;

	Sprite* background;
};

