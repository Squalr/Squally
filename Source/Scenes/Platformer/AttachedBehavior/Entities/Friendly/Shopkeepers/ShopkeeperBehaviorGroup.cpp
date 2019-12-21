#include "ShopkeeperBehaviorGroup.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Events/DialogueEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Cinematic/EntityCinematicHijackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDeveloperBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Shopkeepers/ShopkeeperDialogueBehavior.h"

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
	EntityDialogueBehavior::create(owner),
	LookAtSquallyBehavior::create(owner),
	ShopkeeperDialogueBehavior::create(owner),
	})
{
}

ShopkeeperBehaviorGroup::~ShopkeeperBehaviorGroup()
{
}

void ShopkeeperBehaviorGroup::onLoad()
{
}
