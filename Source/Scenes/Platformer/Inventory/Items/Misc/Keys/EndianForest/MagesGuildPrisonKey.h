#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MagesGuildPrisonKey : public Key
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
	typedef Key super;
};
