#pragma once

#include "Engine/Maps/GameObject.h"

class ClickableNode;
class ItemPreview;

class ShopItem : public GameObject
{
public:
	static ShopItem* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyShopItem;

protected:
	ShopItem(cocos2d::ValueMap& initProperties);
	~ShopItem();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	ItemPreview* itemPreview;
	ClickableNode* itemClickHitbox;
};
