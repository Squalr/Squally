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

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAppolo::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentChiron::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCooper::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCyclops::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDudly::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentEnt::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKingGrogg::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLycan::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOgre::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOrcBomber::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOrcGrunt::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOrcSwordsman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOrcWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPolyphemus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessMittens::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRobin::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRupert::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRusty::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentThug::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentToben::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTroll::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuForest::~HexusOpponentMenuForest()
{
}
