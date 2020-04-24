#pragma once

#include "Engine/SmartNode.h"

class CardPreview;
class ConstantString;
class Equipable;
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
	enum EquipHintMode
	{
		None,
		Equip,
		Unequip,
	};
	
	static ItemPreview* create(bool showItemName = false, bool allowCardPreview = false);

	void toggleShowItemName(bool showItemName);
	void preview(EquipHintMode equipHintMode, Item* item);
	void clearPreview();
	CardPreview* getCardPreview();

protected:
	ItemPreview(bool showItemName, bool allowCardPreview);
	virtual ~ItemPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	void setGenericStatline(Equipable* equipable);
	void setWeaponStatline(Weapon* weapon);
	void setHexusInfo(HexusCard* hexusCard);
	
	LocalizedLabel* createStatline();
	void bindStatlineToIntRange(std::function<LocalizedString*()> prefixFunc, int min, int max);
	void bindStatlineToNonZeroInt(std::function<LocalizedString*()> prefixFunc, int value);
	void bindStatlineToNonZeroFloat(std::function<LocalizedString*()> prefixFunc, float value);

	cocos2d::Node* previewNode;
	CardPreview* cardPreview;
	std::vector<LocalizedLabel*> statlines;
	ConstantString* cardString;
	LocalizedLabel* cardLabel;
	LocalizedLabel* useHint;
	LocalizedLabel* equipHint;
	LocalizedLabel* unequipHint;
	LocalizedLabel* itemName;

	int nextStatline;
	bool allowCardPreview;

	static const int MaxStatlines;
};
