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
	bool tryOpen() override;
	void unlockAndGiveItems() override;

private:
	typedef GlassDisplayBase super;

	void onDialogueClose();
	bool inspectItem();

	std::string itemName;
	Item* item;
	std::string tutorialName;

	static const std::string PropertyItemName;
	static const std::string PropertyTutorial;
	static const std::string TutorialLightHint;
};
