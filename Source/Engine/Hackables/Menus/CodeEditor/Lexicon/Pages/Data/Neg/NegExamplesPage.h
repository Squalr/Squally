#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlockSigned;
class TextPanel;

class NegExamplesPage : public LexiconPage
{
public:
	static NegExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	NegExamplesPage();
	virtual ~NegExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlockSigned* registerBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* negButton = nullptr;
	ClickableTextNode* negPtrButton = nullptr;
	ClickableTextNode* negPtrOffsetButton = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelpButton = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp = nullptr;
	LocalizedLabel* negLabel = nullptr;
	LocalizedLabel* negPtrLabel = nullptr;
	LocalizedLabel* negPtrOffsetLabel = nullptr;
};
