#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class WaterPortal : public MagePortal
{
public:
	static WaterPortal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyWaterPortal;

protected:
	WaterPortal(cocos2d::ValueMap& properties);
	~WaterPortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MagePortal super;

	cocos2d::DrawNode* background;
	cocos2d::ParticleSystem* portalParticles;
	cocos2d::DrawNode* edge;
	cocos2d::ParticleSystem* edgeParticles;
};
