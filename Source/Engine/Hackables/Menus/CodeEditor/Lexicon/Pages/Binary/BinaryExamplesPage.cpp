#include "BinaryExamplesPage.h"

#include <iomanip>
#include <sstream>

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BinaryExamplesPage::AndIdentifier = "AND_EXAMPLES_PAGE";
const std::string BinaryExamplesPage::OrIdentifier = "OR_EXAMPLES_PAGE";
const std::string BinaryExamplesPage::XorIdentifier = "XOR_EXAMPLES_PAGE";
const std::string BinaryExamplesPage::ShlIdentifier = "SHL_EXAMPLES_PAGE";
const std::string BinaryExamplesPage::ShrIdentifier = "SHR_EXAMPLES_PAGE";
const std::string BinaryExamplesPage::NotIdentifier = "NOT_EXAMPLES_PAGE";
const std::string BinaryExamplesPage::BswapIdentifier = "BSWAP_EXAMPLES_PAGE";

BinaryExamplesPage* BinaryExamplesPage::create(Operation operation)
{
	BinaryExamplesPage* instance = new BinaryExamplesPage(operation);

	instance->autorelease();

	return instance;
}

BinaryExamplesPage::BinaryExamplesPage(Operation operation) : super(BinaryExamplesPage::getIdentifier(operation), PageType::Right)
{
	this->operation = operation;
	this->examplesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Hacking_Lexicon_Examples::create());
	this->registerBlock = RegisterBlock::create(true, true);
	this->resetButton = this->buildResetButton();
	this->example0Button = this->buildExecuteButton();
	this->example1Button = this->buildExecuteButton();
	this->example2Button = this->buildExecuteButton();
	this->example3Button = this->buildExecuteButton();
	this->binaryButton = this->buildFormatButton("BIN");
	this->decimalButton = this->buildFormatButton("DEC");
	this->hexButton = this->buildFormatButton("HEX");
	this->immediate0String = ConstantString::create(this->formatOperandValue(this->getImmediate0()));
	this->immediate1String = ConstantString::create(this->formatOperandValue(this->getImmediate1()));

	this->examplesLabel->setTextColor(super::TextColor);

	this->buildExampleLabels();
	this->resetState();
	this->setDisplayMode(RegisterBlock::DisplayMode::Bin);
	this->addExampleChildren();
}

BinaryExamplesPage::~BinaryExamplesPage()
{
}

const std::string& BinaryExamplesPage::getIdentifier(Operation operation)
{
	switch (operation)
	{
		case Operation::And: return BinaryExamplesPage::AndIdentifier;
		case Operation::Or: return BinaryExamplesPage::OrIdentifier;
		case Operation::Xor: return BinaryExamplesPage::XorIdentifier;
		case Operation::Shl: return BinaryExamplesPage::ShlIdentifier;
		case Operation::Shr: return BinaryExamplesPage::ShrIdentifier;
		case Operation::Not: return BinaryExamplesPage::NotIdentifier;
		case Operation::Bswap: return BinaryExamplesPage::BswapIdentifier;
		default: return BinaryExamplesPage::AndIdentifier;
	}
}

void BinaryExamplesPage::initializePositions()
{
	super::initializePositions();

	const float buttonOffset = -32.0f;
	const float buttonSpacing = -64.0f;

	this->registerBlock->setPosition(Vec2(0.0f, 160.0f));
	this->examplesLabel->setPosition(Vec2(0.0f, super::ChapterLocation.y - 16.0f));
	this->example0Button->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 0.0f));
	this->example1Button->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 1.0f));
	this->example2Button->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 2.0f));
	this->example3Button->setPosition(Vec2(-180.0f, buttonOffset + buttonSpacing * 3.0f));
	this->example0Label->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 0.0f));
	this->example1Label->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 1.0f));
	this->example2Label->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 2.0f));
	this->example3Label->setPosition(Vec2(-72.0f, buttonOffset + buttonSpacing * 3.0f));
	this->binaryButton->setPosition(Vec2(-112.0f, -280.0f));
	this->decimalButton->setPosition(Vec2(0.0f, -280.0f));
	this->hexButton->setPosition(Vec2(112.0f, -280.0f));
	this->resetButton->setPosition(Vec2(0.0f, -336.0f));
}

void BinaryExamplesPage::initializeListeners()
{
	super::initializeListeners();

	this->resetButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->resetState();
	});

	this->example0Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->executeExample(0); });
	this->example1Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->executeExample(1); });
	this->example2Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->executeExample(2); });
	this->example3Button->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->executeExample(3); });
	this->binaryButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setDisplayMode(RegisterBlock::DisplayMode::Bin); });
	this->decimalButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setDisplayMode(RegisterBlock::DisplayMode::Dec); });
	this->hexButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { this->setDisplayMode(RegisterBlock::DisplayMode::Hex); });

	this->example0Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightExample(0); });
	this->example1Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightExample(1); });
	this->example2Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightExample(2); });
	this->example3Button->setMouseOverCallback([=](InputEvents::MouseEventArgs*) { this->highlightExample(3); });

	this->example0Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*) { this->clearHighlights(); });
	this->example1Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*) { this->clearHighlights(); });
	this->example2Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*) { this->clearHighlights(); });
	this->example3Button->setMouseOutCallback([=](InputEvents::MouseEventArgs*) { this->clearHighlights(); });
}

void BinaryExamplesPage::resetState()
{
	switch (this->operation)
	{
		case Operation::Shl:
		{
			this->registerBlock->initEax(0x00000081ULL);
			this->registerBlock->initEbx(0x000000F0ULL);
			this->registerBlock->initEcx(0x00FF0000ULL);
			this->registerBlock->initEdx(0x80000001ULL);
			break;
		}
		case Operation::Shr:
		{
			this->registerBlock->initEax(0x80000001ULL);
			this->registerBlock->initEbx(0xF0000000ULL);
			this->registerBlock->initEcx(0x00FF0000ULL);
			this->registerBlock->initEdx(0x00000001ULL);
			break;
		}
		case Operation::Not:
		{
			this->registerBlock->initEax(0x00000000ULL);
			this->registerBlock->initEbx(0xFFFFFFFFULL);
			this->registerBlock->initEcx(0xAAAAAAAAULL);
			this->registerBlock->initEdx(0x0F0F0F0FULL);
			break;
		}
		case Operation::Bswap:
		{
			this->registerBlock->initEax(0x12345678ULL);
			this->registerBlock->initEbx(0xAABBCCDDULL);
			this->registerBlock->initEcx(0x0F1E2D3CULL);
			this->registerBlock->initEdx(0x80402010ULL);
			break;
		}
		default:
		{
			this->registerBlock->initEax(0xCCAAF00FULL);
			this->registerBlock->initEbx(0x3333CCCCULL);
			this->registerBlock->initEcx(0xAAAAAAAAULL);
			this->registerBlock->initEdx(0x5555FFFFULL);
			break;
		}
	}

	this->registerBlock->initEdi(0xF0F00F0FULL);
	this->registerBlock->initEsi(0x0FF00FF0ULL);
	this->registerBlock->initEbp(0x00FF00FFULL);
	this->registerBlock->initEsp(0xFF00FF00ULL);
	this->registerBlock->initEip(0x5A5AA5A5ULL);
}

void BinaryExamplesPage::executeExample(int exampleIndex)
{
	const unsigned long long mask = this->getWordMask();

	switch (this->operation)
	{
		case Operation::And:
		{
			if (exampleIndex == 0) { this->registerBlock->setEax(this->registerBlock->getEax() & this->getImmediate0()); }
			else if (exampleIndex == 1) { this->registerBlock->setEbx(this->registerBlock->getEbx() & this->getImmediate1()); }
			else if (exampleIndex == 2) { this->registerBlock->setEcx(this->registerBlock->getEcx() & this->registerBlock->getEdx()); }
			else { this->registerBlock->setEsi(this->registerBlock->getEsi() & this->registerBlock->getEbp()); }
			break;
		}
		case Operation::Or:
		{
			if (exampleIndex == 0) { this->registerBlock->setEax(this->registerBlock->getEax() | this->getImmediate0()); }
			else if (exampleIndex == 1) { this->registerBlock->setEbx(this->registerBlock->getEbx() | this->getImmediate1()); }
			else if (exampleIndex == 2) { this->registerBlock->setEcx(this->registerBlock->getEcx() | this->registerBlock->getEdx()); }
			else { this->registerBlock->setEsi(this->registerBlock->getEsi() | this->registerBlock->getEbp()); }
			break;
		}
		case Operation::Xor:
		{
			if (exampleIndex == 0) { this->registerBlock->setEax(this->registerBlock->getEax() ^ this->getImmediate0()); }
			else if (exampleIndex == 1) { this->registerBlock->setEbx(this->registerBlock->getEbx() ^ this->getImmediate1()); }
			else if (exampleIndex == 2) { this->registerBlock->setEcx(this->registerBlock->getEcx() ^ this->registerBlock->getEdx()); }
			else { this->registerBlock->setEsi(this->registerBlock->getEsi() ^ this->registerBlock->getEbp()); }
			break;
		}
		case Operation::Shl:
		{
			if (exampleIndex == 0) { this->registerBlock->setEax((this->registerBlock->getEax() << 1) & mask); }
			else if (exampleIndex == 1) { this->registerBlock->setEbx((this->registerBlock->getEbx() << 4) & mask); }
			else if (exampleIndex == 2) { this->registerBlock->setEcx((this->registerBlock->getEcx() << 8) & mask); }
			else { this->registerBlock->setEdx((this->registerBlock->getEdx() << 1) & mask); }
			break;
		}
		case Operation::Shr:
		{
			if (exampleIndex == 0) { this->registerBlock->setEax(this->registerBlock->getEax() >> 1); }
			else if (exampleIndex == 1) { this->registerBlock->setEbx(this->registerBlock->getEbx() >> 4); }
			else if (exampleIndex == 2) { this->registerBlock->setEcx(this->registerBlock->getEcx() >> 8); }
			else { this->registerBlock->setEdx(this->registerBlock->getEdx() >> 1); }
			break;
		}
		case Operation::Not:
		{
			if (exampleIndex == 0) { this->registerBlock->setEax((~this->registerBlock->getEax()) & mask); }
			else if (exampleIndex == 1) { this->registerBlock->setEbx((~this->registerBlock->getEbx()) & mask); }
			else if (exampleIndex == 2) { this->registerBlock->setEcx((~this->registerBlock->getEcx()) & mask); }
			else { this->registerBlock->setEdx((~this->registerBlock->getEdx()) & mask); }
			break;
		}
		case Operation::Bswap:
		{
			if (exampleIndex == 0) { this->registerBlock->setEax(this->byteSwap(this->registerBlock->getEax())); }
			else if (exampleIndex == 1) { this->registerBlock->setEbx(this->byteSwap(this->registerBlock->getEbx())); }
			else if (exampleIndex == 2) { this->registerBlock->setEcx(this->byteSwap(this->registerBlock->getEcx())); }
			else { this->registerBlock->setEdx(this->byteSwap(this->registerBlock->getEdx())); }
			break;
		}
	}
}

void BinaryExamplesPage::highlightExample(int exampleIndex)
{
	if (this->operation == Operation::Bswap)
	{
		if (exampleIndex == 0) { this->registerBlock->highlightEax(true); }
		else if (exampleIndex == 1) { this->registerBlock->highlightEbx(true); }
		else if (exampleIndex == 2) { this->registerBlock->highlightEcx(true); }
		else { this->registerBlock->highlightEdx(true); }
		return;
	}

	if (exampleIndex == 0)
	{
		this->registerBlock->highlightEax(true);
	}
	else if (exampleIndex == 1)
	{
		this->registerBlock->highlightEbx(true);
	}
	else if (exampleIndex == 2)
	{
		if (this->operation == Operation::And || this->operation == Operation::Or || this->operation == Operation::Xor)
		{
			this->registerBlock->highlightEcx(true);
			this->registerBlock->highlightEdx(false);
		}
		else
		{
			this->registerBlock->highlightEcx(true);
		}
	}
	else
	{
		if (this->operation == Operation::And || this->operation == Operation::Or || this->operation == Operation::Xor)
		{
			this->registerBlock->highlightEsi(true);
			this->registerBlock->highlightEbp(false);
		}
		else
		{
			this->registerBlock->highlightEdx(true);
		}
	}
}

void BinaryExamplesPage::clearHighlights()
{
	this->registerBlock->clearHighlights();
}

void BinaryExamplesPage::addExampleChildren()
{
	this->addChild(this->examplesLabel);
	this->addChild(this->registerBlock);
	this->addChild(this->resetButton);
	this->addChild(this->example0Button);
	this->addChild(this->example1Button);
	this->addChild(this->example2Button);
	this->addChild(this->example3Button);
	this->addChild(this->example0Label);
	this->addChild(this->example1Label);
	this->addChild(this->example2Label);
	this->addChild(this->example3Label);
	this->addChild(this->binaryButton);
	this->addChild(this->decimalButton);
	this->addChild(this->hexButton);
}

void BinaryExamplesPage::setDisplayMode(RegisterBlock::DisplayMode displayMode)
{
	this->displayMode = displayMode;
	this->registerBlock->setDisplayBitCount(this->getRegisterBitCount());
	this->registerBlock->setDisplayMode(displayMode);
	this->immediate0String->setString(this->formatOperandValue(this->getImmediate0()));
	this->immediate1String->setString(this->formatOperandValue(this->getImmediate1()));
}

ClickableTextNode* BinaryExamplesPage::buildFormatButton(std::string text)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(text));
	LocalizedLabel* labelSelected = label->clone();
	std::string buttonResource = UIResources::Menus_LexiconMenu_DecButton;
	std::string buttonSelectedResource = UIResources::Menus_LexiconMenu_DecButtonSelected;

	if (text == "BIN")
	{
		buttonResource = UIResources::Menus_LexiconMenu_BinButton;
		buttonSelectedResource = UIResources::Menus_LexiconMenu_BinButtonSelected;
	}
	else if (text == "HEX")
	{
		buttonResource = UIResources::Menus_LexiconMenu_HexButton;
		buttonSelectedResource = UIResources::Menus_LexiconMenu_HexButtonSelected;
	}

	ClickableTextNode* button = ClickableTextNode::create(label, labelSelected, buttonResource, buttonSelectedResource);

	label->setTextColor(LexiconPage::TextColor);
	labelSelected->setTextColor(LexiconPage::TextColor);

	return button;
}

std::string BinaryExamplesPage::formatOperandValue(unsigned long long value)
{
	switch (this->displayMode)
	{
		case RegisterBlock::DisplayMode::Bin:
		{
			std::string result = "0b";

			for (int index = this->getRegisterBitCount() - 1; index >= 0; index--)
			{
				result += ((value >> index) & 1ULL) == 0 ? "0" : "1";
			}

			return result;
		}
		case RegisterBlock::DisplayMode::Hex:
		{
			std::stringstream stream;
			int digitCount = (this->getRegisterBitCount() + 3) / 4;

			stream << std::uppercase << std::hex << std::setfill('0') << std::setw(digitCount) << value;

			return "0x" + stream.str();
		}
		default:
		{
			return std::to_string(value);
		}
	}
}

unsigned long long BinaryExamplesPage::getImmediate0() const
{
	return 0x0F0FF0F0ULL;
}

unsigned long long BinaryExamplesPage::getImmediate1() const
{
	return 0x00FF00FFULL;
}

int BinaryExamplesPage::getRegisterBitCount() const
{
	return 32;
}

void BinaryExamplesPage::buildExampleLabels()
{
	LocalizedString* op = this->buildInstructionString();

	if (this->operation == Operation::Not || this->operation == Operation::Bswap)
	{
		this->example0Label = this->createInstructionLabelSingle(op->clone(), this->registerAString());
		this->example1Label = this->createInstructionLabelSingle(op->clone(), this->registerBString());
		this->example2Label = this->createInstructionLabelSingle(op->clone(), this->registerCString());
		this->example3Label = this->createInstructionLabelSingle(op->clone(), this->registerDString());
		return;
	}

	if (this->operation == Operation::Shl || this->operation == Operation::Shr)
	{
		this->example0Label = this->createInstructionLabelDouble(op->clone(), this->registerAString(), ConstantString::create("1"));
		this->example1Label = this->createInstructionLabelDouble(op->clone(), this->registerBString(), ConstantString::create("4"));
		this->example2Label = this->createInstructionLabelDouble(op->clone(), this->registerCString(), ConstantString::create("8"));
		this->example3Label = this->createInstructionLabelDouble(op->clone(), this->registerDString(), ConstantString::create("1"));
		return;
	}

	this->example0Label = this->createInstructionLabelDouble(op->clone(), this->registerAString(), this->immediate0String);
	this->example1Label = this->createInstructionLabelDouble(op->clone(), this->registerBString(), this->immediate1String);
	this->example2Label = this->createInstructionLabelDouble(op->clone(), this->registerCString(), this->registerDString());
	this->example3Label = this->createInstructionLabelDouble(op->clone(), this->indexRegisterString(), this->pointerRegisterString());
}

LocalizedString* BinaryExamplesPage::buildInstructionString()
{
	switch (this->operation)
	{
		case Operation::And: return ConstantString::create("and %s1, %s2");
		case Operation::Or: return ConstantString::create("or %s1, %s2");
		case Operation::Xor: return ConstantString::create("xor %s1, %s2");
		case Operation::Shl: return ConstantString::create("shl %s1, %s2");
		case Operation::Shr: return ConstantString::create("shr %s1, %s2");
		case Operation::Not: return ConstantString::create("not %s1");
		case Operation::Bswap: return ConstantString::create("bswap %s1");
		default: return ConstantString::create("");
	}
}

LocalizedString* BinaryExamplesPage::registerAString()
{
	return Strings::Menus_Hacking_Lexicon_Assembly_RegisterEax::create();
}

LocalizedString* BinaryExamplesPage::registerBString()
{
	return Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbx::create();
}

LocalizedString* BinaryExamplesPage::registerCString()
{
	return Strings::Menus_Hacking_Lexicon_Assembly_RegisterEcx::create();
}

LocalizedString* BinaryExamplesPage::registerDString()
{
	return Strings::Menus_Hacking_Lexicon_Assembly_RegisterEdx::create();
}

LocalizedString* BinaryExamplesPage::indexRegisterString()
{
	return Strings::Menus_Hacking_Lexicon_Assembly_RegisterEsi::create();
}

LocalizedString* BinaryExamplesPage::pointerRegisterString()
{
	return Strings::Menus_Hacking_Lexicon_Assembly_RegisterEbp::create();
}

unsigned long long BinaryExamplesPage::getWordMask() const
{
	return this->getRegisterBitCount() >= 64 ? ~0ULL : ((1ULL << this->getRegisterBitCount()) - 1ULL);
}

unsigned long long BinaryExamplesPage::byteSwap(unsigned long long value) const
{
	unsigned long long result = 0;
	int byteCount = this->getRegisterBitCount() / 8;

	value &= this->getWordMask();

	for (int index = 0; index < byteCount; index++)
	{
		result = (result << 8) | ((value >> (index * 8)) & 0xFFULL);
	}

	return result;
}
