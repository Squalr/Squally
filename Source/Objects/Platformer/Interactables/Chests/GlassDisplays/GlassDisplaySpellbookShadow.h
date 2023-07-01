#pragma once

#include "Objects/Platformer/Interactables/Chests/GlassDisplays/GlassDisplayBase.h"

class MinMaxPool;
class Item;

class GlassDisplaySpellbookShadow : public GlassDisplayBase
{
public:
	static GlassDisplaySpellbookShadow* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	GlassDisplaySpellbookShadow(cocos2d::ValueMap& properties);
	virtual ~GlassDisplaySpellbookShadow();

	void onEnter() override;
	void initializeListeners() override;
	bool tryOpen() override;
	void unlockAndGiveItems() override;

private:
	typedef GlassDisplayBase super;
};
