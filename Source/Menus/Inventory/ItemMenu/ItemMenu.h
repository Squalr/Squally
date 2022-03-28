#pragma once
#include <functional>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class Item;
class ItemEntry;
class ItemPreview;
class SmartClippingNode;

class ItemMenu : public SmartNode
{
public:
	static ItemMenu* create(LocalizedLabel* headerLabel = nullptr);

	void clearPreview();
	void clearVisibleItems();
	ItemPreview* getItemPreview();
	void setPreviewCallback(std::function<void(Item*)> previewCallback);
	ItemEntry* pushVisibleItem(Item* visibleItem, std::function<void()> onToggle);
	void setPreviewOffset(cocos2d::Vec2 previewOffset);
	void setTextOffset(cocos2d::Vec3 textOffset);
	void updateAndPositionItemText();
	void focus();
	void unfocus();
	bool hasFocus();

	static const cocos2d::Vec2 DefaultPreviewOffset;
	static const cocos2d::Vec3 DefaultTextOffset;

protected:
	ItemMenu(LocalizedLabel* headerLabel = nullptr);
	virtual ~ItemMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void scrollInventoryUp();
	void scrollInventoryDown();

	cocos2d::Vec2 previewOffset;
	cocos2d::Vec3 textOffset;

	LocalizedLabel* headerLabel = nullptr;
	ItemPreview* itemPreview = nullptr;
	cocos2d::Sprite* selectedInventoryRow = nullptr;
	cocos2d::Sprite* inventorySelectionArrow = nullptr;
	SmartClippingNode* itemListNode = nullptr;
	cocos2d::Node* itemListNodeContent = nullptr;

	std::function<void(Item*)> previewCallback = nullptr;
	std::map<Item*, ItemEntry*> itemEntryMapping;
	std::vector<ItemEntry*> visibleItems;
	int selectedItemIndex = 0;
	bool isFocused = false;

	static const float LabelSpacing;
	static const cocos2d::CSize LabelSize;
	static const cocos2d::CSize ClipSize;
	static const float ClipTopBuffer;
	static const float ClipRightBuffer;
};
