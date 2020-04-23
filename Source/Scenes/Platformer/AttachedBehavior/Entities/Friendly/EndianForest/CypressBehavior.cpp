#include "CypressBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CypressBehavior::MapKey = "cypress";
const std::string CypressBehavior::SaveKeyItemGiven = "CYPRESS_ITEM_GIVEN";

CypressBehavior* CypressBehavior::create(GameObject* owner)
{
	CypressBehavior* instance = new CypressBehavior(owner);

	instance->autorelease();

	return instance;
}

CypressBehavior::CypressBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

CypressBehavior::~CypressBehavior()
{
}

void CypressBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	if (!this->entity->getObjectStateOrDefault(CypressBehavior::SaveKeyItemGiven, Value(false)).asBool())
	{
		this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_Misc_Cypress_A_Clever::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
				},
				SoundResources::Platformer_Entities_Generic_ChatterShort1,
				false
			));
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_Misc_Cypress_B_TakeThis::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					PlatformerEvents::TriggerGiveItem(PlatformerEvents::GiveItemArgs(SapphireBand::create()));
					this->entity->saveObjectState(CypressBehavior::SaveKeyItemGiven, Value(true));
				},
				SoundResources::Platformer_Entities_Generic_ChatterMedium1,
				true
			));
		});
	}
}

void CypressBehavior::onDisable()
{
	super::onDisable();
}
