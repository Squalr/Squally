#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class EmeraldPendant : public Necklace
{
public:
	static EmeraldPendant* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	EmeraldPendant();
	virtual ~EmeraldPendant();

private:
	typedef Necklace super;
};
