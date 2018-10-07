#include "HexusOpponentMenuForest.h"

HexusOpponentMenuForest * HexusOpponentMenuForest::create()
{
	HexusOpponentMenuForest* instance = new HexusOpponentMenuForest();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuForest::HexusOpponentMenuForest() : HexusOpponentMenuBase(HexusChapterPreviewForest::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuForest::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestAppolo::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestRogue::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestPrincess::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestArcher::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestAssassin::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestWerewolf::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestBandit::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestThief::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestHighwayman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestEnt::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestEntMage::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestGoblinGuard::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestGoblinWarriorPig::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestPolyphemus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestGoblinGruntBoar::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestGoblinShaman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestOrcGrunt::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestOrcWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestTroll::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestCyclops::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestDragonOrcKing::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuForest::~HexusOpponentMenuForest()
{
}
