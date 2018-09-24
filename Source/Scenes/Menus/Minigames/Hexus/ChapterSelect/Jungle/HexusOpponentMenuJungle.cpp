#include "HexusOpponentMenuJungle.h"

HexusOpponentMenuJungle * HexusOpponentMenuJungle::create()
{
	HexusOpponentMenuJungle* instance = new HexusOpponentMenuJungle();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuJungle::HexusOpponentMenuJungle()
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuJungle::~HexusOpponentMenuJungle()
{
}
