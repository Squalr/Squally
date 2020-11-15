#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlock;
class TextPanel;

class MovExamplesPage : public LexiconPage
{
public:
	static MovExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	MovExamplesPage();
	~MovExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel;
	RegisterBlock* registerBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* movRegImmButton;
	ClickableTextNode* movRegRegButton;
	ClickableTextNode* movPtrImmButton;
	ClickableTextNode* movPtrRegButton;
	ClickableTextNode* movPtrOffsetImmButton;
	ClickableTextNode* movPtrOffsetRegButton;
	ClickableNode* remainderHelpButton;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelp4Button;
	ClickableNode* offsetHelp8Button;
	TextPanel* textPanelRemainderHelp;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp4;
	TextPanel* textPanelOffsetHelp8;
	LocalizedLabel* movRegImmLabel;
	LocalizedLabel* movRegRegLabel;
	LocalizedLabel* movPtrImmLabel;
	LocalizedLabel* movPtrRegLabel;
	LocalizedLabel* movPtrOffsetImmLabel;
	LocalizedLabel* movPtrOffsetRegLabel;
};
