#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class ClickableTextNode;
class LocalizedLabel;
class LocalizedString;
class RegisterBlock;
class StackBlock;

class ControlFlowExamplesPage : public LexiconPage
{
public:
	enum class Operation
	{
		Nop,
		Jmp,
		Call,
		Ret,
		Loop,
	};

	static ControlFlowExamplesPage* create(Operation operation);

	static const std::string NopIdentifier;
	static const std::string JmpIdentifier;
	static const std::string CallIdentifier;
	static const std::string RetIdentifier;
	static const std::string LoopIdentifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef LexiconPage super;

	ControlFlowExamplesPage(Operation operation);
	virtual ~ControlFlowExamplesPage();

	static const std::string& getIdentifier(Operation operation);

	void resetState();
	void executeExample(int exampleIndex);
	void highlightExample(int exampleIndex);
	void clearHighlights();
	void addExampleChildren();
	void buildExampleLabels();

	bool usesStack() const;
	int getExampleCount() const;
	unsigned long long getTarget(int exampleIndex) const;
	unsigned long long getInstructionSize() const;
	LocalizedString* buildInstructionString();

	Operation operation = Operation::Nop;
	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	StackBlock* stackBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* example0Button = nullptr;
	ClickableTextNode* example1Button = nullptr;
	ClickableTextNode* example2Button = nullptr;
	LocalizedLabel* example0Label = nullptr;
	LocalizedLabel* example1Label = nullptr;
	LocalizedLabel* example2Label = nullptr;
};
