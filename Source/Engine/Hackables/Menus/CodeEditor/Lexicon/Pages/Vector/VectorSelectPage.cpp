﻿#include "VectorSelectPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Nop/NopPage.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VectorSelectPage::Identifier = "VECTOR_SELECT_PAGE";

VectorSelectPage* VectorSelectPage::create()
{
	VectorSelectPage* instance = new VectorSelectPage();

	instance->autorelease();

	return instance;
}

VectorSelectPage::VectorSelectPage() : super(VectorSelectPage::Identifier, PageType::Right)
{
	this->decorLine = Sprite::create(UIResources::Menus_LexiconMenu_DecorLine);

	this->operationSelectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Pages_ChapterSelect_ChooseAnOperation::create());
	this->nopOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Nop::create(), NopPage::Identifier);
	
	this->operationSelectLabel->setTextColor(super::TextColor);

	this->addChild(this->decorLine);
	this->addChild(this->operationSelectLabel);
	this->addChild(this->nopOperationButton);
}

VectorSelectPage::~VectorSelectPage()
{
}

void VectorSelectPage::initializePositions()
{
	super::initializePositions();

	const float vOffset = -48.0f;
	const float vSpacing = -144.0f;

	this->decorLine->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset));
	this->operationSelectLabel->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 56.0f));
	this->nopOperationButton->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 0.0f));

	// addss
	// subss
	// mulss
	// divss
	
	// minss
	// maxss
	// sqrtss
	// comiss
}

void VectorSelectPage::initializeListeners()
{
	super::initializeListeners();
}
