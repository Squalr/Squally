#pragma once
#include <set>

#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class FirePortal : public MagePortal
{
public:
	static FirePortal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyFirePortal;

protected:
	FirePortal(cocos2d::ValueMap& properties);
	~FirePortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MagePortal super;

	cocos2d::ParticleSystem* portalParticles;
	cocos2d::ParticleSystem* edgeParticles;
};
