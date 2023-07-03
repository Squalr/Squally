#include "LycanBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/DropPools/EndianForest/RewardPoolLycan.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LycanBehavior::MapKey = "lycan";

LycanBehavior* LycanBehavior::create(GameObject* owner)
{
	LycanBehavior* instance = new LycanBehavior(owner);

	instance->autorelease();

	return instance;
}

LycanBehavior::LycanBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		ValueMap props = ValueMap();
		
		this->rewardPool = RewardPoolLycan::create(props);

		this->addChild(this->rewardPool);
	}
}

LycanBehavior::~LycanBehavior()
{
}

void LycanBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	this->entity->getAnimations()->playAnimation("Sit", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(1.0f));

	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Save key for wind spellbook is a good proxy for whether or not Elriel was rescued. Just use that flag since it's easier to access.
		if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySpellBookWind, Value(false)).asBool())
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_FindElriel_Lycan_A_Tired::create()
					->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create()),
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
		}
		else
		{
			// Elriel saved, add in some post completion dialogue
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_FindElriel_Lycan_X_GossipDone::create()
					->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create()),
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
		}
		
		if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyLycanItemGiven, Value(false)).asBool())
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_EndianForest_FindElriel_Lycan_B_TakeThis::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					PlatformerEvents::TriggerGiveItemsFromPool(PlatformerEvents::GiveItemsFromPoolArgs(this->rewardPool));
					SaveManager::SaveProfileData(SaveKeys::SaveKeyLycanItemGiven, Value(true));
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		}
	});
}

void LycanBehavior::onDisable()
{
	super::onDisable();
}
