#include "RakaBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Interactables/Doors/Mayan/MayanDoor.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RakaBehavior::MapKey = "raka";

RakaBehavior* RakaBehavior::create(GameObject* owner)
{
	RakaBehavior* instance = new RakaBehavior(owner);

	instance->autorelease();

	return instance;
}

RakaBehavior::RakaBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

RakaBehavior::~RakaBehavior()
{
}

void RakaBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<MayanDoor>(this, [=](MayanDoor* mayanDoor)
	{
		this->mayanDoor = mayanDoor;

		this->defer([=]()
		{
			if (!this->mayanDoor->getIsLocked())
			{
				this->removeDialogueOption();
			}
		});
	}, MayanDoor::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		this->dialogueOption = DialogueOption::create(
			Strings::Platformer_Quests_DataMines_StackPuzzle_A_DoYouKnowHowToOpenDoor::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_DataMines_StackPuzzle_B_NumbersMatch::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->entity, true)
					),
					[=]()
					{
					},
					Voices::GetNextVoiceLong(),
					true
				));
			}),

		interactionBehavior->getMainDialogueSet()->addDialogueOption(this->dialogueOption, 1.0f);
	});

	this->entity->listenForMapEvent(MayanDoor::MapEventPuzzleComplete, [=](ValueMap args)
	{
		this->removeDialogueOption();
	});
}

void RakaBehavior::onDisable()
{
	super::onDisable();
}

void RakaBehavior::removeDialogueOption()
{
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->removeDialogueOption(this->dialogueOption);
		this->dialogueOption = nullptr;
	});
}
