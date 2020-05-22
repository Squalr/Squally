#include "DialogueBox.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/FX/TypeWriterEffect.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const Color4F DialogueBox::PanelColor = Color4F(Color4B(189, 215, 221, 196));
const Color4F DialogueBox::PanelEdgeColor = Color4F(Color4B(47, 71, 78, 196));
const Color4B DialogueBox::PanelTextColor = Color4B(47, 71, 78, 255);
const float DialogueBox::PanelBorderSize = 3.0f;
const float DialogueBox::DialogueHeight = 320.0f;

DialogueBox::DialogueBox(float textWidth, float speakerOffset, float speakerWidth)
{
	this->containerNode = Node::create();
	this->panel = DrawNode::create(3.0f);
	this->text = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Empty::create());
	this->contentNode = Node::create();
	this->onDialogueClose = std::function<void()>();
	this->dialogueEffectComplete = false;
	this->textWidth = textWidth;
	this->speakerOffset = speakerOffset;
	this->speakerWidth = speakerWidth;

	this->text->setTextColor(DialogueBox::PanelTextColor);

	const Size visibleSize = Director::getInstance()->getVisibleSize();
	const Size dialogueSize = Size(visibleSize.width - 64.0f, DialogueBox::DialogueHeight);
	const Vec2 halfSize = Vec2(dialogueSize.width / 2.0f, dialogueSize.height / 2.0f);

	this->panel->drawSolidRect(-halfSize, halfSize, DialogueBox::PanelColor);
	this->panel->drawRect(-halfSize, halfSize, DialogueBox::PanelEdgeColor);

	this->panel->setOpacity(0);
	this->text->setOpacity(0);
	this->contentNode->setOpacity(0);

	this->containerNode->addChild(this->panel);
	this->containerNode->addChild(this->text);
	this->containerNode->addChild(this->contentNode);
	this->addChild(this->containerNode);
}

DialogueBox::~DialogueBox()
{
}

void DialogueBox::initializePositions()
{
	super::initializePositions();
}

void DialogueBox::initializeListeners()
{
	super::initializeListeners();
}

void DialogueBox::runDialogue(LocalizedString* localizedString, DialogueDock dialogueDock, DialogueAlignment dialogueAlignment, std::function<void()> onDialogueClose)
{
	this->dialogueEffectComplete = false;

	TypeWriterEffect::cancelEffect(this->text);
	this->text->setLocalizedString(localizedString);

	this->panel->runAction(FadeTo::create(0.25f, 255));
	this->text->runAction(FadeTo::create(0.25f, 255));
	this->contentNode->runAction(FadeTo::create(0.25f, 255));

	switch(dialogueDock)
	{
		default:
		case DialogueDock::Top:
		{
			this->containerNode->setPosition(Vec2(0.0f, 720.0f));
			break;
		}
		case DialogueDock::Bottom:
		{
			this->containerNode->setPosition(Vec2::ZERO);
			break;
		}
	}

	this->text->setDimensions(this->textWidth, 0.0f);
	this->onDialogueClose = onDialogueClose;

	// Math on this is wrong, but I don't have time to worry about this bs. If the constants change, this might break.
	float distanceToMargin = (this->speakerOffset + this->speakerWidth / 2.0f - this->textWidth / 2.0f) / 2.0f - 80.0f;

	switch(dialogueAlignment)
	{
		default:
		case DialogueAlignment::Center:
		{
			this->text->setHorizontalAlignment(TextHAlignment::CENTER);
			this->text->setAnchorPoint(Vec2(0.5f, 1.0f));
			this->text->setPosition(Vec2(0.0f, DialogueBox::DialogueHeight / 2.0f - 96.0f));
			break;
		}
		case DialogueAlignment::Left:
		{
			this->text->setHorizontalAlignment(TextHAlignment::LEFT);
			this->text->setAnchorPoint(Vec2(0.0f, 1.0f));
			this->text->setPosition(Vec2(-this->textWidth / 2.0f - distanceToMargin, DialogueBox::DialogueHeight / 2.0f - 96.0f));
			break;
		}
		case DialogueAlignment::Right:
		{
			// Left align if multi-line. This ends up looking cleaner.
			if (this->text->getContentSize().height > this->text->getLineHeight())
			{
				this->text->setHorizontalAlignment(TextHAlignment::LEFT);
			}
			else
			{
				this->text->setHorizontalAlignment(TextHAlignment::RIGHT);
			}

			this->text->setAnchorPoint(Vec2(1.0f, 1.0f));
			this->text->setPosition(Vec2(this->textWidth / 2.0f + distanceToMargin, DialogueBox::DialogueHeight / 2.0f - 96.0f));
			break;
		}
	}

	TypeWriterEffect::cancelEffect(this->text);
	TypeWriterEffect::runTypeWriterEffect(this, this->text, [=]() { this->onTypeWriterEffectComplete(); });
}

void DialogueBox::hideDialogue()
{
	this->panel->runAction(FadeTo::create(0.25f, 0));
	this->text->runAction(FadeTo::create(0.25f, 0));
	this->contentNode->runAction(FadeTo::create(0.25f, 0));

	if (this->onDialogueClose != nullptr)
	{
		this->onDialogueClose();
	}
}

void DialogueBox::onTypeWriterEffectComplete()
{
	this->dialogueEffectComplete = true;
}

bool DialogueBox::isDialogueEffectComplete()
{
	return this->dialogueEffectComplete;
}
