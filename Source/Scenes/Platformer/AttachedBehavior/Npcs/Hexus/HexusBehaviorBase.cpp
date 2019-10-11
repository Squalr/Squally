#include "HexusBehaviorBase.h"

#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HexusEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/Dialogue/NpcDialogueBehavior.h"

#include "Resources/EntityResources.h"

#include "Strings/Hexus/Hexus.h"
#include "Strings/Platformer/Entities/HowAboutARoundOfHexus.h"

using namespace cocos2d;

HexusBehaviorBase::HexusBehaviorBase(GameObject* owner, LocalizedString* dialogueChoiceOverride) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->dialogueChoiceOverride = dialogueChoiceOverride;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	if (this->dialogueChoiceOverride != nullptr)
	{
		this->addChild(this->dialogueChoiceOverride);
	}
}

HexusBehaviorBase::~HexusBehaviorBase()
{
}

void HexusBehaviorBase::onLoad()
{
	this->entity->watchForAttachedBehavior<NpcDialogueBehavior>([=](NpcDialogueBehavior* interactionBehavior)
	{
		if (this->dialogueChoiceOverride != nullptr)
		{
			interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				this->dialogueChoiceOverride->clone(),
				[=]()
				{
					HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
				}),
				0.5f
			);
		}
		else
		{
			interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				Strings::Platformer_Entities_HowAboutARoundOfHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
				[=]()
				{
					HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
				}),
				0.5f
			);
		}
	});
}

void HexusBehaviorBase::onWin()
{

}

void HexusBehaviorBase::onLoss()
{

}

void HexusBehaviorBase::onDraw()
{

}
