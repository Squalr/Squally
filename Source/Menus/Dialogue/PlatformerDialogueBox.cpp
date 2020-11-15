#include "PlatformerDialogueBox.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Sound/Sound.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"

#include "Strings/Strings.h"

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
	this->inputOptions = std::vector<std::function<bool()>>();
	this->inputCancel = nullptr;

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

	this->unhijack = true;
	this->allowSpace = false;

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
			this->inputOptions = args->inputOptions;
			this->inputCancel = args->inputCancel;
			this->leftSpeakerNode->removeAllChildren();
			this->rightSpeakerNode->removeAllChildren();

			if (args->visualArgs.leftContentNode != nullptr)
			{
				Node* content = args->visualArgs.leftContentNode();
				
				if (content != nullptr)
				{
					this->leftSpeakerNode->addChild(content);
				}
			}

			if (args->visualArgs.rightContentNode != nullptr)
			{
				Node* content = args->visualArgs.rightContentNode();

				if (content != nullptr)
				{
					this->rightSpeakerNode->addChild(content);
				}
			}

			if (args->visualArgs.bigFont)
			{
				this->text->setFontSize(LocalizedLabel::FontSize::M1);
			}
			else
			{
				this->text->setFontSize(LocalizedLabel::FontSize::H3);
			}

			if (!args->soundResource.empty())
			{
				Sound* sound = Sound::create(args->soundResource);

				this->leftSpeakerNode->addChild(sound);

				sound->play();
			}

			this->runDialogue(args->dialogue, args->visualArgs.dialogueDock, args->visualArgs.dialogueAlignment, args->onDialogueClose, args->allowSpace, args->unhijack);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(DialogueEvents::EventDialogueClose, [=](EventCustom* eventCustom)
	{
		DialogueEvents::DialogueCloseArgs* args = static_cast<DialogueEvents::DialogueCloseArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			if (this->isDialogueEffectComplete() && this->isDialogueFocused)
			{
				this->hideDialogue();

				if (args->onCloseCallback != nullptr)
				{
					args->onCloseCallback();
				}
			}
		}
	}));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](KeyboardEventArgs* args)
	{
		if (this->allowSpace && this->isDialogueEffectComplete() && this->isDialogueFocused)
		{
			args->handle();

			this->hideDialogue();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_TAB }, [=](KeyboardEventArgs* args)
	{
		if (this->allowSpace && this->isDialogueEffectComplete() && this->isDialogueFocused)
		{
			args->handle();

			// Allow tab-cancel dialogue into hacker mode
			this->hideDialogue();
			HackableEvents::TriggerForceUseHackerMode();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_1 }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused && this->chooseOption(1))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_2 }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused && this->chooseOption(2))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_3 }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused && this->chooseOption(3))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_4 }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused && this->chooseOption(4))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_5 }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused && this->chooseOption(5))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_6 }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused && this->chooseOption(6))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_7 }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused && this->chooseOption(7))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_8 }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused && this->chooseOption(8))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_9 }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueEffectComplete() && this->isDialogueFocused && this->chooseOption(9))
		{
			args->handle();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_BACK, EventKeyboard::KeyCode::KEY_ESCAPE }, [=](KeyboardEventArgs* args)
	{
		if (this->isDialogueFocused && this->cancelOptionChoice())
		{
			this->hideDialogue();
			args->handle();
		}
	});
}

void PlatformerDialogueBox::runDialogue(LocalizedString* localizedString, DialogueDock dialogueDock, DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose, bool allowSpace, bool unhijack)
{
	this->spaceToContinueLabel->runAction(FadeTo::create(0.25f, 0));

	super::runDialogue(localizedString, dialogueDock, dialogueAlignment, onDialogueClose);

	this->allowSpace = allowSpace;
	this->unhijack = unhijack;

	PlatformerEvents::TriggerCinematicHijack();
	this->isDialogueFocused = true;
}

void PlatformerDialogueBox::hideDialogue()
{
	if (this->unhijack)
	{
		PlatformerEvents::TriggerCinematicRestore();
	}

	this->isDialogueFocused = false;
	
	super::hideDialogue();
}

bool PlatformerDialogueBox::chooseOption(int index)
{
	index--;

	if (index >= 0 && index < int(this->inputOptions.size()) && this->inputOptions[index] != nullptr)
	{
		auto callback = this->inputOptions[index];

		this->hideDialogue();
		
		return callback();
	}

	return false;
}

bool PlatformerDialogueBox::cancelOptionChoice()
{
	if (inputCancel != nullptr)
	{
		return inputCancel();
	}

	return false;
}

void PlatformerDialogueBox::onTypeWriterEffectComplete()
{
	super::onTypeWriterEffectComplete();

	if (this->allowSpace)
	{
		this->spaceToContinueLabel->runAction(FadeTo::create(0.25f, 255));
	}
}
