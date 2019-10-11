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

void DialogueEvents::TriggerDialogueClose()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		DialogueEvents::EventDialogueClose
	);
}

Node* DialogueEvents::BuildPreviewNode(PlatformerEntity* entity, bool isFlipped)
{
	if (entity == nullptr)
	{
		return nullptr;
	}

	Node* wrapper = Node::create();
	SmartAnimationNode* animations = SmartAnimationNode::create(entity->getAnimationResource());

	animations->playAnimation();
	animations->setFlippedX(isFlipped);
	animations->setPosition(entity->getDialogueOffset() - Vec2(0.0f, entity->getEntitySize().height / 2.0f));
	animations->setScale(entity->getScale());

	wrapper->addChild(animations);

	return wrapper;
}
