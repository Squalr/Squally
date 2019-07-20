#pragma once

#include "Engine/SmartNode.h"

class Item;
class LocalizedLabel;

class ItemPreview : public SmartNode
{
public:
	static ItemPreview* create(bool allowEquipHint = true);

	void preview(Item* item);
	void clearPreview();

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
	ItemPreview(bool allowEquipHint);
	~ItemPreview();

	cocos2d::Node* previewNode;
	LocalizedLabel* equipHint;

	bool allowEquipHint;
};
