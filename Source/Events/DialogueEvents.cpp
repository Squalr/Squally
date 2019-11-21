#include "DialogueEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"

using namespace cocos2d;

const std::string DialogueEvents::EventDialogueOpen = "EVENT_DIALOGUE_OPEN";
const std::string DialogueEvents::EventDialogueClose = "EVENT_DIALOGUE_CLOSE";

void DialogueEvents::TriggerDialogueOpen(DialogueOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DialogueEvents::EventDialogueOpen,
		&args
	);
}

void DialogueEvents::TriggerTryDialogueClose(DialogueCloseArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DialogueEvents::EventDialogueClose,
		&args
	);
}

Node* DialogueEvents::BuildPreviewNode(PlatformerEntity* entity, bool isFlipped)
{
	const float offsetY = -96.0f;

	if (entity == nullptr)
	{
		return nullptr;
	}

	Node* wrapper = Node::create();
	PlatformerEntity* softClone = entity->softClone();

	if (softClone != nullptr)
	{
		softClone->getAnimations()->setFlippedX(isFlipped);
		wrapper->addChild(softClone);
		softClone->setPosition(softClone->getDialogueOffset() + Vec2(0.0f, offsetY));
	}

	return wrapper;
}
