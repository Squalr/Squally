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

	cocos2d::Node* portalEffectNode = nullptr;

private:
	typedef Portal super;
	
	std::tuple<cocos2d::Node*, cocos2d::Node*> createWeight(std::string weightResource);

	SmartClippingNode* clippingNode = nullptr;
	cocos2d::DrawNode* background = nullptr;
	cocos2d::Sprite* clock = nullptr;
	cocos2d::Node* clippingContentNode = nullptr;
	cocos2d::Sprite* pendulum = nullptr;
	std::vector<std::tuple<cocos2d::Node*, cocos2d::Node*>> weights;
	cocos2d::Node* handNode = nullptr;
	cocos2d::Sprite* handCenter = nullptr;
	cocos2d::Sprite* handMinutes = nullptr;
	cocos2d::Sprite* handHours = nullptr;

	SmartParticles* portalParticles = nullptr;
	SmartParticles* edgeParticles = nullptr;

	bool isHaunted = false;
	
	static const std::string PropertyClockStyle;
	static const std::string ClockStyleHaunted;
	static const cocos2d::Color4B BaseColor;
	static const cocos2d::CSize ClipSize;
};
