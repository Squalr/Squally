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
	virtual ~SubExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* subRegImmButton = nullptr;
	ClickableTextNode* subRegRegButton = nullptr;
	ClickableTextNode* subPtrImmButton = nullptr;
	ClickableTextNode* subPtrRegButton = nullptr;
	ClickableTextNode* subPtrOffsetImmButton = nullptr;
	ClickableTextNode* subPtrOffsetRegButton = nullptr;
	ClickableNode* remainderHelpButton = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelp4Button = nullptr;
	ClickableNode* offsetHelp8Button = nullptr;
	TextPanel* textPanelRemainderHelp = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp4 = nullptr;
	TextPanel* textPanelOffsetHelp8 = nullptr;
	LocalizedLabel* subRegImmLabel = nullptr;
	LocalizedLabel* subRegRegLabel = nullptr;
	LocalizedLabel* subPtrImmLabel = nullptr;
	LocalizedLabel* subPtrRegLabel = nullptr;
	LocalizedLabel* subPtrOffsetImmLabel = nullptr;
	LocalizedLabel* subPtrOffsetRegLabel = nullptr;
};
