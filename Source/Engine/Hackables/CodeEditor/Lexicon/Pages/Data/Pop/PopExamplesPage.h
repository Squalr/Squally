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
class StackBlock;
class TextPanel;

class PopExamplesPage : public LexiconPage
{
public:
	static PopExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	PopExamplesPage();
	~PopExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel;
	RegisterBlock* registerBlock;
	StackBlock* stackBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* popButton;
	ClickableTextNode* popPtrButton;
	ClickableTextNode* popPtrOffsetButton;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelpButton;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp;
	LocalizedLabel* popLabel;
	LocalizedLabel* popPtrLabel;
	LocalizedLabel* popPtrOffsetLabel;
};
