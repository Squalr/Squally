#pragma once
#include <set>

#include "Engine/Physics/Liquid/LiquidNode.h"

class AcidFX;

class Acid : public LiquidNode
{
public:
	static Acid* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Acid(cocos2d::ValueMap& properties);
	virtual ~Acid();
	
	void onEnter() override;
	void initializeListeners() override;
	void applyAcidForce(CollisionObject* target, float dt);

private:
	typedef LiquidNode super;

	void runBubbles();
	void runBubbleLoop(int index);
	void runBubble(int index);

	std::vector<AcidFX*> bubbles;
	bool bubblesDisabled = false;

	static const cocos2d::Color4B SurfaceColor;
	static const cocos2d::Color4B BodyColor;
	static const float AcidGravity;
	static const float BubbleDensityPer1024Px;
};
