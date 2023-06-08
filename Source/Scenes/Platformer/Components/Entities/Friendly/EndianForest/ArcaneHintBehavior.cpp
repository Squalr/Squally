#include "ArcaneHintBehavior.h"

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

const std::string ArcaneHintBehavior::MapKey = "arcane-hint";

ArcaneHintBehavior* ArcaneHintBehavior::create(GameObject* owner)
{
	ArcaneHintBehavior* instance = new ArcaneHintBehavior(owner);

	instance->autorelease();

	return instance;
}

ArcaneHintBehavior::ArcaneHintBehavior(GameObject* owner) : super(owner)
{
}

ArcaneHintBehavior::~ArcaneHintBehavior()
{
}

void ArcaneHintBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	this->owner->listenForMapEventOnce(ArcaneHintBehavior::MapKey, [=](ValueMap)
	{
		if (!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyArcaneHint, Value(false)).asBool() &&
			!SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeySpellBookArcane, Value(false)).asBool())
		{
			this->runCinematicSequencePt1();
		}
	});
}

void ArcaneHintBehavior::onDisable()
{
	super::onDisable();
}

void ArcaneHintBehavior::runCinematicSequencePt1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_Misc_ArcaneMagic_A_Guarded::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceQuestion(Voices::VoiceType::Droid),
		true
	));
}

void ArcaneHintBehavior::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Ellipses::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true),
			true
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		"",
		true
	));
}

void ArcaneHintBehavior::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_Misc_ArcaneMagic_B_ThoughtNot::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			SaveManager::SaveProfileData(SaveKeys::SaveKeyArcaneHint, Value(true));
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		true
	));
}
