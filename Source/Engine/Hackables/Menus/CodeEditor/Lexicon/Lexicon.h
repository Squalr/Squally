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

protected:
	Lexicon();
	virtual ~Lexicon();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Hud super;
	
	cocos2d::Sprite* background = nullptr;
	cocos2d::Sprite* banner = nullptr;
	LocalizedSprite* title = nullptr;
	cocos2d::Sprite* lexiconBack = nullptr;
	cocos2d::Sprite* lexiconFront = nullptr;
	cocos2d::Node* leftPageNode = nullptr;
	cocos2d::Node* rightPageNode = nullptr;
	ClickableTextNode* backButton = nullptr;
	cocos2d::Sprite* darkFrame = nullptr;

	std::function<void()> closeCallback = nullptr;
	std::vector<LexiconPage*> pages;
};
