#include "HexusBehaviorBase.h"

#include "Engine/Localization/ConstantString.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/Dialogue/NpcInteractionBehavior.h"

#include "Resources/EntityResources.h"

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
		interactionBehavior->addDialogueOption(NpcInteractionBehavior::DialogueOption(
			ConstantString::create("How about a round of Hexus?"),
			[=]()
			{

			}),
			0.5f
		);
	});
}
