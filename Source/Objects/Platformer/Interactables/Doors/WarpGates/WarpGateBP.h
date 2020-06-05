#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

namespace cocos2d
{
	class DrawNode;
}

class SmartParticles;

class WarpGateBP : public WarpGate
{
public:
	static WarpGateBP* create(cocos2d::ValueMap& properties);

	void closePortal(bool instant) override;
	void openPortal(bool instant) override;

	static const std::string MapKey;

protected:
	WarpGateBP(cocos2d::ValueMap& properties);
	virtual ~WarpGateBP();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef WarpGate super;

	SmartParticles* portalParticles;
	SmartParticles* edgeParticles;
};
