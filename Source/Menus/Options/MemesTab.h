#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class BetterScrollPane;

class MemesTab : public SmartNode
{
public:
	static MemesTab* create();

protected:
	MemesTab();
	~MemesTab();

private:
	typedef SmartNode super;

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	BetterScrollPane* contentScrollPane;
	LocalizedLabel* developersTitle;
	cocos2d::Sprite* zacSprite;
	cocos2d::Sprite* mattSprite;
	cocos2d::Sprite* nathanSprite;
};
