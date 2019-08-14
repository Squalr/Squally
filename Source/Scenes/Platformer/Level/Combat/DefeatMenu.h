#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class PlatformerEntity;
class ScrollPane;

class DefeatMenu : public SmartNode
{
public:
	static DefeatMenu* create();
	
	void show();

private:
	typedef SmartNode super;
	DefeatMenu();
	~DefeatMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* defeatBanner;
	LocalizedLabel* defeatLabel;
	ClickableTextNode* returnButton;
};
