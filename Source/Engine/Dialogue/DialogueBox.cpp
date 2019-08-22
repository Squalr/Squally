#include "DialogueBox.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/UI/FX/TypeWriterEffect.h"

#include "Strings/Common/Empty.h"

using namespace cocos2d;

const Color4F DialogueBox::PanelColor = Color4F(Color4B(189, 215, 221, 196));
const Color4F DialogueBox::PanelEdgeColor = Color4F(Color4B(47, 71, 78, 196));
const Color4B DialogueBox::PanelTextColor = Color4B(47, 71, 78, 255);
const float DialogueBox::PanelBorderSize = 3.0f;

DialogueBox::DialogueBox(float textWidth)
{
	this->panel = DrawNode::create(3.0f);
	this->text = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Empty::create());
	this->contentNode = Node::create();
	this->onDialogueClose = std::function<void()>();
	this->dialogueEffectComplete = false;

	this->text->setTextColor(DialogueBox::PanelTextColor);

	const Size visibleSize = Director::getInstance()->getVisibleSize();
	const Size dialogueSize = Size(visibleSize.width - 64.0f, 320.0f);
	const Vec2 halfSize = Vec2(dialogueSize.width / 2.0f, dialogueSize.height / 2.0f);

	this->panel->drawSolidRect(-halfSize, halfSize, DialogueBox::PanelColor);
	this->panel->drawRect(-halfSize, halfSize, DialogueBox::PanelEdgeColor);
	this->text->setDimensions(textWidth, 0.0f);
	this->text->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->panel->setOpacity(0);

	this->panel->addChild(this->text);
	this->addChild(this->panel);
	this->addChild(this->contentNode);
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

void DialogueBox::runDialogue(LocalizedString* localizedString, std::function<void()> onDialogueClose)
{
	this->dialogueEffectComplete = false;

	this->panel->runAction(FadeTo::create(0.5f, 255));
	this->text->runAction(FadeTo::create(0.5f, 255));
	this->contentNode->runAction(FadeTo::create(0.5f, 255));

	this->text->setLocalizedString(localizedString);
	this->onDialogueClose = onDialogueClose;

	TypeWriterEffect::runTypeWriterEffect(this->text, [=]() { this->onTypeWriterEffectComplete(); });
}

void DialogueBox::hideDialogue()
{
	this->panel->runAction(FadeTo::create(0.5f, 0));
	this->text->runAction(FadeTo::create(0.5f, 0));
	this->contentNode->runAction(FadeTo::create(0.5f, 0));

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
