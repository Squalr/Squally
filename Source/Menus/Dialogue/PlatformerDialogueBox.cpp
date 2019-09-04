#include "PlatformerDialogueBox.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Common/Empty.h"
#include "Strings/Input/Spacebar.h"

using namespace cocos2d;

const Color4F PlatformerDialogueBox::SpeakerBackgroundColor = Color4F(Color4B(24, 101, 113, 127));
const float PlatformerDialogueBox::TextWidth = 920.0f;
const float PlatformerDialogueBox::SpeakerPanelWidth = 272.0f;
const float PlatformerDialogueBox::SpeakerPanelOffset = 768.0f;

PlatformerDialogueBox* PlatformerDialogueBox::create()
{
	PlatformerDialogueBox* instance = new PlatformerDialogueBox();

	instance->autorelease();

	return instance;
}

PlatformerDialogueBox::PlatformerDialogueBox() : super(PlatformerDialogueBox::TextWidth, PlatformerDialogueBox::SpeakerPanelOffset, PlatformerDialogueBox::SpeakerPanelWidth)
{
	LocalizedString* bracketString = Strings::Common_Brackets::create();
	LocalizedString* spaceString = Strings::Input_Spacebar::create();

	bracketString->setStringReplacementVariables(spaceString);

	Rect speakerRect = Rect(-PlatformerDialogueBox::SpeakerPanelWidth / 2.0f, -DialogueBox::DialogueHeight / 2.0f, PlatformerDialogueBox::SpeakerPanelWidth, DialogueBox::DialogueHeight);

	this->spaceToContinueLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, bracketString);
	this->leftSpeakerNode = Node::create();
	this->rightSpeakerNode = Node::create();
	this->leftSpeakerBackground = DrawNode::create();
	this->rightSpeakerBackground = DrawNode::create();
	this->leftSpeakerClip = SmartClippingNode::create(this->leftSpeakerBackground, speakerRect);
	this->rightSpeakerClip = SmartClippingNode::create(this->rightSpeakerBackground, speakerRect);

	this->leftSpeakerBackground->drawSolidRect(speakerRect.origin, speakerRect.size, PlatformerDialogueBox::SpeakerBackgroundColor);
	this->rightSpeakerBackground->drawSolidRect(speakerRect.origin, speakerRect.size, PlatformerDialogueBox::SpeakerBackgroundColor);
	this->spaceToContinueLabel->setTextColor(DialogueBox::PanelTextColor);
	this->isDialogueFocused = false;

	this->leftSpeakerBackground->addChild(this->leftSpeakerNode);
	this->rightSpeakerBackground->addChild(this->rightSpeakerNode);
	this->contentNode->addChild(this->spaceToContinueLabel);
	this->contentNode->addChild(this->leftSpeakerClip);
	this->contentNode->addChild(this->rightSpeakerClip);
}

PlatformerDialogueBox::~PlatformerDialogueBox()
{
}

void PlatformerDialogueBox::initializePositions()
{
	super::initializePositions();

	this->spaceToContinueLabel->setPosition(Vec2(0.0f, -128.0f));
	this->leftSpeakerClip->setPosition(Vec2(-PlatformerDialogueBox::SpeakerPanelOffset, 0.0f));
	this->rightSpeakerClip->setPosition(Vec2(PlatformerDialogueBox::SpeakerPanelOffset, 0.0f));
}

void PlatformerDialogueBox::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(DialogueEvents::EventDialogueOpen, [=](EventCustom* eventCustom)
	{
		DialogueEvents::DialogueOpenArgs* args = static_cast<DialogueEvents::DialogueOpenArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
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

			this->runDialogue(args->dialogue, args->dialogueDock, args->dialogueAlignment, args->onDialogueClose);
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

void PlatformerDialogueBox::runDialogue(LocalizedString* localizedString, DialogueDock dialogueDock, DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose)
{
	super::runDialogue(localizedString, dialogueDock, dialogueAlignment, onDialogueClose);

	PlatformerEvents::TriggerCinematicHijack();
	this->isDialogueFocused = true;

	this->spaceToContinueLabel->runAction(FadeTo::create(0.25f, 0));
}

void PlatformerDialogueBox::hideDialogue()
{
	PlatformerEvents::TriggerCinematicRestore();

	this->isDialogueFocused = false;
	
	super::hideDialogue();
}

void PlatformerDialogueBox::onTypeWriterEffectComplete()
{
	super::onTypeWriterEffectComplete();

	this->spaceToContinueLabel->runAction(FadeTo::create(0.25f, 255));
}
