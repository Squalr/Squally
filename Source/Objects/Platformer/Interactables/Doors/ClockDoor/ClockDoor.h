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

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;

protected:
	ClockDoor(cocos2d::ValueMap& properties);
	virtual ~ClockDoor();
	
	void onEnter() override;
	void onInteract(PlatformerEntity* interactingEntity) override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* portalEffectNode = nullptr;

private:
	typedef Portal super;

	void runAnimations();
	void stopAnimations();
	void checkSecret();
	
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

	bool isAnimating = false;
	bool isHaunted = false;

	std::vector<int> combinationSecret = std::vector<int>({0, 6, 9, 4, 2, 0});
	
	static const std::string PropertyClockStyle;
	static const std::string ClockStyleHaunted;
	static const cocos2d::Color4B BaseColor;
	static const cocos2d::CSize ClipSize;
	
	static const float OneFakeMinute;
	static const float OneFakeHour;
};
