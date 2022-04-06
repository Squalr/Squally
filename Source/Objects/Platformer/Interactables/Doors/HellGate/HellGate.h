#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class SmartClippingNode;
class SmartParticles;
class WorldSound;

class HellGate : public Portal
{
public:
	static HellGate* create(cocos2d::ValueMap& properties);

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;

protected:
	HellGate(cocos2d::ValueMap& properties);
	virtual ~HellGate();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* particlesNode = nullptr;
	cocos2d::Node* mapNode = nullptr;

private:
	typedef Portal super;

	SmartClippingNode* clipping = nullptr;
	cocos2d::Node* mapNodeContainer = nullptr;
	cocos2d::Sprite* doorFrame = nullptr;
	SmartParticles* fireParticles = nullptr;
	SmartParticles* centerParticles = nullptr;
	WorldSound* portalOpenSound = nullptr;
};
