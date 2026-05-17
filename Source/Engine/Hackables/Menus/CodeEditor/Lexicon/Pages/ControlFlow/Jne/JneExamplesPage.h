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
class ConstantString;
class LocalizedLabel;
class LocalizedString;
class RegisterBlock;

class JneExamplesPage : public LexiconPage
{
public:
	static JneExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef LexiconPage super;

	JneExamplesPage();
	virtual ~JneExamplesPage();

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
	void buildAddressedCodeLabel(std::string address, LocalizedString* instruction);
	void buildCodeLabel(LocalizedString* text);
	LocalizedLabel* buildExampleLabel(LocalizedString* text);
	LocalizedString* buildRegisterSetupString(unsigned long long valueA, unsigned long long valueB);
	LocalizedString* registerAString();
	LocalizedString* registerBString();
	LocalizedString* registerCString();

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
	ConstantString* flagString = nullptr;
	std::vector<LocalizedLabel*> codeLabels;
	int selectedExampleIndex = 0;
};
