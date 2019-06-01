#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class BinaryIntroPage : public LexiconPage
{
public:
	static BinaryIntroPage* create();

	static const std::string KeyBinaryIntroPage;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	BinaryIntroPage();
	~BinaryIntroPage();

	cocos2d::Sprite* bagSprite;
	cocos2d::Sprite* chapterSprite;
	LocalizedLabel* introText;
	LocalizedLabel* titleLabel;
};
