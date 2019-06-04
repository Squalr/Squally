#include "TextPanel.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/FX/TypeWriterEffect.h"

#include "Strings/Generics/Empty.h"

using namespace cocos2d;

const Color4F TextPanel::PanelColor = Color4F(Color4B(0, 0, 0, 196));
const Color4F TextPanel::PanelEdgeColor = Color4F(Color4B(0, 0, 0, 255));
const Color4B TextPanel::PanelTextColor = Color4B(255, 255, 255, 255);
const float TextPanel::PanelBorderSize = 3.0f;

TextPanel* TextPanel::create(LocalizedString* localizedString)
{
	TextPanel* instance = new TextPanel(localizedString);

	instance->autorelease();

	return instance;
}

TextPanel::TextPanel(LocalizedString* localizedString)
{
	this->panel = DrawNode::create(3.0f);
	this->text = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Generics_Empty::create());

	this->text->setLocalizedString(localizedString);
	this->text->setTextColor(TextPanel::PanelTextColor);

	this->panel->setOpacity(0);
	this->text->setOpacity(0);

	this->addChild(this->panel);
	this->addChild(this->text);
}

TextPanel::~TextPanel()
{
}

void TextPanel::initializePositions()
{
	super::initializePositions();
}

void TextPanel::initializeListeners()
{
	super::initializeListeners();
}

void TextPanel::show(float duration)
{
	const Size padding = Size(16.0f, 16.0f);

	if (duration <= 0.0f)
	{
		this->panel->setOpacity(255);
		this->text->setOpacity(255);
	}
	else
	{
		this->panel->runAction(FadeTo::create(duration, 255));
		this->text->runAction(FadeTo::create(duration, 255));
	}

	this->text->setDimensions(320.0f, 0.0f);

	Size textSize = this->text->getContentSize();
	Vec2 source = Vec2(-textSize.width / 2.0f - padding.width, -padding.height);
	Vec2 dest = Vec2(textSize.width / 2.0f + padding.width, textSize.height + padding.height);

	this->panel->clear();
	this->panel->drawSolidRect(source, dest, TextPanel::PanelColor);
	this->panel->drawRect(source, dest, TextPanel::PanelEdgeColor);
	this->text->setPosition(Vec2(0.0f, textSize.height / 2.0f));
}

void TextPanel::hide(float duration)
{
	if (duration <= 0.0f)
	{
		this->panel->setOpacity(0);
		this->text->setOpacity(0);
	}
	else
	{
		this->panel->runAction(FadeTo::create(duration, 0));
		this->text->runAction(FadeTo::create(duration, 0));
	}
}
