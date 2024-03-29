#pragma once
#include <set>

#include "Engine/Physics/Liquid/LiquidNode.h"

class LavaFX;

class Lava : public LiquidNode
{
public:
	static Lava* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Lava(cocos2d::ValueMap& properties);
	virtual ~Lava();
	
	void onEnter() override;
	void initializeListeners() override;
	void applyLavaForce(CollisionObject* target, float dt);

private:
	typedef LiquidNode super;

	void runBubbles();
	void runBubbleLoop(int index);
	void runBubble(int index);

	std::vector<LavaFX*> bubbles;
	bool bubblesDisabled = false;

	static const cocos2d::Color4B SurfaceColor;
	static const cocos2d::Color4B BodyColor;
	static const float LavaGravity;
	static const float BubbleDensityPer1024Px;
};
