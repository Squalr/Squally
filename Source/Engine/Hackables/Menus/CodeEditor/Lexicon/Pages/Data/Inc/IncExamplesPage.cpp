#include "IncExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IncExamplesPage::Identifier = "INC_EXAMPLES_PAGE";

IncExamplesPage* IncExamplesPage::create()
{
	IncExamplesPage* instance = new IncExamplesPage();

	instance->autorelease();

	return instance;
}

IncExamplesPage::IncExamplesPage() : super(IncExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->resetButton = this->buildResetButton();
	this->incButton = this->buildExecuteButton();
	this->incPtrButton = this->buildExecuteButton();
	this->incPtrOffsetButton = this->buildExecuteButton();
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	LocalizedString* pointerHelpStr = Strings::Menus_Hacking_Lexicon_Pages_Data_Inc_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp = TextPanel::create(Strings::Menus_Hacking_Lexicon_Pages_Data_OffsetHelp8::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create());

		this->incLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Inc::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create()
		);
		this->incPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Inc::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create())
		);
		this->incPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Inc::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEdi::create(), sizeof(int) * 2)
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create());

		this->incLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Inc::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create()
		);
		this->incPtrLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Inc::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create())
		);
		this->incPtrOffsetLabel = this->createInstructionLabelSingle(
			Strings::Menus_Hacking_Lexicon_Assembly_Inc::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRdi::create(), sizeof(int) * 2)
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->incButton);
	this->addChild(this->incPtrButton);
	this->addChild(this->incPtrOffsetButton);
	this->addChild(this->incLabel);
	this->addChild(this->incPtrLabel);
	this->addChild(this->incPtrOffsetLabel);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelpButton);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp);
}

IncExamplesPage::~IncExamplesPage()
{
}

void IncExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -64.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->incButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->incPtrButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->incPtrOffsetButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->incLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->incPtrLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->incPtrOffsetLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->resetButton->setPosition(Vec2(0.0f, -312.0f));

	this->pointerHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 1.0f));
	this->offsetHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f));

	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 1.0f + 48.0f));
	this->textPanelOffsetHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
}

void IncExamplesPage::initializeListeners()
{
	super::initializeListeners();

	this->pointerHelpButton->setMouseOverCallback([=](MouseEventArgs*)
	{
		this->textPanelPointerHelp->show();
	});

	this->pointerHelpButton->setMouseOutCallback([=](MouseEventArgs*)
	{
		this->textPanelPointerHelp->hide();
	});

	this->offsetHelpButton->setMouseOverCallback([=](MouseEventArgs*)
	{
		this->textPanelOffsetHelp->show();
	});

	this->offsetHelpButton->setMouseOutCallback([=](MouseEventArgs*)
	{
		this->textPanelOffsetHelp->hide();
	});

	this->resetButton->setMouseClickCallback([=](MouseEventArgs*)
	{
		this->resetState();
	});

	this->incButton->setMouseClickCallback([=](MouseEventArgs*)
	{
		this->registerBlock->setEcx(this->registerBlock->getEcx() + 1);
	});

	this->incButton->setMouseOverCallback([=](MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
	});

	this->incButton->setMouseOutCallback([=](MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->incPtrButton->setMouseClickCallback([=](MouseEventArgs*)
	{
		this->registerBlock->setEaxPtr(this->registerBlock->getEaxPtr(0) + 1, 0);
	});

	this->incPtrButton->setMouseOverCallback([=](MouseEventArgs*)
	{
		this->registerBlock->highlightEaxPtr(true, 0);
	});

	this->incPtrButton->setMouseOutCallback([=](MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->incPtrOffsetButton->setMouseClickCallback([=](MouseEventArgs*)
	{
		this->registerBlock->setEdiPtr(this->registerBlock->getEdiPtr(2) + 1, 2);
	});

	this->incPtrOffsetButton->setMouseOverCallback([=](MouseEventArgs*)
	{
		this->registerBlock->highlightEdiPtr(true, 2);
	});

	this->incPtrOffsetButton->setMouseOutCallback([=](MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});
}


void IncExamplesPage::resetState()
{
	this->registerBlock->initEax(0x300F000, { 10 });
	this->registerBlock->initEbx(1025);
	this->registerBlock->initEcx(0);
	this->registerBlock->initEdx(65535);
	this->registerBlock->initEdi(0x2D20000, { 128, 110, 500 });
	this->registerBlock->initEsi(205);
	this->registerBlock->initEbp(0x0D20000);
	this->registerBlock->initEsp(0x0D20008);
	this->registerBlock->initEip(0x1F7029C);
}