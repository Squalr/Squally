#include "IntroPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/Intro/Intro.h"
#include "Strings/Hacking/Lexicon/Pages/Intro/Title.h"

using namespace cocos2d;

const std::string IntroPage::KeyIntroPage = "INTRO_PAGE";

IntroPage* IntroPage::create()
{
	IntroPage* instance = new IntroPage();

	instance->autorelease();

	return instance;
}

IntroPage::IntroPage() : super(IntroPage::KeyIntroPage, PageType::Left)
{
	this->ratSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Rat); 
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hacking_Lexicon_Pages_Intro_Title::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Hacking_Lexicon_Pages_Intro_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->ratSprite);
	this->addChild(this->chapterSprite);
	this->addChild(this->titleLabel);
	this->addChild(this->introText);
}

IntroPage::~IntroPage()
{
}

void IntroPage::initializePositions()
{
	super::initializePositions();

	this->ratSprite->setPosition(Vec2(-96.0f, -224.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void IntroPage::initializeListeners()
{
	super::initializeListeners();
}
