#pragma once
#include <set>

#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class WindPortal : public MagePortal
{
public:
	static WindPortal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyWindPortal;

protected:
	WindPortal(cocos2d::ValueMap& properties);
	~WindPortal();
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
