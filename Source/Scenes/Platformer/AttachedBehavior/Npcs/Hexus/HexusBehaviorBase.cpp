#include "HexusBehaviorBase.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HexusEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/Dialogue/NpcInteractionBehavior.h"

#include "Resources/EntityResources.h"

#include "Strings/Hexus/Hexus.h"
#include "Strings/Platformer/Entities/HowAboutARoundOfHexus.h"

using namespace cocos2d;

HexusBehaviorBase::HexusBehaviorBase(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

HexusBehaviorBase::~HexusBehaviorBase()
{
}

void HexusBehaviorBase::onLoad()
{
	this->entity->watchForAttachedBehavior<NpcInteractionBehavior>([=](NpcInteractionBehavior* interactionBehavior)
	{
		LocalizedString* hexusDialogue = Strings::Platformer_Entities_HowAboutARoundOfHexus::create();
		LocalizedString* hexus = Strings::Hexus_Hexus::create();

		hexusDialogue->setStringReplacementVariables(hexus);

		interactionBehavior->addDialogueOption(NpcInteractionBehavior::DialogueOption(
			hexusDialogue,
			[=]()
			{
				HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
			}),
			0.5f
		);
	});
}
