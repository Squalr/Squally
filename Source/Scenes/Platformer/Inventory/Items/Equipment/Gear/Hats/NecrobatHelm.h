#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class NecrobatHelm : public Hat
{
public:
	static NecrobatHelm* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyNecrobatHelm;

protected:
	NecrobatHelm();
	virtual ~NecrobatHelm();

private:
	typedef Hat super;
};
