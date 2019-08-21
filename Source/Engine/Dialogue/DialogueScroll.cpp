#include "DialogueScroll.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/FX/TypeWriterEffect.h"

#include "Strings/Common/Empty.h"

using namespace cocos2d;

const Color4F DialogueScroll::PanelColor = Color4F(Color4B(189, 215, 221, 196));
const Color4F DialogueScroll::PanelEdgeColor = Color4F(Color4B(47, 71, 78, 196));
const Color4B DialogueScroll::PanelTextColor = Color4B(47, 71, 78, 255);
const float DialogueScroll::PanelBorderSize = 3.0f;

DialogueScroll* DialogueScroll::create()
{
	DialogueScroll* instance = new DialogueScroll();

	instance->autorelease();

	return instance;
}

DialogueScroll::DialogueScroll()
{
	this->panel = DrawNode::create(3.0f);
	this->text = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Common_Empty::create());

	this->text->setTextColor(DialogueScroll::PanelTextColor);

	this->panel->setOpacity(0);
	this->text->setOpacity(0);

	this->addChild(this->panel);
	this->addChild(this->text);
}

DialogueScroll::~DialogueScroll()
{
}

void DialogueScroll::initializePositions()
{
	super::initializePositions();
}

void DialogueScroll::initializeListeners()
{
	super::initializeListeners();
}

void DialogueScroll::runDialogue(LocalizedString* localizedString)
{
	const Size padding = Size(16.0f, 16.0f);
	const float centerAutoOffset = 256.0f;
	const Size triangleSize = Size(16.0f, 32.0f);

	this->panel->runAction(FadeTo::create(0.5f, 255));
	this->text->runAction(FadeTo::create(0.5f, 255));

	this->text->setLocalizedString(localizedString);
	this->text->setDimensions(1600.0f, 0.0f);
	this->text->setAnchorPoint(Vec2(0.5f, 0.0f));

	TypeWriterEffect::runTypeWriterEffect(this->text);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->panel->clear();
	this->panel->drawSolidRect(Vec2::ZERO, Vec2(visibleSize.width, 256.0f), DialogueScroll::PanelColor);
	this->panel->drawRect(Vec2::ZERO, Vec2(visibleSize.width, 256.0f), DialogueScroll::PanelEdgeColor);
}

void DialogueScroll::hideDialogue()
{
	this->panel->runAction(FadeTo::create(0.5f, 0));
	this->text->runAction(FadeTo::create(0.5f, 0));
}
