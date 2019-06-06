#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;

class DataSelectPage : public LexiconPage
{
public:
	static DataSelectPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	DataSelectPage();
	~DataSelectPage();

	cocos2d::Sprite* decorLine;
	LocalizedLabel* operationSelectLabel;
	ClickableTextNode* incOperationButton;
	ClickableTextNode* decOperationButton;
	ClickableTextNode* addOperationButton;
	ClickableTextNode* subOperationButton;
	ClickableTextNode* divOperationButton;
	ClickableTextNode* mulOperationButton;
	ClickableTextNode* movOperationButton;
	ClickableTextNode* pushOperationButton;
	ClickableTextNode* popOperationButton;
	ClickableTextNode* negOperationButton;
	LocalizedLabel* introText;
};
