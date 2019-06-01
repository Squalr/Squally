#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class DataIntroPage : public LexiconPage
{
public:
	static DataIntroPage* create();

	static const std::string KeyDataIntroPage;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	DataIntroPage();
	~DataIntroPage();

	cocos2d::Sprite* bagSprite;
	cocos2d::Sprite* chapterSprite;
	LocalizedLabel* introText;
	LocalizedLabel* titleLabel;
};
