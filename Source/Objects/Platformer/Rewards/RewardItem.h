#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ItemPreview;
class Item;

class RewardItem : public GameObject
{
public:
	static RewardItem* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PropertyRewardPool;

protected:
	RewardItem(cocos2d::ValueMap& properties);
	virtual ~RewardItem();
	
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	void sellItem();
	void removeRewardItem();

	ItemPreview* itemPreview;
	Item* item;
	cocos2d::Node* itemNode;
	ClickableNode* itemClickHitbox;
	std::string poolName;
	
	bool available;
};
