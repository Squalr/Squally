#include "ControlFlowIntroPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/ControlFlow/Intro.h"
#include "Strings/Hacking/Lexicon/Pages/ControlFlow/Title.h"

using namespace cocos2d;

const std::string ControlFlowIntroPage::KeyControlFlowIntroPage = "CONTROL_FLOW_INTRO_PAGE";

ControlFlowIntroPage* ControlFlowIntroPage::create()
{
	ControlFlowIntroPage* instance = new ControlFlowIntroPage();

	instance->autorelease();

	return instance;
}

ControlFlowIntroPage::ControlFlowIntroPage() : super(ControlFlowIntroPage::KeyControlFlowIntroPage, PageType::Left)
{
	this->hourglassSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Hourglass);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Hacking_Lexicon_Pages_ControlFlow_Title::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Hacking_Lexicon_Pages_ControlFlow_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->hourglassSprite);
	this->addChild(this->chapterSprite);
	this->addChild(this->introText);
	this->addChild(this->titleLabel);
}

ControlFlowIntroPage::~ControlFlowIntroPage()
{
}

void ControlFlowIntroPage::initializePositions()
{
	super::initializePositions();

	this->hourglassSprite->setPosition(Vec2(32.0f, -160.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
}

void ControlFlowIntroPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(IntroPage::KeyIntroPage, ChapterSelectPage::KeyChapterSelectPage);
}
