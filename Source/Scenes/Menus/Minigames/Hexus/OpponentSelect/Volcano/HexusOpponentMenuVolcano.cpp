#include "HexusOpponentMenuVolcano.h"

HexusOpponentMenuVolcano * HexusOpponentMenuVolcano::create()
{
	HexusOpponentMenuVolcano* instance = new HexusOpponentMenuVolcano();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuVolcano::HexusOpponentMenuVolcano() : HexusOpponentMenuBase(HexusChapterPreviewVolcano::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuVolcano::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAsh::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAsmodeus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBrine::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCeleste::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCindra::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonDragon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonGhost::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonGrunt::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonRogue::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonShaman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonSwordsman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentFireElemental::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentIgneus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLavaGolem::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLucifer::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMagnus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPan::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRagnis::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentScaldor::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZelina::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuVolcano::~HexusOpponentMenuVolcano()
{
}
