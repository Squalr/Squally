#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class EmeraldPendant : public Necklace
{
public:
	static EmeraldPendant* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	EmeraldPendant();
	virtual ~EmeraldPendant();

private:
	typedef Necklace super;
};
