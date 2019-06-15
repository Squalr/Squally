#include "DecExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Assembly/Dec.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEbx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEcx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterEsi.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRbx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRcx.h"
#include "Strings/Hacking/Lexicon/Assembly/RegisterRsi.h"
#include "Strings/Hacking/Lexicon/Examples.h"
#include "Strings/Hacking/Lexicon/Instructions/Data/Dec.h"
#include "Strings/Hacking/Lexicon/Pages/Data/Dec/PointerHelp.h"
#include "Strings/Hacking/Lexicon/Pages/Data/OffsetHelp12.h"

using namespace cocos2d;

const std::string DecExamplesPage::Identifier = "DEC_EXAMPLES_PAGE";

DecExamplesPage* DecExamplesPage::create()
{
	DecExamplesPage* instance = new DecExamplesPage();

	instance->autorelease();

	return instance;
}

DecExamplesPage::DecExamplesPage() : super(DecExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->resetButton = this->buildResetButton();
	this->decButton = this->buildExecuteButton();
	this->decPtrButton = this->buildExecuteButton();
	this->decPtrOffsetButton = this->buildExecuteButton();
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	LocalizedString* pointerHelpStr = Strings::Hacking_Lexicon_Pages_Data_Dec_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp = TextPanel::create(Strings::Hacking_Lexicon_Pages_Data_OffsetHelp12::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Hacking_Lexicon_Assembly_RegisterEbx::create());
		
		this->decLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Dec::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterEcx::create()
		);
		this->decPtrLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Dec::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterEbx::create())
		);
		this->decPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Dec::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterEsi::create(), sizeof(int) * 3)
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Hacking_Lexicon_Assembly_RegisterRbx::create());

		this->decLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Dec::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterRcx::create()
		);
		this->decPtrLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Dec::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterRbx::create())
		);
		this->decPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Hacking_Lexicon_Assembly_Dec::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterRsi::create(), sizeof(int) * 3)
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->decButton);
	this->addChild(this->decPtrButton);
	this->addChild(this->decPtrOffsetButton);
	this->addChild(this->decLabel);
	this->addChild(this->decPtrLabel);
	this->addChild(this->decPtrOffsetLabel);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelpButton);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp);
}

DecExamplesPage::~DecExamplesPage()
{
}

void DecExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -64.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->decButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->decPtrButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->decPtrOffsetButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->decLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->decPtrLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->decPtrOffsetLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->resetButton->setPosition(Vec2(0.0f, -312.0f));

	this->pointerHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 1.0f));
	this->offsetHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f));

	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 1.0f + 48.0f));
	this->textPanelOffsetHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
}

void DecExamplesPage::initializeListeners()
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

	this->decButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEcx(this->registerBlock->getEcx() - 1);
	});

	this->decButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
	});

	this->decButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->decPtrButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbxPtr(this->registerBlock->getEbxPtr(0) - 1, 0);
	});

	this->decPtrButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbxPtr(true, 0);
	});

	this->decPtrButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->decPtrOffsetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEsiPtr(this->registerBlock->getEsiPtr(3) - 1, 3);
	});

	this->decPtrOffsetButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEsiPtr(true, 3);
	});

	this->decPtrOffsetButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});
}


void DecExamplesPage::resetState()
{
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