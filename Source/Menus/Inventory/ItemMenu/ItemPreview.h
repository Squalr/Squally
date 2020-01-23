#pragma once

#include "Engine/SmartNode.h"

class ConstantString;
class Hat;
class HexusCard;
class Item;
class Offhand;
class LocalizedLabel;
class LocalizedString;
class Weapon;

class ItemPreview : public SmartNode
{
public:
	static ItemPreview* create(bool allowEquipHint = true, bool showItemName = false);

	void preview(Item* item);
	void clearPreview();

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
	ItemPreview(bool allowEquipHint, bool showItemName);
	virtual ~ItemPreview();

	void setHatStatline(Hat* hat);
	void setOffhandStatline(Offhand* offhand);
	void setWeaponStatline(Weapon* weapon);
	void setHexusInfo(HexusCard* hexusCard);
	
	LocalizedLabel* createStatline();
	void bindStatlineToIntRange(std::function<LocalizedString*()> prefixFunc, int min, int max);
	void bindStatlineToNonZeroInt(std::function<LocalizedString*()> prefixFunc, int value);
	void bindStatlineToNonZeroFloat(std::function<LocalizedString*()> prefixFunc, float value);

	cocos2d::Node* previewNode;
	std::vector<LocalizedLabel*> statlines;
	ConstantString* cardString;
	LocalizedLabel* cardLabel;
	LocalizedLabel* equipHint;
	LocalizedLabel* itemName;

	int nextStatline;

	static const int MaxStatlines;
};
