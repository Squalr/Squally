#include "PopExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Components/StackBlock.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PopExamplesPage::Identifier = "POP_EXAMPLES_PAGE";

PopExamplesPage* PopExamplesPage::create()
{
	PopExamplesPage* instance = new PopExamplesPage();

	instance->autorelease();

	return instance;
}

PopExamplesPage::PopExamplesPage() : super(PopExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->stackBlock = StackBlock::create();
	this->resetButton = this->buildResetButton();
	this->popButton = this->buildExecuteButton();
	this->popPtrButton = this->buildExecuteButton();
	this->popPtrOffsetButton = this->buildExecuteButton();
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	LocalizedString* pointerHelpStr = Strings::Menus_Hacking_Lexicon_Pages_Data_Pop_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp = TextPanel::create(Strings::Menus_Hacking_Lexicon_Pages_Data_OffsetHelp12::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create());
		
		this->popLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Pop::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create()
		);
		this->popPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Pop::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())
		);
		this->popPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Pop::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsi::create(), sizeof(int) * 3)
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create());

		this->popLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Pop::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create()
		);
		this->popPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Pop::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create())
		);
		this->popPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Pop::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsi::create(), sizeof(int) * 3)
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->stackBlock);
	this->addChild(this->resetButton);
	this->addChild(this->popButton);
	this->addChild(this->popPtrButton);
	this->addChild(this->popPtrOffsetButton);
	this->addChild(this->popLabel);
	this->addChild(this->popPtrLabel);
	this->addChild(this->popPtrOffsetLabel);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelpButton);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp);
}

PopExamplesPage::~PopExamplesPage()
{
}

void PopExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -48.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->stackBlock->setPosition(Vec2(164.0f, -160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));

	this->popLabel->setPosition(Vec2(-256.0f, buttonOffset + buttonSpacing * 0.0f));
	this->popButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->popPtrLabel->setPosition(Vec2(-256.0f, buttonOffset + buttonSpacing * 2.0f));
	this->popPtrButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 3.0f));
	this->popPtrOffsetLabel->setPosition(Vec2(-256.0f, buttonOffset + buttonSpacing * 4.0f));
	this->popPtrOffsetButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 5.0f));

	this->resetButton->setPosition(Vec2(0.0f, -332.0f));

	this->pointerHelpButton->setPosition(Vec2(-32.0f, buttonOffset + buttonSpacing * 2.5f));
	this->offsetHelpButton->setPosition(Vec2(-32.0f, buttonOffset + buttonSpacing * 4.5f));

	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 1.0f + 48.0f));
	this->textPanelOffsetHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
}

void PopExamplesPage::initializeListeners()
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

	this->popButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEcx(this->stackBlock->pop());
		this->registerBlock->setEsp(this->registerBlock->getEsp() - sizeof(void*));
	});

	this->popButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
		this->stackBlock->highlightTop();
	});

	this->popButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
		this->stackBlock->clearHighlights();
	});

	this->popPtrButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbxPtr(this->stackBlock->pop(), 0);
		this->registerBlock->setEsp(this->registerBlock->getEsp() - sizeof(void*));
	});

	this->popPtrButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbxPtr(true, 0);
		this->stackBlock->highlightTop();
	});

	this->popPtrButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
		this->stackBlock->clearHighlights();
	});

	this->popPtrOffsetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEsiPtr(this->stackBlock->pop(), 3);
		this->registerBlock->setEsp(this->registerBlock->getEsp() - sizeof(void*));
	});

	this->popPtrOffsetButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEsiPtr(true, 3);
		this->stackBlock->highlightTop();
	});

	this->popPtrOffsetButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
		this->stackBlock->clearHighlights();
	});
}


void PopExamplesPage::resetState()
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