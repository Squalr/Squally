#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class Item;
class ItemPreview;

class ItemInfoMenu : public SmartNode
{
public:
	static ItemInfoMenu* create();

	void open(Item* item, std::function<void()> takeItemCallback = nullptr);
	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	ItemInfoMenu();
	virtual ~ItemInfoMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void close();

	cocos2d::LayerColor* backdrop;
	cocos2d::Sprite* itemWindow;
	LocalizedLabel* itemLabel;
	ItemPreview* itemPreview;
	ClickableTextNode* takeItemButton;
	ClickableTextNode* returnButton;
	ClickableNode* closeButton;

	std::function<void()> returnClickCallback;
};
