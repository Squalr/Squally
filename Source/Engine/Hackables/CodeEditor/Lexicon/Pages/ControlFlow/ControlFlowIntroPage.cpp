#include "ControlFlowIntroPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Hacking/Lexicon/Pages/ControlFlow/Intro.h"
#include "Strings/Menus/Hacking/Lexicon/Pages/ControlFlow/Title.h"

using namespace cocos2d;

const std::string ControlFlowIntroPage::Identifier = "CONTROL_FLOW_INTRO_PAGE";

ControlFlowIntroPage* ControlFlowIntroPage::create()
{
	ControlFlowIntroPage* instance = new ControlFlowIntroPage();

	instance->autorelease();

	return instance;
}

ControlFlowIntroPage::ControlFlowIntroPage() : super(ControlFlowIntroPage::Identifier, PageType::Left)
{
	this->decorSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Hourglass);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Pages_ControlFlow_Title::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Menus_Hacking_Lexicon_Pages_ControlFlow_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->decorSprite);
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

	this->decorSprite->setPosition(Vec2(48.0f, -128.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void ControlFlowIntroPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(IntroPage::Identifier, ChapterSelectPage::Identifier);
}
