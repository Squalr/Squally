#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Spawns/PortalSpawn.h"

class CartSpawn : public PortalSpawn
{
public:
	static CartSpawn* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	CartSpawn(cocos2d::ValueMap& properties);
	virtual ~CartSpawn();

	void onPlayerSpawn() override;

private:
	typedef PortalSpawn super;
};
