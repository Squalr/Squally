#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MedusaMirror : public Key
{
public:
	static MedusaMirror* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MedusaMirror();
	virtual ~MedusaMirror();

private:
	typedef Key super;
};
