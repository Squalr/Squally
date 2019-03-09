#pragma once

#include "Engine/Inventory/Currency.h"

class Doubloons : public Currency
{
public:
	static Doubloons* create();

	Item* clone() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDoubloons;

protected:
	Doubloons();
	virtual ~Doubloons();

private:
	typedef Currency super;
};
