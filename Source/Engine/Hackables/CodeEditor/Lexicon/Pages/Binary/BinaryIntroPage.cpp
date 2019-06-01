#include "BinaryIntroPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/Binary/Intro.h"
#include "Strings/Hacking/Lexicon/Pages/Binary/Title.h"

using namespace cocos2d;

const std::string BinaryIntroPage::KeyBinaryIntroPage = "BINARY_INTRO_PAGE";

BinaryIntroPage* BinaryIntroPage::create()
{
	BinaryIntroPage* instance = new BinaryIntroPage();

	instance->autorelease();

	return instance;
}

BinaryIntroPage::BinaryIntroPage() : super(BinaryIntroPage::KeyBinaryIntroPage, PageType::Left)
{
	this->bagSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Bag);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Hacking_Lexicon_Pages_Binary_Title::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Hacking_Lexicon_Pages_Binary_Intro::create(),
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

BinaryIntroPage::~BinaryIntroPage()
{
}

void BinaryIntroPage::initializePositions()
{
	super::initializePositions();

	this->bagSprite->setPosition(Vec2(32.0f, -160.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
}

void BinaryIntroPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(IntroPage::KeyIntroPage, ChapterSelectPage::KeyChapterSelectPage);
}
