#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class LocalizedString;

class CollectablesMenu : public SmartNode
{
public:
	static CollectablesMenu* create();

	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	CollectablesMenu();
	~CollectablesMenu();

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Node* buildMenuLabel(LocalizedString* text, cocos2d::Sprite* icon = nullptr);

	cocos2d::Sprite* collectablesWindow;
	LocalizedLabel* collectablesLabel;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;

	std::function<void()> returnClickCallback;
};
