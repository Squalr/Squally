#include "VectorSelectPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Addss/AddssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Comiss/ComissPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Divss/DivssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Maxss/MaxssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Minss/MinssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Mulss/MulssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Sqrtss/SqrtssPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/Vector/Subss/SubssPage.h"
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
	this->addssOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_Vector_Addss::create(), AddssPage::Identifier);
	this->comissOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_Vector_Comiss::create(), ComissPage::Identifier);
	this->divssOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_Vector_Divss::create(), DivssPage::Identifier);
	this->maxssOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_Vector_Maxss::create(), MaxssPage::Identifier);
	this->minssOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_Vector_Minss::create(), MinssPage::Identifier);
	this->mulssOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_Vector_Mulss::create(), MulssPage::Identifier);
	this->sqrtssOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_Vector_Sqrtss::create(), SqrtssPage::Identifier);
	this->subssOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_Vector_Subss::create(), SubssPage::Identifier);
	
	this->operationSelectLabel->setTextColor(super::TextColor);

	this->addChild(this->decorLine);
	this->addChild(this->operationSelectLabel);
	this->addChild(this->addssOperationButton);
	this->addChild(this->comissOperationButton);
	this->addChild(this->divssOperationButton);
	this->addChild(this->maxssOperationButton);
	this->addChild(this->minssOperationButton);
	this->addChild(this->mulssOperationButton);
	this->addChild(this->sqrtssOperationButton);
	this->addChild(this->subssOperationButton);
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

	this->addssOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 144.0f + vSpacing * 0.0f));
	this->divssOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 144.0f + vSpacing * 1.0f));
	this->minssOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 144.0f + vSpacing * 2.0f));
	this->sqrtssOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 144.0f + vSpacing * 3.0f));

	this->subssOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 144.0f + vSpacing * 0.0f + vSpacing / 2.0f));
	this->mulssOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 144.0f + vSpacing * 1.0f + vSpacing / 2.0f));
	this->maxssOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 144.0f + vSpacing * 2.0f + vSpacing / 2.0f));
	this->comissOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 144.0f + vSpacing * 3.0f + vSpacing / 2.0f));
}

void VectorSelectPage::initializeListeners()
{
	super::initializeListeners();
}
