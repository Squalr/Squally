#include "PushExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Components/StackBlock.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Assembly/Push.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEbx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEcx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEsi.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRbx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRcx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRsi.h"
#include "Strings/Hacking/Lexicon/Examples.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Push.h"
#include "Strings/Hacking/Lexicon/Pages/Data/Push/PointerHelp.h"
#include "Strings/Hacking/Lexicon/Pages/Data/OffsetHelp12.h"

using namespace cocos2d;

const std::string PushExamplesPage::Identifier = "PUSH_EXAMPLES_PAGE";

PushExamplesPage* PushExamplesPage::create()
{
	PushExamplesPage* instance = new PushExamplesPage();

	instance->autorelease();

	return instance;
}

PushExamplesPage::PushExamplesPage() : super(PushExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->stackBlock = StackBlock::create();
	this->resetButton = this->buildResetButton();
	this->pushButton = this->buildExecuteButton();
	this->pushPtrButton = this->buildExecuteButton();
	this->pushPtrOffsetButton = this->buildExecuteButton();
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	LocalizedString* pointerHelpStr = Strings::Hacking_Lexicon_Pages_Data_Push_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp = TextPanel::create(Strings::Hacking_Lexicon_Pages_Data_OffsetHelp12::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Hacking_Lexicon_Assembly_RegisterEbx::create());
		
		this->pushLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Push::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterEcx::create()
		);
		this->pushPtrLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Push::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterEbx::create())
		);
		this->pushPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Push::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterEsi::create(), sizeof(int) * 3)
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Hacking_Lexicon_Assembly_RegisterRbx::create());

		this->pushLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Push::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterRcx::create()
		);
		this->pushPtrLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Push::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterRbx::create())
		);
		this->pushPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Push::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterRsi::create(), sizeof(int) * 3)
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->stackBlock);
	this->addChild(this->resetButton);
	this->addChild(this->pushButton);
	this->addChild(this->pushPtrButton);
	this->addChild(this->pushPtrOffsetButton);
	this->addChild(this->pushLabel);
	this->addChild(this->pushPtrLabel);
	this->addChild(this->pushPtrOffsetLabel);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelpButton);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp);
}

PushExamplesPage::~PushExamplesPage()
{
}

void PushExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -48.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->stackBlock->setPosition(Vec2(164.0f, -160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));

	this->pushLabel->setPosition(Vec2(-256.0f, buttonOffset + buttonSpacing * 0.0f));
	this->pushButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->pushPtrLabel->setPosition(Vec2(-256.0f, buttonOffset + buttonSpacing * 2.0f));
	this->pushPtrButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 3.0f));
	this->pushPtrOffsetLabel->setPosition(Vec2(-256.0f, buttonOffset + buttonSpacing * 4.0f));
	this->pushPtrOffsetButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 5.0f));

	this->resetButton->setPosition(Vec2(0.0f, -332.0f));

	this->pointerHelpButton->setPosition(Vec2(-32.0f, buttonOffset + buttonSpacing * 2.5f));
	this->offsetHelpButton->setPosition(Vec2(-32.0f, buttonOffset + buttonSpacing * 4.5f));

	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 1.0f + 48.0f));
	this->textPanelOffsetHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
}

void PushExamplesPage::initializeListeners()
{
	super::initializeListeners();

	this->pointerHelpButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->textPanelPointerHelp->show();
	});

	this->pointerHelpButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->textPanelPointerHelp->hide();
	});

	this->offsetHelpButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp->show();
	});

	this->offsetHelpButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp->hide();
	});

	this->resetButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->resetState();
	});

	this->pushButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->stackBlock->push(this->registerBlock->getEcx());
	});

	this->pushButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
		this->stackBlock->highlightTop();
	});

	this->pushButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
		this->stackBlock->clearHighlights();
	});

	this->pushPtrButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->stackBlock->push(this->registerBlock->getEbxPtr(0));
	});

	this->pushPtrButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbxPtr(true, 0);
		this->stackBlock->highlightTop();
	});

	this->pushPtrButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
		this->stackBlock->clearHighlights();
	});

	this->pushPtrOffsetButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->stackBlock->push(this->registerBlock->getEsiPtr(3));
	});

	this->pushPtrOffsetButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEsiPtr(true, 3);
		this->stackBlock->highlightTop();
	});

	this->pushPtrOffsetButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
		this->stackBlock->clearHighlights();
	});
}


void PushExamplesPage::resetState()
{
	this->stackBlock->clear();
	this->stackBlock->push(24);
	this->stackBlock->push(1024);
	this->stackBlock->push(256);
	this->stackBlock->push(0);
	this->stackBlock->push(65536);
	this->stackBlock->push(92);
	this->stackBlock->push(1);

	this->registerBlock->initEax(420);
	this->registerBlock->initEbx(0x400F000, { 10 });
	this->registerBlock->initEcx(100);
	this->registerBlock->initEdx(65535);
	this->registerBlock->initEdi(1920);
	this->registerBlock->initEsi(0x2E20000, { 22, 740, 22, 500 });
	this->registerBlock->initEbp(0x0E20000);
	this->registerBlock->initEsp(0x0E20008);
	this->registerBlock->initEip(0x2F7029C);
}