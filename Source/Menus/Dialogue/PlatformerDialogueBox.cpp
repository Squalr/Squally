#include "PlatformerDialogueBox.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"

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
	this->leftSpeakerNode = Node::create();
	this->rightSpeakerNode = Node::create();

	this->spaceToContinueLabel->setTextColor(DialogueBox::PanelTextColor);
	this->isDialogueFocused = false;

	this->contentNode->addChild(this->spaceToContinueLabel);
	this->contentNode->addChild(this->leftSpeakerNode);
	this->contentNode->addChild(this->rightSpeakerNode);
}

PlatformerDialogueBox::~PlatformerDialogueBox()
{
}

void PlatformerDialogueBox::initializePositions()
{
	super::initializePositions();

	this->spaceToContinueLabel->setPosition(Vec2(0.0f, -128.0f));
	this->leftSpeakerNode->setPosition(Vec2(-768.0f, -DialogueBox::DialogueHeight / 4.0f));
	this->rightSpeakerNode->setPosition(Vec2(768.0f, -DialogueBox::DialogueHeight / 4.0f));
}

void PlatformerDialogueBox::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(DialogueEvents::EventDialogueOpen, [=](EventCustom* eventCustom)
	{
		DialogueEvents::DialogueOpenArgs* args = static_cast<DialogueEvents::DialogueOpenArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			DialogueAlignment dialogueAlignment = DialogueAlignment::Center;

			switch(args->dialogueAlignment)
			{
				default:
				case DialogueEvents::DialogueAlignment::Center:
				{
					dialogueAlignment = DialogueAlignment::Center;
					break;
				}
				case DialogueEvents::DialogueAlignment::Left:
				{
					dialogueAlignment = DialogueAlignment::Left;
					break;
				}
				case DialogueEvents::DialogueAlignment::Right:
				{
					dialogueAlignment = DialogueAlignment::Right;
					break;
				}
			}

			this->leftSpeakerNode->removeAllChildren();
			this->rightSpeakerNode->removeAllChildren();

			if (args->leftContentNode != nullptr)
			{
				this->leftSpeakerNode->addChild(args->leftContentNode);
			}

			if (args->rightContentNode != nullptr)
			{
				this->rightSpeakerNode->addChild(args->rightContentNode);
			}

			this->runDialogue(args->dialogue, dialogueAlignment, args->onDialogueClose);
		}
	}));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](InputEvents::InputArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused)
		{
			args->handle();

			this->hideDialogue();
		}
	});
}

void PlatformerDialogueBox::runDialogue(LocalizedString* localizedString, DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose)
{
	super::runDialogue(localizedString, dialogueAlignment, onDialogueClose);

	PlatformerEvents::TriggerCinematicHijack();
	this->isDialogueFocused = true;

	this->spaceToContinueLabel->runAction(FadeTo::create(0.25f, 0));
}

void PlatformerDialogueBox::hideDialogue()
{
	super::hideDialogue();

	PlatformerEvents::TriggerCinematicRestore();
	this->isDialogueFocused = false;
}

void PlatformerDialogueBox::onTypeWriterEffectComplete()
{
	super::onTypeWriterEffectComplete();

	this->spaceToContinueLabel->runAction(FadeTo::create(0.25f, 255));
}
