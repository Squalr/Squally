#include "HexusOpponentMenuObelisk.h"

HexusOpponentMenuObelisk * HexusOpponentMenuObelisk::create()
{
	HexusOpponentMenuObelisk* instance = new HexusOpponentMenuObelisk();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuObelisk::HexusOpponentMenuObelisk() : HexusOpponentMenuBase(HexusChapterPreviewObelisk::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuObelisk::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuObelisk::~HexusOpponentMenuObelisk()
{
}
