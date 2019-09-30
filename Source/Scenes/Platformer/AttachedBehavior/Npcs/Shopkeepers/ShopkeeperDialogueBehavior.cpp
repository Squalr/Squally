#include "ShopkeeperDialogueBehavior.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Events/DialogueEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/Dialogue/NpcInteractionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/LookAtSquallyBehavior.h"

#include "Strings/Platformer/Entities/Shopkeepers/HowDoIBuySomething.h"
#include "Strings/Platformer/Entities/Shopkeepers/HowToBuySomething.h"

using namespace cocos2d;

const std::string ShopkeeperDialogueBehavior::MapKeyAttachedBehavior = "shopkeeper";

ShopkeeperDialogueBehavior* ShopkeeperDialogueBehavior::create(GameObject* owner)
{
	ShopkeeperDialogueBehavior* instance = new ShopkeeperDialogueBehavior(owner);

	instance->autorelease();

	return instance;
}

ShopkeeperDialogueBehavior::ShopkeeperDialogueBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

ShopkeeperDialogueBehavior::~ShopkeeperDialogueBehavior()
{
}

void ShopkeeperDialogueBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});

	this->entity->watchForAttachedBehavior<NpcInteractionBehavior>([=](NpcInteractionBehavior* interactionBehavior)
	{
		interactionBehavior->addDialogueOption(NpcInteractionBehavior::DialogueOption(
			Strings::Platformer_Entities_Shopkeepers_HowDoIBuySomething::create(),
			[=]()
			{
				DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Entities_Shopkeepers_HowToBuySomething::create(),
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					[=]()
					{
					},
					DialogueEvents::BuildPreviewNode(this->entity, false),
					DialogueEvents::BuildPreviewNode(this->squally, true)
				));
			}),
			1.0f
		);
	});
}
