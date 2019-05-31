#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class NopPage : public LexiconPage
{
public:
	static NopPage* create();

	static const std::string KeyNopPage;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	NopPage();
	~NopPage();

	cocos2d::Sprite* hourglassSprite;
	cocos2d::Sprite* chapterSprite;
	LocalizedLabel* introText;
	LocalizedLabel* nopLabel;
};
