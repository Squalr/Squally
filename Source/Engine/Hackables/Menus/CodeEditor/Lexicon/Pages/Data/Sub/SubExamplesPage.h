#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlock;
class TextPanel;

class SubExamplesPage : public LexiconPage
{
public:
	static SubExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	SubExamplesPage();
	~SubExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel;
	RegisterBlock* registerBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* subRegImmButton;
	ClickableTextNode* subRegRegButton;
	ClickableTextNode* subPtrImmButton;
	ClickableTextNode* subPtrRegButton;
	ClickableTextNode* subPtrOffsetImmButton;
	ClickableTextNode* subPtrOffsetRegButton;
	ClickableNode* remainderHelpButton;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelp4Button;
	ClickableNode* offsetHelp8Button;
	TextPanel* textPanelRemainderHelp;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp4;
	TextPanel* textPanelOffsetHelp8;
	LocalizedLabel* subRegImmLabel;
	LocalizedLabel* subRegRegLabel;
	LocalizedLabel* subPtrImmLabel;
	LocalizedLabel* subPtrRegLabel;
	LocalizedLabel* subPtrOffsetImmLabel;
	LocalizedLabel* subPtrOffsetRegLabel;
};
