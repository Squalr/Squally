#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;

class VectorSelectPage : public LexiconPage
{
public:
	static VectorSelectPage* create();

	static const std::string Identifier;

protected:
	VectorSelectPage();
	virtual ~VectorSelectPage();
	
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	cocos2d::Sprite* decorLine = nullptr;
	LocalizedLabel* operationSelectLabel = nullptr;
	ClickableTextNode* addssOperationButton = nullptr;
	ClickableTextNode* comissOperationButton = nullptr;
	ClickableTextNode* divssOperationButton = nullptr;
	ClickableTextNode* maxssOperationButton = nullptr;
	ClickableTextNode* minssOperationButton = nullptr;
	ClickableTextNode* mulssOperationButton = nullptr;
	ClickableTextNode* sqrtssOperationButton = nullptr;
	ClickableTextNode* subssOperationButton = nullptr;
	LocalizedLabel* introText = nullptr;
};
