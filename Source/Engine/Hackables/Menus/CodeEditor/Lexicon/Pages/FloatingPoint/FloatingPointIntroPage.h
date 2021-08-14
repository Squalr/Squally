#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class FloatingPointIntroPage : public LexiconPage
{
public:
	static FloatingPointIntroPage* create();

	static const std::string Identifier;

protected:
	FloatingPointIntroPage();
	virtual ~FloatingPointIntroPage();
	
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	cocos2d::Sprite* skullSprite = nullptr;
	cocos2d::Sprite* chapterSprite = nullptr;
	LocalizedLabel* introText = nullptr;
	LocalizedLabel* titleLabel = nullptr;
};
