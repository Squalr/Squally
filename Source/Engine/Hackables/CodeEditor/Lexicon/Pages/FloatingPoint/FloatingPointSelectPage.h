#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;

class FloatingPointSelectPage : public LexiconPage
{
public:
	static FloatingPointSelectPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	FloatingPointSelectPage();
	~FloatingPointSelectPage();

	cocos2d::Sprite* decorLine;
	LocalizedLabel* operationSelectLabel;
	ClickableTextNode* nopOperationButton;
	LocalizedLabel* introText;
};
