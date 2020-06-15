#include "DivExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DivExamplesPage::Identifier = "DIV_EXAMPLES_PAGE";

DivExamplesPage* DivExamplesPage::create()
{
	DivExamplesPage* instance = new DivExamplesPage();

	instance->autorelease();

	return instance;
}

DivExamplesPage::DivExamplesPage() : super(DivExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->resetButton = this->buildResetButton();
	this->divImmButton = this->buildExecuteButton();
	this->divRegButton = this->buildExecuteButton();
	this->divPtrButton = this->buildExecuteButton();
	this->divPtrOffsetButton = this->buildExecuteButton();
	this->divPtrOffset2Button = this->buildExecuteButton();
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelp4Button = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelp8Button = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	
	LocalizedString* pointerHelpStr = Strings::Menus_Hacking_Lexicon_Pages_Data_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp4 = TextPanel::create(Strings::Menus_Hacking_Lexicon_Pages_Data_OffsetHelp4::create());
	this->textPanelOffsetHelp8 = TextPanel::create(Strings::Menus_Hacking_Lexicon_Pages_Data_OffsetHelp8::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create());
		
		this->divImmLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create()
		);
		this->divRegLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsi::create()
		);
		this->divPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())
		);
		this->divPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 1)
		);
		this->divPtrOffsetLabel2 = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 2)
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create());
		
		this->divImmLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create()
		);
		this->divRegLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsi::create()
		);
		this->divPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create())
		);
		this->divPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 1)
		);
		this->divPtrOffsetLabel2 = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Div::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 2)
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->divImmButton);
	this->addChild(this->divRegButton);
	this->addChild(this->divPtrButton);
	this->addChild(this->divPtrOffsetButton);
	this->addChild(this->divPtrOffset2Button);
	this->addChild(this->divImmLabel);
	this->addChild(this->divRegLabel);
	this->addChild(this->divPtrLabel);
	this->addChild(this->divPtrOffsetLabel);
	this->addChild(this->divPtrOffsetLabel2);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelp4Button);
	this->addChild(this->offsetHelp8Button);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp4);
	this->addChild(this->textPanelOffsetHelp8);
}

DivExamplesPage::~DivExamplesPage()
{
}

void DivExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -48.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->divImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->divRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->divPtrButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->divPtrOffsetButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 3.0f));
	this->divPtrOffset2Button->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 4.0f));
	this->divImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->divRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->divPtrLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->divPtrOffsetLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 3.0f));
	this->divPtrOffsetLabel2->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 4.0f));
	this->resetButton->setPosition(Vec2(0.0f, -336.0f));

	this->pointerHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f));
	this->offsetHelp4Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 3.0f));
	this->offsetHelp8Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f));
	
	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
	this->textPanelOffsetHelp4->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f + 48.0f));
	this->textPanelOffsetHelp8->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f + 48.0f));
}

void DivExamplesPage::initializeListeners()
{
	super::initializeListeners();

	this->pointerHelpButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelPointerHelp->show();
	});

	this->pointerHelpButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelPointerHelp->hide();
	});

	this->offsetHelp4Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp4->show();
	});

	this->offsetHelp4Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp4->hide();
	});

	this->offsetHelp8Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp8->show();
	});

	this->offsetHelp8Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp8->hide();
	});

	this->resetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->resetState();
	});

	this->divImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEdx(this->safeMod(this->registerBlock->getEax(), this->registerBlock->getEcx()));
		this->registerBlock->setEax(this->safeDiv(this->registerBlock->getEax(), this->registerBlock->getEcx()));
	});

	this->divImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEax(true);
		this->registerBlock->highlightEcx(false);
	});

	this->divImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->divRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEdx(this->safeMod(this->registerBlock->getEax(), this->registerBlock->getEsi()));
		this->registerBlock->setEax(this->safeDiv(this->registerBlock->getEax(), this->registerBlock->getEsi()));
	});

	this->divRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEax(true);
		this->registerBlock->highlightEsi(false);
	});

	this->divRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->divPtrButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEdx(this->safeMod(this->registerBlock->getEax(), this->registerBlock->getEbxPtr(0)));
		this->registerBlock->setEax(this->safeDiv(this->registerBlock->getEax(), this->registerBlock->getEbxPtr(0)));
	});

	this->divPtrButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEax(true);
		this->registerBlock->highlightEbxPtr(false, 0);
	});

	this->divPtrButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->divPtrOffsetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEdx(this->safeMod(this->registerBlock->getEax(), this->registerBlock->getEspPtr(1)));
		this->registerBlock->setEax(this->safeDiv(this->registerBlock->getEax(), this->registerBlock->getEspPtr(1)));
	});

	this->divPtrOffsetButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEax(true);
		this->registerBlock->highlightEspPtr(false, 1);
	});

	this->divPtrOffsetButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->divPtrOffset2Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEdx(this->safeMod(this->registerBlock->getEax(), this->registerBlock->getEspPtr(2)));
		this->registerBlock->setEax(this->safeDiv(this->registerBlock->getEax(), this->registerBlock->getEspPtr(2)));
	});

	this->divPtrOffset2Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEax(true);
		this->registerBlock->highlightEspPtr(false, 2);
	});

	this->divPtrOffset2Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});
}

void DivExamplesPage::resetState()
{
	this->registerBlock->initEax(120);
	this->registerBlock->initEbx(0x04CF0000, { 3 });
	this->registerBlock->initEcx(12);
	this->registerBlock->initEdx(0);
	this->registerBlock->initEdi(1024);
	this->registerBlock->initEsi(20);
	this->registerBlock->initEbp(0x0920000);
	this->registerBlock->initEsp(0x0920008, { 512, 4, 40 });
	this->registerBlock->initEip(0x2F7029C);
}

unsigned long long DivExamplesPage::safeDiv(unsigned long long num, unsigned long long denom)
{
	return denom == 0 ? 0 : (num / denom);
}

unsigned long long DivExamplesPage::safeMod(unsigned long long num, unsigned long long denom)
{
	return denom == 0 ? 0 : (num % denom);
}
