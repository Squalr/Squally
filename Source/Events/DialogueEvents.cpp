#include "DialogueEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Strings/Strings.h"

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

LocalizedString* DialogueEvents::BuildOptions(LocalizedString* intro, std::vector<LocalizedString*> optionList)
{
	LocalizedString* options = Strings::Common_Triconcat::create();
	LocalizedString* prelude = intro == nullptr ? nullptr : Strings::Common_Triconcat::create()
		->setStringReplacementVariables({intro, Strings::Common_Newline::create(), options });
	LocalizedString* currentOption = options;
	int index = 1;

	for (auto it = optionList.begin(); it != optionList.end(); it++, index++)
	{
		bool lastIter = it == (--optionList.end());
		LocalizedString* option = *it;
		LocalizedString* nextOption = lastIter ? (LocalizedString*)Strings::Common_Empty::create() : (LocalizedString*)Strings::Common_Triconcat::create();

		LocalizedString* dash = Strings::Common_Dash::create();
		LocalizedString* brackets = Strings::Common_Brackets::create();

		brackets->setStringReplacementVariables(ConstantString::create(std::to_string(index)));

		dash->setStringReplacementVariables({ brackets, option });

		currentOption->setStringReplacementVariables({ dash, Strings::Common_Newline::create(), nextOption });
		currentOption = nextOption;
	}

	return prelude != nullptr ? prelude : options;
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
