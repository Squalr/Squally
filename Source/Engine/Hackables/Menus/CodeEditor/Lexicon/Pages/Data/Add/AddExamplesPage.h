#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlock;
class TextPanel;

class AddExamplesPage : public LexiconPage
{
public:
	static AddExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	AddExamplesPage();
	virtual ~AddExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* addRegImmButton = nullptr;
	ClickableTextNode* addRegRegButton = nullptr;
	ClickableTextNode* addPtrImmButton = nullptr;
	ClickableTextNode* addPtrRegButton = nullptr;
	ClickableTextNode* addPtrOffsetImmButton = nullptr;
	ClickableTextNode* addPtrOffsetRegButton = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelp4Button = nullptr;
	ClickableNode* offsetHelp8Button = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp4 = nullptr;
	TextPanel* textPanelOffsetHelp8 = nullptr;
	LocalizedLabel* addRegImmLabel = nullptr;
	LocalizedLabel* addRegRegLabel = nullptr;
	LocalizedLabel* addPtrImmLabel = nullptr;
	LocalizedLabel* addPtrRegLabel = nullptr;
	LocalizedLabel* addPtrOffsetImmLabel = nullptr;
	LocalizedLabel* addPtrOffsetRegLabel = nullptr;
};
