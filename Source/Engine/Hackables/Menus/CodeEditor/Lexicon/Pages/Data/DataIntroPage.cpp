#include "DataIntroPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ChapterSelectPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/IntroPage.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DataIntroPage::Identifier = "DATA_INTRO_PAGE";

DataIntroPage* DataIntroPage::create()
{
	DataIntroPage* instance = new DataIntroPage();

	instance->autorelease();

	return instance;
}

DataIntroPage::DataIntroPage() : super(DataIntroPage::Identifier, PageType::Left)
{
	this->donkeySprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Donkey);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Pages_Data_Title::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Menus_Hacking_Lexicon_Pages_Data_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->donkeySprite);
	this->addChild(this->chapterSprite);
	this->addChild(this->introText);
	this->addChild(this->titleLabel);
}

DataIntroPage::~DataIntroPage()
{
}

void DataIntroPage::initializePositions()
{
	super::initializePositions();

	this->donkeySprite->setPosition(Vec2(48.0f, -144.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void DataIntroPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(IntroPage::Identifier, ChapterSelectPage::Identifier);
}
