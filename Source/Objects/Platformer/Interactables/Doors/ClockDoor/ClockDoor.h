#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class DrawNode;
	class Sprite;
}

class SmartClippingNode;

class ClockDoor : public Portal
{
public:
	static ClockDoor* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ClockDoor(cocos2d::ValueMap& properties);
	virtual ~ClockDoor();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* portalEffectNode;

private:
	typedef Portal super;
	
	std::tuple<cocos2d::Node*, cocos2d::Node*> createWeight(std::string weightResource);

	SmartClippingNode* clippingNode;
	cocos2d::DrawNode* background;
	cocos2d::Sprite* clock;
	cocos2d::Node* clippingContentNode;
	cocos2d::Sprite* pendulum;
	std::vector<std::tuple<cocos2d::Node*, cocos2d::Node*>> weights;
	cocos2d::Node* handNode;
	cocos2d::Sprite* handCenter;
	cocos2d::Sprite* handMinutes;
	cocos2d::Sprite* handHours;

	SmartParticles* portalParticles;
	SmartParticles* edgeParticles;

	bool isHaunted;
	
	static const std::string PropertyClockStyle;
	static const std::string ClockStyleHaunted;
	static const cocos2d::Color4B BaseColor;
	static const cocos2d::Size ClipSize;
};
