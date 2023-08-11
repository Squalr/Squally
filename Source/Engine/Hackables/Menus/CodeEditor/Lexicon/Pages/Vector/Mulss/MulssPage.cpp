#include "MulssPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/VectorIntroPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/VectorSelectPage.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MulssPage::Identifier = "MULSS_PAGE";

MulssPage* MulssPage::create()
{
	MulssPage* instance = new MulssPage();

	instance->autorelease();

	return instance;
}

MulssPage::MulssPage() : super(MulssPage::Identifier, PageType::Full)
{
	this->decorSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Bread);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Instructions_Vector_Mulss::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Menus_Hacking_Lexicon_Pages_Vector_Mulss_Intro::create(),
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

MulssPage::~MulssPage()
{
}

void MulssPage::initializePositions()
{
	super::initializePositions();

	this->decorSprite->setPosition(Vec2(32.0f, -160.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void MulssPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(VectorIntroPage::Identifier, VectorSelectPage::Identifier);
}
