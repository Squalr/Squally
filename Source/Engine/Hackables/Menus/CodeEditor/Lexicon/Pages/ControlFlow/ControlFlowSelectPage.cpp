#include "ControlFlowSelectPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Call/CallPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jnabe/JnabePage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jne/JnePage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jngle/JnglePage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jmp/JmpPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jne/JnePage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jno/JnoPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jnp/JnpPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jns/JnsPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jnz/JnzPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Jzcxz/JzcxzPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Loop/LoopPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Nop/NopPage.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/ControlFlow/Ret/RetPage.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ControlFlowSelectPage::Identifier = "CONTROL_FLOW_SELECT_PAGE";

ControlFlowSelectPage* ControlFlowSelectPage::create()
{
	ControlFlowSelectPage* instance = new ControlFlowSelectPage();

	instance->autorelease();

	return instance;
}

ControlFlowSelectPage::ControlFlowSelectPage() : super(ControlFlowSelectPage::Identifier, PageType::Right)
{
	this->decorLine = Sprite::create(UIResources::Menus_LexiconMenu_DecorLine);

	this->operationSelectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Menus_Hacking_Lexicon_Pages_ChapterSelect_ChooseAnOperation::create());
	this->callOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Call::create(), CallPage::Identifier);
	this->jnabeOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Jnabe::create(), JnabePage::Identifier);
	this->jneOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Jne::create(), JnePage::Identifier);
	this->jngleOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Jngle::create(), JnglePage::Identifier);
	this->jnoOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Jno::create(), JnoPage::Identifier);
	this->jnpOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Jnp::create(), JnpPage::Identifier);
	this->jmpOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Jmp::create(), JmpPage::Identifier);
	this->jnsOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Jns::create(), JnsPage::Identifier);
	this->jnzOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Jnz::create(), JnzPage::Identifier);
	this->jzcxzOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Jzcxz::create(), JzcxzPage::Identifier);
	this->loopOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Loop::create(), LoopPage::Identifier);
	this->nopOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Nop::create(), NopPage::Identifier);
	this->retOperationButton = this->buildInstructionLabel(Strings::Menus_Hacking_Lexicon_Instructions_ControlFlow_Ret::create(), RetPage::Identifier);

	this->operationSelectLabel->setTextColor(super::TextColor);

	this->addChild(this->decorLine);
	this->addChild(this->operationSelectLabel);
	this->addChild(this->callOperationButton);
	this->addChild(this->jnabeOperationButton);
	this->addChild(this->jneOperationButton);
	this->addChild(this->jngleOperationButton);
	this->addChild(this->jnoOperationButton);
	this->addChild(this->jnpOperationButton);
	this->addChild(this->jmpOperationButton);
	this->addChild(this->jnsOperationButton);
	this->addChild(this->jnzOperationButton);
	this->addChild(this->jzcxzOperationButton);
	this->addChild(this->loopOperationButton);
	this->addChild(this->nopOperationButton);
	this->addChild(this->retOperationButton);
}

ControlFlowSelectPage::~ControlFlowSelectPage()
{
}

void ControlFlowSelectPage::initializePositions()
{
	super::initializePositions();

	const float vOffset = -48.0f;
	const float vSpacing = -92.0f;

	this->decorLine->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset));
	this->operationSelectLabel->setPosition(Vec2(0.0f, super::PageSize.height / 2.0f + vOffset - 56.0f));

	this->nopOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 0.0f));
	this->callOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 1.0f));
	this->jmpOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 2.0f));
	this->jneOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 3.0f));
	this->jnoOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 4.0f));
	this->jnpOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 5.0f));
	this->jzcxzOperationButton->setPosition(Vec2(-112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 6.0f));

	this->retOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 0.0f + vSpacing / 2.0f));
	this->jnzOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 1.0f + vSpacing / 2.0f));
	this->jngleOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 2.0f + vSpacing / 2.0f));
	this->jnabeOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 3.0f + vSpacing / 2.0f));
	this->jnsOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 4.0f + vSpacing / 2.0f));
	this->loopOperationButton->setPosition(Vec2(112.0f, super::PageSize.height / 2.0f + vOffset - 128.0f + vSpacing * 5.0f + vSpacing / 2.0f));
}

void ControlFlowSelectPage::initializeListeners()
{
	super::initializeListeners();
}
