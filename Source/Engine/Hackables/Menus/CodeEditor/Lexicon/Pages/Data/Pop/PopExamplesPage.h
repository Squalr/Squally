#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlock;
class StackBlock;
class TextPanel;

class PopExamplesPage : public LexiconPage
{
public:
	static PopExamplesPage* create();

	static const std::string Identifier;

protected:
	PopExamplesPage();
	virtual ~PopExamplesPage();

	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	void resetState();

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	StackBlock* stackBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* popButton = nullptr;
	ClickableTextNode* popPtrButton = nullptr;
	ClickableTextNode* popPtrOffsetButton = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelpButton = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp = nullptr;
	LocalizedLabel* popLabel = nullptr;
	LocalizedLabel* popPtrLabel = nullptr;
	LocalizedLabel* popPtrOffsetLabel = nullptr;
};
