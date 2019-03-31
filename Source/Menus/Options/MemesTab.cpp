#include "MemesTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/platform/CCApplication.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Credits/Developers.h"
#include "Strings/Menus/Credits/MattTwitter.h"
#include "Strings/Menus/Credits/NateTwitter.h"
#include "Strings/Menus/Credits/ZacTwitter.h"

using namespace cocos2d;

MemesTab* MemesTab::create()
{
	MemesTab* instance = new MemesTab();

	instance->autorelease();

	return instance;
}

MemesTab::MemesTab()
{
	this->contentScrollPane = ScrollPane::create(Size(672.0f, 544.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
	this->developersTitle = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Credits_Developers::create());
	this->zacSprite = Sprite::create(UIResources::Menus_CreditsMenu_Zac);
	this->mattSprite = Sprite::create(UIResources::Menus_CreditsMenu_Matt);
	this->nathanSprite = Sprite::create(UIResources::Menus_CreditsMenu_Nathan);

	LocalizedLabel* zacLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Credits_ZacTwitter::create());
	LocalizedLabel* mattLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Credits_MattTwitter::create());
	LocalizedLabel* nateLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Credits_NateTwitter::create());

	nateLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	
	this->twitterButtonZac = ClickableTextNode::create(zacLabel, zacLabel->clone(), UIResources::Menus_Buttons_SmallGenericButton, UIResources::Menus_Buttons_SmallGenericButtonSelected);
	this->twitterButtonMatt = ClickableTextNode::create(mattLabel, mattLabel->clone(), UIResources::Menus_Buttons_SmallGenericButton, UIResources::Menus_Buttons_SmallGenericButtonSelected);
	this->twitterButtonNate = ClickableTextNode::create(nateLabel, nateLabel->clone(), UIResources::Menus_Buttons_SmallGenericButton, UIResources::Menus_Buttons_SmallGenericButtonSelected);

	Sprite* twitterZac = Sprite::create(UIResources::Menus_CreditsMenu_Twitter);
	Sprite* twitterMatt = Sprite::create(UIResources::Menus_CreditsMenu_Twitter);
	Sprite* twitterNate = Sprite::create(UIResources::Menus_CreditsMenu_Twitter);

	this->twitterButtonZac->addChild(twitterZac);
	this->twitterButtonMatt->addChild(twitterMatt);
	this->twitterButtonNate->addChild(twitterNate);

	twitterZac->setPosition(Vec2(-72.0f, 0.0f));
	twitterMatt->setPosition(Vec2(-72.0f, 0.0f));
	twitterNate->setPosition(Vec2(-72.0f, 0.0f));

	this->developersTitle->enableOutline(Color4B::BLACK, 3);

	this->contentScrollPane->addChild(this->developersTitle);
	this->contentScrollPane->addChild(this->zacSprite);
	this->contentScrollPane->addChild(this->mattSprite);
	this->contentScrollPane->addChild(this->nathanSprite);
	this->contentScrollPane->addChild(this->twitterButtonZac);
	this->contentScrollPane->addChild(this->twitterButtonMatt);
	this->contentScrollPane->addChild(this->twitterButtonNate);
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

	this->twitterButtonZac->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		Application::getInstance()->openURL("https://twitter.com/zcanann");
	});

	this->twitterButtonMatt->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		Application::getInstance()->openURL("https://twitter.com/letsRTFM");
	});

	this->twitterButtonNate->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		Application::getInstance()->openURL("https://twitter.com/Teknoman117");
	});
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
	this->twitterButtonZac->setPosition(Vec2(paneSize.width / 2.0f - 224.0f, -256.0f));
	this->twitterButtonMatt->setPosition(Vec2(paneSize.width / 2.0f, -256.0f));
	this->twitterButtonNate->setPosition(Vec2(paneSize.width / 2.0f + 224.0f, -256.0f));
	this->twitterButtonNate->setTextOffset(Vec2(-64.0f, 0.0f));
}
