#include "HexusOpponentMenuCastle.h"

HexusOpponentMenuCastle * HexusOpponentMenuCastle::create()
{
	HexusOpponentMenuCastle* instance = new HexusOpponentMenuCastle();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuCastle::HexusOpponentMenuCastle() : HexusOpponentMenuBase(HexusChapterPreviewCastle::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuCastle::onGameEndCallback, this);

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

HexusOpponentMenuCastle::~HexusOpponentMenuCastle()
{
}
