#include "HexusPuzzleBehaviorBase.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Engine/Events/ObjectEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

HexusPuzzleBehaviorBase::HexusPuzzleBehaviorBase(GameObject* owner, std::string voiceResource, LocalizedString* dialogueChoiceOverride) : super(owner, voiceResource, true, dialogueChoiceOverride)
{
	this->squally = nullptr;
}

HexusPuzzleBehaviorBase::~HexusPuzzleBehaviorBase()
{
}

void HexusPuzzleBehaviorBase::onEnter()
{
	super::onEnter();

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Dialogue_Hexus_PuzzleForYou::create(),
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
	});
}

LocalizedString* HexusPuzzleBehaviorBase::getCustomWinDialogue()
{
	return Strings::Platformer_Dialogue_Hexus_GoodGameZalgo::create();
}

LocalizedString* HexusPuzzleBehaviorBase::getCustomDrawDialogue()
{
	return Strings::Platformer_Dialogue_Hexus_ADrawZalgo::create();
}

LocalizedString* HexusPuzzleBehaviorBase::getCustomLossDialogue()
{
	// TODO: Reinstate zalgo text when microsoft fixes their shit
	return Strings::Platformer_Dialogue_Hexus_BetterLuckNextTime::create();
}
