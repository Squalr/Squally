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

	void open(Item* item, std::function<void()> takeItemCallback = nullptr, std::function<void()> onExitSecondary = nullptr);
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

	cocos2d::LayerColor* backdrop = nullptr;
	cocos2d::Sprite* itemWindow = nullptr;
	LocalizedLabel* titleLabel = nullptr;
	ItemPreview* itemPreview = nullptr;
	ClickableTextNode* takeItemButton = nullptr;
	ClickableTextNode* returnButton = nullptr;
	ClickableNode* closeButton = nullptr;

	std::function<void()> returnClickCallback = nullptr;
	std::function<void()> onExitSecondary = nullptr;
};
