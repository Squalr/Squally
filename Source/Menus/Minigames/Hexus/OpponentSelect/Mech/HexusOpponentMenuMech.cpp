#include "HexusOpponentMenuMech.h"

HexusOpponentMenuMech * HexusOpponentMenuMech::create()
{
	HexusOpponentMenuMech* instance = new HexusOpponentMenuMech();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuMech::HexusOpponentMenuMech() : HexusOpponentMenuBase(HexusChapterPreviewMech::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuMech::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMara::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPiper::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMarcel::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentIllia::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLeon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentYsara::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAtreus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentExterminator::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRadon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRoboGolem::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentXenon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentQueenElise::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentEvilEye::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuMech::~HexusOpponentMenuMech()
{
}
