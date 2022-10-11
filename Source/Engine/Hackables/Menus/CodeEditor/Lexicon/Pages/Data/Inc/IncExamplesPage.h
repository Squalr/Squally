#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlock;
class TextPanel;

class IncExamplesPage : public LexiconPage
{
public:
	static IncExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	IncExamplesPage();
	virtual ~IncExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* incButton = nullptr;
	ClickableTextNode* incPtrButton = nullptr;
	ClickableTextNode* incPtrOffsetButton = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelpButton = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp = nullptr;
	LocalizedLabel* incLabel = nullptr;
	LocalizedLabel* incPtrLabel = nullptr;
	LocalizedLabel* incPtrOffsetLabel = nullptr;
};
