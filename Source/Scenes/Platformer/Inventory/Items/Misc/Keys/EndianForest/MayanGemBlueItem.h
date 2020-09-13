#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MayanGemBlueItem : public Key
{
public:
	static MayanGemBlueItem* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MayanGemBlueItem();
	virtual ~MayanGemBlueItem();

private:
	typedef Key super;
};
