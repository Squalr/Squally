#include "NegExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Components/RegisterBlockSigned.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string NegExamplesPage::Identifier = "NEG_EXAMPLES_PAGE";

NegExamplesPage* NegExamplesPage::create()
{
	NegExamplesPage* instance = new NegExamplesPage();

	instance->autorelease();

	return instance;
}

NegExamplesPage::NegExamplesPage() : super(NegExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlockSigned::create();
	this->resetButton = this->buildResetButton();
	this->negButton = this->buildExecuteButton();
	this->negPtrButton = this->buildExecuteButton();
	this->negPtrOffsetButton = this->buildExecuteButton();
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	LocalizedString* pointerHelpStr = Strings::Menus_Hacking_Lexicon_Pages_Data_Neg_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp = TextPanel::create(Strings::Menus_Hacking_Lexicon_Pages_Data_OffsetHelp12::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create());
		
		this->negLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Neg::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create()
		);
		this->negPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Neg::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create())
		);
		this->negPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Neg::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsi::create(), sizeof(int) * 3)
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create());

		this->negLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Neg::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create()
		);
		this->negPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Neg::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create())
		);
		this->negPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Neg::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsi::create(), sizeof(int) * 3)
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->negButton);
	this->addChild(this->negPtrButton);
	this->addChild(this->negPtrOffsetButton);
	this->addChild(this->negLabel);
	this->addChild(this->negPtrLabel);
	this->addChild(this->negPtrOffsetLabel);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelpButton);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp);
}

NegExamplesPage::~NegExamplesPage()
{
}

void NegExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -64.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->negButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->negPtrButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->negPtrOffsetButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->negLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->negPtrLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->negPtrOffsetLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->resetButton->setPosition(Vec2(0.0f, -312.0f));

	this->pointerHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 1.0f));
	this->offsetHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f));

	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 1.0f + 48.0f));
	this->textPanelOffsetHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
}

void NegExamplesPage::initializeListeners()
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

	this->negButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEcx(-this->registerBlock->getEcx());
	});

	this->negButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
	});

	this->negButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->negPtrButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbxPtr(-this->registerBlock->getEbxPtr(0), 0);
	});

	this->negPtrButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbxPtr(true, 0);
	});

	this->negPtrButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->negPtrOffsetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEsiPtr(-this->registerBlock->getEsiPtr(3), 3);
	});

	this->negPtrOffsetButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEsiPtr(true, 3);
	});

	this->negPtrOffsetButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});
}


void NegExamplesPage::resetState()
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