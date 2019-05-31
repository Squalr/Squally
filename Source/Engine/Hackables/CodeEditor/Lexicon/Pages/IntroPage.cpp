#include "IntroPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/Intro/Intro.h"

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
	this->compileDiagram = Sprite::create(UIResources::Menus_LexiconMenu_CompileDiagram);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Hacking_Lexicon_Pages_Intro_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->compileDiagram);
	this->addChild(this->chapterSprite);
	this->addChild(this->introText);
}

IntroPage::~IntroPage()
{
}

void IntroPage::initializePositions()
{
	super::initializePositions();

	this->compileDiagram->setPosition(Vec2(8.0f, -192.0f));
	this->introText->setPosition(Vec2(-96.0f, super::PageSize.height / 2.0f));
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
}

void IntroPage::initializeListeners()
{
	super::initializeListeners();
}
