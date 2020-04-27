#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class ScrollPane;

class MemesTab : public SmartNode
{
public:
	static MemesTab* create();

protected:
	MemesTab();
	virtual ~MemesTab();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	ScrollPane* contentScrollPane;
	LocalizedLabel* developersTitle;
	cocos2d::Sprite* zacSprite;
	cocos2d::Sprite* mattSprite;
	cocos2d::Sprite* nathanSprite;
	ClickableTextNode* twitterButtonZac;
	ClickableTextNode* twitterButtonMatt;
	ClickableTextNode* twitterButtonNate;
};
