#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

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
	virtual ~DataSelectPage();

	cocos2d::Sprite* decorLine = nullptr;
	LocalizedLabel* operationSelectLabel = nullptr;
	ClickableTextNode* incOperationButton = nullptr;
	ClickableTextNode* decOperationButton = nullptr;
	ClickableTextNode* addOperationButton = nullptr;
	ClickableTextNode* subOperationButton = nullptr;
	ClickableTextNode* divOperationButton = nullptr;
	ClickableTextNode* mulOperationButton = nullptr;
	ClickableTextNode* movOperationButton = nullptr;
	ClickableTextNode* pushOperationButton = nullptr;
	ClickableTextNode* popOperationButton = nullptr;
	ClickableTextNode* negOperationButton = nullptr;
	LocalizedLabel* introText = nullptr;
};
