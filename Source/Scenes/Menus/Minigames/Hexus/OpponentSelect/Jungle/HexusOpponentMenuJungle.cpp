#include "HexusOpponentMenuJungle.h"

HexusOpponentMenuJungle * HexusOpponentMenuJungle::create()
{
	HexusOpponentMenuJungle* instance = new HexusOpponentMenuJungle();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuJungle::HexusOpponentMenuJungle() : HexusOpponentMenuBase(HexusChapterPreviewJungle::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuJungle::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleBarbarian::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJunglePirate::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleDwarf::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleGeezer::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleFighter::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJunglePigDemon::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleHades::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleMinotaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleThor::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleViking::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleGoblinSwordsman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleGoblinWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleMantis::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleTikiGolem::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleRhinoman::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuJungle::~HexusOpponentMenuJungle()
{
}
