#include "EFURTransportationBehavior.h"

#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Events/DialogueEvents.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EFURTransportationBehavior::MapKeyAttachedBehavior = "ef-ur-transportation";
const std::string EFURTransportationBehavior::QuestTagBackPortal = "back-portal";
const std::string EFURTransportationBehavior::QuestTagLeavePortal = "leave-portal";

EFURTransportationBehavior* EFURTransportationBehavior::create(GameObject* owner)
{
	EFURTransportationBehavior* instance = new EFURTransportationBehavior(owner);

	instance->autorelease();

	return instance;
}

EFURTransportationBehavior::EFURTransportationBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
	this->innerChoices = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EFURTransportationBehavior::~EFURTransportationBehavior()
{
}

void EFURTransportationBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);

	ObjectEvents::watchForObject<Portal>(this, [=](Portal* portal)
	{
		this->backPortal = portal;
	}, EFURTransportationBehavior::QuestTagBackPortal);

	ObjectEvents::watchForObject<Portal>(this, [=](Portal* portal)
	{
		this->leavePortal = portal;
	}, EFURTransportationBehavior::QuestTagLeavePortal);

	this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		this->innerChoices = DialogueSet::create(DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->entity, true)
		));

		this->innerChoices->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Dialogue_Transportation_Yes::create(),
			[=]()
			{
				interactionBehavior->setActiveDialogueSet(interactionBehavior->getMainDialogueSet(), false);

				if (this->leavePortal != nullptr)
				{
					this->leavePortal->loadMap();
				}
			}),
			1.0f
		);

		innerChoices->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Dialogue_Transportation_No::create(),
			[=]()
			{
				interactionBehavior->setActiveDialogueSet(interactionBehavior->getMainDialogueSet(), false);
			}),
			0.9f
		);

		interactionBehavior->addDialogueSet(innerChoices);

		/*
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Dialogue_Transportation_AreWeThereYet::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Dialogue_Transportation_AreYouReady::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->scrappy, false),
						DialogueEvents::BuildPreviewNode(&this->entity, true)
					),
					[=]()
					{
						interactionBehavior->setActiveDialogueSet(innerChoices);
					},
					SoundResources::Platformer_Entities_Generic_ChatterQuestion1
				));
			}),
			1.0f
		);
		*/

		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Dialogue_Transportation_IForgotSomething::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Dialogue_Transportation_Seriously::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->scrappy, false),
						DialogueEvents::BuildPreviewNode(&this->entity, true)
					),
					[=]()
					{
						if (this->backPortal != nullptr)
						{
							this->backPortal->loadMap();
						}
					},
					SoundResources::Platformer_Entities_Generic_ChatterQuestion1
				));
			}),
			0.9f
		);
	});
}
