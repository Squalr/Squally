#include "ControlFlowExamplesPage.h"

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Components/StackBlock.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ControlFlowExamplesPage::NopIdentifier = "NOP_EXAMPLES_PAGE";
const std::string ControlFlowExamplesPage::JmpIdentifier = "JMP_EXAMPLES_PAGE";
const std::string ControlFlowExamplesPage::CallIdentifier = "CALL_EXAMPLES_PAGE";
const std::string ControlFlowExamplesPage::RetIdentifier = "RET_EXAMPLES_PAGE";
const std::string ControlFlowExamplesPage::LoopIdentifier = "LOOP_EXAMPLES_PAGE";

ControlFlowExamplesPage* ControlFlowExamplesPage::create(Operation operation)
{
	ControlFlowExamplesPage* instance = new ControlFlowExamplesPage(operation);

	instance->autorelease();

	return instance;
}

ControlFlowExamplesPage::ControlFlowExamplesPage(Operation operation) : super(ControlFlowExamplesPage::getIdentifier(operation), PageType::Right)
{
	this->operation = operation;
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create();
	this->stackBlock = StackBlock::create();
	this->resetButton = this->buildResetButton();
	this->example0Button = this->buildExecuteButton();
	this->example1Button = this->buildExecuteButton();
	this->example2Button = this->buildExecuteButton();

	this->examplesLabel->setTextColor(super::TextColor);

	this->buildExampleLabels();
	this->resetState();
	this->addExampleChildren();
}

ControlFlowExamplesPage::~ControlFlowExamplesPage()
{
}

const std::string& ControlFlowExamplesPage::getIdentifier(Operation operation)
{
	switch (operation)
	{
		case Operation::Nop: return ControlFlowExamplesPage::NopIdentifier;
		case Operation::Jmp: return ControlFlowExamplesPage::JmpIdentifier;
		case Operation::Call: return ControlFlowExamplesPage::CallIdentifier;
		case Operation::Ret: return ControlFlowExamplesPage::RetIdentifier;
		case Operation::Loop: return ControlFlowExamplesPage::LoopIdentifier;
		default: return ControlFlowExamplesPage::NopIdentifier;
	}
}

void ControlFlowExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -64.0f;

	this->registerBlock->setPosition(Vec2(-160.0f, 160.0f));
	this->stackBlock->setPosition(Vec2(164.0f, -160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));

	this->example0Button->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->example1Button->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->example2Button->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->example0Label->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->example1Label->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->example2Label->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->resetButton->setPosition(Vec2(0.0f, -312.0f));
}

void ControlFlowExamplesPage::initializeListeners()
{
	super::initializeListeners();

	this->resetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->resetState();
	});

	this->example0Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->executeExample(0); });
	this->example1Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->executeExample(1); });
	this->example2Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->executeExample(2); });

	this->example0Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightExample(0); });
	this->example1Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightExample(1); });
	this->example2Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightExample(2); });

	this->example0Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*) { this->clearHighlights(); });
	this->example1Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*) { this->clearHighlights(); });
	this->example2Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*) { this->clearHighlights(); });
}

void ControlFlowExamplesPage::resetState()
{
	this->stackBlock->clear();

	this->registerBlock->initEax(420);
	this->registerBlock->initEbx(256);
	this->registerBlock->initEcx(this->operation == Operation::Loop ? 3 : 100);
	this->registerBlock->initEdx(512);
	this->registerBlock->initEdi(768);
	this->registerBlock->initEsi(1024);
	this->registerBlock->initEbp(0x0E20000);
	this->registerBlock->initEsp(0x0E20008);
	this->registerBlock->initEip(100);

	if (this->operation == Operation::Ret)
	{
		this->stackBlock->push(240);
		this->stackBlock->push(320);
		this->stackBlock->push(400);
	}
}

void ControlFlowExamplesPage::executeExample(int exampleIndex)
{
	switch (this->operation)
	{
		case Operation::Nop:
		{
			this->registerBlock->setEip(this->registerBlock->getEip() + this->getInstructionSize());
			break;
		}
		case Operation::Jmp:
		{
			this->registerBlock->setEip(this->getTarget(exampleIndex));
			break;
		}
		case Operation::Call:
		{
			this->stackBlock->push(this->registerBlock->getEip() + this->getInstructionSize());
			this->registerBlock->setEsp(this->registerBlock->getEsp() + sizeof(void*));
			this->registerBlock->setEip(this->getTarget(exampleIndex));
			break;
		}
		case Operation::Ret:
		{
			this->registerBlock->setEip(this->stackBlock->pop());
			this->registerBlock->setEsp(this->registerBlock->getEsp() - sizeof(void*));
			break;
		}
		case Operation::Loop:
		{
			unsigned long long nextEcx = this->registerBlock->getEcx() == 0 ? 0 : this->registerBlock->getEcx() - 1;

			this->registerBlock->setEcx(nextEcx);
			this->registerBlock->setEip(nextEcx == 0 ? this->registerBlock->getEip() + this->getInstructionSize() : this->getTarget(exampleIndex));
			break;
		}
	}
}

void ControlFlowExamplesPage::highlightExample(int)
{
	switch (this->operation)
	{
		case Operation::Nop:
		case Operation::Jmp:
		{
			this->registerBlock->highlightEip(true);
			break;
		}
		case Operation::Call:
		{
			this->registerBlock->highlightEip(true);
			this->stackBlock->highlightTopPlus1();
			break;
		}
		case Operation::Ret:
		{
			this->registerBlock->highlightEip(true);
			this->stackBlock->highlightTop();
			break;
		}
		case Operation::Loop:
		{
			this->registerBlock->highlightEcx(true);
			this->registerBlock->highlightEip(false);
			break;
		}
	}
}

void ControlFlowExamplesPage::clearHighlights()
{
	this->registerBlock->clearHighlights();
	this->stackBlock->clearHighlights();
}

void ControlFlowExamplesPage::addExampleChildren()
{
	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);

	if (this->usesStack())
	{
		this->addChild(this->stackBlock);
	}

	this->addChild(this->resetButton);
	this->addChild(this->example0Button);
	this->addChild(this->example1Button);
	this->addChild(this->example2Button);
	this->addChild(this->example0Label);
	this->addChild(this->example1Label);
	this->addChild(this->example2Label);
}

void ControlFlowExamplesPage::buildExampleLabels()
{
	if (this->operation == Operation::Nop)
	{
		this->example0Label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create("nop"));
		this->example1Label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create("nop"));
		this->example2Label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create("nop"));
	}
	else if (this->operation == Operation::Ret)
	{
		this->example0Label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create("ret"));
		this->example1Label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create("ret"));
		this->example2Label = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::P, ConstantString::create("ret"));
	}
	else
	{
		LocalizedString* instruction = this->buildInstructionString();

		this->example0Label = this->createInstructionLabelSingle(instruction->clone(), ConstantString::create(std::to_string(this->getTarget(0))));
		this->example1Label = this->createInstructionLabelSingle(instruction->clone(), ConstantString::create(std::to_string(this->getTarget(1))));
		this->example2Label = this->createInstructionLabelSingle(instruction->clone(), ConstantString::create(std::to_string(this->getTarget(2))));
	}

	this->example0Label->setTextColor(super::TextColor);
	this->example1Label->setTextColor(super::TextColor);
	this->example2Label->setTextColor(super::TextColor);
	this->example0Label->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->example1Label->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->example2Label->setAnchorPoint(Vec2(0.0f, 0.5f));
}

bool ControlFlowExamplesPage::usesStack() const
{
	return this->operation == Operation::Call || this->operation == Operation::Ret;
}

unsigned long long ControlFlowExamplesPage::getTarget(int exampleIndex) const
{
	switch (this->operation)
	{
		case Operation::Loop:
		{
			const unsigned long long targets[] = { 80, 120, 160 };
			return targets[exampleIndex];
		}
		default:
		{
			const unsigned long long targets[] = { 240, 320, 400 };
			return targets[exampleIndex];
		}
	}
}

unsigned long long ControlFlowExamplesPage::getInstructionSize() const
{
	switch (this->operation)
	{
		case Operation::Nop: return 1;
		case Operation::Loop: return 2;
		default: return 5;
	}
}

LocalizedString* ControlFlowExamplesPage::buildInstructionString()
{
	switch (this->operation)
	{
		case Operation::Jmp: return Strings::Menus_Hacking_Lexicon_Assembly_Jmp::create();
		case Operation::Call: return ConstantString::create("call %s1");
		case Operation::Loop: return ConstantString::create("loop %s1");
		default: return ConstantString::create("");
	}
}
