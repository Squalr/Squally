#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Binary14 : public HexusCard
{
public:
	static Binary14* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBinary14;

protected:
	Binary14();
	~Binary14();

private:
	typedef HexusCard super;
};
