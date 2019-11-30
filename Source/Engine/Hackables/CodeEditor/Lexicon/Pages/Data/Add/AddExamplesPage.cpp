#include "AddExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AddExamplesPage::Identifier = "ADD_EXAMPLES_PAGE";

AddExamplesPage* AddExamplesPage::create()
{
	AddExamplesPage* instance = new AddExamplesPage();

	instance->autorelease();

	return instance;
}

AddExamplesPage::AddExamplesPage() : super(AddExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->resetButton = this->buildResetButton();
	this->addRegImmButton = this->buildExecuteButton();
	this->addRegRegButton = this->buildExecuteButton();
	this->addPtrImmButton = this->buildExecuteButton();
	this->addPtrRegButton = this->buildExecuteButton();
	this->addPtrOffsetImmButton = this->buildExecuteButton();
	this->addPtrOffsetRegButton = this->buildExecuteButton();
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
		
		this->addRegImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create(),
			ConstantString::create(std::to_string(2))
		);
		this->addRegRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEdx::create()
		);
		this->addPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create()),
			ConstantString::create(std::to_string(10))
		);
		this->addPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbp::create()),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEdi::create()
		);
		this->addPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(4))
		);
		this->addPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbp::create(), sizeof(int) * 2),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsi::create()
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create());
		
		this->addRegImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create(),
			ConstantString::create(std::to_string(2))
		);
		this->addRegRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRdx::create()
		);
		this->addPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create()),
			ConstantString::create(std::to_string(10))
		);
		this->addPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbp::create()),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRdi::create()
		);
		this->addPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(4))
		);
		this->addPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Add::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbp::create(), sizeof(int) * 2),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsi::create()
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->addRegImmButton);
	this->addChild(this->addRegRegButton);
	this->addChild(this->addPtrImmButton);
	this->addChild(this->addPtrRegButton);
	this->addChild(this->addPtrOffsetImmButton);
	this->addChild(this->addPtrOffsetRegButton);
	this->addChild(this->addRegImmLabel);
	this->addChild(this->addRegRegLabel);
	this->addChild(this->addPtrImmLabel);
	this->addChild(this->addPtrRegLabel);
	this->addChild(this->addPtrOffsetImmLabel);
	this->addChild(this->addPtrOffsetRegLabel);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelp4Button);
	this->addChild(this->offsetHelp8Button);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp4);
	this->addChild(this->textPanelOffsetHelp8);
}

AddExamplesPage::~AddExamplesPage()
{
}

void AddExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -48.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->addRegImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->addRegRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->addPtrImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->addPtrRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 3.0f));
	this->addPtrOffsetImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 4.0f));
	this->addPtrOffsetRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 5.0f));
	this->addRegImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->addRegRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->addPtrImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->addPtrRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 3.0f));
	this->addPtrOffsetImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 4.0f));
	this->addPtrOffsetRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 5.0f));
	this->resetButton->setPosition(Vec2(0.0f, -336.0f));

	this->pointerHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f));
	this->offsetHelp4Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f));
	this->offsetHelp8Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f));

	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
	this->textPanelOffsetHelp4->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f + 48.0f));
	this->textPanelOffsetHelp8->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f + 48.0f));
}

void AddExamplesPage::initializeListeners()
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

	this->addRegImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEax(this->registerBlock->getEax() + 2);
	});

	this->addRegImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEax(true);
	});

	this->addRegImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->addRegRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEcx(this->registerBlock->getEcx() + this->registerBlock->getEdx());
	});

	this->addRegRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
		this->registerBlock->highlightEdx(false);
	});

	this->addRegRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->addPtrImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbxPtr(this->registerBlock->getEbxPtr(0) + 10, 0);
	});

	this->addPtrImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbxPtr(true, 0);
	});

	this->addPtrImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->addPtrRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbpPtr(this->registerBlock->getEbpPtr(0) + this->registerBlock->getEdi(), 0);
	});

	this->addPtrRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbpPtr(true, 0);
		this->registerBlock->highlightEdi(false);
	});

	this->addPtrRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->addPtrOffsetImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbpPtr(this->registerBlock->getEbpPtr(1) + 4, 1);
	});

	this->addPtrOffsetImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbpPtr(true, 1);
	});

	this->addPtrOffsetImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->addPtrOffsetRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbpPtr(this->registerBlock->getEbpPtr(2) + this->registerBlock->getEsi(), 2);
	});

	this->addPtrOffsetRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbpPtr(true, 2);
		this->registerBlock->highlightEsi(false);
	});

	this->addPtrOffsetRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});
}

void AddExamplesPage::resetState()
{
	this->registerBlock->initEax(2);
	this->registerBlock->initEbx(0x07CF0000, { 10 });
	this->registerBlock->initEcx(12);
	this->registerBlock->initEdx(3);
	this->registerBlock->initEdi(2);
	this->registerBlock->initEsi(3);
	this->registerBlock->initEbp(0x0940000, { 0, 0, 0 });
	this->registerBlock->initEsp(0x0940008);
	this->registerBlock->initEip(0x0317034C);
}
