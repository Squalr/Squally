#include "HexusOpponentMenuMech.h"

HexusOpponentMenuMech * HexusOpponentMenuMech::create()
{
	HexusOpponentMenuMech* instance = new HexusOpponentMenuMech();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuMech::HexusOpponentMenuMech()
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

HexusOpponentMenuMech::~HexusOpponentMenuMech()
{
}
