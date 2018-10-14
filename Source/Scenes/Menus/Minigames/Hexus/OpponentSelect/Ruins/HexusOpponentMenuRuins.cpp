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

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentHorus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAnubisPup::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAphrodite::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLioness::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAres::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLionMan::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAthena::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTigress::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentHera::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTigerMan::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGeryon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMummyPriest::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAjax::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMummyWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGriffin::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMermaid::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZeus::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMedusa::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPoseidon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAnubisWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCleopatra::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOsiris::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuRuins::~HexusOpponentMenuRuins()
{
}
