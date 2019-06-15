#include "DivExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Assembly/Div.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEax.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEbx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEcx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEdx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEdi.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEsi.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEbp.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEsp.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRax.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRbx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRcx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRdx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRdi.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRsi.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRsp.h"
#include "Strings/Hacking/Lexicon/Examples.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Div.h"
#include "Strings/Hacking/Lexicon/Pages/Data/Div/RemainderHelp.h"
#include "Strings/Hacking/Lexicon/Pages/Data/PointerHelp.h"
#include "Strings/Hacking/Lexicon/Pages/Data/OffsetHelp4.h"
#include "Strings/Hacking/Lexicon/Pages/Data/OffsetHelp8.h"

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
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->resetButton = this->buildResetButton();
	this->divRegImmButton = this->buildExecuteButton();
	this->divRegRegButton = this->buildExecuteButton();
	this->divPtrImmButton = this->buildExecuteButton();
	this->divPtrRegButton = this->buildExecuteButton();
	this->divPtrOffsetImmButton = this->buildExecuteButton();
	this->divPtrOffsetRegButton = this->buildExecuteButton();
	this->remainderHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelp4Button = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelp8Button = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	
	this->textPanelRemainderHelp = TextPanel::create(Strings::Hacking_Lexicon_Pages_Data_Div_RemainderHelp::create());
	LocalizedString* pointerHelpStr = Strings::Hacking_Lexicon_Pages_Data_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp4 = TextPanel::create(Strings::Hacking_Lexicon_Pages_Data_OffsetHelp4::create());
	this->textPanelOffsetHelp8 = TextPanel::create(Strings::Hacking_Lexicon_Pages_Data_OffsetHelp8::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Hacking_Lexicon_Assembly_RegisterEax::create());
		
		this->divRegImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterEbx::create(),
			ConstantString::create(std::to_string(2))
		);
		this->divRegRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterEcx::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterEdx::create()
		);
		this->divPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterEax::create()),
			ConstantString::create(std::to_string(10))
		);
		this->divPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterEsp::create()),
			Strings::Hacking_Lexicon_Assembly_RegisterEdi::create()
		);
		this->divPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(4))
		);
		this->divPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 2),
			Strings::Hacking_Lexicon_Assembly_RegisterEsi::create()
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Hacking_Lexicon_Assembly_RegisterRax::create());
		
		this->divRegImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterRbx::create(),
			ConstantString::create(std::to_string(2))
		);
		this->divRegRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterRcx::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterRdx::create()
		);
		this->divPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterRax::create()),
			ConstantString::create(std::to_string(10))
		);
		this->divPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterRsp::create()),
			Strings::Hacking_Lexicon_Assembly_RegisterRdi::create()
		);
		this->divPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(4))
		);
		this->divPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Div::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 2),
			Strings::Hacking_Lexicon_Assembly_RegisterRsi::create()
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->divRegImmButton);
	this->addChild(this->divRegRegButton);
	this->addChild(this->divPtrImmButton);
	this->addChild(this->divPtrRegButton);
	this->addChild(this->divPtrOffsetImmButton);
	this->addChild(this->divPtrOffsetRegButton);
	this->addChild(this->divRegImmLabel);
	this->addChild(this->divRegRegLabel);
	this->addChild(this->divPtrImmLabel);
	this->addChild(this->divPtrRegLabel);
	this->addChild(this->divPtrOffsetImmLabel);
	this->addChild(this->divPtrOffsetRegLabel);
	this->addChild(this->remainderHelpButton);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelp4Button);
	this->addChild(this->offsetHelp8Button);
	this->addChild(this->textPanelRemainderHelp);
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
	this->divRegImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->divRegRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->divPtrImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->divPtrRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 3.0f));
	this->divPtrOffsetImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 4.0f));
	this->divPtrOffsetRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 5.0f));
	this->divRegImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->divRegRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->divPtrImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->divPtrRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 3.0f));
	this->divPtrOffsetImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 4.0f));
	this->divPtrOffsetRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 5.0f));
	this->resetButton->setPosition(Vec2(0.0f, -336.0f));

	this->remainderHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 0.0f));
	this->pointerHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f));
	this->offsetHelp4Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f));
	this->offsetHelp8Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f));

	this->textPanelRemainderHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 0.0f + 48.0f));
	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
	this->textPanelOffsetHelp4->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f + 48.0f));
	this->textPanelOffsetHelp8->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f + 48.0f));
}

void DivExamplesPage::initializeListeners()
{
	super::initializeListeners();

	this->remainderHelpButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelRemainderHelp->show();
	});

	this->remainderHelpButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelRemainderHelp->hide();
	});

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

	this->divRegImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbx(this->safeDiv(this->registerBlock->getEbx(), 2));
	});

	this->divRegImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbx(true);
	});

	this->divRegImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->divRegRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEcx(this->safeDiv(this->registerBlock->getEcx(), this->registerBlock->getEdx()));
	});

	this->divRegRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
		this->registerBlock->highlightEdx(false);
	});

	this->divRegRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->divPtrImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEaxPtr(this->safeDiv(this->registerBlock->getEaxPtr(0), 10), 0);
	});

	this->divPtrImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEaxPtr(true, 0);
	});

	this->divPtrImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->divPtrRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->safeDiv(this->registerBlock->getEspPtr(0), this->registerBlock->getEdi()), 0);
	});

	this->divPtrRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 0);
		this->registerBlock->highlightEdi(false);
	});

	this->divPtrRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->divPtrOffsetImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->safeDiv(this->registerBlock->getEspPtr(1), 4), 1);
	});

	this->divPtrOffsetImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 1);
	});

	this->divPtrOffsetImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->divPtrOffsetRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->safeDiv(this->registerBlock->getEspPtr(2), this->registerBlock->getEsi()), 2);
	});

	this->divPtrOffsetRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 2);
		this->registerBlock->highlightEsi(false);
	});

	this->divPtrOffsetRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});
}

void DivExamplesPage::resetState()
{
	this->registerBlock->initEax(0x04CF0000, { 1000000000 });
	this->registerBlock->initEbx(33);
	this->registerBlock->initEcx(12);
	this->registerBlock->initEdx(3);
	this->registerBlock->initEdi(2);
	this->registerBlock->initEsi(3);
	this->registerBlock->initEbp(0x0920000);
	this->registerBlock->initEsp(0x0920008, { 200, 400, 360 });
	this->registerBlock->initEip(0x2F7029C);
}

unsigned long long DivExamplesPage::safeDiv(unsigned long long num, unsigned long long denom)
{
	return denom == 0 ? 0 : (num / denom);
}
