#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class MayanGemBlueItem : public Misc
{
public:
	static MayanGemBlueItem* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyMayanGemBlueItem;

protected:
	MayanGemBlueItem();
	virtual ~MayanGemBlueItem();

private:
	typedef Misc super;
};
