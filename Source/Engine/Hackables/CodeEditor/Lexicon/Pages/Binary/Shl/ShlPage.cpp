#include "ShlPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ShlPage::Identifier = "SHL_PAGE";

ShlPage* ShlPage::create()
{
	ShlPage* instance = new ShlPage();

	instance->autorelease();

	return instance;
}

ShlPage::ShlPage() : super(ShlPage::Identifier, PageType::Full)
{
	this->decorSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Sword);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Instructions_Binary_Shl::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Menus_Hacking_Lexicon_Pages_Binary_Shl_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->decorSprite->setRotation(135.0f);
	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->decorSprite);
	this->addChild(this->chapterSprite);
	this->addChild(this->titleLabel);
	this->addChild(this->introText);
}

ShlPage::~ShlPage()
{
}

void ShlPage::initializePositions()
{
	super::initializePositions();

	this->decorSprite->setPosition(Vec2(super::PageSize.width + 212.0f, -192.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void ShlPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(BinaryIntroPage::Identifier, BinarySelectPage::Identifier);
}
