﻿#include "DecPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/DataIntroPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Data/DataSelectPage.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DecPage::Identifier = "DEC_PAGE";

DecPage* DecPage::create()
{
	DecPage* instance = new DecPage();

	instance->autorelease();

	return instance;
}

DecPage::DecPage() : super(DecPage::Identifier, PageType::Left)
{
	this->decorSprite = Sprite::create(UIResources::Menus_LexiconMenu_BookArt_Frog);
	this->chapterSprite = Sprite::create(UIResources::Menus_LexiconMenu_Chapter);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Instructions_Data_Dec::create());
	this->introText = LocalizedLabel::create(
		LocalizedLabel::FontStyle::Main,
		LocalizedLabel::FontSize::P,
		Strings::Menus_Hacking_Lexicon_Pages_Data_Dec_Intro::create(),
		CSize(super::PageSize.width - 160.0f, super::PageSize.height)
	);

	this->decorSprite->setFlippedX(true);
	this->titleLabel->setTextColor(super::TextColor);
	this->titleLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->introText->setTextColor(super::TextColor);
	this->introText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->decorSprite);
	this->addChild(this->chapterSprite);
	this->addChild(this->titleLabel);
	this->addChild(this->introText);
}

DecPage::~DecPage()
{
}

void DecPage::initializePositions()
{
	super::initializePositions();

	this->decorSprite->setPosition(Vec2(80.0f, -224.0f));
	this->introText->setPosition(super::IntroLocation);
	this->chapterSprite->setPosition(super::ChapterMarkerLocation);
	this->titleLabel->setPosition(super::ChapterLocation);
}

void DecPage::initializeListeners()
{
	super::initializeListeners();

	this->enableBack(DataIntroPage::Identifier, DataSelectPage::Identifier);
}
