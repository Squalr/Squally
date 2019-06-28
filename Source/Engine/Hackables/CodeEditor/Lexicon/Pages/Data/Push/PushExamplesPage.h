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

class PushExamplesPage : public LexiconPage
{
public:
	static PushExamplesPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	PushExamplesPage();
	~PushExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel;
	RegisterBlock* registerBlock;
	StackBlock* stackBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* pushButton;
	ClickableTextNode* pushPtrButton;
	ClickableTextNode* pushPtrOffsetButton;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelpButton;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp;
	LocalizedLabel* pushLabel;
	LocalizedLabel* pushPtrLabel;
	LocalizedLabel* pushPtrOffsetLabel;
};
