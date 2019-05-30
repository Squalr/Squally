#include "Lexicon.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedSprite.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"

using namespace cocos2d;

Lexicon* Lexicon::create()
{
	Lexicon* instance = new Lexicon();

	instance->autorelease();

	return instance;
}

Lexicon::Lexicon()
{
	this->background = Sprite::create(UIResources::Menus_LexiconMenu_desert_background);
	this->banner = Sprite::create(UIResources::Menus_LexiconMenu_Banner);
	this->title = LocalizedSprite::create(UIResources::Menus_LexiconMenu_Lexicon_en);

	LocalizedLabel*	backLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Back::create());
	LocalizedLabel*	backLabelSelected = backLabel->clone();

	backLabel->enableOutline(Color4B::BLACK, 2);
	backLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(backLabel, backLabelSelected, UIResources::Menus_Buttons_GenericButton, UIResources::Menus_Buttons_GenericButtonHover);
	this->darkFrame = Sprite::create(UIResources::Menus_LexiconMenu_DarkFrame);
	this->pages = std::vector<LexiconPage*>();

	this->pages.push_back(NopPage::create());

	this->addChild(this->background);
	this->addChild(this->banner);
	this->addChild(this->title);

	for (auto it = this->pages.begin(); it != this->pages.end(); it++)
	{
		this->addChild(*it);
	}

	this->addChild(this->backButton);
	this->addChild(this->darkFrame);
}

Lexicon::~Lexicon()
{
}

void Lexicon::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->banner->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height / 2.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
	this->darkFrame->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}
	
void Lexicon::initializeListeners()
{
	super::initializeListeners();

	this->backButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->setVisible(false);
		GameUtils::focus(this->getParent());
	});
}