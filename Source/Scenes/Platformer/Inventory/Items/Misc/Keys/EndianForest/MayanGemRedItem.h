#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MayanGemRedItem : public Key
{
public:
	static MayanGemRedItem* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MayanGemRedItem();
	virtual ~MayanGemRedItem();

private:
	typedef Key super;
};
