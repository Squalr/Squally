#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

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
	virtual ~BinarySelectPage();

	cocos2d::Sprite* decorLine = nullptr;
	LocalizedLabel* operationSelectLabel = nullptr;
	ClickableTextNode* andOperationButton = nullptr;
	ClickableTextNode* orOperationButton = nullptr;
	ClickableTextNode* xorOperationButton = nullptr;
	ClickableTextNode* shlOperationButton = nullptr;
	ClickableTextNode* shrOperationButton = nullptr;
	ClickableTextNode* notOperationButton = nullptr;
	ClickableTextNode* bswapOperationButton = nullptr;
	LocalizedLabel* introText = nullptr;
};
