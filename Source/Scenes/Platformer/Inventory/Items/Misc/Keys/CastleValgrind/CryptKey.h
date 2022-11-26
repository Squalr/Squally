
#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class CryptKey : public Key
{
public:
	static CryptKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	CryptKey();
	virtual ~CryptKey();

private:
	typedef Key super;
};
