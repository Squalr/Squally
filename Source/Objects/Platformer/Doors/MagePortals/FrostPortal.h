#pragma once
#include <set>

#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class FrostPortal : public MagePortal
{
public:
	static FrostPortal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyFrostPortal;

protected:
	FrostPortal(cocos2d::ValueMap& properties);
	~FrostPortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MagePortal super;

	cocos2d::ParticleSystem* portalParticles;
	cocos2d::ParticleSystem* edgeParticles;
};
