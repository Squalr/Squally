#include "MenuEntry.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

const Size MenuEntry::LabelSize = Size(288.0f, 32.0f);

MenuEntry* MenuEntry::create(LocalizedString* text, std::string iconResource)
{
	MenuEntry* itemPreview = new MenuEntry(text, iconResource);

	itemPreview->autorelease();

	return itemPreview;
}

MenuEntry::MenuEntry(LocalizedString* text, std::string iconResource)
{
	this->label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);
	this->icon = iconResource.empty() ? nullptr : Sprite::create(iconResource);

	this->label->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->label->enableOutline(Color4B::BLACK, 2);
	this->label->setPositionX(-MenuEntry::LabelSize.width / 2.0f);

	if (this->icon != nullptr)
	{
		this->addChild(this->icon);
	}

	this->addChild(this->label);
}

MenuEntry::~MenuEntry()
{
}

void MenuEntry::onEnter()
{
	super::onEnter();

	this->showIcon();
	this->sizeFont();
}

void MenuEntry::initializePositions()
{
	super::initializePositions();

	this->label->setPositionX(-MenuEntry::LabelSize.width / 2.0f);

	if (this->icon != nullptr)
	{
		this->icon->setPositionX(-MenuEntry::LabelSize.width / 2.0f + 16.0f);
	}
}

void MenuEntry::hideIcon()
{
	if (this->icon == nullptr)
	{
		return;
	}

	this->label->setPositionX(-MenuEntry::LabelSize.width / 2.0f);
	this->icon->setVisible(false);
}

void MenuEntry::showIcon()
{
	if (this->icon == nullptr)
	{
		return;
	}

	this->label->setPositionX(-MenuEntry::LabelSize.width / 2.0f + 40.0f);
	this->icon->setVisible(true);
}

void MenuEntry::sizeFont()
{
	float labelWidth = this->label->getContentSize().width;
	float overdraw = labelWidth - MenuEntry::LabelSize.width;

	if (overdraw <= 0.0f)
	{
		this->label->setFontSize(LocalizedLabel::FontSize::H3);
	}
	else if (overdraw < 32.0f)
	{
		this->label->setFontSize(LocalizedLabel::FontSize::H4);
	}
	else if (overdraw < 48.0f)
	{
		this->label->setFontSize(LocalizedLabel::FontSize::P);
	}
	else
	{
		this->label->setFontSize(LocalizedLabel::FontSize::Small);
	}
}
