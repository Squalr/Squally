#include "DataIntroPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/Data/Intro.h"
#include "Strings/Hacking/Lexicon/Pages/Data/Title.h"

using namespace cocos2d;

const std::string DataIntroPage::KeyDataIntroPage = "DATA_INTRO_PAGE";

DataIntroPage* DataIntroPage::create()
{
	DataIntroPage* instance = new DataIntroPage();

	instance->autorelease();

	return instance;
}

DataIntroPage::DataIntroPage() : super(DataIntroPage::KeyDataIntroPage, PageType::Left)
{
	this->bagSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Bag);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Hacking_Lexicon_Pages_Data_Title::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Hacking_Lexicon_Pages_Data_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->bagSprite);
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

	this->bagSprite->setPosition(Vec2(32.0f, -160.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
}

void DataIntroPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(IntroPage::KeyIntroPage, ChapterSelectPage::KeyChapterSelectPage);
}
