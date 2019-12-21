#include "PushPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PushPage::Identifier = "PUSH_PAGE";

PushPage* PushPage::create()
{
	PushPage* instance = new PushPage();

	instance->autorelease();

	return instance;
}

PushPage::PushPage() : super(PushPage::Identifier, PageType::Left)
{
	this->decorSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Spear);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Instructions_Data_Push::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Menus_Hacking_Lexicon_Pages_Data_Push_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->decorSprite);
	this->addChild(this->chapterSprite);
	this->addChild(this->titleLabel);
	this->addChild(this->introText);
}

PushPage::~PushPage()
{
}

void PushPage::initializePositions()
{
	super::initializePositions();

	this->decorSprite->setPosition(Vec2(96.0f, -196.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void PushPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(DataIntroPage::Identifier, DataSelectPage::Identifier);
}
