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

std::function<Node*()> DialogueEvents::BuildPreviewNode(void* entity, bool isFlipped)
{
	const float offsetY = -96.0f;

	return [=]()
	{
		if (entity == nullptr)
		{
			return (Node*)nullptr;
		}

		PlatformerEntity** entityPtr = static_cast<PlatformerEntity**>(entity);

		if (entityPtr == nullptr)
		{
			return (Node*)nullptr;
		}

		Node* wrapper = Node::create();
		PlatformerEntity* softClone = (*entityPtr)->softClone();

		if (softClone != nullptr)
		{
			softClone->getAnimations()->setFlippedX(isFlipped);
			wrapper->addChild(softClone);
			softClone->setPosition(softClone->getDialogueOffset() + Vec2(0.0f, offsetY));
		}

		return wrapper;
	};
}
