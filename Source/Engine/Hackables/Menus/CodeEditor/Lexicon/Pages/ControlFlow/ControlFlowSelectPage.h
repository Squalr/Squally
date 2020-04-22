#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;

class ControlFlowSelectPage : public LexiconPage
{
public:
	static ControlFlowSelectPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	ControlFlowSelectPage();
	~ControlFlowSelectPage();

	cocos2d::Sprite* decorLine;
	LocalizedLabel* operationSelectLabel;
	ClickableTextNode* nopOperationButton;
	LocalizedLabel* introText;
};
