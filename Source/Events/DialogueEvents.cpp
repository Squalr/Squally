#include "DialogueEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"

using namespace cocos2d;

const std::string DialogueEvents::EventDialogueOpen = "EVENT_DIALOGUE_OPEN";
const std::string DialogueEvents::EventDialogueClose = "EVENT_DIALOGUE_CLOSE";

void DialogueEvents::TriggerOpenDialogue(DialogueOpenArgs args)
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
		PlatformerEntity** entityPtr = (PlatformerEntity**)(entity);

		if (entityPtr == nullptr || *entityPtr == nullptr)
		{
			return (Node*)nullptr;
		}

		Node* wrapper = Node::create();
		PlatformerEntity* uiClone = (*entityPtr)->uiClone();

		if (uiClone != nullptr)
		{
			uiClone->getAnimations()->setFlippedX(isFlipped);
			wrapper->addChild(uiClone);
			uiClone->setPosition(uiClone->getDialogueOffset() + Vec2(0.0f, offsetY));
		}

		return wrapper;
	};
}
