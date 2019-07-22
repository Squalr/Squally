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

class MapMenu : public SmartNode
{
public:
	static MapMenu* create();

	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	MapMenu();
	~MapMenu();

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Node* buildMenuLabel(LocalizedString* text, cocos2d::Sprite* icon = nullptr);

	cocos2d::Sprite* mapWindow;
	LocalizedLabel* mapLabel;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;

	std::function<void()> returnClickCallback;
};
