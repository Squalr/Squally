#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Components/RegisterBlock.h"
#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class ClickableTextNode;
class ConstantString;
class LocalizedLabel;
class LocalizedString;

class BinaryExamplesPage : public LexiconPage
{
public:
	enum class Operation
	{
		And,
		Or,
		Xor,
		Shl,
		Shr,
		Not,
		Bswap,
	};

	static BinaryExamplesPage* create(Operation operation);

	static const std::string AndIdentifier;
	static const std::string OrIdentifier;
	static const std::string XorIdentifier;
	static const std::string ShlIdentifier;
	static const std::string ShrIdentifier;
	static const std::string NotIdentifier;
	static const std::string BswapIdentifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef LexiconPage super;

	BinaryExamplesPage(Operation operation);
	virtual ~BinaryExamplesPage();

	static const std::string& getIdentifier(Operation operation);

	void resetState();
	void executeExample(int exampleIndex);
	void highlightExample(int exampleIndex);
	void clearHighlights();
	void addExampleChildren();
	void buildExampleLabels();
	void setDisplayMode(RegisterBlock::DisplayMode displayMode);
	ClickableTextNode* buildFormatButton(std::string text);
	std::string formatOperandValue(unsigned long long value);
	unsigned long long getImmediate0() const;
	unsigned long long getImmediate1() const;
	int getRegisterBitCount() const;

	LocalizedString* buildInstructionString();
	LocalizedString* registerAString();
	LocalizedString* registerBString();
	LocalizedString* registerCString();
	LocalizedString* registerDString();
	LocalizedString* indexRegisterString();
	LocalizedString* pointerRegisterString();

	unsigned long long getWordMask() const;
	unsigned long long byteSwap(unsigned long long value) const;

	Operation operation = Operation::And;
	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* example0Button = nullptr;
	ClickableTextNode* example1Button = nullptr;
	ClickableTextNode* example2Button = nullptr;
	ClickableTextNode* example3Button = nullptr;
	ClickableTextNode* binaryButton = nullptr;
	ClickableTextNode* decimalButton = nullptr;
	ClickableTextNode* hexButton = nullptr;
	LocalizedLabel* example0Label = nullptr;
	LocalizedLabel* example1Label = nullptr;
	LocalizedLabel* example2Label = nullptr;
	LocalizedLabel* example3Label = nullptr;
	ConstantString* immediate0String = nullptr;
	ConstantString* immediate1String = nullptr;
	RegisterBlock::DisplayMode displayMode = RegisterBlock::DisplayMode::Bin;
};
