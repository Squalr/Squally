#include "FldzPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/FloatingPointIntroPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/FloatingPoint/FloatingPointSelectPage.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FldzPage::Identifier = "FLDZ_PAGE";

FldzPage* FldzPage::create()
{
	FldzPage* instance = new FldzPage();

	instance->autorelease();

	return instance;
}

FldzPage::FldzPage() : super(FldzPage::Identifier, PageType::Full)
{
	this->decorSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Bread);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Instructions_FloatingPoint_Fldz::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Menus_Hacking_Lexicon_Pages_FloatingPoint_Fldz_Intro::create(),
		CSize(super::PageSize.width - 160.0f, super::PageSize.height)
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

FldzPage::~FldzPage()
{
}

void FldzPage::initializePositions()
{
	super::initializePositions();

	this->decorSprite->setPosition(Vec2(32.0f, -160.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void FldzPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(FloatingPointIntroPage::Identifier, FloatingPointSelectPage::Identifier);
}
