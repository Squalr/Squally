#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class DarkPortal : public MagePortal
{
public:
	static DarkPortal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyDarkPortal;

protected:
	DarkPortal(cocos2d::ValueMap& properties);
	virtual ~DarkPortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MagePortal super;

	cocos2d::ParticleSystem* portalParticles;
	cocos2d::ParticleSystem* edgeParticles;
};
