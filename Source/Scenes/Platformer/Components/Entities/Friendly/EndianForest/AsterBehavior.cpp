#include "AsterBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AsterBehavior::MapKey = "aster";

AsterBehavior* AsterBehavior::create(GameObject* owner)
{
	AsterBehavior* instance = new AsterBehavior(owner);

	instance->autorelease();

	return instance;
}

AsterBehavior::AsterBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

AsterBehavior::~AsterBehavior()
{
}

void AsterBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyAsterItemGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_Misc_Jasper_A_Clever::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
				},
				Voices::GetNextVoiceShort(),
				false
			));
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_Misc_Jasper_B_TakeThis::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ SapphireBand::create() }));
					SaveManager::SaveProfileData(SaveKeys::SaveKeyAsterItemGiven, Value(true));
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});
	}
}

void AsterBehavior::onDisable()
{
	super::onDisable();
}
