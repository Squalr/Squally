#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class HackableData;
class InteractMenu;

class PortalSpawn : public HackableObject
{
public:
	static PortalSpawn* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyPortalSpawn;
	static const std::string MapKeyPortalSpawnTransition;

protected:
	PortalSpawn(cocos2d::ValueMap& properties);
	virtual ~PortalSpawn();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;

	std::string transition;
};
