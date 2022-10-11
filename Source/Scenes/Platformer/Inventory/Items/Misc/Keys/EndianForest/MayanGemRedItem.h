#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MayanGemRedItem : public Key
{
public:
	static MayanGemRedItem* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	MayanGemRedItem();
	virtual ~MayanGemRedItem();

private:
	typedef Key super;
};
