#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class VectorIntroPage : public LexiconPage
{
public:
	static VectorIntroPage* create();

	static const std::string KeyVectorIntroPage;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	VectorIntroPage();
	~VectorIntroPage();

	cocos2d::Sprite* barrelSprite;
	cocos2d::Sprite* chapterSprite;
	LocalizedLabel* introText;
	LocalizedLabel* titleLabel;
};
