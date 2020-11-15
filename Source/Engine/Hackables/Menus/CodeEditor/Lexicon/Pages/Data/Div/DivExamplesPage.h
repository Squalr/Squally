#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

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
	DivExamplesPage();
	virtual ~DivExamplesPage();

	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	void resetState();
	unsigned long long safeDiv(unsigned long long num, unsigned long long denom);
	unsigned long long safeMod(unsigned long long num, unsigned long long denom);

	LocalizedLabel* examplesLabel;
	RegisterBlock* registerBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* divImmButton;
	ClickableTextNode* divRegButton;
	ClickableTextNode* divPtrButton;
	ClickableTextNode* divPtrOffsetButton;
	ClickableTextNode* divPtrOffset2Button;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelp4Button;
	ClickableNode* offsetHelp8Button;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp4;
	TextPanel* textPanelOffsetHelp8;
	LocalizedLabel* divImmLabel;
	LocalizedLabel* divRegLabel;
	LocalizedLabel* divPtrLabel;
	LocalizedLabel* divPtrOffsetLabel;
	LocalizedLabel* divPtrOffsetLabel2;
};
