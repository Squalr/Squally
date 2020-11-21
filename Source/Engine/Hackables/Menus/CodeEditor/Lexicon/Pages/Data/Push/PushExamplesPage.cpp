#include "PushExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Components/StackBlock.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

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
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->stackBlock = StackBlock::create();
	this->resetButton = this->buildResetButton();
	this->pushButton = this->buildExecuteButton();
	this->pushPtrButton = this->buildExecuteButton();
	this->pushPtrOffsetButton = this->buildExecuteButton();
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	LocalizedString* pointerHelpStr = Strings::Menus_Hacking_Lexicon_Pages_Data_Push_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp = TextPanel::create(Strings::Menus_Hacking_Lexicon_Pages_Data_OffsetHelp12::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create());
		
		this->pushLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Push::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create()
		);
		this->pushPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Push::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())
		);
		this->pushPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Push::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsi::create(), sizeof(int) * 3)
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create());

		this->pushLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Push::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create()
		);
		this->pushPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Push::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create())
		);
		this->pushPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Push::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsi::create(), sizeof(int) * 3)
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

	this->pointerHelpButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelPointerHelp->show();
	});

	this->pointerHelpButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelPointerHelp->hide();
	});

	this->offsetHelpButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp->show();
	});

	this->offsetHelpButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp->hide();
	});

	this->resetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->resetState();
	});

	this->pushButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->stackBlock->push(this->registerBlock->getEcx());
		this->registerBlock->setEsp(this->registerBlock->getEsp() + sizeof(void*));
	});

	this->pushButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
		this->stackBlock->highlightTopPlus1();
	});

	this->pushButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
		this->stackBlock->clearHighlights();
	});

	this->pushPtrButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->stackBlock->push(this->registerBlock->getEbxPtr(0));
		this->registerBlock->setEsp(this->registerBlock->getEsp() + sizeof(void*));
	});

	this->pushPtrButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbxPtr(true, 0);
		this->stackBlock->highlightTopPlus1();
	});

	this->pushPtrButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
		this->stackBlock->clearHighlights();
	});

	this->pushPtrOffsetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->stackBlock->push(this->registerBlock->getEsiPtr(3));
		this->registerBlock->setEsp(this->registerBlock->getEsp() + sizeof(void*));
	});

	this->pushPtrOffsetButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEsiPtr(true, 3);
		this->stackBlock->highlightTopPlus1();
	});

	this->pushPtrOffsetButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
		this->stackBlock->clearHighlights();
	});
}


void PushExamplesPage::resetState()
{
	this->stackBlock->clear();

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