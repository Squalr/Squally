#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlock;
class TextPanel;

class DecExamplesPage : public LexiconPage
{
public:
	static DecExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	DecExamplesPage();
	virtual ~DecExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* decButton = nullptr;
	ClickableTextNode* decPtrButton = nullptr;
	ClickableTextNode* decPtrOffsetButton = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelpButton = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp = nullptr;
	LocalizedLabel* decLabel = nullptr;
	LocalizedLabel* decPtrLabel = nullptr;
	LocalizedLabel* decPtrOffsetLabel = nullptr;
};
