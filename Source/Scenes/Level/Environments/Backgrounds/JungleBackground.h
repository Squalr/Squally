#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Resources.h"
#include "Scenes/Level/Environments/Backgrounds/BackgroundBase.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class JungleBackground : public BackgroundBase
{
public:
	static JungleBackground * create(std::string name, ValueMap properties);

	static const std::string KeyBackgroundJungle;

private:
	JungleBackground(std::string name, ValueMap properties);
	~JungleBackground();

	void update(float) override;

	Sprite * background;
	InfiniteParallaxNode * layer6;
	InfiniteParallaxNode * layer5;
	InfiniteParallaxNode * layer4;
	InfiniteParallaxNode * layer2;
};

