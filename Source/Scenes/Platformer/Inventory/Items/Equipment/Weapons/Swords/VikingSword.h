#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class VikingSword : public Sword
{
public:
	static VikingSword* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyVikingSword;

protected:
	VikingSword();
	virtual ~VikingSword();

private:
	typedef Sword super;
};
