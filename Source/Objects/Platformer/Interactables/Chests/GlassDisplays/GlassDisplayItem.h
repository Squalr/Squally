#pragma once

#include "Objects/Platformer/Interactables/Chests/GlassDisplays/GlassDisplayBase.h"

class MinMaxPool;
class Item;

class GlassDisplayItem : public GlassDisplayBase
{
public:
	static GlassDisplayItem* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	GlassDisplayItem(cocos2d::ValueMap& properties);
	virtual ~GlassDisplayItem();

	void onEnter() override;
	void initializeListeners() override;
	bool tryOpen() override;
	void unlockAndGiveItems() override;

private:
	typedef GlassDisplayBase super;

	void tryRunTutorials();
	bool inspectItem();
	void takeGroupedItem();
	bool canTakeGroupedItem();

	std::string itemName;
	Item* item;
	std::string tutorialName;
	std::string displayGroup;

	static const std::string PropertyItemName;
	static const std::string PropertyTutorial;
	static const std::string PropertyDisplayGroup;
	static const std::string MapEventDisableDisplayGroup;
	static const std::string SaveKeyIsDisabled;
	static const std::string TutorialLightHint;
};
