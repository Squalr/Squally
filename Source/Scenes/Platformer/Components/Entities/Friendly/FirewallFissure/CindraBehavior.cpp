#include "CindraBehavior.h"

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

const std::string CindraBehavior::MapKey = "cindra";

CindraBehavior* CindraBehavior::create(GameObject* owner)
{
	CindraBehavior* instance = new CindraBehavior(owner);

	instance->autorelease();

	return instance;
}

CindraBehavior::CindraBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

CindraBehavior::~CindraBehavior()
{
}

void CindraBehavior::onLoad()
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

void CindraBehavior::setPostText()
{
	this->defer([=]()
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySpellBookFire, Value(false)).asBool())
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_FirewallFissure_Spellbook_Cindra_A_Flame::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->entity, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
					},
					Voices::GetNextVoiceQuestion(),
					false
				));
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_FirewallFissure_Spellbook_Cindra_B_TakeThis::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->entity, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
						SaveManager::SaveProfileData(SaveKeys::SaveKeySpellBookFire, Value(true));
						HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
						
						NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
							Strings::Platformer_Spellbooks_SpellbookAcquired::create(),
							Strings::Platformer_Spellbooks_SpellbookOfFire::create(),
							ItemResources::Spellbooks_SpellBookFire,
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
					Strings::Platformer_Quests_FirewallFissure_Spellbook_Cindra_C_BestOfLuck::create(),
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

void CindraBehavior::onDisable()
{
	super::onDisable();
}
