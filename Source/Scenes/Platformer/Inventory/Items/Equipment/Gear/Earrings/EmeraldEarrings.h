#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class EmeraldEarrings : public Earring
{
public:
	static EmeraldEarrings* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	EmeraldEarrings();
	virtual ~EmeraldEarrings();

private:
	typedef Earring super;
};
