#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;

class BinarySelectPage : public LexiconPage
{
public:
	static BinarySelectPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	BinarySelectPage();
	~BinarySelectPage();

	cocos2d::Sprite* decorLine;
	LocalizedLabel* operationSelectLabel;
	ClickableTextNode* andOperationButton;
	ClickableTextNode* orOperationButton;
	ClickableTextNode* xorOperationButton;
	ClickableTextNode* shlOperationButton;
	ClickableTextNode* shrOperationButton;
	ClickableTextNode* notOperationButton;
	ClickableTextNode* bswapOperationButton;
	LocalizedLabel* introText;
};
