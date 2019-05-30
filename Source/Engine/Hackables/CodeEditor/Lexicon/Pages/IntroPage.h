#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class IntroPage : public LexiconPage
{
public:
	static IntroPage* create();

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	IntroPage();
	~IntroPage();

	cocos2d::Sprite* chapterSprite;
};
