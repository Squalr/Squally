#include "PopPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Instructions/Data/Pop.h"
#include "Strings/Hacking/Lexicon/Pages/Data/Pop/Intro.h"

using namespace cocos2d;

const std::string PopPage::Identifier = "POP_PAGE";

PopPage* PopPage::create()
{
	PopPage* instance = new PopPage();

	instance->autorelease();

	return instance;
}

PopPage::PopPage() : super(PopPage::Identifier, PageType::Full)
{
	this->decorSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Sword);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Hacking_Lexicon_Instructions_Data_Pop::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Hacking_Lexicon_Pages_Data_Pop_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
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

PopPage::~PopPage()
{
}

void PopPage::initializePositions()
{
	super::initializePositions();

	this->decorSprite->setPosition(Vec2(super::PageSize.width + 172.0f, -196.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void PopPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(DataIntroPage::Identifier, DataSelectPage::Identifier);
}
