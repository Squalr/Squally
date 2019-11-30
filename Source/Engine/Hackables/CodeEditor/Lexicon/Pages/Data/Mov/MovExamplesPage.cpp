#include "MovExamplesPage.h"

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

const std::string MovExamplesPage::Identifier = "MOV_EXAMPLES_PAGE";

MovExamplesPage* MovExamplesPage::create()
{
	MovExamplesPage* instance = new MovExamplesPage();

	instance->autorelease();

	return instance;
}

MovExamplesPage::MovExamplesPage() : super(MovExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->resetButton = this->buildResetButton();
	this->movRegImmButton = this->buildExecuteButton();
	this->movRegRegButton = this->buildExecuteButton();
	this->movPtrImmButton = this->buildExecuteButton();
	this->movPtrRegButton = this->buildExecuteButton();
	this->movPtrOffsetImmButton = this->buildExecuteButton();
	this->movPtrOffsetRegButton = this->buildExecuteButton();
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelp4Button = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelp8Button = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	
	LocalizedString* pointerHelpStr = Strings::Menus_Hacking_Lexicon_Pages_Data_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp4 = TextPanel::create(Strings::Menus_Hacking_Lexicon_Pages_Data_OffsetHelp4::create());
	this->textPanelOffsetHelp8 = TextPanel::create(Strings::Menus_Hacking_Lexicon_Pages_Data_OffsetHelp8::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create());
		
		this->movRegImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create(),
			ConstantString::create(std::to_string(200))
		);
		this->movRegRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEdx::create()
		);
		this->movPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create()),
			ConstantString::create(std::to_string(10))
		);
		this->movPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsp::create()),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEdi::create()
		);
		this->movPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(100))
		);
		this->movPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 2),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsi::create()
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create());
		
		this->movRegImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create(),
			ConstantString::create(std::to_string(200))
		);
		this->movRegRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRdx::create()
		);
		this->movPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create()),
			ConstantString::create(std::to_string(10))
		);
		this->movPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsp::create()),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRdi::create()
		);
		this->movPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(100))
		);
		this->movPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mov::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 2),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsi::create()
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->movRegImmButton);
	this->addChild(this->movRegRegButton);
	this->addChild(this->movPtrImmButton);
	this->addChild(this->movPtrRegButton);
	this->addChild(this->movPtrOffsetImmButton);
	this->addChild(this->movPtrOffsetRegButton);
	this->addChild(this->movRegImmLabel);
	this->addChild(this->movRegRegLabel);
	this->addChild(this->movPtrImmLabel);
	this->addChild(this->movPtrRegLabel);
	this->addChild(this->movPtrOffsetImmLabel);
	this->addChild(this->movPtrOffsetRegLabel);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelp4Button);
	this->addChild(this->offsetHelp8Button);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp4);
	this->addChild(this->textPanelOffsetHelp8);
}

MovExamplesPage::~MovExamplesPage()
{
}

void MovExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -48.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->movRegImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->movRegRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->movPtrImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->movPtrRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 3.0f));
	this->movPtrOffsetImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 4.0f));
	this->movPtrOffsetRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 5.0f));
	this->movRegImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->movRegRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->movPtrImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->movPtrRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 3.0f));
	this->movPtrOffsetImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 4.0f));
	this->movPtrOffsetRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 5.0f));
	this->resetButton->setPosition(Vec2(0.0f, -336.0f));

	this->pointerHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f));
	this->offsetHelp4Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f));
	this->offsetHelp8Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f));

	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
	this->textPanelOffsetHelp4->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f + 48.0f));
	this->textPanelOffsetHelp8->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f + 48.0f));
}

void MovExamplesPage::initializeListeners()
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

	this->movRegImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbx(200);
	});

	this->movRegImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbx(true);
	});

	this->movRegImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->movRegRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEcx(this->registerBlock->getEdx());
	});

	this->movRegRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
		this->registerBlock->highlightEdx(false);
	});

	this->movRegRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->movPtrImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEaxPtr(10, 0);
	});

	this->movPtrImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEaxPtr(true, 0);
	});

	this->movPtrImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->movPtrRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->registerBlock->getEdi(), 0);
	});

	this->movPtrRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 0);
		this->registerBlock->highlightEdi(false);
	});

	this->movPtrRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->movPtrOffsetImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(100, 1);
	});

	this->movPtrOffsetImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 1);
	});

	this->movPtrOffsetImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->movPtrOffsetRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->registerBlock->getEsi(), 2);
	});

	this->movPtrOffsetRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 2);
		this->registerBlock->highlightEsi(false);
	});

	this->movPtrOffsetRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});
}

void MovExamplesPage::resetState()
{
	this->registerBlock->initEax(0x08C10000, { 0 });
	this->registerBlock->initEbx(2048);
	this->registerBlock->initEcx(4000);
	this->registerBlock->initEdx(777);
	this->registerBlock->initEdi(128);
	this->registerBlock->initEsi(1234);
	this->registerBlock->initEbp(0x0830000);
	this->registerBlock->initEsp(0x0830008, { 10, 10, 10 });
	this->registerBlock->initEip(0x2D60320);
}
