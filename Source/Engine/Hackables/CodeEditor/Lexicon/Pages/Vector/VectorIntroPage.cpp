#include "VectorIntroPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/Vector/Intro.h"
#include "Strings/Hacking/Lexicon/Pages/Vector/Title.h"

using namespace cocos2d;

const std::string VectorIntroPage::KeyVectorIntroPage = "VECTOR_INTRO_PAGE";

VectorIntroPage* VectorIntroPage::create()
{
	VectorIntroPage* instance = new VectorIntroPage();

	instance->autorelease();

	return instance;
}

VectorIntroPage::VectorIntroPage() : super(VectorIntroPage::KeyVectorIntroPage, PageType::Left)
{
	this->barrelSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Barrel);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Hacking_Lexicon_Pages_Vector_Title::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Hacking_Lexicon_Pages_Vector_Intro::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->barrelSprite);
	this->addChild(this->chapterSprite);
	this->addChild(this->introText);
	this->addChild(this->titleLabel);
}

VectorIntroPage::~VectorIntroPage()
{
}

void VectorIntroPage::initializePositions()
{
	super::initializePositions();

	this->barrelSprite->setPosition(Vec2(32.0f, -160.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
}

void VectorIntroPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(IntroPage::KeyIntroPage, ChapterSelectPage::KeyChapterSelectPage);
}
