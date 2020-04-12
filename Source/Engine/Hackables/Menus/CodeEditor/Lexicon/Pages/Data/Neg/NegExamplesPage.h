#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

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
	~NegExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel;
	RegisterBlockSigned* registerBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* negButton;
	ClickableTextNode* negPtrButton;
	ClickableTextNode* negPtrOffsetButton;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelpButton;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp;
	LocalizedLabel* negLabel;
	LocalizedLabel* negPtrLabel;
	LocalizedLabel* negPtrOffsetLabel;
};
