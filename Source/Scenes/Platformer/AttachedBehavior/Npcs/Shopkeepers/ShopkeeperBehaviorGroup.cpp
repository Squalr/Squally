#include "ShopkeeperBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Cinematic/EntityCinematicHijackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDeveloperBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/Dialogue/NpcInteractionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/LookAtSquallyBehavior.h"

#include "Strings/Platformer/Entities/Shopkeepers/HowDoIBuySomething.h"

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
	NpcInteractionBehavior::create(owner),
	LookAtSquallyBehavior::create(owner),
	})
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

ShopkeeperBehaviorGroup::~ShopkeeperBehaviorGroup()
{
}

void ShopkeeperBehaviorGroup::onLoad()
{
	this->entity->watchForAttachedBehavior<NpcInteractionBehavior>([=](NpcInteractionBehavior* interactionBehavior)
	{
		interactionBehavior->addDialogueOption(NpcInteractionBehavior::DialogueOption(
			Strings::Platformer_Entities_Shopkeepers_HowDoIBuySomething::create(),
			[=]()
			{

			}),
			1.0f
		);
	});
}
