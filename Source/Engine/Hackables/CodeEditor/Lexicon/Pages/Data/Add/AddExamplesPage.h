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
	~AddExamplesPage();

	void resetState();

	LocalizedLabel* examplesLabel;
	RegisterBlock* registerBlock;
	ClickableTextNode* resetButton;
	ClickableTextNode* addRegImmButton;
	ClickableTextNode* addRegRegButton;
	ClickableTextNode* addPtrImmButton;
	ClickableTextNode* addPtrRegButton;
	ClickableTextNode* addPtrOffsetImmButton;
	ClickableTextNode* addPtrOffsetRegButton;
	ClickableNode* pointerHelpButton;
	ClickableNode* offsetHelp4Button;
	ClickableNode* offsetHelp8Button;
	TextPanel* textPanelPointerHelp;
	TextPanel* textPanelOffsetHelp4;
	TextPanel* textPanelOffsetHelp8;
	LocalizedLabel* addRegImmLabel;
	LocalizedLabel* addRegRegLabel;
	LocalizedLabel* addPtrImmLabel;
	LocalizedLabel* addPtrRegLabel;
	LocalizedLabel* addPtrOffsetImmLabel;
	LocalizedLabel* addPtrOffsetRegLabel;
};
