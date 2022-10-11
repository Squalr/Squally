#pragma once

#include "Engine/Hackables/Menus/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class OrPage : public LexiconPage
{
public:
	static OrPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;

	OrPage();
	virtual ~OrPage();

	cocos2d::Sprite* decorSprite = nullptr;
	cocos2d::Sprite* chapterSprite = nullptr;
	LocalizedLabel* introText = nullptr;
	LocalizedLabel* titleLabel = nullptr;
};
