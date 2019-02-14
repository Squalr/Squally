#include "MemesTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/BetterScrollPane.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Credits/Developers.h"

using namespace cocos2d;

MemesTab* MemesTab::create()
{
	MemesTab* instance = new MemesTab();

	instance->autorelease();

	return instance;
}

MemesTab::MemesTab()
{
	this->contentScrollPane = BetterScrollPane::create(Size (672.0f, 544.0f));
	this->developersTitle = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Credits_Developers::create());
	this->zacSprite = Sprite::create(UIResources::Menus_CreditsMenu_Zac);
	this->mattSprite = Sprite::create(UIResources::Menus_CreditsMenu_Matt);
	this->nathanSprite = Sprite::create(UIResources::Menus_CreditsMenu_Nathan);

	this->developersTitle->enableOutline(Color4B::BLACK, 3);

	this->contentScrollPane->addChild(this->developersTitle);
	this->contentScrollPane->addChild(this->zacSprite);
	this->contentScrollPane->addChild(this->mattSprite);
	this->contentScrollPane->addChild(this->nathanSprite);
	this->addChild(this->contentScrollPane);
}

MemesTab::~MemesTab()
{
}

void MemesTab::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;
}

void MemesTab::initializeListeners()
{
	super::initializeListeners();
}

void MemesTab::initializePositions()
{
	super::initializePositions();

	Size paneSize = this->contentScrollPane->getContentSize();

	this->contentScrollPane->setPosition(Vec2(-8.0f, -48.0f));

	this->developersTitle->setPosition(Vec2(paneSize.width / 2.0f, 0.0f));
	this->zacSprite->setPosition(Vec2(paneSize.width / 2.0f - 224.0f, -128.0f));
	this->mattSprite->setPosition(Vec2(paneSize.width / 2.0f, -128.0f));
	this->nathanSprite->setPosition(Vec2(paneSize.width / 2.0f + 224.0f, -128.0f));
}
