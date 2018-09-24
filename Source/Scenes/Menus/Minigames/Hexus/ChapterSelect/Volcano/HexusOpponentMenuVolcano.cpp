#include "HexusOpponentMenuVolcano.h"

HexusOpponentMenuVolcano * HexusOpponentMenuVolcano::create()
{
	HexusOpponentMenuVolcano* instance = new HexusOpponentMenuVolcano();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuVolcano::HexusOpponentMenuVolcano()
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

HexusOpponentMenuVolcano::~HexusOpponentMenuVolcano()
{
}
