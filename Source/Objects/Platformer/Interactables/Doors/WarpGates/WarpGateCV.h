#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

namespace cocos2d
{
	class DrawNode;
}

class SmartParticles;

class WarpGateCV : public WarpGate
{
public:
	static WarpGateCV* create(cocos2d::ValueMap& properties);
	
	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;

protected:
	WarpGateCV(cocos2d::ValueMap& properties);
	virtual ~WarpGateCV();

	void onEnter() override;

private:
	typedef WarpGate super;

	SmartParticles* portalParticles;
};
