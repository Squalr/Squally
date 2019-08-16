#include "ShopkeeperBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Cinematic/EntityCinematicHijackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDeveloperBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/Shopkeepers/ShopkeeperMovementBehavior.h"

using namespace cocos2d;

const std::string ShopkeeperBehaviorGroup::MapKeyAttachedBehavior = "shopkeeper";

ShopkeeperBehaviorGroup* ShopkeeperBehaviorGroup::create(GameObject* owner)
{
	ShopkeeperBehaviorGroup* instance = new ShopkeeperBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

ShopkeeperBehaviorGroup::ShopkeeperBehaviorGroup(GameObject* owner) : super(owner, {
	EntityCinematicHijackBehavior::create(owner),
	EntityDeveloperBehavior::create(owner),
	EntityStatsBehaviorGroup::create(owner),
	ShopkeeperMovementBehavior::create(owner),
	})
{
}

ShopkeeperBehaviorGroup::~ShopkeeperBehaviorGroup()
{
}

void ShopkeeperBehaviorGroup::onLoad()
{
}
