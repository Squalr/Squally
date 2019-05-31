#include "NopPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/Nop/Nop.h"

using namespace cocos2d;

const std::string NopPage::KeyNopPage = "NOP_PAGE";

NopPage* NopPage::create()
{
	NopPage* instance = new NopPage();

	instance->autorelease();

	return instance;
}

NopPage::NopPage() : super(NopPage::KeyNopPage, PageType::Left)
{
	this->compileDiagram = Sprite::create(UIResources::Menus_LexiconMenu_CompileDiagram);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Hacking_Lexicon_Pages_Nop_Nop::create(),
		Size(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->compileDiagram);
	this->addChild(this->chapterSprite);
	this->addChild(this->introText);
}

NopPage::~NopPage()
{
}

void NopPage::initializePositions()
{
	super::initializePositions();

	this->compileDiagram->setPosition(Vec2(8.0f, -192.0f));
	this->introText->setPosition(Vec2(-96.0f, super::PageSize.height / 2.0f));
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
}

void NopPage::initializeListeners()
{
	super::initializeListeners();
}
