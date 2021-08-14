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

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* divImmButton = nullptr;
	ClickableTextNode* divRegButton = nullptr;
	ClickableTextNode* divPtrButton = nullptr;
	ClickableTextNode* divPtrOffsetButton = nullptr;
	ClickableTextNode* divPtrOffset2Button = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelp4Button = nullptr;
	ClickableNode* offsetHelp8Button = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp4 = nullptr;
	TextPanel* textPanelOffsetHelp8 = nullptr;
	LocalizedLabel* divImmLabel = nullptr;
	LocalizedLabel* divRegLabel = nullptr;
	LocalizedLabel* divPtrLabel = nullptr;
	LocalizedLabel* divPtrOffsetLabel = nullptr;
	LocalizedLabel* divPtrOffsetLabel2 = nullptr;
};
