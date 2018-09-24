#include "HexusOpponentMenuCastle.h"

HexusOpponentMenuCastle * HexusOpponentMenuCastle::create()
{
	HexusOpponentMenuCastle* instance = new HexusOpponentMenuCastle();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuCastle::HexusOpponentMenuCastle()
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

HexusOpponentMenuCastle::~HexusOpponentMenuCastle()
{
}
