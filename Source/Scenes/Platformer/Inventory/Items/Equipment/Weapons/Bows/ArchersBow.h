#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Bows/Bow.h"

class ArchersBow : public Bow
{
public:
	static ArchersBow* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyArchersBow;

protected:
	ArchersBow();
	virtual ~ArchersBow();

private:
	typedef Bow super;
};
