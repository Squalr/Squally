#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Spawns/PortalSpawn.h"

class Sound;

class WoodDoorSpawn : public PortalSpawn
{
public:
	static WoodDoorSpawn* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WoodDoorSpawn(cocos2d::ValueMap& properties);
	virtual ~WoodDoorSpawn();

	void onPlayerSpawn(PlatformerEntity* entity) override;

private:
	typedef PortalSpawn super;

	Sound* doorSound;
};
