#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Resources/BackgroundResources.h"
#include "Scenes/Maps/Platformer/Backgrounds/BackgroundBase.h"

using namespace cocos2d;

class JungleBackground : public BackgroundBase
{
public:
	static JungleBackground* create(ValueMap* properties, std::string name);

	static const std::string MapKeyBackgroundLayerJungle;

private:
	JungleBackground(ValueMap* properties, std::string name);
	~JungleBackground();

	void update(float) override;

	Sprite* background;
	InfiniteParallaxNode* layer6;
	InfiniteParallaxNode* layer5;
	InfiniteParallaxNode* layer4;
	InfiniteParallaxNode* layer2;
};

