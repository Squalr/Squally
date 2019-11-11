#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class EssenceOfFire : public Misc
{
public:
	static EssenceOfFire* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyEssenceOfFire;

protected:
	EssenceOfFire();
	~EssenceOfFire();

private:
	typedef Misc super;
};
