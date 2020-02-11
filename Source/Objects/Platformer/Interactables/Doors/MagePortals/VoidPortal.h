#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"

namespace cocos2d
{
	class DrawNode;
}

class SmartParticles;

class VoidPortal : public MagePortal
{
public:
	static VoidPortal* create(cocos2d::ValueMap& properties);

	void closePortal(bool instant) override;
	void openPortal(bool instant) override;

	static const std::string MapKeyVoidPortal;

protected:
	VoidPortal(cocos2d::ValueMap& properties);
	virtual ~VoidPortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MagePortal super;

	SmartParticles* portalParticles;
	SmartParticles* edgeParticles;
};
