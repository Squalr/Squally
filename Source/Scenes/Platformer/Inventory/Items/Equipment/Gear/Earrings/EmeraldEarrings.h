#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Earrings/Earring.h"

class EmeraldEarrings : public Earring
{
public:
	static EmeraldEarrings* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	EmeraldEarrings();
	virtual ~EmeraldEarrings();

private:
	typedef Earring super;
};
