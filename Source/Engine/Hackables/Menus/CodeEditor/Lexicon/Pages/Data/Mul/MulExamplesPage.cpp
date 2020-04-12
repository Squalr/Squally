#include "MulExamplesPage.h"

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

const std::string MulExamplesPage::Identifier = "MUL_EXAMPLES_PAGE";

MulExamplesPage* MulExamplesPage::create()
{
	MulExamplesPage* instance = new MulExamplesPage();

	instance->autorelease();

	return instance;
}

MulExamplesPage::MulExamplesPage() : super(MulExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->resetButton = this->buildResetButton();
	this->mulRegImmButton = this->buildExecuteButton();
	this->mulRegRegButton = this->buildExecuteButton();
	this->mulPtrImmButton = this->buildExecuteButton();
	this->mulPtrRegButton = this->buildExecuteButton();
	this->mulPtrOffsetImmButton = this->buildExecuteButton();
	this->mulPtrOffsetRegButton = this->buildExecuteButton();
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
		
		this->mulRegImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create(),
			ConstantString::create(std::to_string(2))
		);
		this->mulRegRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEdx::create()
		);
		this->mulPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create()),
			ConstantString::create(std::to_string(10))
		);
		this->mulPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsp::create()),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEdi::create()
		);
		this->mulPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(100))
		);
		this->mulPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 2),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsi::create()
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create());
		
		this->mulRegImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRbx::create(),
			ConstantString::create(std::to_string(2))
		);
		this->mulRegRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRcx::create(),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRdx::create()
		);
		this->mulPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRax::create()),
			ConstantString::create(std::to_string(10))
		);
		this->mulPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			this->pointerizeString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsp::create()),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRdi::create()
		);
		this->mulPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(100))
		);
		this->mulPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Menus_Hacking_Lexicon_Assembly_Mul::create(),
			this->offsetString(Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 2),
			Strings::Menus_Hacking_Lexicon_Assembly_RegisterRsi::create()
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->mulRegImmButton);
	this->addChild(this->mulRegRegButton);
	this->addChild(this->mulPtrImmButton);
	this->addChild(this->mulPtrRegButton);
	this->addChild(this->mulPtrOffsetImmButton);
	this->addChild(this->mulPtrOffsetRegButton);
	this->addChild(this->mulRegImmLabel);
	this->addChild(this->mulRegRegLabel);
	this->addChild(this->mulPtrImmLabel);
	this->addChild(this->mulPtrRegLabel);
	this->addChild(this->mulPtrOffsetImmLabel);
	this->addChild(this->mulPtrOffsetRegLabel);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelp4Button);
	this->addChild(this->offsetHelp8Button);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp4);
	this->addChild(this->textPanelOffsetHelp8);
}

MulExamplesPage::~MulExamplesPage()
{
}

void MulExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -48.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->mulRegImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->mulRegRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->mulPtrImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->mulPtrRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 3.0f));
	this->mulPtrOffsetImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 4.0f));
	this->mulPtrOffsetRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 5.0f));
	this->mulRegImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->mulRegRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->mulPtrImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->mulPtrRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 3.0f));
	this->mulPtrOffsetImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 4.0f));
	this->mulPtrOffsetRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 5.0f));
	this->resetButton->setPosition(Vec2(0.0f, -336.0f));

	this->pointerHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f));
	this->offsetHelp4Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f));
	this->offsetHelp8Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f));

	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
	this->textPanelOffsetHelp4->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f + 48.0f));
	this->textPanelOffsetHelp8->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f + 48.0f));
}

void MulExamplesPage::initializeListeners()
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

	this->mulRegImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbx(this->registerBlock->getEbx() * 2);
	});

	this->mulRegImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbx(true);
	});

	this->mulRegImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->mulRegRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEcx(this->registerBlock->getEcx() * this->registerBlock->getEdx());
	});

	this->mulRegRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
		this->registerBlock->highlightEdx(false);
	});

	this->mulRegRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->mulPtrImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEaxPtr(this->registerBlock->getEaxPtr(0) * 10, 0);
	});

	this->mulPtrImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEaxPtr(true, 0);
	});

	this->mulPtrImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->mulPtrRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->registerBlock->getEspPtr(0) * this->registerBlock->getEdi(), 0);
	});

	this->mulPtrRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 0);
		this->registerBlock->highlightEdi(false);
	});

	this->mulPtrRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->mulPtrOffsetImmButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->registerBlock->getEspPtr(1) * 100, 1);
	});

	this->mulPtrOffsetImmButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 1);
	});

	this->mulPtrOffsetImmButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->mulPtrOffsetRegButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->registerBlock->getEspPtr(2) * this->registerBlock->getEsi(), 2);
	});

	this->mulPtrOffsetRegButton->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 2);
		this->registerBlock->highlightEsi(false);
	});

	this->mulPtrOffsetRegButton->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});
}

void MulExamplesPage::resetState()
{
	this->registerBlock->initEax(0x06C10000, { 100 });
	this->registerBlock->initEbx(2);
	this->registerBlock->initEcx(4000);
	this->registerBlock->initEdx(2);
	this->registerBlock->initEdi(4);
	this->registerBlock->initEsi(6);
	this->registerBlock->initEbp(0x0820000);
	this->registerBlock->initEsp(0x0820008, { 10, 10, 10 });
	this->registerBlock->initEip(0x1D60320);
}
