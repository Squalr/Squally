#include "HexusOpponentMenuRuins.h"

HexusOpponentMenuRuins * HexusOpponentMenuRuins::create()
{
	HexusOpponentMenuRuins* instance = new HexusOpponentMenuRuins();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuRuins::HexusOpponentMenuRuins() : HexusOpponentMenuBase(HexusChapterPreviewRuins::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuRuins::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsAnubisTiny::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsAnubisWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsAphrodite::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsAres::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsAthena::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsGriffin::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsHorus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsLioness::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsLionMan::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsTigress::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsTigerMan::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsManticore::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsMedusa::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsMedusaSmall::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsMermaid::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsMinotaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsMummyPharaoh::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsPoseidon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsSpartan::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsSwordswoman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsZeus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRuinsEgyptianGoddess::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuRuins::~HexusOpponentMenuRuins()
{
}
