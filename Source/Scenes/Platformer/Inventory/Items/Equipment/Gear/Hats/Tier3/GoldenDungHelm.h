#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class GoldenDungHelm : public Hat
{
public:
	static GoldenDungHelm* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKey;

protected:
	GoldenDungHelm();
	virtual ~GoldenDungHelm();

private:
	typedef Hat super;
};
