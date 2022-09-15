#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class LetterForThePrincess : public Key
{
public:
	static LetterForThePrincess* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	LetterForThePrincess();
	virtual ~LetterForThePrincess();

private:
	typedef Key super;
};
