#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LexiconPage;
class LocalizedSprite;

class Lexicon : public Hud
{
public:
	static Lexicon* create();

private:
	typedef Hud super;
	Lexicon();
	~Lexicon();

	void initializePositions() override;
	void initializeListeners() override;
	
	cocos2d::Sprite* background;
	cocos2d::Sprite* banner;
	LocalizedSprite* title;
	ClickableTextNode* backButton;
	cocos2d::Sprite* darkFrame;

	std::vector<LexiconPage*> pages;
};
