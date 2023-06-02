#include "CypressBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/HexusResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CypressBehavior::MapKey = "cypress";

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

	this->setPostText();
}

void CypressBehavior::setPostText()
{
	this->defer([=]()
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySpellBookNature, Value(false)).asBool())
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::TODO::create(),
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
					Strings::TODO::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->entity, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
						SaveManager::SaveProfileData(SaveKeys::SaveKeySpellBookNature, Value(true));
						HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
						
						NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
							Strings::Platformer_Spellbooks_SpellbookAcquired::create(),
							Strings::Platformer_Spellbooks_SpellbookNature::create(),
							ItemResources::Spellbooks_SpellBookNature,
							SoundResources::Notifications_NotificationGood1
						));
						this->setPostText();
					},
					Voices::GetNextVoiceMedium(),
					true
				));
			}
			else
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::TODO::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->entity, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
						this->setPostText();
					},
					Voices::GetNextVoiceMedium(),
					true
				));
			}
		});
	});
}

void CypressBehavior::onDisable()
{
	super::onDisable();
}
