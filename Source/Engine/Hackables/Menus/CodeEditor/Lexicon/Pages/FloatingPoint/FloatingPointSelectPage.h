#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

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
	FloatingPointSelectPage();
	virtual ~FloatingPointSelectPage();
	
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	cocos2d::Sprite* decorLine = nullptr;
	LocalizedLabel* operationSelectLabel = nullptr;

	ClickableTextNode* fabsOperationButton = nullptr;
	ClickableTextNode* fcmovnbeOperationButton = nullptr;
	ClickableTextNode* fcosOperationButton = nullptr;
	ClickableTextNode* fiaddpOperationButton = nullptr;
	ClickableTextNode* ficomppOperationButton = nullptr;
	ClickableTextNode* fidivrpOperationButton = nullptr;
	ClickableTextNode* fildOperationButton = nullptr;
	ClickableTextNode* fimulpOperationButton = nullptr;
	ClickableTextNode* fistpOperationButton = nullptr;
	ClickableTextNode* fisubrpOperationButton = nullptr;
	ClickableTextNode* fld1OperationButton = nullptr;
	ClickableTextNode* fldpiOperationButton = nullptr;
	ClickableTextNode* fldzOperationButton = nullptr;
	ClickableTextNode* frndintOperationButton = nullptr;
	ClickableTextNode* fsinOperationButton = nullptr;
	ClickableTextNode* fsqrtPageOperationButton = nullptr;
	ClickableTextNode* ftstPageOperationButton = nullptr;
	ClickableTextNode* fxchPageOperationButton = nullptr;

	LocalizedLabel* introText = nullptr;
};
