#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class NopPage : public LexiconPage
{
public:
	static NopPage* create();
	
private:
	typedef LexiconPage super;
	NopPage();
	~NopPage();

	cocos2d::Sprite* chapterSprite;
};
