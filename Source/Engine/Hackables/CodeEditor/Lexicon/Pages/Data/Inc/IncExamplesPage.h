#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

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
	~IncExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel;
	RegisterBlock* registerBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* incButton;
	ClickableTextNode* incPtrButton;
	ClickableTextNode* incPtrOffsetButton;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelpButton;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp;
	LocalizedLabel* incLabel;
	LocalizedLabel* incPtrLabel;
	LocalizedLabel* incPtrOffsetLabel;
};
