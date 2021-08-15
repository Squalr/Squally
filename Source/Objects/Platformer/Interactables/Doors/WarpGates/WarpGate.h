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

class WarpGate : public Portal
{
public:
	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string TagWarpGate;

protected:
	WarpGate(cocos2d::ValueMap& properties);
	virtual ~WarpGate();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* particlesNode = nullptr;
	cocos2d::Node* mapNode = nullptr;

private:
	typedef Portal super;

	SmartClippingNode* mapClip = nullptr;
	cocos2d::Node* mapNodeContainer = nullptr;
	cocos2d::Sprite* doorClosed = nullptr;
	cocos2d::Sprite* doorFrame = nullptr;
	SmartParticles* centerParticles = nullptr;
	SmartParticles* edgeParticlesLeft = nullptr;
	SmartParticles* edgeParticlesRight = nullptr;
	SmartParticles* edgeParticlesUp = nullptr;
	SmartParticles* edgeParticlesDown = nullptr;
	WorldSound* portalOpenSound = nullptr;
};
