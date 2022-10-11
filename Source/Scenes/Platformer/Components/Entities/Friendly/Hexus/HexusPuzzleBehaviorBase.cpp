#include "HexusPuzzleBehaviorBase.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Engine/Events/ObjectEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

HexusPuzzleBehaviorBase::HexusPuzzleBehaviorBase(GameObject* owner, std::string voiceResource, LocalizedString* dialogueChoiceOverride) : super(owner, voiceResource, dialogueChoiceOverride)
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

	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Dialogue_Hexus_PuzzleForYouZalgo::create()->setOverrideMap(
				{
					{ LanguageType::KOREAN, LanguageType::ENGLISH },
					{ LanguageType::JAPANESE, LanguageType::ENGLISH },
					{ LanguageType::THAI, LanguageType::ENGLISH },
					{ LanguageType::CHINESE_SIMPLIFIED, LanguageType::ENGLISH },
					{ LanguageType::CHINESE_TRADITIONAL, LanguageType::ENGLISH },
				}
			),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->entity, true)
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
	return  nullptr; //Strings::Platformer_Dialogue_Hexus_GoodGameZalgo::create();
}

LocalizedString* HexusPuzzleBehaviorBase::getCustomDrawDialogue()
{
	return  nullptr; //Strings::Platformer_Dialogue_Hexus_ADrawZalgo::create();
}

LocalizedString* HexusPuzzleBehaviorBase::getCustomLossDialogue()
{
	return nullptr; // Strings::Platformer_Dialogue_Hexus_BetterLuckNextTimeZalgo::create();
}
