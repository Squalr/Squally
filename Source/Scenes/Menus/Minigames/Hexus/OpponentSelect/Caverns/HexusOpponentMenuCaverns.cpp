#include "HexusOpponentMenuCaverns.h"

HexusOpponentMenuCaverns * HexusOpponentMenuCaverns::create()
{
	HexusOpponentMenuCaverns* instance = new HexusOpponentMenuCaverns();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuCaverns::HexusOpponentMenuCaverns() : HexusOpponentMenuBase(HexusChapterPreviewCaverns::stringKeyChapterName)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuCaverns::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBrock::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentShaman::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCypress::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentForestGolem::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentFinch::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentEarthGolem::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAlder::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentEarthElemental::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentFraya::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalArcher::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentOlive::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalWarrior::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJasper::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSkeletalNecromancer::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMildred::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGenie::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessDawn::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentShen::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLightningGolem::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSarude::getInstance(), callback));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKrampus::getInstance(), callback));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuCaverns::~HexusOpponentMenuCaverns()
{
}
