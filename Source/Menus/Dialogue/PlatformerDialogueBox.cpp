#include "PlatformerDialogueBox.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Events/DialogueEvents.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Common/Empty.h"
#include "Strings/Input/Spacebar.h"

using namespace cocos2d;

PlatformerDialogueBox* PlatformerDialogueBox::create()
{
	PlatformerDialogueBox* instance = new PlatformerDialogueBox();

	instance->autorelease();

	return instance;
}

PlatformerDialogueBox::PlatformerDialogueBox() : super(1024.0f)
{
	LocalizedString* bracketString = Strings::Common_Brackets::create();
	LocalizedString* spaceString = Strings::Input_Spacebar::create();

	bracketString->setStringReplacementVariables(spaceString);

	this->spaceToContinueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, bracketString);

	this->spaceToContinueLabel->setTextColor(DialogueBox::PanelTextColor);

	this->addChild(this->spaceToContinueLabel);
}

PlatformerDialogueBox::~PlatformerDialogueBox()
{
}

void PlatformerDialogueBox::initializePositions()
{
	super::initializePositions();
}

void PlatformerDialogueBox::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(DialogueEvents::EventDialogueOpen, [=](EventCustom* eventCustom)
	{
		DialogueEvents::DialogueOpenArgs* args = static_cast<DialogueEvents::DialogueOpenArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->runDialogue(args->dialogue);
		}
	}));
}

void PlatformerDialogueBox::runDialogue(LocalizedString* localizedString)
{
	super::runDialogue(localizedString);

	this->spaceToContinueLabel->runAction(FadeTo::create(0.5f, 255));
}

void PlatformerDialogueBox::hideDialogue()
{
	super::hideDialogue();
}
