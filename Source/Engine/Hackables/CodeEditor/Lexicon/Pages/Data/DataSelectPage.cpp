#include "DataSelectPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Pages/ChapterSelect/ChooseAnOperation.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Adc.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Add.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Dec.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Div.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Idiv.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Imul.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Inc.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Lea.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Mov.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Mul.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Neg.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Pop.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Push.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Sbb.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Sub.h"

using namespace cocos2d;

const std::string DataSelectPage::Identifier = "DATA_SELECT_PAGE";

DataSelectPage* DataSelectPage::create()
{
	DataSelectPage* instance = new DataSelectPage();

	instance->autorelease();

	return instance;
}

DataSelectPage::DataSelectPage() : super(DataSelectPage::Identifier, PageType::Right)
{
	this->decorLine = Sprite::create(UIResources::Menus_LexiconMenu_DecorLine);

	this->operationSelectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Hacking_Lexicon_Pages_ChapterSelect_ChooseAnOperation::create());
	this->incOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Inc::create(), IncPage::Identifier, IncExamplesPage::Identifier);
	this->decOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Dec::create(), DecPage::Identifier, DecExamplesPage::Identifier);
	this->addOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Add::create(), AddPage::Identifier, AddExamplesPage::Identifier);
	this->subOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Sub::create(), SubPage::Identifier, SubExamplesPage::Identifier);
	this->divOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Div::create(), DivPage::Identifier, DivExamplesPage::Identifier);
	this->mulOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Mul::create(), MulPage::Identifier, MulExamplesPage::Identifier);
	this->movOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Mov::create(), MovPage::Identifier);
	this->leaOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Lea::create(), LeaPage::Identifier);
	this->pushOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Push::create(), PushPage::Identifier);
	this->popOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Pop::create(), PopPage::Identifier);
	this->negOperationButton = this->buildInstructionLabel(Strings::Hacking_Lexicon_Instructions_Data_Neg::create(), NegPage::Identifier);
	
	this->operationSelectLabel->setTextColor(super::TextColor);

	this->addChild(this->decorLine);
	this->addChild(this->operationSelectLabel);
	this->addChild(this->incOperationButton);
	this->addChild(this->decOperationButton);
	this->addChild(this->addOperationButton);
	this->addChild(this->subOperationButton);
	this->addChild(this->divOperationButton);
	this->addChild(this->mulOperationButton);
	this->addChild(this->negOperationButton);
	this->addChild(this->movOperationButton);
	this->addChild(this->leaOperationButton);
	this->addChild(this->pushOperationButton);
	this->addChild(this->popOperationButton);
}

DataSelectPage::~DataSelectPage()
{
}

void DataSelectPage::initializePositions()
{
	super::initializePositions();

	const float vOffset = -48.0f;
	const float vSpacing = -96.0f;

	this->decorLine->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset));
	this->operationSelectLabel->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 56.0f));

	this->incOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 0.0f));
	this->decOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 1.0f));
	this->addOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 2.0f));
	this->subOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 3.0f));
	this->divOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 4.0f));
	this->mulOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 5.0f));

	this->movOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 0.0f + vSpacing / 2.0f));
	this->leaOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 1.0f + vSpacing / 2.0f));
	this->pushOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 2.0f + vSpacing / 2.0f));
	this->popOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 3.0f + vSpacing / 2.0f));
	this->negOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 4.0f + vSpacing / 2.0f));
}

void DataSelectPage::initializeListeners()
{
	super::initializeListeners();
}
