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
	virtual ~MovExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* movRegImmButton = nullptr;
	ClickableTextNode* movRegRegButton = nullptr;
	ClickableTextNode* movPtrImmButton = nullptr;
	ClickableTextNode* movPtrRegButton = nullptr;
	ClickableTextNode* movPtrOffsetImmButton = nullptr;
	ClickableTextNode* movPtrOffsetRegButton = nullptr;
	ClickableNode* remainderHelpButton = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelp4Button = nullptr;
	ClickableNode* offsetHelp8Button = nullptr;
	TextPanel* textPanelRemainderHelp = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp4 = nullptr;
	TextPanel* textPanelOffsetHelp8 = nullptr;
	LocalizedLabel* movRegImmLabel = nullptr;
	LocalizedLabel* movRegRegLabel = nullptr;
	LocalizedLabel* movPtrImmLabel = nullptr;
	LocalizedLabel* movPtrRegLabel = nullptr;
	LocalizedLabel* movPtrOffsetImmLabel = nullptr;
	LocalizedLabel* movPtrOffsetRegLabel = nullptr;
};
