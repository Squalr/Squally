#include "HexusOpponentMenuTraining.h"

HexusOpponentMenuTraining * HexusOpponentMenuTraining::create()
{
	HexusOpponentMenuTraining* instance = new HexusOpponentMenuTraining();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuTraining::HexusOpponentMenuTraining()
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuTraining::~HexusOpponentMenuTraining()
{
}
