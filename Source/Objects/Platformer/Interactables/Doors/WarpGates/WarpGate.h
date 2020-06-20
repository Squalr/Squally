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

	cocos2d::Node* contentNode;

private:
	typedef Portal super;

	cocos2d::Node* innerContentNode;

	SmartClippingNode* portalClip;
	cocos2d::Sprite* doorClosed;
	cocos2d::Sprite* doorFrame;
	SmartParticles* centerParticles;
	SmartParticles* edgeParticlesLeft;
	SmartParticles* edgeParticlesRight;
	SmartParticles* edgeParticlesUp;
	SmartParticles* edgeParticlesDown;
	WorldSound* portalOpenSound;
};
