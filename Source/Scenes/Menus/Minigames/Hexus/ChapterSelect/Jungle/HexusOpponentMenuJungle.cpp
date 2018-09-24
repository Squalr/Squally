#include "HexusOpponentMenuJungle.h"

HexusOpponentMenuJungle * HexusOpponentMenuJungle::create()
{
	HexusOpponentMenuJungle* instance = new HexusOpponentMenuJungle();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuJungle::HexusOpponentMenuJungle()
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleBarbarian::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleDwarf::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleFighter::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleGeezer::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleHades::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJunglePeasant::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJunglePirate::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJunglePrincess::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleThor::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleViking::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuJungle::~HexusOpponentMenuJungle()
{
}
