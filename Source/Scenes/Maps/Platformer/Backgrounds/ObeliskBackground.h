#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Resources/BackgroundResources.h"
#include "Scenes/Maps/Platformer/Backgrounds/BackgroundBase.h"

using namespace cocos2d;

class ObeliskBackground : public BackgroundBase
{
public:
	static ObeliskBackground* create(ValueMap* properties, std::string name);

	static const std::string MapKeyBackgroundLayerObelisk;

private:
	ObeliskBackground(ValueMap* properties, std::string name);
	~ObeliskBackground();

	void update(float) override;

	Sprite* background;
	InfiniteParallaxNode* background2;
	InfiniteParallaxNode* background3;
	InfiniteParallaxNode* midground1;
	InfiniteParallaxNode* midground2;
};

