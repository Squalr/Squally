#include "RupertBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RupertBehavior::MapKey = "rupert";

RupertBehavior* RupertBehavior::create(GameObject* owner)
{
	RupertBehavior* instance = new RupertBehavior(owner);

	instance->autorelease();

	return instance;
}

RupertBehavior::RupertBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

RupertBehavior::~RupertBehavior()
{
}

void RupertBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Rupert_A_DoYouKnowAnything::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_UnderflowRuins_CureTown_Rupert_B_NothingIsReal::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->entity, true)
					),
					[=]()
					{
						DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
							Strings::Platformer_Quests_UnderflowRuins_CureTown_Rupert_C_NotVeryUseful::create(),
							DialogueEvents::DialogueVisualArgs(
								DialogueBox::DialogueDock::Bottom,
								DialogueBox::DialogueAlignment::Right,
								DialogueEvents::BuildPreviewNode(&this->squally, false),
								DialogueEvents::BuildPreviewNode(&this->scrappy, true)
							),
							[=]()
							{
							},
							Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
							true
						));
					},
					Voices::GetNextVoiceShort(),
					false
				));
			}),
			0.5f
		);
	});
}

void RupertBehavior::onDisable()
{
	super::onDisable();
}
