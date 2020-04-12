#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

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
	~MulExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel;
	RegisterBlock* registerBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* mulRegImmButton;
	ClickableTextNode* mulRegRegButton;
	ClickableTextNode* mulPtrImmButton;
	ClickableTextNode* mulPtrRegButton;
	ClickableTextNode* mulPtrOffsetImmButton;
	ClickableTextNode* mulPtrOffsetRegButton;
	ClickableNode* remainderHelpButton;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelp4Button;
	ClickableNode* offsetHelp8Button;
	TextPanel* textPanelRemainderHelp;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp4;
	TextPanel* textPanelOffsetHelp8;
	LocalizedLabel* mulRegImmLabel;
	LocalizedLabel* mulRegRegLabel;
	LocalizedLabel* mulPtrImmLabel;
	LocalizedLabel* mulPtrRegLabel;
	LocalizedLabel* mulPtrOffsetImmLabel;
	LocalizedLabel* mulPtrOffsetRegLabel;
};
