#include "LycanBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LycanBehavior::MapKeyAttachedBehavior = "lycan";

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
}

LycanBehavior::~LycanBehavior()
{
}

void LycanBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Entities_EndianForest_Lycan_LetMeIntoTown::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Entities_EndianForest_Lycan_NobodyAllowedIntoTown::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->entity, true)
					),
					[=]()
					{
					},
					SoundResources::Platformer_Entities_Generic_ChatterShort2,
					true
				));
			}),
			0.5f
		);
	});
}
