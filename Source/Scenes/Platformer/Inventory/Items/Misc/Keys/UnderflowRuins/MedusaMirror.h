#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class MedusaMirror : public Misc
{
public:
	static MedusaMirror* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MedusaMirror();
	virtual ~MedusaMirror();

private:
	typedef Misc super;
};
