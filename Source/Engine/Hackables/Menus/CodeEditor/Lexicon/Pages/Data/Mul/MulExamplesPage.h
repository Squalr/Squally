#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class RegisterBlock;
class TextPanel;

class MulExamplesPage : public LexiconPage
{
public:
	static MulExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	MulExamplesPage();
	virtual ~MulExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel = nullptr;
	RegisterBlock* registerBlock = nullptr;
	ClickableTextNode* resetButton = nullptr;
	ClickableTextNode* mulRegImmButton = nullptr;
	ClickableTextNode* mulRegRegButton = nullptr;
	ClickableTextNode* mulPtrImmButton = nullptr;
	ClickableTextNode* mulPtrRegButton = nullptr;
	ClickableTextNode* mulPtrOffsetImmButton = nullptr;
	ClickableTextNode* mulPtrOffsetRegButton = nullptr;
	ClickableNode* remainderHelpButton = nullptr;
	ClickableNode* pointerHelpButton = nullptr;
	ClickableNode* offsetHelp4Button = nullptr;
	ClickableNode* offsetHelp8Button = nullptr;
	TextPanel* textPanelRemainderHelp = nullptr;
	TextPanel* textPanelPointerHelp = nullptr;
	TextPanel* textPanelOffsetHelp4 = nullptr;
	TextPanel* textPanelOffsetHelp8 = nullptr;
	LocalizedLabel* mulRegImmLabel = nullptr;
	LocalizedLabel* mulRegRegLabel = nullptr;
	LocalizedLabel* mulPtrImmLabel = nullptr;
	LocalizedLabel* mulPtrRegLabel = nullptr;
	LocalizedLabel* mulPtrOffsetImmLabel = nullptr;
	LocalizedLabel* mulPtrOffsetRegLabel = nullptr;
};
