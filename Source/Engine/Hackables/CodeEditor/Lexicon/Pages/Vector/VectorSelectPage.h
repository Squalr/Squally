#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

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
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	VectorSelectPage();
	~VectorSelectPage();

	cocos2d::Sprite* decorLine;
	LocalizedLabel* operationSelectLabel;
	ClickableTextNode* nopOperationButton;
	LocalizedLabel* introText;
};
