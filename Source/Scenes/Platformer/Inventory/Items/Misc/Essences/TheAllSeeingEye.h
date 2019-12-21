#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class TheAllSeeingEye : public Misc
{
public:
	static TheAllSeeingEye* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyTheAllSeeingEye;

protected:
	TheAllSeeingEye();
	~TheAllSeeingEye();

private:
	typedef Misc super;
};
