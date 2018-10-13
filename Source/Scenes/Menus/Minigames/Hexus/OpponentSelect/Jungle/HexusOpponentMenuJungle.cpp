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

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBarbarian::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBlackbeard::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBodom::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDrak::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentElriel::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGoblinGruntBoar::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGoblinShaman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGoblinWarriorPig::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGorilla::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGramps::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentHades::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMinos::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMinotaur::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessMatu::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRaka::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentReanimatedPig::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRhinoman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalPirate::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentThor::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTikiGolem::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentViking::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuJungle::~HexusOpponentMenuJungle()
{
}
