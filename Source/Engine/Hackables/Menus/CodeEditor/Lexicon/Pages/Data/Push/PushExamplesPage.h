#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlock;
class StackBlock;
class TextPanel;

class PushExamplesPage : public LexiconPage
{
public:
	static PushExamplesPage* create();

	static const std::string Identifier;

protected:
	PushExamplesPage();
	virtual ~PushExamplesPage();
	
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	void resetState();

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	StackBlock* stackBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* pushButton = nullptr;
	ClickableTextNode* pushPtrButton = nullptr;
	ClickableTextNode* pushPtrOffsetButton = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelpButton = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp = nullptr;
	LocalizedLabel* pushLabel = nullptr;
	LocalizedLabel* pushPtrLabel = nullptr;
	LocalizedLabel* pushPtrOffsetLabel = nullptr;
};
