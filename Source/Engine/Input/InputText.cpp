#include "InputText.h"

#include "cocos/2d/CCNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/Controls/MenuLabel.h"

#include "Strings/Generics/Newline.h"

using namespace cocos2d;
using namespace cocos2d::ui;


InputText* InputText::create(LocalizedLabel* referenceContentLabel)
{
	InputText* instance = new InputText(referenceContentLabel);

	instance->autorelease();

	return instance;
}

InputText::InputText(LocalizedLabel* referenceContentLabel)
{
}

void InputText::onEnter()
{
	super::onEnter();
}

void InputText::initializePositions()
{
	super::initializePositions();
}

void InputText::initializeListeners()
{
	super::initializeListeners();
}
