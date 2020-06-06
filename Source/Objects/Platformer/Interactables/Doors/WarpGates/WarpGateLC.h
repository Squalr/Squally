#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

namespace cocos2d
{
	class DrawNode;
}

class SmartParticles;

class WarpGateLC : public WarpGate
{
public:
	static WarpGateLC* create(cocos2d::ValueMap& properties);
	
	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;

protected:
	WarpGateLC(cocos2d::ValueMap& properties);
	virtual ~WarpGateLC();

	void onEnter() override;

private:
	typedef WarpGate super;

	SmartParticles* portalParticles;
};
