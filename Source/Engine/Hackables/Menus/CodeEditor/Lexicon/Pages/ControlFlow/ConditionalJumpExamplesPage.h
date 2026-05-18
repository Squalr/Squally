#pragma once

#include <string>
#include <vector>

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class DrawNode;
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class LocalizedString;
class RegisterBlock;

class ConditionalJumpExamplesPage : public LexiconPage
{
public:
	enum class Operation
	{
		Jnabe,
		Jne,
		Jngle,
		Jno,
		Jnp,
		Jns,
		Jnz,
		Jzcxz,
	};

	static ConditionalJumpExamplesPage* create(Operation operation);

	static const std::string JnabeIdentifier;
	static const std::string JneIdentifier;
	static const std::string JngleIdentifier;
	static const std::string JnoIdentifier;
	static const std::string JnpIdentifier;
	static const std::string JnsIdentifier;
	static const std::string JnzIdentifier;
	static const std::string JzcxzIdentifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef LexiconPage super;

	enum class SetupInstruction
	{
		Cmp,
		Add,
		Test,
		None,
	};

	ConditionalJumpExamplesPage(Operation operation);
	virtual ~ConditionalJumpExamplesPage();

	static const std::string& getIdentifier(Operation operation);

	void resetState();
	void setExample(int exampleIndex);
	void executeExample();
	void highlightSetAndReset();
	void highlightExecute();
	void clearHighlights();
	void hideSelectors();
	bool isMouseOverActionButton(cocos2d::Vec2 mouseCoords);
	void updateState(int exampleIndex, bool executeWholeExample);
	void updateCodeHighlights(bool jumps, bool executeWholeExample);
	void drawFlowArrows(bool jumps);
	void drawArrowSegment(cocos2d::Vec2 from, cocos2d::Vec2 to, const cocos2d::Color4F& color);
	ClickableTextNode* buildSetAndResetButton();
	void buildCodeLabels();
	void buildAddressedCodeLabel(std::string address, LocalizedString* instruction);
	void buildCodeLabel(LocalizedString* text);
	LocalizedLabel* buildExampleLabel(int exampleIndex);
	LocalizedString* buildRegisterSetupString(LocalizedString* registerString, unsigned long long value);
	LocalizedString* buildRegisterSetupString(unsigned long long valueA, unsigned long long valueB);
	LocalizedString* registerAString();
	LocalizedString* registerBString();
	LocalizedString* registerCString();
	LocalizedString* resultRegisterString();
	LocalizedString* setupInstructionString();
	LocalizedString* jumpInstructionString();
	LocalizedString* conditionString(int exampleIndex);
	LocalizedString* pathString(int exampleIndex);
	unsigned long long registerAValue(int exampleIndex) const;
	unsigned long long registerBValue(int exampleIndex) const;
	unsigned long long conditionRegisterValue(int exampleIndex) const;
	unsigned long long registerAExecutedValue(int exampleIndex) const;
	unsigned long long resultRegisterValue(int exampleIndex, bool executeWholeExample) const;
	bool jumps(int exampleIndex) const;
	bool usesRegisterBSelector() const;
	bool usesConditionRegisterSelector() const;
	bool usesHexDisplay() const;
	SetupInstruction setupInstruction() const;
	int jumpCodeIndex() const;
	int targetCodeIndex() const;
	std::string targetAddress() const;
	std::string setupAddress() const;
	std::string jumpAddress() const;
	std::string fallthroughAddress() const;
	std::string targetLabelAddress() const;
	std::string resultAddress() const;
	unsigned long long finalInstructionPointer() const;
	unsigned long long maxSignedValue() const;
	unsigned long long signBitValue() const;

	Operation operation = Operation::Jne;
	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	cocos2d::Sprite* codePanel = nullptr;
	cocos2d::Sprite* registerASelector = nullptr;
	cocos2d::Sprite* registerBSelector = nullptr;
	cocos2d::Sprite* instructionPointerSelector = nullptr;
	cocos2d::DrawNode* flowArrowNode = nullptr;
	ClickableTextNode* executeButton = nullptr;
	ClickableTextNode* example0Button = nullptr;
	ClickableTextNode* example1Button = nullptr;
	ClickableTextNode* example2Button = nullptr;
	LocalizedLabel* example0Label = nullptr;
	LocalizedLabel* example1Label = nullptr;
	LocalizedLabel* example2Label = nullptr;
	LocalizedLabel* flagLabel = nullptr;
	LocalizedLabel* pathLabel = nullptr;
	std::vector<LocalizedLabel*> codeLabels;
	int selectedExampleIndex = 0;
};
