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

	ScrollPane* contentScrollPane = nullptr;
	LocalizedLabel* developersTitle = nullptr;
	cocos2d::Sprite* zacSprite = nullptr;
	cocos2d::Sprite* mattSprite = nullptr;
	cocos2d::Sprite* nathanSprite = nullptr;
	ClickableTextNode* twitterButtonZac = nullptr;
	ClickableTextNode* twitterButtonMatt = nullptr;
	ClickableTextNode* twitterButtonNate = nullptr;
};
