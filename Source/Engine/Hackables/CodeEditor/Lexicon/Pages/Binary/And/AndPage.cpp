#include "AndPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Instructions/Binary/And.h"
#include "Strings/Hacking/Lexicon/Pages/Binary/And/Intro.h"

using namespace cocos2d;

const std::string AndPage::Identifier = "AND_PAGE";

AndPage* AndPage::create()
{
	AndPage* instance = new AndPage();

	instance->autorelease();

	return instance;
}

AndPage::AndPage() : super(AndPage::Identifier, PageType::Right)
{
	this->hourglassSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Hourglass);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Hacking_Lexicon_Instructions_Binary_And::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Hacking_Lexicon_Pages_Binary_And_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->hourglassSprite);
	this->addChild(this->chapterSprite);
	this->addChild(this->titleLabel);
	this->addChild(this->introText);
}

AndPage::~AndPage()
{
}

void AndPage::initializePositions()
{
	super::initializePositions();

	this->hourglassSprite->setPosition(Vec2(32.0f, -160.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void AndPage::initializeListeners()
{
	super::initializeListeners();
}
