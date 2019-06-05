#include "SubExamplesPage.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/TextPanel.h"

#include "Resources/UIResources.h"

#include "Strings/Hacking/Lexicon/Assembly/Sub.h"
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
#include "Strings/Hacking/Lexicon/Instructions/Data/Sub.h"
#include "Strings/Hacking/Lexicon/Pages/Data/PointerHelp.h"
#include "Strings/Hacking/Lexicon/Pages/Data/OffsetHelp4.h"
#include "Strings/Hacking/Lexicon/Pages/Data/OffsetHelp8.h"

using namespace cocos2d;

const std::string SubExamplesPage::Identifier = "SUB_EXAMPLES_PAGE";

SubExamplesPage* SubExamplesPage::create()
{
	SubExamplesPage* instance = new SubExamplesPage();

	instance->autorelease();

	return instance;
}

SubExamplesPage::SubExamplesPage() : super(SubExamplesPage::Identifier, PageType::Right)
{
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->resetButton = this->buildResetButton();
	this->subRegImmButton = this->buildExecuteButton();
	this->subRegRegButton = this->buildExecuteButton();
	this->subPtrImmButton = this->buildExecuteButton();
	this->subPtrRegButton = this->buildExecuteButton();
	this->subPtrOffsetImmButton = this->buildExecuteButton();
	this->subPtrOffsetRegButton = this->buildExecuteButton();
	this->pointerHelpButton = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelp4Button = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	this->offsetHelp8Button = ClickableNode::create(UIResources::Menus_LexiconMenu_HelpButton, UIResources::Menus_LexiconMenu_HelpButtonSelected);
	
	LocalizedString* pointerHelpStr = Strings::Hacking_Lexicon_Pages_Data_PointerHelp::create();
	this->textPanelPointerHelp = TextPanel::create(pointerHelpStr);
	this->textPanelOffsetHelp4 = TextPanel::create(Strings::Hacking_Lexicon_Pages_Data_OffsetHelp4::create());
	this->textPanelOffsetHelp8 = TextPanel::create(Strings::Hacking_Lexicon_Pages_Data_OffsetHelp8::create());

	if (sizeof(void*) == 4)
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Hacking_Lexicon_Assembly_RegisterEax::create());
		
		this->subRegImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterEbx::create(),
			ConstantString::create(std::to_string(2))
		);
		this->subRegRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterEcx::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterEdx::create()
		);
		this->subPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterEax::create()),
			ConstantString::create(std::to_string(10))
		);
		this->subPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterEsp::create()),
			Strings::Hacking_Lexicon_Assembly_RegisterEdi::create()
		);
		this->subPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(100))
		);
		this->subPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterEsp::create(), sizeof(int) * 2),
			Strings::Hacking_Lexicon_Assembly_RegisterEsi::create()
		);
	}
	else
	{
		pointerHelpStr->setStringReplacementVariables(Strings::Hacking_Lexicon_Assembly_RegisterRax::create());
		
		this->subRegImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterRbx::create(),
			ConstantString::create(std::to_string(2))
		);
		this->subRegRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterRcx::create(),
			Strings::Hacking_Lexicon_Assembly_RegisterRdx::create()
		);
		this->subPtrImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterRax::create()),
			ConstantString::create(std::to_string(10))
		);
		this->subPtrRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			this->pointerizeString(Strings::Hacking_Lexicon_Assembly_RegisterRsp::create()),
			Strings::Hacking_Lexicon_Assembly_RegisterRdi::create()
		);
		this->subPtrOffsetImmLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 1),
			ConstantString::create(std::to_string(100))
		);
		this->subPtrOffsetRegLabel = this->createInstructionLabelDouble(
			Strings::Hacking_Lexicon_Assembly_Sub::create(),
			this->offsetString(Strings::Hacking_Lexicon_Assembly_RegisterRsp::create(), sizeof(int) * 2),
			Strings::Hacking_Lexicon_Assembly_RegisterRsi::create()
		);
	}

	this->examplesLabel->setTextColor(super::TextColor);

	this->resetState();

	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->subRegImmButton);
	this->addChild(this->subRegRegButton);
	this->addChild(this->subPtrImmButton);
	this->addChild(this->subPtrRegButton);
	this->addChild(this->subPtrOffsetImmButton);
	this->addChild(this->subPtrOffsetRegButton);
	this->addChild(this->subRegImmLabel);
	this->addChild(this->subRegRegLabel);
	this->addChild(this->subPtrImmLabel);
	this->addChild(this->subPtrRegLabel);
	this->addChild(this->subPtrOffsetImmLabel);
	this->addChild(this->subPtrOffsetRegLabel);
	this->addChild(this->pointerHelpButton);
	this->addChild(this->offsetHelp4Button);
	this->addChild(this->offsetHelp8Button);
	this->addChild(this->textPanelPointerHelp);
	this->addChild(this->textPanelOffsetHelp4);
	this->addChild(this->textPanelOffsetHelp8);
}

SubExamplesPage::~SubExamplesPage()
{
}

void SubExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -48.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->subRegImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->subRegRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->subPtrImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->subPtrRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 3.0f));
	this->subPtrOffsetImmButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 4.0f));
	this->subPtrOffsetRegButton->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 5.0f));
	this->subRegImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->subRegRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->subPtrImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->subPtrRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 3.0f));
	this->subPtrOffsetImmLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 4.0f));
	this->subPtrOffsetRegLabel->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 5.0f));
	this->resetButton->setPosition(Vec2(0.0f, -336.0f));

	this->pointerHelpButton->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f));
	this->offsetHelp4Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f));
	this->offsetHelp8Button->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f));

	this->textPanelPointerHelp->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 2.0f + 48.0f));
	this->textPanelOffsetHelp4->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 4.0f + 48.0f));
	this->textPanelOffsetHelp8->setPosition(Vec2(212.0f, buttonOffset + buttonSpacing * 5.0f + 48.0f));
}

void SubExamplesPage::initializeListeners()
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

	this->offsetHelp4Button->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp4->show();
	});

	this->offsetHelp4Button->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp4->hide();
	});

	this->offsetHelp8Button->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp8->show();
	});

	this->offsetHelp8Button->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->textPanelOffsetHelp8->hide();
	});

	this->resetButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->resetState();
	});

	this->subRegImmButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->setEbx(this->registerBlock->getEbx() - 2);
	});

	this->subRegImmButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEbx(true);
	});

	this->subRegImmButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->subRegRegButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->setEcx(this->registerBlock->getEcx() - this->registerBlock->getEdx());
	});

	this->subRegRegButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEcx(true);
		this->registerBlock->highlightEdx(false);
	});

	this->subRegRegButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->subPtrImmButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->setEaxPtr(this->registerBlock->getEaxPtr(0) - 10, 0);
	});

	this->subPtrImmButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEaxPtr(true, 0);
	});

	this->subPtrImmButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->subPtrRegButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->registerBlock->getEspPtr(0) - this->registerBlock->getEdi(), 0);
	});

	this->subPtrRegButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 0);
		this->registerBlock->highlightEdi(false);
	});

	this->subPtrRegButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->subPtrOffsetImmButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->registerBlock->getEspPtr(1) - 100, 1);
	});

	this->subPtrOffsetImmButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 1);
	});

	this->subPtrOffsetImmButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});

	this->subPtrOffsetRegButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->setEspPtr(this->registerBlock->getEspPtr(2) - this->registerBlock->getEsi(), 2);
	});

	this->subPtrOffsetRegButton->setMouseOverCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->highlightEspPtr(true, 2);
		this->registerBlock->highlightEsi(false);
	});

	this->subPtrOffsetRegButton->setMouseOutCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->registerBlock->clearHighlights();
	});
}

void SubExamplesPage::resetState()
{
	this->registerBlock->initEax(0x04CF0000, { 1000 });
	this->registerBlock->initEbx(1024);
	this->registerBlock->initEcx(5000);
	this->registerBlock->initEdx(2);
	this->registerBlock->initEdi(4);
	this->registerBlock->initEsi(6);
	this->registerBlock->initEbp(0x0920000);
	this->registerBlock->initEsp(0x0920008, { 200, 9000, 800 });
	this->registerBlock->initEip(0x2F7029C);
}
