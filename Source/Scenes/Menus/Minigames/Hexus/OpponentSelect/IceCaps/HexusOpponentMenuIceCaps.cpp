#include "HexusOpponentMenuIceCaps.h"

HexusOpponentMenuIceCaps * HexusOpponentMenuIceCaps::create()
{
	HexusOpponentMenuIceCaps* instance = new HexusOpponentMenuIceCaps();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuIceCaps::HexusOpponentMenuIceCaps() : HexusOpponentMenuBase(HexusChapterPreviewIceCaps::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuIceCaps::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentToySoldierGoblin::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentNessie::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentYeti::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAspen::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPenguinGrunt::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAster::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGoblinElf::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCookie::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPenguinWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentIrmik::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentYetiWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJingles::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentIceGolem::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJuniper::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentFrostFiend::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKringle::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentWaterElemental::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTinsel::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSnowFiend::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTheldar::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessPepper::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSanta::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCryogen::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuIceCaps::~HexusOpponentMenuIceCaps()
{
}
