#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class BinaryIntroPage : public LexiconPage
{
public:
	static BinaryIntroPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	BinaryIntroPage();
	virtual ~BinaryIntroPage();

	cocos2d::Sprite* hammerSprite = nullptr;
	cocos2d::Sprite* chapterSprite = nullptr;
	LocalizedLabel* introText = nullptr;
	LocalizedLabel* titleLabel = nullptr;
};
