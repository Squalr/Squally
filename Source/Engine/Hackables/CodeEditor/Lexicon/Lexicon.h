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

	void open();
	void close();
	void setCloseCallBack(std::function<void()> closeCallback);

private:
	typedef Hud super;
	Lexicon();
	~Lexicon();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	
	cocos2d::Sprite* background;
	cocos2d::Sprite* banner;
	LocalizedSprite* title;
	cocos2d::Sprite* lexiconBack;
	cocos2d::Sprite* lexiconFront;
	cocos2d::Node* leftPageNode;
	cocos2d::Node* rightPageNode;
	ClickableTextNode* backButton;
	cocos2d::Sprite* darkFrame;

	std::function<void()> closeCallback;
	std::vector<LexiconPage*> leftPages;
	std::vector<LexiconPage*> rightPages;
	std::vector<LexiconPage*> allPages;
};
