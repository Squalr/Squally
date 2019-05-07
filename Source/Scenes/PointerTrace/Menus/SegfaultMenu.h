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

class SegfaultMenu : public SmartNode
{
public:
	static SegfaultMenu* create();

	void setRetryParams(std::string mapResource, std::function<void()> onLevelClearCallback);

private:
	typedef SmartNode super;
	SegfaultMenu();
	virtual ~SegfaultMenu() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* segfaultMenu;
	LocalizedLabel* titleLabel;
	ClickableTextNode* retryButton;
	ClickableTextNode* quitToTitleButton;
};
