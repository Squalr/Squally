#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

namespace cocos2d
{
	class DrawNode;
}

class SmartParticles;

class WarpGateVS : public WarpGate
{
public:
	static WarpGateVS* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateVS(cocos2d::ValueMap& properties);
	virtual ~WarpGateVS();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef WarpGate super;

	SmartParticles* portalParticles;
	SmartParticles* edgeParticles;
};
