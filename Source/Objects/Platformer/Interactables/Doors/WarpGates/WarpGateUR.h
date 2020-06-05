#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

namespace cocos2d
{
	class DrawNode;
}

class SmartParticles;

class WarpGateUR : public WarpGate
{
public:
	static WarpGateUR* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateUR(cocos2d::ValueMap& properties);
	virtual ~WarpGateUR();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef WarpGate super;

	cocos2d::DrawNode* background;
	SmartParticles* portalParticles;
	cocos2d::DrawNode* edge;
	SmartParticles* edgeParticles;
};
