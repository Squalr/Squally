#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MayanGemPurpleItem : public Key
{
public:
	static MayanGemPurpleItem* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	MayanGemPurpleItem();
	virtual ~MayanGemPurpleItem();

private:
	typedef Key super;
};
