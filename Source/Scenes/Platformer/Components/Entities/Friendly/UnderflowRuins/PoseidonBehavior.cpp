#include "PoseidonBehavior.h"

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

const std::string PoseidonBehavior::MapKey = "poseidon";

PoseidonBehavior* PoseidonBehavior::create(GameObject* owner)
{
	PoseidonBehavior* instance = new PoseidonBehavior(owner);

	instance->autorelease();

	return instance;
}

PoseidonBehavior::PoseidonBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

PoseidonBehavior::~PoseidonBehavior()
{
}

void PoseidonBehavior::onLoad()
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
			Strings::Platformer_Quests_UnderflowRuins_CureTown_Poseidon_A_DoYouKnowAnything::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_UnderflowRuins_CureTown_Poseidon_B_FindMirror::create()
						->setStringReplacementVariables(Strings::Items_Misc_Keys_MedusasMirror::create()),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->entity, true)
					),
					[=]()
					{
					},
					Voices::GetNextVoiceShort(),
					true
				));
			}),
			0.5f
		);
	});
}

void PoseidonBehavior::onDisable()
{
	super::onDisable();
}
