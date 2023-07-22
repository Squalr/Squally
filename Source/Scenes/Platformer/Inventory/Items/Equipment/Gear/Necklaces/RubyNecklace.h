#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Necklaces/Necklace.h"

class RubyNecklace : public Necklace
{
public:
	static RubyNecklace* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	Recipe* getRecipe() override;

	static const std::string SaveKey;

protected:
	RubyNecklace();
	virtual ~RubyNecklace();

private:
	typedef Necklace super;
};
