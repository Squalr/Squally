#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MayanGemBlueItem : public Key
{
public:
	static MayanGemBlueItem* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	MayanGemBlueItem();
	virtual ~MayanGemBlueItem();

private:
	typedef Key super;
};
