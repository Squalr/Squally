#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlock;
class TextPanel;

class DivExamplesPage : public LexiconPage
{
public:
	static DivExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	DivExamplesPage();
	~DivExamplesPage();

	void resetState();
	unsigned long long safeDiv(unsigned long long num, unsigned long long denom);

	LocalizedLabel* examplesLabel;
	RegisterBlock* registerBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* divRegImmButton;
	ClickableTextNode* divRegRegButton;
	ClickableTextNode* divPtrImmButton;
	ClickableTextNode* divPtrRegButton;
	ClickableTextNode* divPtrOffsetImmButton;
	ClickableTextNode* divPtrOffsetRegButton;
	ClickableNode* remainderHelpButton;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelp4Button;
	ClickableNode* offsetHelp8Button;
	TextPanel* textPanelRemainderHelp;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp4;
	TextPanel* textPanelOffsetHelp8;
	LocalizedLabel* divRegImmLabel;
	LocalizedLabel* divRegRegLabel;
	LocalizedLabel* divPtrImmLabel;
	LocalizedLabel* divPtrRegLabel;
	LocalizedLabel* divPtrOffsetImmLabel;
	LocalizedLabel* divPtrOffsetRegLabel;
};
