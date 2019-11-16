#include "ShopkeeperDialogueBehavior.h"

#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Events/DialogueEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/LookAtSquallyBehavior.h"

#include "Resources/SoundResources.h"

#include "Strings/Platformer/Dialogue/Shopkeepers/HowDoIBuySomething.h"
#include "Strings/Platformer/Dialogue/Shopkeepers/HowToBuySomething.h"

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
	}, Squally::MapKeySqually);

	this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Dialogue_Shopkeepers_HowDoIBuySomething::create(),
			[=]()
			{
				DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Dialogue_Shopkeepers_HowToBuySomething::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(this->entity, false),
						DialogueEvents::BuildPreviewNode(this->squally, true)
					),
					[=]()
					{
					},
					SoundResources::Platformer_Entities_Generic_ChatterQuestion1
				));
			}),
			1.0f
		);
	});
}
