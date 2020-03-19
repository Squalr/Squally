#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class MagesGuildPrisonKey : public Misc
{
public:
	static MagesGuildPrisonKey* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MagesGuildPrisonKey();
	virtual ~MagesGuildPrisonKey();

private:
	typedef Misc super;
};
