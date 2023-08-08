#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class RetPage : public LexiconPage
{
public:
	static RetPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	
	RetPage();
	virtual ~RetPage();

	cocos2d::Sprite* decorSprite = nullptr;
	cocos2d::Sprite* chapterSprite = nullptr;
	LocalizedLabel* introText = nullptr;
	LocalizedLabel* titleLabel = nullptr;
};
