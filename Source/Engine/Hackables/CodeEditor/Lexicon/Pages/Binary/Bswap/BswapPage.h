#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class BswapPage : public LexiconPage
{
public:
	static BswapPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	BswapPage();
	~BswapPage();

	cocos2d::Sprite* decorSprite;
	cocos2d::Sprite* chapterSprite;
	LocalizedLabel* introText;
	LocalizedLabel* titleLabel;
};
