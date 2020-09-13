#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MayanGemPurpleItem : public Key
{
public:
	static MayanGemPurpleItem* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MayanGemPurpleItem();
	virtual ~MayanGemPurpleItem();

private:
	typedef Key super;
};
