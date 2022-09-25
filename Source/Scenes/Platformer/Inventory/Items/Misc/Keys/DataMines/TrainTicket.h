#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class TrainTicket : public Key
{
public:
	static TrainTicket* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	TrainTicket();
	virtual ~TrainTicket();

private:
	typedef Key super;
};
