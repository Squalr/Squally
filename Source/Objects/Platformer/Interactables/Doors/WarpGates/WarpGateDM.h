#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class WarpGateDM : public WarpGate
{
public:
	static WarpGateDM* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateDM(cocos2d::ValueMap& properties);
	virtual ~WarpGateDM();
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
