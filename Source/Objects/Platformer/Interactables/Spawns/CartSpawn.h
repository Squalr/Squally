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

	void onPlayerSpawn(PlatformerEntity* entity) override;

private:
	typedef PortalSpawn super;

	void enterCart(PlatformerEntity* entity);

	std::string linkTag;
	std::string direction;

	static const std::string PropertyLinkTag;
	static const std::string PropertyDirection;
};
